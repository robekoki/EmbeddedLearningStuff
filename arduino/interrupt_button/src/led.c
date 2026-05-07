#include "led.h"
#include <stdint.h>
#include <Arduino.h>

void led_init(LED *led) {
  DDRB |= led->mask;
  PORTB &= ~led->mask;
  led->state = 0;
  led->last_blink_time = millis();
}

void led_on(LED *led) {
  PORTB |= led->mask;
  led->state = 1;
}

void led_off(LED *led) {
  PORTB &= ~led->mask;
  led->state = 0;
}

void led_toggle(LED *led) {
  if (led->state) {
    led_off(led);
  } else {
    led_on(led);
  }
}