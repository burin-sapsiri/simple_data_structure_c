#include "simple_list.h"

static void copy_from_front(void *dst, void *src, uint32_t size);
static void copy_from_back(void *dst, void *src, uint32_t size);
static simple_list_bool_t compare(void *v1, void *v2, uint32_t size);

void simple_list_init(simple_list_t *p_hndl,
                      void *buf,
                      uint32_t element_size,
                      uint32_t len)
{
    p_hndl->buf = buf;
    p_hndl->element_size = element_size;
    p_hndl->buf_len = len;
    
    p_hndl->tail = 0;
}

simple_list_result_t simple_list_insert_at(simple_list_t *p_hndl,
                                           uint32_t index,
                                           void *p_data)
{
    if (p_hndl->tail >= p_hndl->buf_len) {
        return SIMPLE_LIST_FAIL;
    }

    /* Move data after specific index forward for 1 slot. */
    copy_from_back((void*)((uint8_t*)(p_hndl->buf) + ((index+1) * p_hndl->element_size)),
                   (void*)((uint8_t*)p_hndl->buf + (index * p_hndl->element_size)),
                   ((p_hndl->tail - index) * p_hndl->element_size));

    /* Place the input data in the specific index. */
    copy_from_front((void*)((uint8_t*)p_hndl->buf + (index * p_hndl->element_size)),
                    p_data,
                    p_hndl->element_size);

    p_hndl->tail++;

    return SIMPLE_LIST_SUCCESS;
}
                      
simple_list_result_t simple_list_prepend(simple_list_t *p_hndl,
                                             void *p_data)
{
    return simple_list_insert_at(p_hndl, 0, p_data);
}

simple_list_result_t simple_list_append(simple_list_t *p_hndl,
                                        void *p_data)
{
    if (p_hndl->tail >= p_hndl->buf_len) {
        return SIMPLE_LIST_FAIL;
    }
    
    /* Place the input after last slot. */
    copy_from_front((void*)((uint8_t*)(p_hndl->buf) + (p_hndl->element_size * p_hndl->tail)),
                    p_data,
                    p_hndl->element_size);
    
    p_hndl->tail++;
    
    return SIMPLE_LIST_SUCCESS;
}

simple_list_result_t simple_list_remove(simple_list_t *p_hndl,
                                        uint32_t index)
{
    if (index >= p_hndl->tail) {
        /* Invalid index */
        return SIMPLE_LIST_FAIL;
    }
    
    if (p_hndl->tail == 0) {
        return SIMPLE_LIST_FAIL;
    }
    
    copy_from_front((void*)((uint8_t*)(p_hndl->buf) + (p_hndl->element_size * index)),
                    (void*)((uint8_t*)(p_hndl->buf) + (p_hndl->element_size * (index+1))),
                    ((p_hndl->tail - index) - 1) * p_hndl->element_size);
         
    p_hndl->tail--;
                    
    return SIMPLE_LIST_SUCCESS;
}

simple_list_result_t simple_list_remove_by_value(simple_list_t *p_hndl,
                                                 void *p_data)
{
    simple_list_result_t result = SIMPLE_LIST_FAIL;
    uint32_t i = 0;
    
    for (i=0; i<p_hndl->tail; ) {
        if (compare(simple_list_at(p_hndl, i), p_data, p_hndl->element_size) == SIMPLE_LIST_TRUE) {
            simple_list_remove(p_hndl, i);
            result = SIMPLE_LIST_SUCCESS;
        } else {
            i++;
        }
    }
    
    return result;
}

simple_list_bool_t simple_list_contain(simple_list_t *p_hndl,
                                       void *p_data)
{
    uint32_t i = 0;

    for (i=0; i<p_hndl->tail; i++) {
        if (compare(simple_list_at(p_hndl, i), p_data, p_hndl->element_size) == SIMPLE_LIST_TRUE) {
            return SIMPLE_LIST_TRUE;
        }
    }

    return SIMPLE_LIST_FALSE;
}

void* simple_list_at(simple_list_t *p_hndl,
                     uint32_t index)
{
    return (void*)((uint8_t*)p_hndl->buf + (p_hndl->element_size * index));
}

uint32_t simple_list_size(simple_list_t *p_hndl)
{
    return p_hndl->tail;
}

static void copy_from_front(void *dst, void *src, uint32_t size)
{
    uint32_t i = 0;
    uint8_t *p_dst = (uint8_t*)dst;
    uint8_t *p_src = (uint8_t*)src;

    for (i=0; i<size; i++) {
        p_dst[i] = p_src[i];
    }
}

static void copy_from_back(void *dst, void *src, uint32_t size)
{
    uint32_t i = 0;
    uint8_t *p_dst = (uint8_t*)dst;
    uint8_t *p_src = (uint8_t*)src;

    for (i=size; i>0; i--) {
        p_dst[i-1] = p_src[i-1];
    }
}

static simple_list_bool_t compare(void *v1, void *v2, uint32_t size)
{
    simple_list_bool_t result = SIMPLE_LIST_TRUE;
    uint32_t i = 0;
    uint8_t *p_v1 = (uint8_t*)v1;
    uint8_t *p_v2 = (uint8_t*)v2;
    
    for (i=0; i<size; i++) {
        if (p_v1[i] != p_v2[i]) {
            result = SIMPLE_LIST_FALSE;
            break;
        }
    }
    
    return result;
}
