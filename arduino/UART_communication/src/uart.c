#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include "uart.h"

volatile static uint8_t dataByte;
volatile static uint8_t byteAvailable;

void UART_init_9600() {
    UBRR0H = 0;
    UBRR0L = 103; // set baud rate to 9600 

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // enable tx and rx with interrupt

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void UART_sendByte(uint8_t byte) {
    while (!(UCSR0A & (1 << UDRE0))) { // poll till UDR Empty flag == 1
    }
     UDR0 = byte; // copy byte to data register
}

void UART_sendString(const char *str) {
    while (*str != '\0') {
        UART_sendByte(*str); // send char by char till '\0'
        str++;
    }
}

uint8_t UART_receiveByte() {
    while(!(UCSR0A & (1 << RXC0))) {}// wait until flag is set
    uint8_t byte = UDR0; // read byte, will be cleared automatically
    return byte; // return data  
}

uint8_t UART_hasNext() {
    return (UCSR0A & (1 << RXC0));
}

uint8_t UART_getBufferedByte() {
    byteAvailable = 0;
    return dataByte;
}

uint8_t UART_hasNextBuffered() {
    return byteAvailable == 1;
}

ISR(USART_RX_vect) {
    dataByte = UDR0;
    byteAvailable = 1;
}