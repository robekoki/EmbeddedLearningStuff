#include <Arduino.h>
#include <stdint.h>
#include "timer.h"
#include "button.h"
#include "led.h"

static LED led1 = { (1u << 5), 0, 0, 500ul };

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
