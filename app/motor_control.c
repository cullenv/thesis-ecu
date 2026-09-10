#include "motor_control.h"
#include "pid.h"
#include "ramp.h"
#include "hal_pwm.h"

static PI_Controller_t motor_pid;
static Ramp_t motor_ramp;
static float driver_target_speed = 0.0f;

void App_MotorControl_Init(void){
    PID_Init(&motor_pid, 2.0f, 0.5f, 100.0f);
    Ramp_Init(&motor_ramp, 5.0f, 10.0f);
}

void App_MotorControl_SetTargetSpeed(float speed_rpm){
    driver_target_speed = speed_rpm;
}

void App_MotorControl_Task(void) {
    // 1. Rate Limit: Pass in driver request, catch the safe step
    float safe_target = Ramp_Update(&motor_ramp, driver_target_speed);

    // 2. Measure: Hardcoded for now
    float measured_speed = 0.0f;

    // 3. Control: Pass in the safe target, catch the control effort
    float control_effort = PID_Update(&motor_pid, safe_target, measured_speed, 0.010f);

    // 4. Saturation Clamp: Protect the hardware from timer wrap-around
    if (control_effort > 100.0f) {
        control_effort = 100.0f;
    } else if (control_effort < -100.0f) {
        control_effort = -100.0f;
    }
    
    // 5. Send to hardware... (We will do this next!)
    PWM_SetDutyCycle(control_effort);    
}