#include "simple_set.h"

#ifndef NULL
    #define NULL            0U
#endif

void simple_set_init(simple_set_t *p_hndl,
                     void *buf,
                     uint32_t element_size,
                     uint32_t len,
                     simple_set_compare_cb_t compare_cb)
{
    p_hndl->buf = buf;
    p_hndl->buf_len = len;
    p_hndl->element_size = element_size;

    simple_list_init(&p_hndl->item_list,
                     p_hndl->buf,
                     p_hndl->element_size,
                     p_hndl->buf_len);

    p_hndl->compare_cb = compare_cb;
}

simple_set_result_t simple_set_insert(simple_set_t *p_hndl,
                                      void *p_data)
{
    uint32_t i = 0;

    if (simple_list_contain(&p_hndl->item_list, p_data) == SIMPLE_LIST_TRUE) {
        return SIMPLE_SET_FAIL;
    }

    if (p_hndl->compare_cb != NULL) {
        /* If compare function is provided, the data will be sort. */
        for (i=0; i<simple_list_size(&p_hndl->item_list); i++) {

            /* Find the position that the data to be added less than. */
            if (p_hndl->compare_cb(p_data, simple_list_at(&p_hndl->item_list, i)) <= 0) {
                break;
            }
        }

        if (simple_list_insert_at(&p_hndl->item_list, i, p_data) != SIMPLE_LIST_SUCCESS) {
            return SIMPLE_SET_FAIL;
        }
    } else {
        /* If compare function is not provided, the data will be append to the last. */
        if (simple_list_append(&p_hndl->item_list, p_data) != SIMPLE_LIST_SUCCESS) {
            return SIMPLE_SET_FAIL;
        }
    }

    return SIMPLE_SET_SUCCESS;
}

simple_set_result_t simple_set_remove(simple_set_t *p_hndl,
                                      void *p_data)
{
    uint32_t i = 0;
    simple_set_result_t result = SIMPLE_SET_FAIL;

    if (p_hndl->compare_cb != NULL) {
        /* If compare function is provided, the data will be sort. */
        for (i=0; i<simple_list_size(&p_hndl->item_list); i++) {

            /* Find the position that the data to be added less than. */
            if (p_hndl->compare_cb(p_data, simple_list_at(&p_hndl->item_list, i)) == 0) {
                break;
            }
        }

        if (i < simple_list_size(&p_hndl->item_list)) {
            if (simple_list_remove((&p_hndl->item_list), i) == SIMPLE_LIST_SUCCESS) {
                result = SIMPLE_SET_SUCCESS;
            }
        }
    } else {
        if (simple_list_remove_by_value(&p_hndl->item_list, p_data) == SIMPLE_LIST_SUCCESS) {
            result =  SIMPLE_SET_SUCCESS;
        }
    }

    return result;
}

simple_set_bool_t simple_set_contain(simple_set_t *p_hndl,
                                     void *p_data)
{
    if (simple_list_contain(&p_hndl->item_list, p_data) == SIMPLE_LIST_TRUE) {
        return SIMPLE_SET_TRUE;
    } else {
        return SIMPLE_SET_FALSE;
    }
}

void* simple_set_at(simple_set_t *p_hndl,
                    uint32_t index)
{
    return simple_list_at(&p_hndl->item_list, index);
}

uint32_t simple_set_size(simple_set_t *p_hndl)
{
    return simple_list_size(&p_hndl->item_list);
}
