#include <Arduino.h>
#include <stdint.h>
#include "uart.h"

void setup() {
  UART_init_9600();
}

void loop() {
  UART_sendString("Hello\r\n");
  delay(5000);
}