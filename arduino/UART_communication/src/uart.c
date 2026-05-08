#include <avr/io.h>
#include <stdint.h>
#include "uart.h"

/*
1. Set baud rate: UBRR0H / UBRR0L
2. Enable transmitter: TXEN0
3. Configure frame format: 8N1
*/
void UART_init_9600() {
    UBRR0H = 0;
    UBRR0L = 103; // set baud rate to 9600 

    UCSR0B |= 1 << TXEN0; // enable tx

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
