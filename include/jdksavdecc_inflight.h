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
#include "jdksavdecc_pdu.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup inflight Inflight message handling */
/*@{*/

#ifndef JDKSAVDECC_INFLIGHT_MAX_COMMANDS
#define JDKSAVDECC_INFLIGHT_MAX_COMMANDS (8)
#endif


struct jdksavdecc_inflight_command_info {
    /// This is the timestamp of the last command that we sent to another entity
    jdksavdecc_timestamp_in_milliseconds sent_time;

    /// This is the number of milliseconds before the message times out
    uint16_t time_out_in_ms;

    /// This is the entity id that was the target of the last command that we sent
    struct jdksavdecc_eui64 target_entity_id;

    /// This is the command_type of the last command that we sent to another entity
    uint16_t command_type;

    /// This is the sequence id of the command that was sent
    uint16_t sequence_id;

    /// This is the pointer to the function to call when the command timed out
    void (*timed_out)(
            struct jdksavdecc_inflight_command_info *self,
            void *context );
};

void jdksavdecc_inflight_command_info_init(
        struct jdksavdecc_inflight_command_info *self);

int jdksavdecc_inflight_command_info_compare(
        void const *lhs,
        void const *rhs );

struct jdksavdecc_inflight_commands {
    int num_inflight_commands;
    struct jdksavdecc_inflight_command_info inflight_commands[ JDKSAVDECC_INFLIGHT_MAX_COMMANDS ];
};

void jdksavdecc_inflight_commands_init( struct jdksavdecc_inflight_commands *self );

bool jdksacdecc_entity_manager_inflight_commands_full( struct jdksavdecc_inflight_commands *self );

void jdksavdecc_inflight_commands_sort(
        struct jdksavdecc_inflight_commands *self );

bool jdksavdecc_inflight_commands_add(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_inflight_command_info const *info );

int jdksavdecc_inflight_commands_find(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        uint16_t sequence_id );

void jdksavdecc_inflight_commands_tick(
        struct jdksavdecc_inflight_commands *self,
        jdksavdecc_timestamp_in_milliseconds cur_time,
        void *context );

void jdksavdecc_inflight_commands_remove(
        struct jdksavdecc_inflight_commands *self,
        int num );

void jdksavdecc_inflight_commands_remove_target(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id );



/*@}*/

#ifdef __cplusplus
}
#endif

