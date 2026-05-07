#include <stdint.h>

#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint8_t debouncing;
    volatile uint8_t debounce_counter;
    volatile uint8_t pressed_event;
    uint8_t pin_mask;
} Button;

void Button_init(Button *btn);
void Button_handleInterrupt(Button *btn);
void Button_tick_1ms(Button *btn);
uint8_t Button_wasPressed(Button *btn);

#ifdef __cplusplus
}
#endif

#endif