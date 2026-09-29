#include "hal_can.h"
#include <stdint.h>
#include <stdbool.h>

extern bool MCAL_CAN_IsMailboxEmpty(uint8_t mailbox_num);
extern void MCAL_CAN_LoadMailbox(uint8_t mailbox_num, CAN_Frame_t *frame);

void HAL_CAN_Transmit(CAN_Frame_t *frame){

    if (MCAL_CAN_IsMailboxEmpty(0)) {
       
        MCAL_CAN_LoadMailbox(0, frame); // frame is okey to load
    }
}
