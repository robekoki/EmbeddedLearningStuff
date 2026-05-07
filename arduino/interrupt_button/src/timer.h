#include <stdint.h>

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

void timer1_init_1ms(void);
extern volatile uint16_t ms_counter;

#ifdef __cplusplus
}
#endif

#endif