/**
  ******************************************************************************
  * @file           : simple_q.c
  * @date           : 24 July 2017
  * @brief          : This file implement queue data structure.
  * @author         : Burin Sapsiri <burin.coding@gmail.com>
  *
  ******************************************************************************
*/

#include "simple_q.h"

/* string.h contain function memcpy. */
#include <string.h>

void simple_q_init(simple_q_t *p_hndl,
                   void *buf,
                   int32_t size,
                   int32_t len)
{
    p_hndl->buf = buf;
    p_hndl->element_size = size;
    p_hndl->buf_len = len;
    p_hndl->overwrite = SIMPLE_Q_NONOVERWRITABLE;

    p_hndl->head = -1;
    p_hndl->tail = -1;
}

void simple_q_set_overwrite(simple_q_t *p_hndl,
                            simple_q_overwrite_t overwrite)
{
    p_hndl->overwrite = overwrite;
}

simple_q_result_t simple_q_push(simple_q_t *p_hndl,
                                const void *p_data)
{
    int32_t tail_tmp = p_hndl->tail;
    int32_t head_tmp = p_hndl->head;

    if (simple_q_size(p_hndl) == p_hndl->buf_len) {
        if (p_hndl->overwrite == SIMPLE_Q_NONOVERWRITABLE) {
            /* Queue full. */
            return SIMPLE_Q_FULL;
        } else {
            head_tmp = (head_tmp + 1) % p_hndl->buf_len;
        }
    }

    tail_tmp = (tail_tmp + 1) % p_hndl->buf_len;

    if (p_data != NULL) {
        memcpy((void*)((uint8_t*)p_hndl->buf+(tail_tmp*p_hndl->element_size)), p_data, p_hndl->element_size);
    }

    p_hndl->tail = tail_tmp;
    p_hndl->head = head_tmp;
    
    if (p_hndl->head == -1) {
        p_hndl->head = 0;
    }

    return SIMPLE_Q_SUCCESS;
}

simple_q_result_t simple_q_pop(simple_q_t *p_hndl,
                               void *p_data)
{
    if (simple_q_size(p_hndl) == 0) {
        /* Queue empty. */
        return SIMPLE_Q_EMPTY;
    }

    if (p_data != NULL) {
        memcpy(p_data, (void*)((uint8_t*)p_hndl->buf+(p_hndl->head*p_hndl->element_size)), p_hndl->element_size);
    }

    if (p_hndl->head == p_hndl->tail) {
        p_hndl->head = -1;
        p_hndl->tail = -1;
    } else {
        p_hndl->head = (p_hndl->head + 1) % p_hndl->buf_len;
    }

    return SIMPLE_Q_SUCCESS;
}

simple_q_result_t simple_q_peek(simple_q_t *p_hndl,
                                void *p_data)
{
    if (simple_q_size(p_hndl) == 0) {
        /* Queue empty. */
        return SIMPLE_Q_EMPTY;
    }

    if (p_data != NULL) {
        memcpy(p_data, (void*)((uint8_t*)p_hndl->buf+(p_hndl->head*p_hndl->element_size)), p_hndl->element_size);
    }

    return SIMPLE_Q_SUCCESS;
}

void* simple_q_peek_ptr(simple_q_t *p_hndl)
{
    if (simple_q_size(p_hndl) == 0) {
        return NULL;
    }

    return (void*)((uint8_t*)p_hndl->buf+(p_hndl->head*p_hndl->element_size));
}

int32_t simple_q_size(simple_q_t *p_hndl)
{
    if (p_hndl->head == -1) {
        return 0;
    }

    if (p_hndl->tail >= p_hndl->head) {
        return (p_hndl->tail - p_hndl->head) + 1;
    } else {
        return (p_hndl->buf_len - p_hndl->head) + p_hndl->tail + 1;
    }
}

void simple_q_flush(simple_q_t *p_hndl)
{
    p_hndl->head = -1;
    p_hndl->tail = -1;
}

