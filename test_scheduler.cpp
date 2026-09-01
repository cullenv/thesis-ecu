#include "CppUTest/TestHarness.h"

extern "C" {
    #include "app/scheduler.h"
}

TEST_GROUP(Scheduler) {
    void setup() {
        Scheduler_Init(); // Reset counters before every test
    }
    void teardown() {}
};

TEST(Scheduler, TenMillisecondTaskFiresCorrectly) {
    // Simulate 9 milliseconds passing
    for (int i = 0; i < 9; i++) {
        Scheduler_UpdateTick();
    }
    
    // At 9ms, the flag should STILL be false
    CHECK_FALSE(Scheduler_Is10msTaskDue());

    // Tick the 10th millisecond
    Scheduler_UpdateTick();

    // Now the flag MUST be true
    CHECK_TRUE(Scheduler_Is10msTaskDue());

    // Because of Clear-on-Read, if we ask immediately again, it MUST be false
    CHECK_FALSE(Scheduler_Is10msTaskDue());
}