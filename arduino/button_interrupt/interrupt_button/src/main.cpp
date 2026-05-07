#include <Arduino.h>
#include <stdint.h>
#include "timer.h"
#include "button.h"

typedef struct {
  uint8_t mask;
  uint8_t state;
  unsigned long last_blink_time;
  unsigned long blink_interval;
} LED;

static LED led1 = { (1u << 5), 0, 0, 500ul };

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

void setup() {
  led_init(&led1);
  Button_init();
  timer1_init_1ms();
}

void loop() {
  if (Button_wasPressed()) {
    led_toggle(&led1);
  }
}
