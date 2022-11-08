/**
  ******************************************************************************
  * @file           : simple_pool.h
  * @date           : 30 January 2018
  * @brief          : This file implement simple memory pool.
  *
  * @author         : Burin Sapsiri <burin.coding@gmail.com>
  *
  ******************************************************************************
*/

#include "simple_pool.h"
#include <string.h>

typedef enum {
    MGMT_UNSET = 0,
    MGMT_SET = !MGMT_UNSET
}mgmt_status_t;

#define POOL_PER_MGMT                               32U

static uint32_t dividup(uint32_t numer, uint32_t denom);

static void mgmt_init(simple_pool_mgmt_t *p_mgmt, uint32_t len);
static void mgmt_set(simple_pool_mgmt_t *p_mgmt, uint32_t index, mgmt_status_t status);
static mgmt_status_t mgmt_get(simple_pool_mgmt_t *p_mgmt, uint32_t index);
static void* pointer_of(void *base, uint32_t index, uint32_t element_size);
static uint32_t index_of(void *base, void *p, uint32_t element_size);

void simple_pool_init(simple_pool_t *p_hndl,
                      simple_pool_mgmt_t *p_mgmt,
                      void *buf,
                      uint32_t element_size,
                      uint32_t len)
{
    p_hndl->buf = buf;
    p_hndl->element_size = element_size;
    p_hndl->len = len;

    p_hndl->p_mgmt = p_mgmt;
    mgmt_init(p_hndl->p_mgmt, dividup(p_hndl->len, POOL_PER_MGMT));
}

void* simple_pool_alloc(simple_pool_t *p_hndl)
{
    uint32_t i = 0;

    for (i=0; i<p_hndl->len; i++) {
        if (mgmt_get(p_hndl->p_mgmt, i) == MGMT_UNSET) {
            mgmt_set(p_hndl->p_mgmt, i, MGMT_SET);
            return pointer_of(p_hndl->buf, i, p_hndl->element_size);
        }
    }

    return NULL;
}

void simple_pool_free(simple_pool_t *p_hndl, void *p_target)
{
    uint32_t i = 0;

    i = index_of(p_hndl->buf, p_target, p_hndl->element_size);

    mgmt_set(p_hndl->p_mgmt, i, MGMT_UNSET);
}



static uint32_t dividup(uint32_t numer, uint32_t denom)
{
    uint32_t rslt = numer / denom;

    if ((numer % denom) == 0) {
        return rslt;
    } else {
        return rslt + 1;
    }
}

static void mgmt_init(simple_pool_mgmt_t *p_mgmt, uint32_t len)
{
    memset(p_mgmt, 0x00, sizeof(simple_pool_mgmt_t)*len);
}

static void mgmt_set(simple_pool_mgmt_t *p_mgmt, uint32_t index, mgmt_status_t status)
{
    uint32_t mgmt_index = index / POOL_PER_MGMT;
    uint32_t bit_index = index % POOL_PER_MGMT;

    if (status == MGMT_SET) {
        p_mgmt[mgmt_index] |= (1 << bit_index);
    } else {
        p_mgmt[mgmt_index] &= ~(1 << bit_index);
    }
}

static mgmt_status_t mgmt_get(simple_pool_mgmt_t *p_mgmt, uint32_t index)
{
    uint32_t mgmt_index = index / POOL_PER_MGMT;
    uint32_t bit_index = index % POOL_PER_MGMT;

    if ((p_mgmt[mgmt_index] & (1 << bit_index)) != 0) {
        return MGMT_SET;
    } else {
        return MGMT_UNSET;
    }
}

static void* pointer_of(void *base, uint32_t index, uint32_t element_size)
{
    return (void*)((uint8_t*)base + (index * element_size));
}

static uint32_t index_of(void *base, void *p, uint32_t element_size)
{
    uint32_t diff = (uint32_t)p - (uint32_t)base;

    return (diff / element_size);
}





#ifdef UNITTEST_ENABLE

#include <stdio.h>

#define TEST_EQUAL(x, y)                    do { \
                                                if (x != y) { \
                                                     printf ("Get %d not equal to %d %s:%d.\r\n", x, y, __FILE__, __LINE__); \
                                                } \
                                            } while (0);

#define TEST_NOT_EQUAL(x, y)                do { \
                                                if (x == y) { \
                                                     printf ("Get %d equal to %d %s:%d.\r\n", x, y, __FILE__, __LINE__); \
                                                } \
                                            } while (0);

#define POOL_LEN                            5U
#define POOL_ELEMENT_SIZE                   sizeof(uint32_t)
#define POOL_MGMT_LEN                       ((POOL_LEN /  32) + 1)

static simple_pool_t unittest_hndl;
static simple_pool_mgmt_t unittest_mgmt[POOL_MGMT_LEN];
static uint8_t *unittest_buf[POOL_LEN * POOL_ELEMENT_SIZE] = {0};

static void UNITTEST_SHOW_POOL(void)
{
    uint32_t i = 0;

    printf ("Pool : ");

    for (i=0; i<POOL_LEN; i++) {
        printf ("%d ", *(((uint32_t*)(unittest_buf)) + i));
    }
    printf ("\r\n");
}

void UNITTEST_SIMPLE_POOL(void)
{
    uint32_t *p_data = 0;

    simple_pool_init(&unittest_hndl, unittest_mgmt, unittest_buf, POOL_ELEMENT_SIZE, POOL_LEN);

    printf ("Allocate 1 block from pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_NOT_EQUAL(p_data, NULL);

    printf ("Set 1 to the allocated block.\r\n");
    *p_data = 1;
    UNITTEST_SHOW_POOL();


    printf ("============================================================\r\n");


    printf ("Allocate 1 block from pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_NOT_EQUAL(p_data, NULL);

    printf ("Set 2 to the allocated block.\r\n");
    *p_data = 2;
    UNITTEST_SHOW_POOL();



    printf ("============================================================\r\n");


    printf ("Allocate 1 block from pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_NOT_EQUAL(p_data, NULL);

    printf ("Set 3 to the allocated block.\r\n");
    *p_data = 3;
    UNITTEST_SHOW_POOL();



    printf ("============================================================\r\n");


    printf ("Allocate 1 block from pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_NOT_EQUAL(p_data, NULL);

    printf ("Set 4 to the allocated block.\r\n");
    *p_data = 4;
    UNITTEST_SHOW_POOL();



    printf ("============================================================\r\n");


    printf ("Allocate 1 block from pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_NOT_EQUAL(p_data, NULL);

    printf ("Set 5 to the allocated block.\r\n");
    *p_data = 5;
    UNITTEST_SHOW_POOL();



    printf ("============================================================\r\n");


    printf ("Allocate 1 block from fulled pool.\r\n");
    p_data = (uint32_t*)simple_pool_alloc(&unittest_hndl);
    TEST_EQUAL(p_data, NULL);


    printf ("============================================================\r\n");


    printf ("Free last block in pool.\r\n");
    simple_pool_free(&unittest_hndl, p_data);
    TEST_EQUAL(p_data, NULL);


    printf ("============================================================\r\n");

}

#endif
