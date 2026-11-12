#include "com_manager.h"
#include <stdint.h>

void COM_Init(void) {
    // com layer
}

void COM_SendMotorSpeed(float speed_rpm) {
    typedef union {
        float f_val;
        uint8_t bytes[4];
    } FloatConverter_t;

    FloatConverter_t converter;
    converter.f_val = speed_rpm;

    CAN_Message_t frame;
    frame.id = 0x101; // REQ-011: CAN ID 0x101 for motor speed & fault status
    frame.dlc = 4;

    // 4 32-bit float to Big-Endian byte order
    frame.data[0] = converter.bytes[3];
    frame.data[1] = converter.bytes[2];
    frame.data[2] = converter.bytes[1];
    frame.data[3] = converter.bytes[0];

    CAN_Transmit(&frame);
}