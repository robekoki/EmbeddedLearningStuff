#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include "uart.h"
#include "ring_buffer.h"

static UART_Callback callback = 0;
static void* callback_ctx = 0;

void UART_registerCallback(UART_Callback callBack, void *context) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
    {
    callback = callBack;
    callback_ctx = context;
    }
}

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

ISR(USART_RX_vect)
{
    uint8_t receivedByte = UDR0;

    if (callback != 0)
    {
        callback(callback_ctx, receivedByte);
    }
}static 