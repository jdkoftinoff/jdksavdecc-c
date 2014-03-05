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
#include "jdksavdecc_descriptor_storage_gen.h"

#ifdef TODO

void
jdksavdecc_descriptor_storage_gen_init(
        struct jdksavdecc_descriptor_storage_gen *self,
        struct jdksavdecc_descriptor_storage_gen_descriptor *descriptor_space,
        uint32_t max_descriptors,
        struct jdksavdecc_descriptor_storage_gen_symbol *symbol_space,
        uint32_t max_symbols ) {
    jdksavdecc_entity_model_init(&self->base);
    self->descriptors = descriptor_space;
    self->num_descriptors = 0;
    self->max_descriptors = max_descriptors;
    self->symbols = symbol_space;
    self->num_symbols = 0;
    self->max_symbols = max_symbols;

    self->base.destroy = jdksavdecc_descriptor_storage_gen_destroy;
    self->base.get_configuration_count = jdksavdecc_descriptor_storage_gen_get_configuration_count;
    self->base.read_descriptor = jdksavdecc_descriptor_storage_gen_read_descriptor;
    self->base.write_descriptor = jdksavdecc_descriptor_storage_gen_write_descriptor;
    self->base.read_localized_string = jdksavdecc_descriptor_storage_gen_read_localized_string;
    self->add_descriptor = jdksavdecc_descriptor_storage_gen_add_descriptor;
    self->find_descriptor = jdksavdecc_descriptor_storage_gen_find_descriptor;
    self->add_symbol = jdksavdecc_descriptor_storage_gen_add_symbol;
    self->sort_descriptors = jdksavdecc_descriptor_storage_gen_sort_descriptors;
    self->sort_symbols = jdksavdecc_descriptor_storage_gen_sort_symbols;
    self->find_symbol = jdksavdecc_descriptor_storage_gen_find_symbol;
}

void jdksavdecc_descriptor_storage_gen_destroy(struct jdksavdecc_entity_model *self) {
    jdksavdecc_entity_model_destroy(self);
}


/// Read the count of configurations in the storage object
uint16_t jdksavdecc_descriptor_storage_gen_get_configuration_count(struct jdksavdecc_entity_model *self_) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    /* TODO: */
    (void)self;
    return 0;
}

uint16_t jdksavdecc_descriptor_storage_gen_read_descriptor(
        struct jdksavdecc_entity_model *self_,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint16_t *result_buffer,
        uint16_t result_buffer_len) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    (void)result_buffer;
    (void)result_buffer_len;

    return 0;
}


uint16_t jdksavdecc_descriptor_storage_gen_write_descriptor(
        struct jdksavdecc_entity_model *self_,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint16_t const *descriptor_data,
        uint16_t descriptor_data_len) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    (void)descriptor_data;
    (void)descriptor_data_len;

    return 0;
}


uint16_t jdksavdecc_descriptor_storage_gen_read_localized_string(
        struct jdksavdecc_entity_model *self_,
        uint16_t configuration_index,
        uint16_t locale_id,
        uint16_t localized_string_id,
        struct jdksavdecc_string *result) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)locale_id;
    (void)localized_string_id;
    (void)result;
    return 0;
}


bool jdksavdecc_descriptor_storage_gen_add_descriptor(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t const *descriptor_data,
        uint16_t descriptor_len) {
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    (void)descriptor_data;
    (void)descriptor_len;
    return false;
}


struct jdksavdecc_descriptor_storage_gen_descriptor *jdksavdecc_descriptor_storage_gen_find_descriptor(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index ) {
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    return 0;
}

bool jdksavdecc_descriptor_storage_gen_add_symbol(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t const *descriptor_data,
        uint16_t descriptor_len) {
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    (void)descriptor_data;
    (void)descriptor_len;
    return false;
}

void jdksavdecc_descriptor_storage_gen_sort_descriptors(struct jdksavdecc_descriptor_storage_gen *self) {
    /* TODO: */
    (void)self;
}

void jdksavdecc_descriptor_storage_gen_sort_symbols(struct jdksavdecc_descriptor_storage_gen *self) {
    /* TODO: */
    (void)self;
}

struct jdksavdecc_descriptor_storage_gen_symbol *jdksavdecc_descriptor_storage_gen_find_symbol(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index ) {
    /* TODO: */
    (void)self;
    (void)configuration_index;
    (void)descriptor_type;
    (void)descriptor_index;
    return 0;
}


int jdksavdecc_descriptor_storage_gen_export_binary(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *fname) {
    /* TODO: */
    (void)self;
    (void)fname;
    return 0;
}

int jdksavdecc_descriptor_storage_gen_export_c(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *symbol_prefix,
        const char *first_include_for_h,
        const char *first_include_for_c,
        const char *prefix_h,
        const char *prefix_c,
        const char *fname_c,
        const char *fname_h) {
    /* TODO: */
    (void)self;
    (void)symbol_prefix;
    (void)first_include_for_c;
    (void)first_include_for_h;
    (void)prefix_h;
    (void)prefix_c;
    (void)fname_c;
    (void)fname_h;
    return 0;
}

#endif

