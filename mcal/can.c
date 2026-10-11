/*
 * can.c
 *
 *  Created on: Oct 10, 2026
 *      Author: culle
 */

#include "can.h"
#include "main.h"
#include <string.h>

extern FDCAN_HandleTypeDef hfdcan1;

// Private ISR-to-Application RX buffer
static volatile bool rx_msg_pending = false;
static CAN_Message_t latest_rx_msg = {0};

// Lookup table to safely map integer DLC (0-8) to STM32G4 FDCAN macros
static const uint32_t dlc_to_fdcan[9] = {
    FDCAN_DLC_BYTES_0, FDCAN_DLC_BYTES_1, FDCAN_DLC_BYTES_2,
    FDCAN_DLC_BYTES_3, FDCAN_DLC_BYTES_4, FDCAN_DLC_BYTES_5,
    FDCAN_DLC_BYTES_6, FDCAN_DLC_BYTES_7, FDCAN_DLC_BYTES_8
};

void CAN_Init(void)
{
    // 1. Accept all incoming standard/extended frames into RX FIFO 0
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

    // 2. Start the FDCAN module
    HAL_FDCAN_Start(&hfdcan1);

    // 3. Route RX FIFO 0 interrupt to Line 0 and activate notification
    HAL_FDCAN_ConfigInterruptLines(&hfdcan1, FDCAN_IT_GROUP_RX_FIFO0, FDCAN_INTERRUPT_LINE0);
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

    // 4. Unmask FDCAN1_IT0 in the ARM Cortex-M4 NVIC
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
}

void CAN_Transmit(CAN_Message_t *msg)
{
    if (msg == NULL) {
        return;
    }

    uint8_t safe_dlc = (msg->dlc > 8U) ? 8U : msg->dlc;

    FDCAN_TxHeaderTypeDef TxHeader = {0};
    TxHeader.Identifier = msg->id;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.DataLength = dlc_to_fdcan[safe_dlc];
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, msg->data);
}

bool CAN_Receive(CAN_Message_t *msg)
{
    if ((msg == NULL) || (!rx_msg_pending)) {
        return false;
    }

    // Critical section: briefly disable IRQ while copying out the buffered frame
    __disable_irq();
    *msg = latest_rx_msg;
    rx_msg_pending = false;
    __enable_irq();

    return true;
}

// ----------------------------------------------------------------------------
// Hardware Interrupt Vector & HAL Callback
// ----------------------------------------------------------------------------

void FDCAN1_IT0_IRQHandler(void)
{
    HAL_FDCAN_IRQHandler(&hfdcan1);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
    {
        FDCAN_RxHeaderTypeDef RxHeader = {0};
        uint8_t RxData[8] = {0};

        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            latest_rx_msg.id = RxHeader.Identifier;

            // Map FDCAN DataLength back to 0..8 byte count
            uint8_t len = 8U;
            for (uint8_t i = 0U; i <= 8U; i++) {
                if (RxHeader.DataLength == dlc_to_fdcan[i]) {
                    len = i;
                    break;
                }
            }
            latest_rx_msg.dlc = len;
            memcpy(latest_rx_msg.data, RxData, 8U);
            rx_msg_pending = true;
        }
    }
}
