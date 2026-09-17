#include "CppUTest/TestHarness.h"

extern "C" {
    #include "fault_manager.h"
}

TEST_GROUP(Fault_Manager) {
    void setup() {}
    void teardown() {}
};

TEST(Fault_Manager, Initialization_StoresDTC_And_ClearsStatus) {
    FaultMonitor_t my_fault;
    my_fault.status = FAULT_ACTIVE; // Garbage data

    // Initialize with a fake DTC: 0x9101 (Encoder Loss)
    Fault_Init(&my_fault, 0x9101);

    LONGS_EQUAL(0x9101, my_fault.dtc);
    LONGS_EQUAL(FAULT_CLEAR, my_fault.status);
}

TEST(Fault_Manager, SetStatus_UpdatesFaultState) {
    FaultMonitor_t my_fault;
    Fault_Init(&my_fault, 0x9101);

    // Trip the fault!
    Fault_SetStatus(&my_fault, FAULT_ACTIVE);
    LONGS_EQUAL(FAULT_ACTIVE, my_fault.status);
}