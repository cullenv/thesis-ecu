#include "pid.h"

void PID_Init(PI_Controller_t *pid, float kp, float ki, float max_integral) {
    pid->kp = kp;
    pid->ki = ki;
    pid->max_integral = max_integral;
    pid->integral_sum = 0.0f;
}

float PID_Update(PI_Controller_t *pid, float setpoint, float measured, float dt){
    float error = setpoint - measured;
    float prop = error * pid->kp;
    pid->integral_sum = pid->integral_sum + (pid->ki * error);

    if(pid->integral_sum >= pid->max_integral) {
        pid->integral_sum = pid->max_integral;
    } else if (pid->integral_sum < -pid->max_integral){

        pid->integral_sum = -pid->max_integral;

    }
    return pid->integral_sum + prop;
}