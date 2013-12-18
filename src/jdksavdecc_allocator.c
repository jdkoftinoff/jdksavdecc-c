
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
#include "jdksavdecc_allocator.h"

#if JDKSAVDECC_ENABLE_MICROSUPPORT==0

struct jdksavdecc_allocator *
jdksavdecc_simple_allocator_init(struct jdksavdecc_simple_allocator *self, void *raw_memory, int32_t raw_memory_length) {
    self->raw_memory = raw_memory;
    self->raw_memory_length = raw_memory_length;
    self->current_position = 0;
    self->base.destroy = jdksavdecc_simple_allocator_destroy;
    self->base.alloc = jdksavdecc_simple_allocator_alloc;
    self->base.free = jdksavdecc_simple_allocator_free;
    return &self->base;
}

void jdksavdecc_simple_allocator_destroy(struct jdksavdecc_allocator *self) {
    /* Do Nothing */
    (void)self;
}

void *jdksavdecc_simple_allocator_alloc(struct jdksavdecc_allocator *self_, int32_t length, int32_t count) {
    struct jdksavdecc_simple_allocator *self = (struct jdksavdecc_simple_allocator *)self_;
    void *result = 0;
    /* round up total size to 32 bit alignment */
    int32_t total_size_to_allocate = jdksavdecc_round_size(length * count);
    if ((self->current_position + total_size_to_allocate) <= (self->raw_memory_length)) {
        result = ((char *)self->raw_memory) + self->current_position;
        self->current_position += total_size_to_allocate;
    }
    return result;
}

void *
jdksavdecc_simple_allocator_realloc(struct jdksavdecc_allocator *self_, const void *orig_ptr, int32_t length, int32_t count) {
    void *new_ptr = self_->alloc(self_, length, count);
    if (new_ptr) {
        memcpy(new_ptr, orig_ptr, jdksavdecc_round_size(length * count));
        self_->free(self_, orig_ptr);
    }
    return new_ptr;
}

void jdksavdecc_simple_allocator_free(struct jdksavdecc_allocator *self_, const void *ptr) {
    (void)self_;
    (void)ptr;
    /* Do nothing; the simple allocator never frees */
}

void jdksavdecc_simple_allocator_reset(struct jdksavdecc_simple_allocator *self) { self->current_position = 0; }

#if jdksavdecc_ENABLE_MALLOC

struct jdksavdecc_allocator *jdksavdecc_malloc_allocator_init(struct jdksavdecc_malloc_allocator *self) {
    self->base.destroy = jdksavdecc_malloc_allocator_destroy;
    self->base.alloc = jdksavdecc_malloc_allocator_alloc;
    self->base.realloc = jdksavdecc_malloc_allocator_realloc;
    self->base.free = jdksavdecc_malloc_allocator_free;
    return &self->base;
}

void jdksavdecc_malloc_allocator_destroy(struct jdksavdecc_allocator *self_) {
    (void)self_;
    /* nothing to destroy, we do not keep track of all mallocs and frees */
}

void *jdksavdecc_malloc_allocator_alloc(struct jdksavdecc_allocator *self, int32_t length, int32_t count) {
    (void)self;
    return jdksavdecc_DEFAULT_MALLOC(jdksavdecc_round_size(length * count));
}

void jdksavdecc_malloc_allocator_free(struct jdksavdecc_allocator_s *self, const void *ptr) {
    (void)self;
    free((void *)ptr);
}

#endif
#endif
