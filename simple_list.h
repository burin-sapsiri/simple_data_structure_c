#ifndef _SIMPLE_LIST_H
#define _SIMPLE_LIST_H

#include <stdint.h>

typedef enum {
    SIMPLE_LIST_SUCCESS = 0,
    SIMPLE_LIST_FAIL
}simple_list_result_t;

typedef enum {
    SIMPLE_LIST_FALSE = 0,
    SIMPLE_LIST_TRUE = !SIMPLE_LIST_FALSE
}simple_list_bool_t;

typedef struct {
    void                            *buf;
    uint32_t                        element_size;
    uint32_t                        buf_len;
    
    uint32_t                        tail;
}simple_list_t;

void simple_list_init(simple_list_t *p_hndl,
                      void *buf,
                      uint32_t element_size,
                      uint32_t len);
                      
simple_list_result_t simple_list_insert_at(simple_list_t *p_hndl,
                                           uint32_t index,
                                           void *p_data);

simple_list_result_t simple_list_prepend(simple_list_t *p_hndl,
                                         void *p_data);

simple_list_result_t simple_list_append(simple_list_t *p_hndl,
                                        void *p_data);

simple_list_result_t simple_list_remove(simple_list_t *p_hndl,
                                        uint32_t index);
                      
simple_list_result_t simple_list_remove_by_value(simple_list_t *p_hndl,
                                                 void *p_data);

simple_list_bool_t simple_list_contain(simple_list_t *p_hndl,
                                       void *p_data);

void* simple_list_at(simple_list_t *p_hndl,
                     uint32_t index);

uint32_t simple_list_size(simple_list_t *p_hndl);

#endif /* _SIMPLE_LIST_H */
