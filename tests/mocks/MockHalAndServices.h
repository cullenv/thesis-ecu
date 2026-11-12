#ifndef MOCK_HAL_AND_SERVICES_H
#define MOCK_HAL_AND_SERVICES_H

#include <stdint.h>

extern "C" {
#include "can.h"
#include "diagnostics.h"
}

// PWM Mock Controls
void MockPWM_Init(void);
float MockPWM_GetLastDutyCycle(void);

// Encoder Mock Controls
void MockEncoder_Init(void);
void MockEncoder_SetSpeedRPM(int16_t speed);

// Diagnostics Mock Controls
void MockDiag_Init(void);
void MockDiag_SetFaultStatus(DiagnosticID_t dtc, FaultStatus_t status);

// CAN Mock Controls
void MockCAN_Init(void);
CAN_Message_t MockCAN_GetLastTxFrame(void);
uint32_t MockCAN_GetTxCount(void);

#endif // MOCK_HAL_AND_SERVICES_H