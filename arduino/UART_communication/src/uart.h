#ifndef UART_H
#define UART_H

#include<stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

void UART_init_9600(void);
void UART_sendByte(uint8_t byte);
void UART_sendString(const char *str);

#ifdef __cplusplus
}
#endif

#endif