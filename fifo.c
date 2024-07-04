/*
 * fifo.c
 *
 *  Created on: Jul 4, 2024
 *      Author: licin
 */


#include "fifo.h"
#include <string.h>

void fifo_init(FIFO_TypeDef *fifo) {
    fifo->head = 0;
    fifo->tail = 0;
}

uint16_t fifo_write(FIFO_TypeDef *fifo, uint8_t *data, uint16_t length) {
    uint16_t free_space = fifo_free_space(fifo);
    uint16_t bytes_to_write = (length > free_space) ? free_space : length;
    uint16_t first_chunk_size = (FIFO_SIZE - fifo->head > bytes_to_write) ? bytes_to_write : FIFO_SIZE - fifo->head;
    uint16_t second_chunk_size = bytes_to_write - first_chunk_size;

    memcpy(&fifo->buffer[fifo->head], data, first_chunk_size);
    if (second_chunk_size > 0) {
        memcpy(fifo->buffer, &data[first_chunk_size], second_chunk_size);
    }

    fifo->head = (fifo->head + bytes_to_write) % FIFO_SIZE;

    if (fifo->head == fifo->tail) {
        fifo->tail = (fifo->tail + bytes_to_write) % FIFO_SIZE;
    }

    return bytes_to_write;
}

uint16_t fifo_read(FIFO_TypeDef *fifo, uint8_t *data, uint16_t length) {
    uint16_t available_data = fifo_available(fifo);
    uint16_t bytes_to_read = (length > available_data) ? available_data : length;
    uint16_t first_chunk_size = (FIFO_SIZE - fifo->tail > bytes_to_read) ? bytes_to_read : FIFO_SIZE - fifo->tail;
    uint16_t second_chunk_size = bytes_to_read - first_chunk_size;

    memcpy(data, &fifo->buffer[fifo->tail], first_chunk_size);
    if (second_chunk_size > 0) {
        memcpy(&data[first_chunk_size], fifo->buffer, second_chunk_size);
    }

    fifo->tail = (fifo->tail + bytes_to_read) % FIFO_SIZE;

    return bytes_to_read;
}

uint16_t fifo_available(FIFO_TypeDef *fifo) {
    return (fifo->head >= fifo->tail) ? (fifo->head - fifo->tail) : (FIFO_SIZE - fifo->tail + fifo->head);
}

uint16_t fifo_free_space(FIFO_TypeDef *fifo) {
    return FIFO_SIZE - fifo_available(fifo) - 1;
}

