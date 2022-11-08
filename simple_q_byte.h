#ifndef _SIMPLE_Q_BYTE_H
#define _SIMPLE_Q_BYTE_H


#include <stdint.h>

typedef enum {
    SIMPLE_Q_BYTE_SUCCESS = 0,
    SIMPLE_Q_BYTE_FULL,
    SIMPLE_Q_BYTE_EMPTY
}simple_q_byte_result_t;

typedef struct {
    uint8_t                 *buf;
    int32_t                 buf_len;
    
    int32_t                 head;
    int32_t                 tail;
}simple_q_byte_t;

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief simple_q_byte_init
 * @param p_hndl
 * @param buf
 * @param size
 * @param len
 */
void simple_q_byte_init(simple_q_byte_t *p_hndl,
                        uint8_t *buf,
                        int32_t len);

/**
 * @brief simple_q_byte_push
 * @param p_hndl
 * @param data
 * @return
 */
simple_q_byte_result_t simple_q_byte_push(simple_q_byte_t *p_hndl,
                                          uint8_t data);

/**
 * @brief simple_q_byte_pop
 * @param p_hndl
 * @param p_data
 * @return
 */
simple_q_byte_result_t simple_q_byte_pop(simple_q_byte_t *p_hndl,
                                         uint8_t *p_data);

/**
 * @brief simple_q_byte_peek
 * @param p_hndl
 * @param p_data
 * @return
 */
simple_q_byte_result_t simple_q_byte_peek(simple_q_byte_t *p_hndl,
                                          uint8_t *p_data);

/**
 * @brief simple_q_byte_size
 * @param p_hndl
 * @return 
 */
int32_t simple_q_byte_size(simple_q_byte_t *p_hndl);

/**
 * @brief simple_q_byte_available
 * @param p_hndl
 * @return
 */
int32_t simple_q_byte_available(simple_q_byte_t *p_hndl);

/**
 * @brief simple_q_byte_flush
 * @param p_hndl
 */
void simple_q_byte_flush(simple_q_byte_t *p_hndl);

#ifdef __cplusplus
    }
#endif


#endif /* _SIMPLE_Q_BYTE_H */
