#include <stdint.h>
#include "button.h"
#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

void Timer1_init_1ms(void);
void Timer_trackButton(Button *btn);
extern volatile uint16_t ms_counter;

#ifdef __cplusplus
}
#endif

#endif