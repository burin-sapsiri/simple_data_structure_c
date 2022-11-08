/**
  ******************************************************************************
  * @file           : simple_pool.h
  * @date           : 30 January 2018
  * @brief          : Header file for the simple_pool.c
  *
  * @author         : Burin Sapsiri <burin.coding@gmail.com>
  *
  ******************************************************************************
*/

#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

#include <stdint.h>

#define SIMPLE_POOL_MGMT_COUNT(x)                               ((x /  32) + 1)

typedef uint32_t simple_pool_mgmt_t;

typedef struct {
    simple_pool_mgmt_t              *p_mgmt;
    void                            *buf;
    uint32_t                        element_size;
    uint32_t                        len;
}simple_pool_t;


#ifdef __cplusplus
extern "C" {
#endif


void simple_pool_init(simple_pool_t *p_hndl,
                      simple_pool_mgmt_t *p_mgmt,
                      void *buf,
                      uint32_t element_size,
                      uint32_t len);

void* simple_pool_alloc(simple_pool_t *p_hndl);
void simple_pool_free(simple_pool_t *p_hndl, void *p_target);

#ifdef __cplusplus
}
#endif

#endif // SIMPLE_POOL_H
