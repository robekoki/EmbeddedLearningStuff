#include <Arduino.h>
#include <stdint.h>
#include "uart.h"
#include "ring_buffer.h"

RingBuffer buffer;
uint8_t data = 0;
uint8_t readOp = 0;

void UART_rxToRingBuffer(void *context, uint8_t data)
{
    RingBuffer_write((RingBuffer *)context, data);
}

void setup() {
  UART_init_9600();
  RingBuffer_init(&buffer);
  UART_registerCallback(UART_rxToRingBuffer, &buffer);
}

void loop() {
uint8_t byte;
if (RingBuffer_read(&buffer, &byte))
{
    UART_sendByte('[');
    UART_sendByte(byte);
    UART_sendByte(']');
    UART_sendString("\r\n");
}
}