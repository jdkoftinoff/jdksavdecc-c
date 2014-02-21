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
#include "jdksavdecc_entity_manager.h"

const char *jdksavdecc_inflight_file = __FILE__;

#ifdef TODO

void jdksavdecc_inflight_command_info_init(
        struct jdksavdecc_inflight_command_info *self) {
}

int jdksavdecc_inflight_command_info_compare(
        void const *lhs,
        void const *rhs ) {
}


void jdksavdecc_inflight_commands_init( struct jdksavdecc_inflight_commands *self ) {
}


bool jdksacdecc_entity_manager_inflight_commands_full( struct jdksavdecc_inflight_commands *self ) {
}


void jdksavdecc_inflight_commands_sort(
        struct jdksavdecc_inflight_commands *self ) {
}


bool jdksavdecc_inflight_commands_add(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_inflight_command_info const *info ) {
}


int jdksavdecc_inflight_commands_find(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        uint16_t sequence_id ) {
}


void jdksavdecc_inflight_commands_tick(
        struct jdksavdecc_inflight_commands *self,
        jdksavdecc_timestamp_in_milliseconds cur_time,
        void *context ) {
}


void jdksavdecc_inflight_commands_remove(
        struct jdksavdecc_inflight_commands *self,
        int num ) {
}


void jdksavdecc_inflight_commands_remove_target(
        struct jdksavdecc_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id ) {
}


#endif
