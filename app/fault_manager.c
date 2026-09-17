#include "fault_manager.h"

void Fault_Init(FaultMonitor_t *monitor, uint32_t dtc){
    monitor->dtc = dtc;            //store the fault code
    monitor->status = FAULT_CLEAR; // clean slate
    montior->error_counter = 0;   // reset error counter
}

void Fault_SetStatus(FaultMonitor_t *monitor, FaultStatus_t new_status){
    monitor->status = new_status;  //update struct with new state
}

void Fault_Update(FaultMonitor_t *monitor, bool is_error_present){
    if(is_error_present){
        monitor->error_counter++; //increment error counter
        if(monitor->error_counter >= monitor->debounce_threshold){
            Fault_SetStatus(monitor, FAULT_ACTIVE); //set fault active
        }
    } else {
        monitor->error_counter = 0; //reset error counter
        Fault_SetStatus(monitor, FAULT_CLEAR); //clear fault
    }
}