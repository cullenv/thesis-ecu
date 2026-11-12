#include "motor_control.h"
#include "pid.h"
#include "ramp.h"
#include "hal_pwm.h"
#include "hal_encoder.h"
#include "diagnostics.h"

#define MOTOR_PWM_MAX_DUTY   (95.0f)   // REQ-005: Limit duty cycle to protect bootstrap circuit 
#define MOTOR_PWM_MIN_DUTY  (-95.0f)   // REQ-005: Bidirectional saturation limit 
#define MOTOR_CONTROL_DT_S   (0.001f)  // REQ-001: 1 ms periodic execution rate 

static PI_Controller_t motor_pid;
static Ramp_t motor_ramp;
static float driver_target_speed = 0.0f;

void App_MotorControl_Init(void) {
    // REQ-009: Integral 95% max duty 
    PID_Init(&motor_pid, 2.0f, 0.5f, MOTOR_PWM_MAX_DUTY);

    // REQ-008: Rate limiter configured for 1000 RPM max change 
    Ramp_Init(&motor_ramp, 1.0f, 1.0f);
    driver_target_speed = 0.0f;
}

void App_MotorControl_SetTargetSpeed(float speed_rpm) {
    // REQ-015: Ignore CAN target speed commands if fault is active
    if (Diagnostics_GetStatus(DTC_ENCODER_LOSS) == STATUS_ACTIVE) {
        driver_target_speed = 0.0f;
        return;
    }
    driver_target_speed = speed_rpm;
}

void App_MotorControl_Task(void) {
    // REQ-015: Force safe shutdown and zero command if encoder loss fault is active
    if (Diagnostics_GetStatus(DTC_ENCODER_LOSS) == STATUS_ACTIVE) {
        driver_target_speed = 0.0f;
        PWM_SetDutyCycle(0.0f);
        return;
    }

    // Rate Limiting: REQ-008 
    float safe_target = Ramp_Update(&motor_ramp, driver_target_speed);

    // Feedback Acquisition: REQ-006 
    float measured_speed = Encoder_GetSpeed();

    // Control Computation: REQ-001 & REQ-007
    float control_effort = PID_Update(&motor_pid, safe_target, measured_speed, MOTOR_CONTROL_DT_S);

    // Saturation Clamping: REQ-005 
    if (control_effort > MOTOR_PWM_MAX_DUTY) {
        control_effort = MOTOR_PWM_MAX_DUTY;
    } else if (control_effort < MOTOR_PWM_MIN_DUTY) {
        control_effort = MOTOR_PWM_MIN_DUTY;
    }
    PWM_SetDutyCycle(control_effort);
}