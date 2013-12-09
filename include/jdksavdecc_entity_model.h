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
#include "jdksavdecc_allocator.h"
#include "jdksavdecc_pdu.h"
#include "jdksavdecc_descriptor_storage.h"
#include "jdksavdecc_state_machine.h"
#include "jdksavdecc_adp.h"
#include "jdksavdecc_acmp_talker.h"
#include "jdksavdecc_acmp_listener.h"
#include "jdksavdecc_maap_sm.h"

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_entity_model {
    struct jdksavdecc_state_machine base;
    struct jdksavdecc_allocator *allocator;
    uint32_t available_index;
    struct jdksavdecc_eui64 entity_model_id;
    struct jdksavdecc_eui64 entity_id;
    struct jdksavdecc_descriptor_storage *descriptor_storage;
    struct jdksavdecc_acmp_listener_stream_infos listener_stream_infos;
    struct jdksavdecc_acmp_listener_stream_info *lister_streams;
    struct jdksavdecc_acmp_talker_stream_infos talker_stream_infos;
    struct jdksavdecc_acmp_talker_stream_info *talker_streams;
    struct jdksavdecc_acmp_listener_state_machine listener_state_machine;
    struct jdksavdecc_acmp_talker_state_machine_vars talker_state_machine_vars;
    struct jdksavdecc_acmp_talker_state_machine talker_state_machine;
    struct jdksavdecc_maap_state_machine maap_state_machine;

    uint16_t (*form_adpdu_entity_available)(struct jdksavdecc_entity_model *self,
                                            uint16_t avb_interface_index,
                                            struct jdksavdecc_frame *frame);

};

int jdksavdecc_entity_model_init(struct jdksavdecc_entity_model *self,
                                 struct jdksavdecc_frame_sender *frame_sender,
                                 uint32_t tag,
                                 void *additional,
                                 struct jdksavdecc_allocator *allocator,
                                 struct jdksavdecc_eui64 const *entity_model_id,
                                 struct jdksavdecc_eui64 const *entity_id,
                                 struct jdksavdecc_descriptor_storage *descriptor_storage);

void jdksavdecc_entity_model_destroy(struct jdksavdecc_entity_model *self);

ssize_t jdksavdecc_entity_model_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos);

int jdksavdecc_state_machine_tick(struct jdksavdecc_state_machine *self, jdksavdecc_timestamp_in_microseconds timestamp);



#ifdef __cplusplus
}
#endif
