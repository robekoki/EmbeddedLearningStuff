#include <stdint.h>
#include "button.h"
#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TimerCallback)(void *);
void Timer1_init_1ms(void);
void Timer_registerCallback(TimerCallback callback, void *context);

#ifdef __cplusplus
}
#endif

#endif