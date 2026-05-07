#include <stdint.h>

#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

void Button_init(void);
void Button_handleInterrupt(void);
void Button_tick_1ms(void);
uint8_t Button_wasPressed(void);

#ifdef __cplusplus
}
#endif

#endif