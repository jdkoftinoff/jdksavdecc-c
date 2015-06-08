#pragma once

/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
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

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup entity model Entity Model */
/**@{*/

struct jdksavdecc_entity_model
{
    /** Destroy the object */
    void ( *destroy )( struct jdksavdecc_entity_model *self );

    void *additional_data;
    int additional_tag;

    /** Read the count of configurations */
    uint16_t ( *get_configuration_count )( struct jdksavdecc_entity_model *self );

    /**
    Read a descriptor for the specified configuration, descriptor_type and
    descriptor_index into result buffer which has a length of
    result_buffer_len.
    Returns the length of the descriptor, or 0 if no descriptor.
    */
    uint16_t ( *read_descriptor )( struct jdksavdecc_entity_model *self,
                                   uint16_t configuration_index,
                                   uint16_t descriptor_type,
                                   uint16_t descriptor_index,
                                   uint8_t *result_buffer,
                                   uint16_t result_buffer_len );

    /**
    Write the descriptor data for the specified configuration, descriptor_type and
    descriptor_index from the descriptor_data with the descriptor_data_length
    Returns the length of the data written, or 0 if not possible
    */
    uint16_t ( *write_descriptor )( struct jdksavdecc_entity_model *self,
                                    uint16_t configuration_index,
                                    uint16_t descriptor_type,
                                    uint16_t descriptor_index,
                                    uint8_t const *descriptor_data,
                                    uint16_t descriptor_data_length );

    uint16_t ( *read_localized_string )( struct jdksavdecc_entity_model *self,
                                         uint16_t configuration_index,
                                         uint16_t locale_id,
                                         uint16_t localized_string_id,
                                         struct jdksavdecc_string *result );

    /**
    Read a symbol for the specified configuration, descriptor_type and
    descriptor_index. Returns true on success
    */
    bool ( *read_symbol )( struct jdksavdecc_entity_model *self,
                           uint16_t configuration_number,
                           uint16_t descriptor_type,
                           uint16_t descriptor_index,
                           uint32_t *result_symbol );
};

void jdksavdecc_entity_model_destroy( struct jdksavdecc_entity_model *self );

uint16_t jdksavdecc_entity_model_read_descriptor( struct jdksavdecc_entity_model *self,
                                                  uint16_t configuration_index,
                                                  uint16_t descriptor_type,
                                                  uint16_t descriptor_index,
                                                  uint8_t *result_buffer,
                                                  uint16_t result_buffer_len );

uint16_t jdksavdecc_entity_model_write_descriptor( struct jdksavdecc_entity_model *self,
                                                   uint16_t configuration_index,
                                                   uint16_t descriptor_type,
                                                   uint16_t descriptor_index,
                                                   uint8_t const *descriptor_data,
                                                   uint16_t descriptor_data_length );

uint16_t jdksavdecc_entity_model_read_localized_string( struct jdksavdecc_entity_model *self,
                                                        uint16_t configuration_index,
                                                        uint16_t locale_id,
                                                        uint16_t localized_string_id,
                                                        struct jdksavdecc_string *result );


/**
 * @brief jdksavdecc_entity_model_read_symbol
 * Read a symbol for the specified configuration, descriptor_type and
 * descriptor_index. Returns true on success
 * @param self
 * @param configuration_number
 * @param descriptor_type
 * @param descriptor_index
 * @param result_symbol
 * @return
 */
bool jdksavdecc_entity_model_read_symbol( struct jdksavdecc_entity_model *self,
                                          uint16_t configuration_number,
                                          uint16_t descriptor_type,
                                          uint16_t descriptor_index,
                                          uint32_t *result_symbol );

static inline void jdksavdecc_entity_model_init( struct jdksavdecc_entity_model *self )
{
    self->destroy = jdksavdecc_entity_model_destroy;
    self->additional_data = 0;
    self->additional_tag = 0;
    self->get_configuration_count = 0;
    self->read_descriptor = jdksavdecc_entity_model_read_descriptor;
    self->write_descriptor = jdksavdecc_entity_model_write_descriptor;
    self->read_symbol = jdksavdecc_entity_model_read_symbol;
}

/*@}*/

#ifdef __cplusplus
}
#endif
