#pragma once
#ifndef JDKSAVDECC_ACMP_TALKER_H
#define JDKSAVDECC_ACMP_TALKER_H

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
#include "jdksavdecc_acmp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup acmp_talker ACMPDU Talker State Machine - Clause 8.2.2.6 */
/*@{*/

struct jdksavdecc_acmp_talker_state_machine_vars
{
    struct jdksavdecc_acmp_talker_stream_infos *talker_stream_infos; /// See Clause 8.2.2.6.1.1
    int rcvd_connect_tx; /// See Clause 8.2.2.6.1.2
    int rcvd_disconnect_tx; /// S See Clause 8.2.2.6.1.3
    int rcvd_get_tx_state; /// See Clause 8.2.2.6.1.4
    int rcvd_get_tx_connection; /// See Clause 8.2.2.6.1.5
};


struct jdksavdecc_acmp_talker_state_machine;

typedef void (*jdksavdecc_acmp_talker_state)(
        struct jdksavdecc_acmp_talker_state_machine *self
        );


/// @todo acmp talker state machine implementation
struct jdksavdecc_acmp_talker_state_machine
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;

    struct jdksavdecc_acmp_talker_state_machine_vars *vars;

    jdksavdecc_acmp_talker_state state;

    void (*tick)( struct jdksavdecc_acmp_talker_state_machine *self, jdksavdecc_time timestamp );
    ssize_t (*rx_frame)( struct jdksavdecc_acmp_talker_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );

    uint8_t (*valid_talker_unique)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            uint16_t talker_unique_id
            );

    uint8_t (*connect_talker)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            struct jdksavdecc_acmp_command_response *respone,
            struct jdksavdecc_acmpdu const *command
            );

    uint8_t (*tx_response)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            uint8_t message_type,
            struct jdksavdecc_acmp_command_response const *response,
            uint8_t error
            );

    uint8_t (*disconnect_talker)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            struct jdksavdecc_acmp_command_response *response,
            struct jdksavdecc_acmpdu const *command
            );

    jdksavdecc_acmp_talker_state waiting;
    jdksavdecc_acmp_talker_state connect;
    jdksavdecc_acmp_talker_state disconnect;
    jdksavdecc_acmp_talker_state get_state;
    jdksavdecc_acmp_talker_state get_connection;
};

void jdksavdecc_acmp_talker_state_machine_init(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

void jdksavdecc_acmp_talker_state_machine_destroy(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.2.1
uint8_t jdksavdecc_acmp_talker_state_machine_valid_talker_unique(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint16_t talker_unique_id
        );

/// See Clause 8.2.2.6.2.2
uint8_t jdksavdecc_acmp_talker_state_machine_connect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.3
uint8_t jdksavdecc_acmp_talker_state_machine_tx_response(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint8_t message_type,
        struct jdksavdecc_acmp_command_response const *respone,
        uint8_t error
        );

/// See Clause 8.2.2.6.2.4
uint8_t jdksavdecc_aem_talker_state_machine_disconnect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.5
uint8_t jdksavdecc_aem_talker_state_machine_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.6
void jdksavdecc_aem_talker_state_machine_state_waiting(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_aem_talker_state_machine_state_connect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_aem_talker_state_machine_state_disconnect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_aem_talker_state_machine_state_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_aem_talker_state_machine_state_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/*@}*/
#ifdef __cplusplus
}
#endif

#endif


