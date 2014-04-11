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
#include "jdksavdecc_aem_descriptor.h"
#include "jdksavdecc_descriptor_storage.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup descriptor_storage Descriptor Storage
*/
/*@{*/

/** \addtogroup descriptor_storage_gen Descriptor Storage Generator
 */
/*@{*/

struct jdksavdecc_descriptor_storage_gen_descriptor {
    uint16_t configuration_index;
    uint16_t descriptor_type;
    uint16_t descriptor_index;
    struct jdksavdecc_descriptor descriptor_data;
    uint16_t descriptor_len;
};

struct jdksavdecc_descriptor_storage_gen_symbol {
    uint16_t configuration_index;
    uint16_t descriptor_type;
    uint16_t descriptor_index;
    uint32_t symbol;
};

struct jdksavdecc_descriptor_storage_gen {
    struct jdksavdecc_entity_model base;

    struct jdksavdecc_descriptor_storage_header *header;
    struct jdksavdecc_descriptor_storage_gen_descriptor *descriptors;
    uint32_t num_descriptors;
    uint32_t max_descriptors;
    struct jdksavdecc_descriptor_storage_gen_symbol *symbols;
    uint32_t num_symbols;
    uint32_t max_symbols;

    bool (*add_descriptor)(
            struct jdksavdecc_descriptor_storage_gen *self,
            uint16_t configuration_index,
            uint16_t descriptor_type,
            uint16_t descriptor_index,
            uint8_t const *descriptor_data,
            uint16_t descriptor_len);

    struct jdksavdecc_descriptor_storage_gen_descriptor *(*find_descriptor)(
            struct jdksavdecc_descriptor_storage_gen *self,
            uint16_t configuration_index,
            uint16_t descriptor_type,
            uint16_t descriptor_index );

    bool (*add_symbol)(
            struct jdksavdecc_descriptor_storage_gen *self,
            uint16_t configuration_index,
            uint16_t descriptor_type,
            uint16_t descriptor_index,
            uint8_t const *descriptor_data,
            uint16_t descriptor_len);

    void (*sort_descriptors)(struct jdksavdecc_descriptor_storage_gen *self);
    void (*sort_symbols)(struct jdksavdecc_descriptor_storage_gen *self);

    struct jdksavdecc_descriptor_storage_gen_symbol *(*find_symbol)(
            struct jdksavdecc_descriptor_storage_gen *self,
            uint16_t configuration_index,
            uint16_t descriptor_type,
            uint16_t descriptor_index );
};

void
jdksavdecc_descriptor_storage_gen_init(
        struct jdksavdecc_descriptor_storage_gen *self,
        struct jdksavdecc_descriptor_storage_gen_descriptor *descriptor_space,
        uint32_t max_descriptors,
        struct jdksavdecc_descriptor_storage_gen_symbol *symbol_space,
        uint32_t max_symbols
        );

void jdksavdecc_descriptor_storage_gen_destroy(struct jdksavdecc_entity_model *self);

/// Read the count of configurations
uint16_t jdksavdecc_descriptor_storage_gen_get_configuration_count(struct jdksavdecc_entity_model *self);

/// Read a descriptor for the specified configuration, descriptor_type and
/// descriptor_index into result buffer which has a length of
/// result_buffer_len.
/// Returns the length of the descriptor, or 0 if no descriptor.
uint16_t jdksavdecc_descriptor_storage_gen_read_descriptor(
        struct jdksavdecc_entity_model *self,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t *result_buffer,
        uint16_t result_buffer_len);

/// Write the descriptor data for the specified configuration, descriptor_type and
/// descriptor_index from the descriptor_data with the descriptor_data_length
/// Returns the length of the data written, or 0 if not possible
uint16_t jdksavdecc_descriptor_storage_gen_write_descriptor(
        struct jdksavdecc_entity_model *self,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t const *descriptor_data,
        uint16_t descriptor_data_length);

uint16_t jdksavdecc_descriptor_storage_gen_read_localized_string(
        struct jdksavdecc_entity_model *self,
        uint16_t configuration_index,
        uint16_t locale_id,
        uint16_t localized_string_id,
        struct jdksavdecc_string *result);

bool jdksavdecc_descriptor_storage_gen_add_descriptor(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t const *descriptor_data,
        uint16_t descriptor_len);

struct jdksavdecc_descriptor_storage_gen_descriptor *jdksavdecc_descriptor_storage_gen_find_descriptor(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index );

bool jdksavdecc_descriptor_storage_gen_add_symbol(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t const *descriptor_data,
        uint16_t descriptor_len);

void jdksavdecc_descriptor_storage_gen_sort_descriptors(struct jdksavdecc_descriptor_storage_gen *self);

void jdksavdecc_descriptor_storage_gen_sort_symbols(struct jdksavdecc_descriptor_storage_gen *self);

struct jdksavdecc_descriptor_storage_gen_symbol *jdksavdecc_descriptor_storage_gen_find_symbol(
        struct jdksavdecc_descriptor_storage_gen *self,
        uint16_t configuration_index,
        uint16_t descriptor_type,
        uint16_t descriptor_index );


int jdksavdecc_descriptor_storage_gen_export_binary(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *fname);

int jdksavdecc_descriptor_storage_gen_export_c(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *symbol_prefix,
        const char *first_include_for_h,
        const char *first_include_for_c,
        const char *prefix_h,
        const char *prefix_c,
        const char *fname_c,
        const char *fname_h);

/*@}*/

/*@}*/
#ifdef __cplusplus
}
#endif
