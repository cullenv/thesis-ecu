#include "com_manager.h"
#include <stdint.h>

extern void HAL_CAN_Transmit(CAN_Frame_t *frame);

void COM_SendMotorSpeed(float speed_rpm){

    typedef union { //serilaztion which you learnerd about in your MCU class
    float f_val;
    uint8_t bytes[4];
} FloatConverter_t;

    FloatConverter_t converter;

    converter.f_val = speed_rpm;

    CAN_Frame_t CAN;
    CAN.id = 0x105;
    CAN.dlc = 4;

    CAN.data[0] = converter.bytes[3]; // realized that CAN is big Endian so swap them to big endian
    CAN.data[1] = converter.bytes[2]; 
    CAN.data[2] = converter.bytes[1]; 
    CAN.data[3] = converter.bytes[0];

    HAL_CAN_Transmit(&CAN);
}

