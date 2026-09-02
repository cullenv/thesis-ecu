#ifndef APP_SCHEDULER_H
#define APP_SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>

// Initialize the scheduler
void Scheduler_Init(void);

// Call this function every 1ms by hardware timer interrupt
void Scheduler_UpdateTick(void);

// what to do on these intevales
bool Scheduler_Is10msTaskDue(void);
bool Scheduler_Is100msTaskDue(void);

#endif // APP_SCHEDULER_H