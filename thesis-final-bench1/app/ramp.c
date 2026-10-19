#include "ramp.h"

void Ramp_Init(Ramp_t *Ramp, float max_step_up, float max_step_down){

    Ramp->max_step_up = max_step_up;
    Ramp->max_step_down = max_step_down;
    Ramp->current_output = 0.0f;

}

float Ramp_Update(Ramp_t *ramp, float target){
    if(ramp->current_output < target){
        ramp->current_output += ramp->max_step_up;

        if(ramp->current_output > target){
            ramp->current_output = target;
        }
    }

    else if(ramp->current_output > target){
        ramp->current_output -= ramp->max_step_down;

        if(ramp->current_output < target){
            ramp->current_output = target;
        }
    }

    return ramp->current_output;
}