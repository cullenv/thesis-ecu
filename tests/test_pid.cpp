#include "CppUTest/TestHarness.h"

extern "C" {
    #include "pid.h"
}

TEST_GROUP(PI_Controller) {
    void setup() {}
    void teardown() {}
};

TEST(PI_Controller, Initialization_SetsStateToZero) {
    // 1. ARRANGE: Create the struct and fill it with garbage data 
    // to prove our init function actually clears it.
    PI_Controller_t my_pid;
    my_pid.integral_sum = 999.9f;

    // 2. ACT: Call your production function
    PID_Init(&my_pid, 2.0f, 0.5f);

    // 3. ASSERT: Did the function do what we expect?
    // DOUBLES_EQUAL takes (expected, actual, tolerance)
    DOUBLES_EQUAL(0.0f, my_pid.integral_sum, 0.001f);
}
    
TEST(PI_Controller, Update_CalculatesProportionalResponse) {
    // 1. ARRANGE
    PI_Controller_t my_pid;
    PID_Init(&my_pid, 2.0f, 0.0f); // Kp = 2.0, Ki = 0.0

    // 2. ACT
    // If setpoint is 10 and measured is 0, error is 10.
    // P-term = Kp * error = 2.0 * 10 = 20.0
    float control_effort = PID_Update(&my_pid, 10.0f, 0.0f);

    // 3. ASSERT
    DOUBLES_EQUAL(20.0f, control_effort, 0.001f);
}

TEST(PI_Controller, Update_CalculatesIntegralResponse) {
    PI_Controller_t my_pid;
    PID_Init(&my_pid, 0.0f, 0.5f, 100.0f); // Kp = 0.0, Ki = 0.5, Max_I = 100.0

    // Cycle 1: Error is 10. Integral adds (10 * 0.5) = 5.0
    PID_Update(&my_pid, 10.0f, 0.0f);
    DOUBLES_EQUAL(5.0f, my_pid.integral_sum, 0.001f);

    // Cycle 2: Error is 10. Integral adds another 5.0. Total = 10.0
    float effort = PID_Update(&my_pid, 10.0f, 0.0f);
    DOUBLES_EQUAL(10.0f, my_pid.integral_sum, 0.001f);
    DOUBLES_EQUAL(10.0f, effort, 0.001f); // Output should equal the integral sum
}

TEST(PI_Controller, Update_ClampsIntegralWindup) {
    PI_Controller_t my_pid;
    // Set a strict limit: Integral cannot exceed 25.0
    PID_Init(&my_pid, 0.0f, 1.0f, 25.0f); 

    // Massive error of 1000! Integral wants to jump to 1000.
    PID_Update(&my_pid, 1000.0f, 0.0f);

    // Assert that the Anti-Windup clamped it to 25.0
    DOUBLES_EQUAL(25.0f, my_pid.integral_sum, 0.001f);
}

TEST(PI_Controller, Update_ScalesIntegralWithTime) {
    PI_Controller_t my_pid;
    PID_Init(&my_pid, 0.0f, 10.0f, 100.0f); // Ki = 10.0

    // 10.0 error * 10.0 Ki * 0.001 dt = 0.1
    PID_Update(&my_pid, 10.0f, 0.0f, 0.001f);
    DOUBLES_EQUAL(0.1f, my_pid.integral_sum, 0.001f);

    // 10.0 error * 10.0 Ki * 0.010 dt = 1.0 (larger dt = larger step)
    PID_Update(&my_pid, 10.0f, 0.0f, 0.010f);
    
    // Total should be previous 0.1 + new 1.0 = 1.1
    DOUBLES_EQUAL(1.1f, my_pid.integral_sum, 0.001f);
}