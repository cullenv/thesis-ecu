#ifndef APP_DIAGNOSTICS_H
#define APP_DIAGNOSTICS_H

#include "fault_manager.h"

typedef enum {
    DTC_ENCODER_LOSS = 0,
    DTC_OVER_CURRENT = 1,
    DTC_CAN_TIMEOUT = 2,
    MAX_DIAGNOSTICS
} DiagnosticID_t;

void Diagnostics_Init(void);

FaultStatus_t Diagnostics_GetStatus(DiagnosticID_t id);

#endif // APP_DIAGNOSTICS_H