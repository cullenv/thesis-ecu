#include "CppUTest/TestHarness.h"

extern "C" {
    #include "ramp.h"
}

TEST_GROUP(Ramp_Generator) {
    void setup() {}
    void teardown() {}
};

TEST(Ramp_Generator, Initialization_SetsStateToZero) {
    // 1. ARRANGE
    Ramp_t my_ramp;
    my_ramp.current_output = 999.0f; // Garbage data

    // 2. ACT
    Ramp_Init(&my_ramp, 10.0f, 20.0f);

    // 3. ASSERT
    DOUBLES_EQUAL(0.0f, my_ramp.current_output, 0.001f);
    DOUBLES_EQUAL(10.0f, my_ramp.max_step_up, 0.001f);
    DOUBLES_EQUAL(20.0f, my_ramp.max_step_down, 0.001f);
}

TEST(Ramp_Generator, Update_PreventsOvershoot) {
    Ramp_t my_ramp;
    Ramp_Init(&my_ramp, 10.0f, 20.0f);
    my_ramp.current_output = 95.0f; // Force state to 95

    // Target is 100. A full step (+10) would overshoot to 105.
    // It should clamp exactly to 100.
    float result = Ramp_Update(&my_ramp, 100.0f);
    DOUBLES_EQUAL(100.0f, result, 0.001f);
}