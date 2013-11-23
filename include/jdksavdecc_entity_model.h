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
#include "jdksavdecc_pdu.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @todo APS state machine
struct jdksavdecc_entity_model {
    void (*destroy)(struct jdksavdecc_entity_model *self);

    struct jdksavdecc_eui64 (*get_entity_model_id)(
        struct jdksavdecc_entity_model *self);

    uint16_t (*read_descriptor)(struct jdksavdecc_entity_model *self,
                                uint16_t configuration_number,
                                uint16_t descriptor_type,
                                uint16_t descriptor_index,
                                uint8_t *result_buffer,
                                uint16_t result_buffer_len);

    uint16_t (*get_control)(struct jdksavdecc_entity_model *self,
                            uint16_t configuration_number,
                            uint16_t descriptor_index, uint8_t *result_buffer,
                            uint16_t result_buffer_len);

    uint16_t (*set_control)(struct jdksavdecc_entity_model *self,
                            uint16_t configuration_number,
                            uint16_t descriptor_index, uint8_t const *buffer,
                            uint16_t buffer_len);
};

int jdksavdecc_entity_model_init(struct jdksavdecc_entity_model *self);
void jdksavdecc_entity_model_destroy(struct jdksavdecc_entity_model *self);

#ifdef __cplusplus
}
#endif
