#include "led.h"
#include <stdint.h>
#include <Arduino.h>

void Led_init(LED *led) {
  DDRB |= led->mask;
  PORTB &= ~led->mask;
  led->state = 0;
}

void Led_on(LED *led) {
  PORTB |= led->mask;
  led->state = 1;
}

void Led_off(LED *led) {
  PORTB &= ~led->mask;
  led->state = 0;
}

void Led_toggle(LED *led) {
  if (led->state) {
    Led_off(led);
  } else {
    Led_on(led);
  }
}