#include <Arduino.h>
#include <stdint.h>
#include "timer.h"
#include "button.h"
#include "led.h"

static LED led1 = { (1u << 5), 0, 0, 500ul };
static Button button = { 0, 0, 0, (1 << PD2) };

void setup() {
  Led_init(&led1);
  Button_init(&button);
  Timer_trackButton(&button);
  Timer1_init_1ms();
}

void loop() {
  if (Button_wasPressed(&button)) {
    Led_toggle(&led1);
  }
}
