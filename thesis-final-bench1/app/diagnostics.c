#include "diagnostics.h"
#include "fault_manager.h" 

static FaultMonitor_t fault_table[MAX_DIAGNOSTICS];

void Diagnostics_Init(void) {
    Fault_Init(&fault_table[DTC_ENCODER_LOSS], 0x9001, 10);
    Fault_Init(&fault_table[DTC_OVER_CURRENT], 0x9002, 10);
    Fault_Init(&fault_table[DTC_CAN_TIMEOUT], 0x9003, 10);
}

FaultStatus_t Diagnostics_GetStatus(DiagnosticID_t id) {
    // ASIL-D using the bounds trick i learned and ensure its within our fault table
    if (id >= MAX_DIAGNOSTICS) {
        return FAULT_CLEAR; 
    }
    
    
    return fault_table[id].status;
}