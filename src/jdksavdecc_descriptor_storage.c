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
#include "jdksavdecc_descriptor_storage.h"

int
jdksavdecc_descriptor_storage_init(struct jdksavdecc_descriptor_storage *self,
                                   void const *user_ptr,
                                   uint32_t storage_length) {
    self->destroy = jdksavdecc_descriptor_storage_destroy;
    self->read_data = 0;
    self->user_ptr = user_ptr;
    self->storage_length = storage_length;
    return 0;
}

void jdksavdecc_descriptor_storage_destroy(
    struct jdksavdecc_descriptor_storage *self) {
    (void)self;
}

int jdksavdecc_descriptor_storage_buffer_init(
    struct jdksavdecc_descriptor_storage *self, void const *user_ptr,
    uint32_t storage_length) {
    self->destroy = jdksavdecc_descriptor_storage_buffer_destroy;
    self->read_data = jdksavdecc_descriptor_storage_buffer_read_data;
    self->user_ptr = user_ptr;
    self->storage_length = storage_length;
    return 0;
}

uint32_t jdksavdecc_descriptor_storage_buffer_read_data(
    struct jdksavdecc_descriptor_storage *self, void *buffer, uint32_t offset,
    uint32_t length) {
    uint32_t r = 0;
    if (self->storage_length >= offset + length) {
        r = length;
        memcpy(buffer, (uint8_t *)(self->user_ptr) + offset, length);
    }
    return r;
}

void jdksavdecc_descriptor_storage_buffer_destroy(
    struct jdksavdecc_descriptor_storage *self) {
    jdksavdecc_descriptor_storage_destroy(self);
}

#ifdef FOPEN_MAX

int jdksavdecc_descriptor_storage_file_init(
    struct jdksavdecc_descriptor_storage *self, const char *file_name) {
    int r = -1;
    FILE *f = fopen(file_name, "rb");
    self->destroy = jdksavdecc_descriptor_storage_file_destroy;
    self->read_data = jdksavdecc_descriptor_storage_file_read_data;
    if (f) {
        self->user_ptr = (void *)f;
        /* \TODO Check header */
        if (fseek(f, 0, SEEK_END) == 0) {
            self->storage_length = ftell(f);
            r = 0;
        } else {
            fclose(f);
        }
    }
    return r;
}

uint32_t jdksavdecc_descriptor_storage_file_read_data(
    struct jdksavdecc_descriptor_storage *self, void *buffer, uint32_t offset,
    uint32_t length) {
    uint32_t r = 0;
    if (self->user_ptr) {
        FILE *f = (FILE *)self->user_ptr;

        if (self->storage_length >= offset + length) {
            if (fseek(f, SEEK_SET, (int)offset) == 0) {
                if (fread(buffer, 1, length, f) == length) {
                    r = length;
                }
            }
        }
    }
    return r;
}

void jdksavdecc_descriptor_storage_file_destroy(
    struct jdksavdecc_descriptor_storage *self) {
    if (self->user_ptr) {
        FILE *f = (FILE *)self->user_ptr;
        fclose(f);
    }
}

#endif

int jdksavdecc_descriptor_storage_read_header(
    struct jdksavdecc_descriptor_storage *self);

uint16_t jdksavdecc_descriptor_storage_get_configuration_count(
    struct jdksavdecc_descriptor_storage *self);

uint16_t jdksavdecc_descriptor_storage_get_configuration_descriptor_list_count(
    struct jdksavdecc_descriptor_storage *self, uint16_t configuration_number);

uint16_t jdksavdecc_descriptor_storage_read_descriptor(
    struct jdksavdecc_descriptor_storage *self, uint16_t configuration_number,
    uint16_t descriptor_type, uint16_t descriptor_index,
    uint16_t *result_buffer, uint16_t result_buffer_len);

int jdksavdecc_descriptor_storage_read_symbol(
    struct jdksavdecc_descriptor_storage *self, uint16_t configuration_number,
    uint16_t descriptor_type, uint16_t descriptor_index,
    uint32_t *result_symbol);
