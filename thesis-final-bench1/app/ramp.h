#ifndef APP_RAMP_H
#define APP_RAMP_H

typedef struct {

    float current_output;
    float max_step_up;
    float max_step_down;
} Ramp_t;

void Ramp_Init(Ramp_t *ramp, float max_step_up, float max_step_down);

float Ramp_Update(Ramp_t *ramp, float target);

#endif