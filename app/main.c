#include "motor_control.h"
#include "com_manager.h"

/* 
 * Minimal host-build bootstrap. 
 * Hardware-specific STM32 clock/GPIO initializations will be 
 * ported here from the bare-metal-baseline branch in Weeks 6-8.
 */
int main(void) {
    /* 1. Initialize Communications */
    COM_Init();

    /* 2. Initialize Motor Control (PID, Ramp) */
    App_MotorControl_Init();

    /* 3. Start System Scheduler (1ms tick) */
    // Scheduler_Init();
    // Scheduler_Run();

    /* 4. Safe Hang Fallback (REQ-030) */
    while(1) {
        // ECU should never reach here unless the scheduler fails
    }

    return 0;
}