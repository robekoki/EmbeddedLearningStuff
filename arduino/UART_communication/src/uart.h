#ifndef UART_H
#define UART_H

#include<stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*UART_Callback)(void *context, uint8_t data);
void UART_registerCallback(UART_Callback callback, void *context);

void UART_init_9600(void);
void UART_sendByte(uint8_t byte);
void UART_sendString(const char *str);
uint8_t UART_receiveByte(void);
uint8_t UART_hasNext(void);
uint8_t UART_getBufferedByte(void);
uint8_t UART_hasNextBuffered(void);

#ifdef __cplusplus
}
#endif

#endif