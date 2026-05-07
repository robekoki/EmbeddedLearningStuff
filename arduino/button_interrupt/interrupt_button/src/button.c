#include "button.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define BUTTON_PIN PD2
#define DEBOUNCE_TIME_MS 25

static volatile uint8_t debouncing = 0;
static volatile uint8_t debounce_counter = 0;
static volatile uint8_t pressed_event = 0;

void Button_init(void)
{
    // PD2 input
    DDRD &= ~(1 << BUTTON_PIN);

    // Enable internal pull-up
    PORTD |= (1 << BUTTON_PIN);

    // INT0 falling edge:
    // ISC01 = 1, ISC00 = 0
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Clear pending INT0 flag
    EIFR |= (1 << INTF0);

    // Enable INT0
    EIMSK |= (1 << INT0);
}

void Button_handleInterrupt(void)
{
    if (!debouncing)
    {
        debouncing = 1;
        debounce_counter = DEBOUNCE_TIME_MS;

        // Disable INT0 during debounce
        EIMSK &= ~(1 << INT0);
    }
}

void Button_tick_1ms(void)
{
    if (!debouncing)
    {
        return;
    }

    if (debounce_counter > 0)
    {
        debounce_counter--;
        return;
    }

    // Debounce time has passed. Confirm button is still pressed.
    if (!(PIND & (1 << BUTTON_PIN)))
    {
        pressed_event = 1;
    }

    debouncing = 0;

    // Clear pending INT0 flag before re-enabling
    EIFR |= (1 << INTF0);

    // Re-enable INT0
    EIMSK |= (1 << INT0);
}

uint8_t Button_wasPressed(void)
{
    uint8_t pressed_event_copy;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        pressed_event_copy = pressed_event;
        pressed_event = 0;
    }

    return pressed_event_copy;
}

ISR(INT0_vect)
{
    Button_handleInterrupt();
}