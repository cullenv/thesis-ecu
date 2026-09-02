#include "app/scheduler.h"

static uint8_t counter_10ms = 0;
static uint8_t counter_100ms = 0;

static bool flag_10ms = false;
static bool flag_100ms = false;

void Scheduler_Init(void) {
    counter_10ms = 0;
    counter_100ms = 0;
    flag_10ms = false;
    flag_100ms = false;
}

void Scheduler_UpdateTick(void) {
    counter_10ms++;
    counter_100ms++;

    // 10 ticks of 1ms = 10ms raise flag 
    if (counter_10ms >= 10) {
        flag_10ms = true;
        counter_10ms = 0;
    }

    if (counter_100ms >= 100) {
        flag_100ms = true;
        counter_100ms = 0;
    }
}

bool Scheduler_Is10msTaskDue(void) {
    if (flag_10ms) {
        flag_10ms = false;
        return true;
    }
    return false;
}

bool Scheduler_Is100msTaskDue(void) {
    if (flag_100ms) {
        flag_100ms = false;
        return true;
    }
    return false;
}
