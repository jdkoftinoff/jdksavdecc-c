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
#include "jdksavdecc_state_machine.h"
#include "jdksavdecc_acmp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup acmp_talker ACMPDU Talker State Machine - Clause 8.2.2.6 */
/*@{*/

struct jdksavdecc_acmp_talker_state_machine_vars
{
    int do_terminate;
    struct jdksavdecc_eui64 my_id; /// See Clause 8.2.2.3.1
    jdksavdecc_acmp_command_response rcvd_cmd_resp; /// See Clause 8.2.2.3.2
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

typedef void (*jdksavdecc_acmp_talker_state_transition)(
        struct jdksavdecc_acmp_talker_state_machine *self
        );


/// @todo acmp talker state machine implementation
struct jdksavdecc_acmp_talker_state_machine
{
    struct jdksavdecc_state_machine base;
    uint16_t talker_unique_id;

    struct jdksavdecc_acmp_talker_state_machine_vars vars;

    jdksavdecc_acmp_talker_state state;

    uint8_t (*valid_talker_unique)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            uint16_t talker_unique_id
            );

    uint8_t (*tx_response)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            uint8_t message_type,
            jdksavdecc_acmp_command_response const *response,
            uint8_t error
            );

    uint8_t (*connect_talker)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            jdksavdecc_acmp_command_response *response,
            struct jdksavdecc_acmpdu const *command
            );

    uint8_t (*disconnect_talker)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            jdksavdecc_acmp_command_response *response,
            struct jdksavdecc_acmpdu const *command
            );

    uint8_t (*get_state)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            jdksavdecc_acmp_command_response *response,
            struct jdksavdecc_acmpdu const *command
            );

    uint8_t (*get_connection)(
            struct jdksavdecc_acmp_talker_state_machine *self,
            jdksavdecc_acmp_command_response *response,
            struct jdksavdecc_acmpdu const *command
            );

    jdksavdecc_acmp_talker_state_transition goto_waiting;
    jdksavdecc_acmp_talker_state state_waiting;

    jdksavdecc_acmp_talker_state_transition goto_connect;
    jdksavdecc_acmp_talker_state state_connect;

    jdksavdecc_acmp_talker_state_transition goto_disconnect;
    jdksavdecc_acmp_talker_state state_disconnect;

    jdksavdecc_acmp_talker_state_transition goto_get_state;
    jdksavdecc_acmp_talker_state state_get_state;

    jdksavdecc_acmp_talker_state_transition goto_get_connection;
    jdksavdecc_acmp_talker_state state_get_connection;
};

/// Initialize the ACMP Talker State Machine
///
/// @param self Pointer to acmp_talker_state_machine to initialize
/// @param talker_entity_id Entity ID of the Talker to represent
/// @param talker_stream_infos Pointer to acmp_talker_stream_infos database of talker stream states
/// @param sender Pointer to frame_sender to use to send ACMP frames to
/// @param tag uint32_t general purpose tag value for high level use
/// @param additional void * general purpose pointer for high level use
/// @returns 0 on success
int jdksavdecc_acmp_talker_state_machine_init(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_eui64 talker_entity_id,
        struct jdksavdecc_acmp_talker_stream_infos *talker_stream_infos,
        struct jdksavdecc_frame_sender *sender,
        uint32_t tag,
        void *additional
        );


/// Destroy the state machine. Frees any allocated data
///
/// @param self Pointer to state_machine base class
/// @returns void
void jdksavdecc_acmp_talker_state_machine_destroy(
        struct jdksavdecc_state_machine *self
        );

/// Run the state machine current state
///
/// @param self Pointer to state_machine base class
/// @param timestamp millisecond_time current time
/// @returns void
void jdksavdecc_acmp_talker_state_machine_tick(
        struct jdksavdecc_state_machine *self,
        jdksavdecc_millisecond_time timestamp
        );

/// Tell the state machine that an ethernet frame was received
///
/// @param self Pointer to state_machine base class
/// @param rx_frame The frame that received
/// @param pos The starting position of the message within the frame
/// @returns ssize_t byte position that the message was parsed up to; 0 for none, or -1 for other error
ssize_t jdksavdecc_acmp_talker_state_machine_rx_frame(
        struct jdksavdecc_state_machine *self,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        );

/// Transmit a frame to a network port
///
/// @param self Pointer to state_machine base class
/// @param rx_frame The frame that received
/// @returns void
void jdksavdecc_acmp_talker_state_machine_tx_frame(
        struct jdksavdecc_state_machine *self,
        struct jdksavdecc_frame const *frame
        );

/// Validate that a unique_id for the talker is valid
///
/// See Clause 8.2.2.6.2.1
///
/// @param self Pointer to state_machine base class
/// @param talker_unique_id uint16_t unique_id to be validated
/// @returns ACMP Message status value
uint8_t jdksavdecc_acmp_talker_state_machine_valid_talker_unique(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint16_t talker_unique_id
        );

/// Do the appropriate function in the talker to connect the talker and fill in the appropriate
/// fields in the command_and_response
///
/// See Clause 8.2.2.6.2.2
///
/// @param self Pointer to state_machine base class
/// @param command_and_response the current command that triggered this.
///        The appropriate additional fields will be filled in.
/// @returns ACMP Message status value
uint8_t jdksavdecc_acmp_talker_state_machine_connect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmpdu *command_and_response
        );

/// See Clause 8.2.2.6.2.3
uint8_t jdksavdecc_acmp_talker_state_machine_tx_response(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint8_t message_type,
        jdksavdecc_acmp_command_response const *response,
        uint8_t error
        );

/// See Clause 8.2.2.6.2.4
uint8_t jdksavdecc_acmp_talker_state_machine_disconnect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmpdu *command_and_response
        );

/// See Clause 8.2.2.6.2.5
uint8_t jdksavdecc_acmp_talker_state_machine_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmpdu *command_and_response
        );


/// See Clause 8.2.2.6.2.6
uint8_t jdksavdecc_acmp_talker_state_machine_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_acmpdu *command_and_response
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_waiting(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_waiting(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_connect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_connect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_disconnect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_disconnect(
        struct jdksavdecc_acmp_talker_state_machine *self
        );


/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self
        );

/*@}*/
#ifdef __cplusplus
}
#endif

#endif


