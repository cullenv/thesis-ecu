#include "fault_manager.h"

void Fault_Init(FaultMonitor_t *monitor, uint32_t dtc){
    monitor->dtc = dtc;            //store the fault code
    monitor->status = FAULT_CLEAR; // clean slate
}

void Fault_SetStatus(FaultMonitor_t *monitor, FaultStatus_t new_status){
    monitor->status = new_status;  //update struct with new state
}