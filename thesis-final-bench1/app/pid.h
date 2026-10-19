#ifndef PID_H
#define PID_H

typedef struct {
    float kp;
    float ki;
    float integral_sum;
    float max_integral;
} PI_Controller_t;

void PID_Init(PI_Controller_t *pid, float kp, float ki, float max_integral);

float PID_Update(PI_Controller_t *pid, float setpoint, float measured, float dt);

#endif