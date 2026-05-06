#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init_1ms(void)
{
    // Stop Timer1 while configuring
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset counter
    TCNT1 = 0;

    // 16 MHz / 64 = 250 kHz
    // 1 timer tick = 4 us
    // 250 ticks = 1 ms
    // OCR1A = 249 because counting starts from 0
    OCR1A = 249;

    // CTC mode: WGM12 = 1
    TCCR1B |= (1 << WGM12);

    // Prescaler 64: CS11 = 1, CS10 = 1
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Enable Timer1 Compare Match A interrupt
    TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    ms_counter++;
}