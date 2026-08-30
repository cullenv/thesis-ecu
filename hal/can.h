#ifndef HAL_CAN_H
#define HAL_CAN_H

#include <stdint.h>
#include <stdbool.h>

// A generic CAN message structure that I found online.
typedef struct {
    uint32_t id;        // The CAN ID (e.g., 0x100)
    uint8_t dlc;        // Data Length Code (how many bytes: 1-8)
    uint8_t data[8];    // The actual payload bytes
} CAN_Message_t;

void CAN_Init(void);
void CAN_Transmit(CAN_Message_t *msg);
bool CAN_Receive(CAN_Message_t *msg); // Returns true if a new message was received

#endif // HAL_CAN_H