#include "MockHalAndServices.h"
#include <string.h>

extern "C" {
#include "stm32g4xx.h"
#include "can.h"
#include "diagnostics.h"
}

// Allocate memory mock hardware 
RCC_TypeDef MockRCC;
TIM_TypeDef MockTIM1;

static int16_t mock_encoder_rpm = 0.0f;
static FaultStatus_t active_encoder_fault = STATUS_INACTIVE;
static CAN_Message_t last_can_frame;
static uint32_t can_tx_count = 0;


void MockEncoder_Init(void) {
    mock_encoder_rpm = 0.0f;
}

void MockEncoder_SetSpeedRPM(int16_t speed) {
    mock_encoder_rpm = speed;
}

void MockDiag_Init(void) {
    active_encoder_fault = STATUS_INACTIVE;
}

void MockDiag_SetFaultStatus(DiagnosticID_t dtc, FaultStatus_t status) {
    if (dtc == DTC_ENCODER_LOSS) {
        active_encoder_fault = status;
    }
}

void MockCAN_Init(void) {
    memset(&last_can_frame, 0, sizeof(CAN_Message_t));
    can_tx_count = 0;
}

CAN_Message_t MockCAN_GetLastTxFrame(void) {
    return last_can_frame;
}

uint32_t MockCAN_GetTxCount(void) {
    return can_tx_count;
}

// C-linkage implementations called by application code
extern "C" {

int16_t Encoder_GetSpeed(void) {
    return mock_encoder_rpm;
}

FaultStatus_t Diagnostics_GetStatus(DiagnosticID_t dtc) {
    if (dtc == DTC_ENCODER_LOSS) {
        return active_encoder_fault;
    }
    return STATUS_INACTIVE;
}

void CAN_Transmit(CAN_Message_t *frame) {
    if (frame != nullptr) {
        last_can_frame = *frame;
        can_tx_count++;
    }
}

} // extern "C"