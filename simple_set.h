#ifndef SIMPLE_SET_H
#define SIMPLE_SET_H

#include <stdint.h>
#include "simple_list.h"

typedef enum {
    SIMPLE_SET_SUCCESS = 0,
    SIMPLE_SET_FAIL
}simple_set_result_t;

typedef enum {
    SIMPLE_SET_FALSE = 0,
    SIMPLE_SET_TRUE = !SIMPLE_SET_FALSE
}simple_set_bool_t;

typedef int8_t(*simple_set_compare_cb_t)(void *src, void *dst);

typedef struct {
    void                    *buf;
    uint32_t                buf_len;
    uint32_t                element_size;

    simple_list_t           item_list;

    simple_set_compare_cb_t compare_cb;
}simple_set_t;

void simple_set_init(simple_set_t *p_hndl,
                     void *buf,
                     uint32_t element_size,
                     uint32_t len,
                     simple_set_compare_cb_t compare_cb);

simple_set_result_t simple_set_insert(simple_set_t *p_hndl,
                                      void *p_data);

simple_set_result_t simple_set_remove(simple_set_t *p_hndl,
                                      void *p_data);

simple_set_bool_t simple_set_contain(simple_set_t *p_hndl,
                                     void *p_data);

void* simple_set_at(simple_set_t *p_hndl,
                    uint32_t index);

uint32_t simple_set_size(simple_set_t *p_hndl);

#endif // SIMPLE_SET_H
