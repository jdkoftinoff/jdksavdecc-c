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
    /* @TODO */
    jdksavdecc_entity_model_init(&self->base);
    self->base.destroy = jdksavdecc_descriptor_storage_gen_destroy;
}

void jdksavdecc_descriptor_storage_gen_destroy(struct jdksavdecc_entity_model *self) {
    jdksavdecc_entity_model_destroy(self);
}

void jdksavdecc_descriptor_storage_gen_finish(struct jdksavdecc_descriptor_storage_gen *self) {
    /* @TODO */
    (void)self;
}

/// Read the count of configurations in the storage object
uint16_t jdksavdecc_descriptor_storage_gen_get_configuration_count(struct jdksavdecc_entity_model *self_) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    /* @TODO */
    return 0;
}

/// Read a descriptor for the specified configuration, descriptor_type and
/// descriptor_index into result buffer which has a length of
/// result_buffer_len.
/// Returns the length of the descriptor, or 0 if no descriptor.
uint16_t jdksavdecc_descriptor_storage_gen_read_descriptor(
        struct jdksavdecc_entity_model *self_,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint16_t *result_buffer,
        uint16_t result_buffer_len) {
    struct jdksavdecc_descriptor_storage_gen *self = (struct jdksavdecc_descriptor_storage_gen *)self_;
    /* @TODO */
    return 0;
}



bool jdksavdecc_descriptor_storage_symbols_add(
        struct jdksavdecc_descriptor_storage_symbols *self,
        bool sort,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type,
        jdksavdecc_descriptor_storage_symbol_dispatch_proc handler ) {
    bool r=false;
    return r;
}

jdksavdecc_descriptor_storage_symbol_dispatch_proc jdksavdecc_descriptor_storage_find_symbol(
        struct jdksavdecc_descriptor_storage_symbols *self,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type ) {
    jdksavdecc_descriptor_storage_symbol_dispatch_proc r=0;
    /* @TODO */
    (void)self;
    return 0;
}

int jdksavdecc_descriptor_storage_gen_export_binary(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *fname) {
    /* @TODO */
    (void)self;
    return 0;
}

int jdksavdecc_descriptor_storage_gen_export_c(
        struct jdksavdecc_descriptor_storage_gen *self,
        const char *prefix_h,
        const char *prefix_c,
        const char *fname_c,
        const char *fname_h) {
    /* @TODO */
    (void)self;
    return 0;
}

#endif

