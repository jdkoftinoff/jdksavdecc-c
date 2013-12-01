
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
            jdksavdecc_frame_list_destroy( &self->acmp_frames );
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
    for( int i=0; i<16; ++i ) {
        const char *message_type_name=
            jdksavdecc_get_name_for_uint16_value(
                jdksavdecc_acmpdu_print_message_type,
                self->current_state.header.message_type);
        if( message_type_name ) {
            log_info(
                JDKSAVDECC_SUBSYSTEM_DIAGNOSTICS,
                "%s count: %d",
                message_type_name,
                self->message_type_histogram[i]);
            log_info(
                JDKSAVDECC_SUBSYSTEM_DIAGNOSTICS,
                "%s last time: %" PRIi64,
                message_type_name,
                self->message_type_timestamp[i]);
            log_info(
                JDKSAVDECC_SUBSYSTEM_DIAGNOSTICS,
                "%s last status: %s",
                message_type_name,
                jdksavdecc_get_name_for_uint16_value(
                    jdksavdecc_acmpdu_print_status,
                    self->message_type_status[i]
                    ));
        }
    }
}

void jdksavdecc_acmp_conversation_destroy(
    struct jdksavdecc_acmp_conversation *self
    )
{
    jdksavdecc_frame_list_destroy( &self->acmp_frames );
}


int jdksavdecc_acmp_conversation_list_init(
        struct jdksavdecc_acmp_conversation_list *self,
        struct jdksavdecc_allocator *allocator
        ) {
    self->allocator = allocator;
    self->first=0;
    self->last=0;
    return 0;
}

void jdksavdecc_acmp_conversation_list_destroy(struct jdksavdecc_acmp_conversation_list *self) {
    struct jdksavdecc_acmp_conversation_list_item *item = self->last;
    while( item ) {
        jdksavdecc_acmp_conversation_destroy(&item->conversation);
        item = item->prev;
    }
    self->first = 0;
    self->last = 0;
}

struct jdksavdecc_acmp_conversation_list_item *jdksavdecc_acmp_conversation_list_find(struct jdksavdecc_acmp_conversation_list *self,
                                                                                      struct jdksavdecc_eui64 *talker_entity_id,
                                                                                      uint16_t talker_unique_id,
                                                                                      struct jdksavdecc_eui64 *listener_entity_id,
                                                                                      uint16_t listener_unique_id) {
    // Start searching from the last item in the linked list, as usually the messages are relating to recent connections
    struct jdksavdecc_acmp_conversation_list_item *item = self->last;
    while( item ) {
        if( jdksavdecc_eui64_compare( listener_entity_id, &item->conversation.listener_entity_id )==0 ) {
            if( listener_unique_id == item->conversation.listener_unique_id ) {
                if( jdksavdecc_eui64_compare( talker_entity_id, &item->conversation.talker_entity_id )==0 ) {
                    if( talker_unique_id == item->conversation.talker_unique_id ) {
                        // found it!
                        break;
                    }
                }
            }
        }
        item = item->prev;
    }
    return item;
}

struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_find_by_frame(struct jdksavdecc_acmp_conversation_list *self,
                                                struct jdksavdecc_frame const *connect_rx_command_frame) {
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;
    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t listener_unique_id;
    talker_entity_id = jdksavdecc_acmpdu_get_talker_entity_id(connect_rx_command_frame->payload,0);
    talker_unique_id = jdksavdecc_acmpdu_get_talker_unique_id(connect_rx_command_frame->payload,0);
    listener_entity_id = jdksavdecc_acmpdu_get_listener_entity_id(connect_rx_command_frame->payload,0);
    listener_unique_id = jdksavdecc_acmpdu_get_listener_unique_id(connect_rx_command_frame->payload,0);
    return jdksavdecc_acmp_conversation_list_find(
                self,
                &talker_entity_id,
                talker_unique_id,
                &listener_entity_id,
                listener_unique_id
                );
}

struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_create_or_add(struct jdksavdecc_acmp_conversation_list *self,
                                                struct jdksavdecc_frame const *initial_connect_rx_command_frame) {
    struct jdksavdecc_acmp_conversation_list_item *item = 0;
    item = jdksavdecc_acmp_conversation_list_find_by_frame( self, initial_connect_rx_command_frame );
    if( !item ) {
        item=jdksavdecc_new(self->allocator,struct jdksavdecc_acmp_conversation_list_item);
        if( item ) {
            jdksavdecc_acmp_conversation_init(
                        &item->conversation,
                        self->allocator,
                        initial_connect_rx_command_frame
                        );

            item->next =0;
            item->prev =self->last;
            self->last=item;
        }
    }
    if( item ) {
        // TODO: track message statistics
    }
    return item;
}

void jdksavdecc_acmp_conversation_tester_init(struct jdksavdecc_acmp_conversation_tester *self,
                                              struct jdksavdecc_allocator *allocator,
                                              struct jdksavdecc_frame_sender *sender, uint32_t tag, void *additional) {

    jdksavdecc_state_machine_init( &self->base, sender, tag, additional );

    self->allocator = allocator;
    self->base.destroy = jdksavdecc_acmp_conversation_tester_destroy;
    self->base.tick = jdksavdecc_acmp_conversation_tester_tick;
    self->base.rx_frame = jdksavdecc_acmp_conversation_tester_rx_frame;
    jdksavdecc_acmp_conversation_list_init( &self->conversations, allocator );

}

void jdksavdecc_acmp_conversation_tester_destroy(struct jdksavdecc_state_machine *self_) {
    struct jdksavdecc_acmp_conversation_tester *self = (struct jdksavdecc_acmp_conversation_tester *)self_;
    jdksavdecc_acmp_conversation_list_destroy( &self->conversations );
}

int jdksavdecc_acmp_conversation_tester_tick(struct jdksavdecc_state_machine *self_,
                                              jdksavdecc_timestamp_in_microseconds timestamp) {

    // Do the normal tick work
    int r=jdksavdecc_state_machine_tick( self_, timestamp );
    
    // if we are not exiting, we may have additional work to do
    if( r==0 ) {
        struct jdksavdecc_acmp_conversation_tester *self = (struct jdksavdecc_acmp_conversation_tester *)self_;
        
        // Were we requested to dump all of the conversations to the logger?
        if( self->do_dump_all ) {
            // Yes, clear the request and do it
            self->do_dump_all = false;
            jdksavdecc_acmp_conversation_tester_dump( self);
        }
    }
    return r;
}

void jdksavdecc_acmp_conversation_tester_dump(struct jdksavdecc_acmp_conversation_tester *self) {
    struct jdksavdecc_acmp_conversation_list_item *item = self->conversations.first;
    while( item ) {
        jdksavdecc_acmp_conversation_log(&item->conversation);
        item = item->next;
    }
}

ssize_t jdksavdecc_acmp_conversation_tester_rx_frame(struct jdksavdecc_state_machine *self_, struct jdksavdecc_frame *rx_frame,
                                                     size_t pos) {
    struct jdksavdecc_acmp_conversation_tester *self = (struct jdksavdecc_acmp_conversation_tester *)self_;
    // assume that the frame is already validated to be a relevant ACMP frame
    
    jdksavdecc_acmp_conversation_list_create_or_add( &self->conversations, rx_frame );
    return rx_frame->length;
}

