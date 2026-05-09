#include <Arduino.h>
#include <stdint.h>
#include "uart.h"
#include "ring_buffer.h"

RingBuffer buffer;
uint8_t data = 0;
uint8_t readOp = 0;

void setup() {
  UART_init_9600();
  RingBuffer_init(&buffer);
}

void loop() {
  // if (UART_hasNext()) {
  //     uint8_t echo = UART_receiveByte();
  //     UART_sendByte('[');
  //     UART_sendByte(echo);
  //     UART_sendByte(']');
  //     UART_sendString("\r\n");
  // }

  readOp = RingBuffer_read(&buffer, &data);
  UART_sendString("Data after read is ");
  UART_sendByte(data + '0');
  UART_sendString("\r\n");
  UART_sendString("read OP is ");
  UART_sendByte(readOp + '0');
  UART_sendString("\r\n");


  UART_sendString("Before write head should be 0 and is ");
  UART_sendByte(buffer.head + '0'); // should be 0
  UART_sendString("\r\n");
  RingBuffer_write(&buffer, 3);
  RingBuffer_write(&buffer, 2);
  RingBuffer_write(&buffer, 1);
  UART_sendString(" After 3 writes head should be 3 and is ");
  UART_sendByte(buffer.head + '0'); // should be 3
  UART_sendString("\r\n");

  readOp = RingBuffer_read(&buffer, &data);
  UART_sendString("Data after read is ");
  UART_sendByte(data + '0');
  UART_sendString("\r\n");
  UART_sendString("read OP is ");
  UART_sendByte(readOp + '0');
  UART_sendString("\r\n");
  UART_sendString("After read tail shoud be 1 and is at ");
  UART_sendByte(buffer.tail + '0');
  UART_sendString("\r\n");


  delay(50000);

  // if (UART_hasNextBuffered()) {
  //   uint8_t echo = UART_getBufferedByte();
  //   UART_sendByte('[');
  //   UART_sendByte(echo);
  //   UART_sendByte(']');
  //   UART_sendString("\r\n");
  // }

  // do other stuff
}