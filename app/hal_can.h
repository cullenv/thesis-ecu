#ifndef HAL_CAN_H
#define HAL_CAN_H

typedef struct {

    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];

} CAN_Frame_t;

#endif