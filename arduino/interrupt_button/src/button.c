#include "button.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define DEBOUNCE_TIME_MS 25

static Button *int0_button;

void Button_init(Button *btn)
{
    int0_button = btn;
    // PD2 input
    DDRD &= ~(btn->pin_mask);

    // Enable internal pull-up
    PORTD |= (btn->pin_mask);

    // INT0 falling edge:
    // ISC01 = 1, ISC00 = 0
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Clear pending INT0 flag
    EIFR |= (1 << INTF0);

    // Enable INT0
    EIMSK |= (1 << INT0);
}

void Button_handleInterrupt(Button *btn)
{
    if (!btn->debouncing)
    {
        btn->debouncing = 1;
        btn->debounce_counter = DEBOUNCE_TIME_MS;

        // Disable INT0 during debounce
        EIMSK &= ~(1 << INT0);
    }
}

void Button_tick_1ms(void *context)
{
    Button *btn = (Button *)context;
    if (!btn->debouncing)
    {
        return;
    }

    if (btn->debounce_counter > 0)
    {
        btn->debounce_counter--;
        return;
    }

    // Debounce time has passed. Confirm button is still pressed.
    if (!(PIND & (btn->pin_mask)))
    {
        int0_button->pressed_event = 1;
    }

    btn->debouncing = 0;

    // Clear pending INT0 flag before re-enabling
    EIFR |= (1 << INTF0);

    // Re-enable INT0
    EIMSK |= (1 << INT0);
}

uint8_t Button_wasPressed(Button *btn)
{
    uint8_t pressed_event_copy;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        pressed_event_copy = btn->pressed_event;
        btn->pressed_event = 0;
    }

    return pressed_event_copy;
}

ISR(INT0_vect)
{
    Button_handleInterrupt(int0_button);
}