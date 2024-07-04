/*
 * fifo.h
 *
 *  Created on: Jul 4, 2024
 *      Author: licin
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>

#define FIFO_SIZE 1024

typedef struct {
    uint8_t buffer[FIFO_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} FIFO_TypeDef;

void fifo_init(FIFO_TypeDef *fifo);
uint16_t fifo_write(FIFO_TypeDef *fifo, uint8_t *data, uint16_t length);
uint16_t fifo_read(FIFO_TypeDef *fifo, uint8_t *data, uint16_t length);
uint16_t fifo_available(FIFO_TypeDef *fifo);
uint16_t fifo_free_space(FIFO_TypeDef *fifo);

#endif /* FIFO_H_ */
