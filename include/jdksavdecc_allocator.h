#pragma once

/*
  Copyright (c) 2013, J.D. Koftinoff Software, Ltd.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of J.D. Koftinoff Software, Ltd. nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include "jdksavdecc_world.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JDKSAVDECC_ENABLE_MALLOC
#define JDKSAVDECC_ENABLE_MALLOC 1
#endif

/** \addtogroup alloc Memory Allocator */
/*@{*/

/** jdksavdecc_new

    A define which simulates c++ new() operator, except it accepts an
    allocator to allocate from.
    No initializers of the objects are called.
*/

#define jdksavdecc_new(ALLOCATOR, T)                                           \
    (T *)((ALLOCATOR)->alloc((ALLOCATOR), (int32_t)sizeof(T), 1))

#define jdksavdecc_delete(ALLOCATOR, PTR)                                      \
    do {                                                                       \
        if ((ALLOCATOR) != 0 && (PTR) != 0)                                    \
            (ALLOCATOR)->free((ALLOCATOR), (PTR));                             \
    } while (false)

/** jdksavdecc_new_array

    A define which simulates c++ new [] operator, except it accepts an
    allocator to allocate from.
*/

#define jdksavdecc_new_array(ALLOCATOR, T, COUNT)                              \
    (T *)((ALLOCATOR)->alloc((ALLOCATOR), (int32_t)sizeof(T), (int32_t)(COUNT)))

/** jdksavdecc_round_size

    Calculate size in bytes rounded up to the nearest 32bit word size.
*/
#define jdksavdecc_round_size(VALUE)                                           \
    (((VALUE) + (uint32_t)(sizeof(uint32_t)) - 1) &                            \
     (uint32_t) ~(sizeof(uint32_t) - 1))

/** jdksavdecc_allocator

    The jdksavdecc_allocator implements a
    simple growing stack of allocations within a fixed buffer size
*/
struct jdksavdecc_allocator {
    /**
       Destroy the allocator.
    */

    void (*destroy)(struct jdksavdecc_allocator *self);

    /**
       Allocate memory from the allocator.
    */
    void *(*alloc)(struct jdksavdecc_allocator *self, int32_t length,
                   int32_t count);

    void (*free)(struct jdksavdecc_allocator *self, const void *ptr);
};

struct jdksavdecc_simple_allocator {
    struct jdksavdecc_allocator base;
    /** pointer to the raw memory pool to allocate from */
    void *raw_memory;

    /** length of the raw memory pool */
    int32_t raw_memory_length;

    /** the current position in the raw memory pool */
    int32_t current_position;
};

/**
   jdksavdecc_simple_allocator_init
   Initialize an jdksavdecc_allocator_t object, attaching it to a block of
   memory
   with a specific size in bytes

   @param self object to initialize
   @param raw_memory pointer to raw memory
   @param raw_memory_length size of raw memory in bytes
   @returns pointer initialized object
*/

struct jdksavdecc_allocator *
    jdksavdecc_simple_allocator_init(struct jdksavdecc_simple_allocator *self,
                                     void *raw_memory,
                                     int32_t raw_memory_length);

void
    jdksavdecc_simple_allocator_reset(struct jdksavdecc_simple_allocator *self);

/** jdksavdecc_simple_allocator_destroy
    simple allocators are allocated from raw memory and have no need to
    do anything to destroy the pool of memory
*/

void jdksavdecc_simple_allocator_destroy(struct jdksavdecc_allocator *self);

/** jdksavdecc_simple_allocator_alloc

    allocate some memory from the allocator's memory pool.

    @param self allocator to allocate from
    @param length in bytes of object to allocate
    @param count count of objects to allocate
    @returns memory void * or NULL if error
*/
void *jdksavdecc_simple_allocator_alloc(struct jdksavdecc_allocator *self,
                                        int32_t length, int32_t count);

void jdksavdecc_simple_allocator_free(struct jdksavdecc_allocator *self,
                                      const void *ptr);

#if JDKSAVDECC_ENABLE_MALLOC

struct jdksavdecc_malloc_allocator {
    struct jdksavdecc_allocator base;
};

/**
   jdksavdecc_malloc_allocator_init
   simple wrapper of malloc/free

   @param self object to initialize
   @returns pointer initialized object
*/

struct jdksavdecc_allocator *
    jdksavdecc_malloc_allocator_init(struct jdksavdecc_malloc_allocator *self);

/** jdksavdecc_malloc_allocator_destroy
    simple allocators are allocated from raw memory and have no need to
    do anything to destroy the pool of memory
*/

void jdksavdecc_malloc_allocator_destroy(struct jdksavdecc_allocator *self);

void *jdksavdecc_malloc_allocator_alloc(struct jdksavdecc_allocator *self,
                                        int32_t length, int32_t count);

void *jdksavdecc_malloc_allocator_realloc(struct jdksavdecc_allocator *self,
                                          const void *orig_ptr, int32_t length,
                                          int32_t count);

void jdksavdecc_malloc_allocator_free(struct jdksavdecc_allocator *self,
                                      const void *ptr);

#endif

/*@}*/

#ifdef __cplusplus
}
#endif
