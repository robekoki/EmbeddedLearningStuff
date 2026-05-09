#include<stdint.h>
#include"ring_buffer.h"

static uint8_t nextIndex(uint8_t index);

void RingBuffer_init(RingBuffer *buf)
{
    buf->head = 0;
    buf->tail = 0;
}

uint8_t RingBuffer_isEmpty(RingBuffer *buf) {
    return (buf->head == buf->tail);
}

uint8_t RingBuffer_isFull(RingBuffer *buf) {
    return (nextIndex(buf->head) == buf->tail) == 1;
}

uint8_t RingBuffer_write(RingBuffer *buf, uint8_t data) {
    if(!RingBuffer_isFull(buf)) {
        buf->data[buf->head] = data; // write to head
        buf->head = nextIndex(buf->head);
        return 1; // successful 
    }
    return 0; // if buffer full return 0 (false = unsuccesful)
}

uint8_t RingBuffer_read(RingBuffer *buf, uint8_t *data) {
    if (!RingBuffer_isEmpty(buf)) {
        *data = buf->data[buf->tail]; // read tail
        buf->tail = nextIndex(buf->tail);
        return 1; // successful
    }
    return 0; // unsuccessful
}

static uint8_t nextIndex(uint8_t index)
{
    if ((index + 1) == RING_BUFFER_SIZE) {
        return 0;
    }
    return index + 1;
}