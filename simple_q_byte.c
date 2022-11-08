#include "simple_q_byte.h"

void simple_q_byte_init(simple_q_byte_t *p_hndl,
                        uint8_t *buf,
                        int32_t len)
{
    p_hndl->buf = buf;
    p_hndl->buf_len = len;

    p_hndl->head = -1;
    p_hndl->tail = -1;
}


simple_q_byte_result_t simple_q_byte_push(simple_q_byte_t *p_hndl,
                                          uint8_t data)
{
    int32_t tail_tmp = p_hndl->tail;
    
    if (simple_q_byte_size(p_hndl) == p_hndl->buf_len) {
        /* Queue full. */
        return SIMPLE_Q_BYTE_FULL;
    }

    tail_tmp = (tail_tmp + 1) % p_hndl->buf_len;

    p_hndl->buf[tail_tmp] = data;

    p_hndl->tail = tail_tmp;
    
    if (p_hndl->head == -1) {
        p_hndl->head = 0;
    }

    return SIMPLE_Q_BYTE_SUCCESS;
}


simple_q_byte_result_t simple_q_byte_pop(simple_q_byte_t *p_hndl,
                                         uint8_t *p_data)
{
    if (simple_q_byte_size(p_hndl) == 0) {
        /* Queue empty. */
        return SIMPLE_Q_BYTE_EMPTY;
    }

    if (p_data != 0) {
        *p_data = p_hndl->buf[p_hndl->head];
    }

    if (p_hndl->head == p_hndl->tail) {
        p_hndl->head = -1;
        p_hndl->tail = -1;
    } else {
        p_hndl->head = (p_hndl->head + 1) % p_hndl->buf_len;
    }

    return SIMPLE_Q_BYTE_SUCCESS;
}


simple_q_byte_result_t simple_q_byte_peek(simple_q_byte_t *p_hndl,
                                          uint8_t *p_data)
{
    if (simple_q_byte_size(p_hndl) == 0) {
        /* Queue empty. */
        return SIMPLE_Q_BYTE_EMPTY;
    }

    if (p_data != 0) {
        *p_data = p_hndl->buf[p_hndl->head];
    }

    return SIMPLE_Q_BYTE_SUCCESS;
}


int32_t simple_q_byte_size(simple_q_byte_t *p_hndl)
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


int32_t simple_q_byte_available(simple_q_byte_t *p_hndl)
{
	if (p_hndl->head == -1) {
		return p_hndl->buf_len;
	}

	return p_hndl->buf_len - simple_q_byte_size(p_hndl);
}


void simple_q_byte_flush(simple_q_byte_t *p_hndl)
{
    p_hndl->head = -1;
    p_hndl->tail = -1;
}
