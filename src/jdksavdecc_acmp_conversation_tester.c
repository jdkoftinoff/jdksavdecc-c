
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
#include "jdksavdecc_acmp_conversation_tester.h"

#if 0 

int jdksavdecc_acmp_conversation_init(struct jdksavdecc_acmp_conversation *self,
                                      struct jdksavdecc_allocator *allocator,
                                      struct jdksavdecc_frame const *initial_connect_rx_command_frame) {
    int r=-1;
    int i;

    r=jdksavdecc_frame_list_init(&self->acmp_frames,allocator);
    if( r==0 ) {
        if( jdksavdecc_acmpdu_read(&self->current_state,initial_connect_rx_command_frame->payload,0,initial_connect_rx_command_frame->length)>0 ) {
            for( i=0; i<16; ++i ) {
                self->message_type_histogram[i] = 0;
                self->message_type_timestamp[i] = 0;
                self->message_type_status[i] = 0;
            }
            self->current_state_timestamp = initial_connect_rx_command_frame->time;
            self->listener_entity_id = self->current_state.listener_entity_id;
            self->listener_unique_id = self->current_state.listener_unique_id;
            self->talker_entity_id = self->current_state.talker_entity_id;
            self->talker_unique_id = self->current_state.talker_unique_id;
            self->message_type_histogram[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ]++;
            self->message_type_timestamp[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ] = initial_connect_rx_command_frame->time;
            self->message_type_status[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ] = self->current_state.header.status;
            jdksavdecc_frame_list_add( &self->acmp_frames, initial_connect_rx_command_frame, 0 );
        }
        else {
            jdksavdecc_frame_list_destroy( self->acmp_frames );
            r=-1;
        }
    }

    return r;
}

void jdksavdecc_acmp_conversation_update(struct jdksavdecc_acmp_conversation *self, struct jdksavdecc_frame const *acmpdu) {
    if( jdksavdecc_acmpdu_read(&self->current_state,acmpdu->payload,0,acmpdu->length)>0 ) {
        self->message_type_histogram[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ]++;
        self->message_type_timestamp[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ] = acmpdu->time;
        self->message_type_status[ JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND ] = self->current_state.header.status;
        jdksavdecc_frame_list_add(&self->acmp_frames,acmpdu,0);
    }
}

void jdksavdecc_acmp_conversation_log(struct jdksavdecc_acmp_conversation *self) {
    log_info( JDKSAVDECC_SUBSYSTEM_DIAGNOSTICS, "%08x:%04x->%08x:%04x:",
              jdksavdecc_eui64_convert_to_uint64(&self->talker_entity_id),
              self->talker_unique_id,
              jdksavdecc_eui64_convert_to_uint64(&self->listener_entity_id),
              self->listener_unique_id
              );
    log_info( JDKSAVDECC_SUBSYSTEM_DIAGNOSTICS, "" );
}

int jdksavdecc_acmp_conversation_list_init(struct jdksavdecc_acmp_conversation *self) {
    // @todo
    return 0;
}

void jdksavdecc_acmp_conversation_list_destroy(struct jdksavdecc_acmp_conversation *self) {
    // @todo
}

struct jdksavdecc_acmp_conversation_list_item *jdksavdecc_acmp_conversation_list_find(struct jdksavdecc_acmp_conversation *self,
                                                                                      struct jdksavdecc_eui64 *talker_entity_id,
                                                                                      uint16_t talker_unique_id,
                                                                                      struct jdksavdecc_eui64 *listener_entity_id,
                                                                                      uint16_t listener_unique_id) {
    // @todo
    return 0;
}

struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_find_by_frame(struct jdksavdecc_acmp_conversation *self,
                                                struct jdksavdecc_frame const *connect_rx_command_frame) {
    // @todo
    return 0;
}

struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_create_or_add(struct jdksavdecc_acmp_conversation *self,
                                                struct jdksavdecc_frame const *initial_connect_rx_command_frame) {
    return 0;
}

void jdksavdecc_acmp_conversation_tester_init(struct jdksavdecc_acmp_conversation_tester *self,
                                              struct jdksavdecc_frame_sender *sender, uint32_t tag, void *additional) {
    // @todo
}

void jdksavdecc_acmp_conversation_tester_destroy(struct jdksavdecc_state_machine *self) {
    // @todo
}

void jdksavdecc_acmp_conversation_tester_tick(struct jdksavdecc_state_machine *self,
                                              jdksavdecc_timestamp_in_microseconds timestamp) {
    // @todo
}

void jdksavdecc_acmp_conversation_tester_dump(struct jdksavdecc_state_machine *self) {
    // @todo
}

ssize_t jdksavdecc_acmp_conversation_tester_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame,
                                                     size_t pos) {
    // @todo
    return -1;
}

#endif
