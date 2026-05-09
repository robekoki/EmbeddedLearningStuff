#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include<stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define RING_BUFFER_SIZE 8

typedef struct
{
    volatile uint8_t head;
    volatile uint8_t tail;
    uint8_t data[RING_BUFFER_SIZE];
} RingBuffer;

void RingBuffer_init(RingBuffer *buf);

uint8_t RingBuffer_isEmpty(RingBuffer *buf);
uint8_t RingBuffer_isFull(RingBuffer *buf);

uint8_t RingBuffer_write(RingBuffer *buf, uint8_t data);
uint8_t RingBuffer_read(RingBuffer *buf, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif