#ifndef APP_FAULT_MANAGER_H
#define APP_FAULT_MANAGER_H
#include <stdint.h>

typedef enum {
    FAULT_CLEAR = 0,
    FAULT_ACTIVE = 1
} FaultStatus_t;

typedef struct {
    uint32_t dtc;
    FaultStatus_t status;
} FaultMonitor_t;

void Fault_Init(FaultMonitor_t *monitor, uint32_t dtc);

void Fault_SetStatus(FaultMonitor_t *monitor, FaultStatus_t new_status);

#endif // APP_FAULT_MANAGER_H