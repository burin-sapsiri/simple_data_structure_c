/**
  ******************************************************************************
  * @file           : simple_q.h
  * @date           : 24 July 2017
  * @brief          : Header file for simple_q.c file.
  * @author         : Burin Sapsiri <burin.coding@gmail.com>
  *
  ******************************************************************************
*/

#ifndef _SIMPLE_Q_H
#define _SIMPLE_Q_H

#include <stdint.h>

typedef enum {
    SIMPLE_Q_SUCCESS = 0,
    SIMPLE_Q_FULL,
    SIMPLE_Q_EMPTY
}simple_q_result_t;

typedef enum {
    SIMPLE_Q_NONOVERWRITABLE = 0,
    SIMPLE_Q_OVERWRITABLE
}simple_q_overwrite_t;

typedef struct {
    void                    *buf;
    int32_t                 element_size;
    int32_t                 buf_len;
    
    simple_q_overwrite_t    overwrite;

    int32_t                 head;
    int32_t                 tail;
}simple_q_t;

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief simple_q_init
 * @param p_hndl
 * @param buf
 * @param size
 * @param len
 */
void simple_q_init(simple_q_t *p_hndl,
                   void *buf,
                   int32_t size,
                   int32_t len);

/**
 * @brief simple_q_init
 * @param overwrite
 */
void simple_q_set_overwrite(simple_q_t *p_hndl,
                            simple_q_overwrite_t overwrite);

/**
 * @brief simple_q_push
 * @param p_hndl
 * @param p_data
 * @return
 */
simple_q_result_t simple_q_push(simple_q_t *p_hndl,
                                const void *p_data);

/**
 * @brief simple_q_pop
 * @param p_hndl
 * @param p_data
 * @return
 */
simple_q_result_t simple_q_pop(simple_q_t *p_hndl,
                               void *p_data);

/**
 * @brief simple_q_peek
 * @param p_hndl
 * @param p_data
 * @return
 */
simple_q_result_t simple_q_peek(simple_q_t *p_hndl,
                                void *p_data);

/**
 * @brief simple_q_peek_ptr
 * @param p_hndl
 * @return
 */
void* simple_q_peek_ptr(simple_q_t *p_hndl);

/**
 * @brief simple_q_size
 * @param p_hndl
 * @return 
 */
int32_t simple_q_size(simple_q_t *p_hndl);

/**
 * @brief simple_q_flush
 * @param p_hndl
 */
void simple_q_flush(simple_q_t *p_hndl);

#ifdef __cplusplus
    }
#endif

#endif /* _SIMPLE_Q_H */
