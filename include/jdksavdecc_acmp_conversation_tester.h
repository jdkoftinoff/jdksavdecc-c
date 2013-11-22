#pragma once
#ifndef JDKSAVDECC_ACMP_CONVERSATION_TESTER_H
#define JDKSAVDECC_ACMP_CONVERSATION_TESTER_H

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
#include "jdksavdecc_state_machine.h"
#include "jdksavdecc_pdu_dispatch.h"
#include "jdksavdecc_frame_list.h"
#include "jdksavdecc_acmp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup acmp_conversation_tester ACMPDU State Machine conversation tester */
/*@{*/


/// An ACMP Conversation Tracker.
struct jdksavdecc_acmp_conversation
{
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;

    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t listener_unique_id;

    struct jdksavdecc_frame_list acmp_frames;
    
    struct jdksavdecc_acmpdu current_state;
    jdksavdecc_timestamp_in_microseconds current_state_timestamp;
    
    int message_type_histogram[16];
    jdksavdecc_timestamp_in_microseconds message_type_timestamp[16];
};


/// Initiialize an ACMP Conversation tracker
int jdksavdecc_acmp_conversation_init(
    struct jdksavdecc_acmp_conversation *self,
    struct jdksavdecc_frame const * initial_connect_rx_command_frame
    );

/// Update the conversation given the incoming associated acmpdu
void jdksavdecc_acmp_conversation_update(
    struct jdksavdecc_acmp_conversation *self,
    struct jdksavdecc_frame const * acmpdu
    );

/// Log the results of the conversation tracker for this connection
void jdksavdecc_acmp_conversation_log(
    struct jdksavdecc_acmp_conversation *self
    );


struct jdksavdecc_acmp_conversation_list_item;

/// A List of ACMP Conversation Tracker objects
struct jdksavdecc_acmp_conversation_list
{
    struct jdksavdecc_acmp_conversation_list_item *first;
    struct jdksavdecc_acmp_conversation_list_item *last;
};

/// An item in the linked list of ACMP Conversations
struct jdksavdecc_acmp_conversation_list_item
{
    struct jdksavdecc_acmp_conversation_list_item *next;
    struct jdksavdecc_acmp_conversation_list_item *prev;
    struct jdksavdecc_acmp_conversation conversation;
};


/// Initialize an ACMP Conversation object
int jdksavdecc_acmp_conversation_list_init(
    struct jdksavdecc_acmp_conversation *self
    );
    
/// Destroy an ACMP Conversation object
void jdksavdecc_acmp_conversation_list_destroy(
    struct jdksavdecc_acmp_conversation *self
    );

/// Search for a conversation that matches the specified talker_id, unique_id and listener_id and unique_id
struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_find(
    struct jdksavdecc_acmp_conversation *self,
    struct jdksavdecc_eui64 *talker_entity_id,
    uint16_t talker_unique_id,
    struct jdksavdecc_eui64 *listener_entity_id,
    uint16_t listener_unique_id
    );

/// Search for a conversation that matches the specified connect_rx_command frame
struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_find_by_frame(
    struct jdksavdecc_acmp_conversation *self,
    struct jdksavdecc_frame const * connect_rx_command_frame
    );
    
/// given the connect_rx_command frame, either find the associated conversation
/// or create one for it
struct jdksavdecc_acmp_conversation_list_item *
jdksavdecc_acmp_conversation_list_create_or_add(
    struct jdksavdecc_acmp_conversation *self,
    struct jdksavdecc_frame const * initial_connect_rx_command_frame
    );
    
/// state machine that tracks all ACMP conversatations seen on a network
struct jdksavdecc_acmp_conversation_tester
{
    struct jdksavdecc_state_machine base;
    struct jdksavdecc_acmp_conversation_list conversations;
    bool do_dump_all;
};

/// Initialize the ACMP conversation tester
void jdksavdecc_acmp_conversation_tester_init(
        struct jdksavdecc_acmp_conversation_tester *self,
        struct jdksavdecc_frame_sender *sender,
        uint32_t tag,
        void *additional
        );

/// Destroy the ACMP Conversation tester object
void jdksavdecc_acmp_conversation_tester_destroy(
        struct jdksavdecc_state_machine *self
        );

/// Some time elapsed for the ACMP Conversation tester
void jdksavdecc_acmp_conversation_tester_tick(
        struct jdksavdecc_state_machine *self,
        jdksavdecc_timestamp_in_microseconds timestamp
        );

/// Dump the information about all known conversations
void jdksavdecc_acmp_conversation_tester_dump(
        struct jdksavdecc_state_machine *self
        );

/// Receive an ACMPDU and track the associated state
ssize_t jdksavdecc_acmp_conversation_tester_rx_frame(
        struct jdksavdecc_state_machine *self,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        );



/*@}*/
#ifdef __cplusplus
}
#endif

#endif

