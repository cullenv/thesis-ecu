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
    uint16_t error_counter;
    uint16_t debounce_threshold;
} FaultMonitor_t;

void Fault_Init(FaultMonitor_t *monitor, uint32_t dtc, uint16_t debounce_threshold);

void Fault_SetStatus(FaultMonitor_t *monitor, FaultStatus_t new_status);

void Fault_Update(FaultMonitor_t *monitor, bool is_error_present);

#endif // APP_FAULT_MANAGER_H