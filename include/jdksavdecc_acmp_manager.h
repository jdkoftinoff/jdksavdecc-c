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
#include "jdksavdecc_acmp.h"
#include "jdksavdecc_entity_model.h"
#include "jdksavdecc_entity_manager.h"
#include "jdksavdecc_state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_entity_manager;
struct jdksavdecc_controller_manager;

/** \addtogroup acmp ACMP - Clause 8 */
/*@{*/

/** \addtogroup acmp_talker ACMP Talker State Machine */
/*@{*/

#ifndef JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM
#define JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM (16)
#endif

#ifndef JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_STREAMS
#define JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_STREAMS (8)
#endif


struct jdksavdecc_acmp_talker_context {
    struct jdksavdecc_eui48 destination_mac_address;
    struct jdksavdecc_eui64 stream_id;
    uint16_t talker_unique_id;
    void *context;

    uint16_t connection_count;
    uint16_t flags;
    uint16_t stream_vlan_id;
    struct jdksavdecc_eui64 listener_entity_id[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM];
    uint16_t listener_unique_id[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM];
};

struct jdksavdecc_acmp_talker_manager {
    struct jdksavdecc_state_machine *base;
    struct jdksavdecc_entity_manager *entity_manager;
    uint16_t talker_stream_sources;
    struct jdksavdecc_acmp_talker_context talker_source[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_STREAMS];
};

bool jdksavdecc_acmp_talker_manager_init(
        struct jdksavdecc_acmp_talker_manager *self,
        struct jdksavdecc_entity_manager *entity_manager,
        struct jdksavdecc_frame_sender *frame_sender,
        uint32_t tag,
        void *additional);

/// Destroy any resources that the jdksavdecc_acmp_talker_manager uses
void jdksavdecc_acmp_talker_manager_destroy(struct jdksavdecc_state_machine *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_talker_manager_rx_frame(
    struct jdksavdecc_state_machine *self,
    struct jdksavdecc_frame *rx_frame,
    size_t pos
    );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_talker_manager_tick(
    struct jdksavdecc_state_machine *self,
    jdksavdecc_timestamp_in_microseconds timestamp);

/*@}*/


/** \addtogroup acmp_talker ACMP Listener State Machine */
/*@{*/

#ifndef JDKSAVDECC_ACMP_LISTENER_MANAGER_MAX_STREAMS
#define JDKSAVDECC_ACMP_LISTENER_MANAGER_MAX_STREAMS (8)
#endif

struct jdksavdecc_acmp_listener_context {
    enum {
        JDKSAVDECC_ACMP_LISTENER_STATE_DISABLED=0,
        JDKSAVDECC_ACMP_LISTENER_STATE_DISCONNECTED,
        JDKSAVDECC_ACMP_LISTENER_STATE_FAST_CONNECTION_IN_PROGRESS,
        JDKSAVDECC_ACMP_LISTENER_STATE_CONNECTION_IN_PROGRESS,
        JDKSAVDECC_ACMP_LISTENER_STATE_CONNECTED,
        JDKSAVDECC_ACMP_LISTENER_STATE_DISCONNECTION_IN_PROGRESS,
    } state;

    struct jdksavdecc_eui48 destination_mac_address;
    struct jdksavdecc_eui64 stream_id;
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;
    uint16_t flags;
    uint16_t stream_vlan_id;
    void *context;
};

struct jdksavdecc_acmp_listener_manager {
    struct jdksavdecc_state_machine *base;
    struct jdksavdecc_entity_manager *entity_manager;
    uint16_t listener_stream_sinks;
    struct jdksavdecc_acmp_listener_context listener_sink[JDKSAVDECC_ACMP_LISTENER_MANAGER_MAX_STREAMS];

};


bool jdksavdecc_acmp_listener_manager_init(
        struct jdksavdecc_acmp_listener_manager *self,
        struct jdksavdecc_entity_manager *entity_manager,
        struct jdksavdecc_frame_sender *frame_sender,
        uint32_t tag,
        void *additional);

/// Destroy any resources that the jdksavdecc_acmp_listener_manager uses
void jdksavdecc_acmp_listener_manager_destroy(struct jdksavdecc_state_machine *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_listener_manager_rx_frame(
    struct jdksavdecc_state_machine *self,
    struct jdksavdecc_frame *rx_frame,
    size_t pos
    );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_listener_manager_tick(
    struct jdksavdecc_state_machine *self,
    jdksavdecc_timestamp_in_microseconds timestamp);


/*@}*/


/** \addtogroup acmp_controller ACMP Controller State Machine */
/*@{*/

struct jdksavdecc_acmp_controller_stream_source {
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;
    struct jdksavdecc_eui48 destination_mac_address;
    struct jdksavdecc_eui64 stream_id;
    uint16_t flags;
    uint8_t status;
    uint16_t connection_count;
    uint16_t stream_vlan_id;
};

struct jdksavdecc_acmp_controller_stream_sink {
    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t listener_unique_id;
    uint16_t flags;
    uint8_t status;
};

struct jdksavdecc_acmp_controller_connection {
    enum {
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_DISABLED=0,
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_DISCONNECTED,
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_CONNECTING,
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_CONNECTED,
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_DISCONNECTING,
        JDKSAVDECC_ACMP_CONTROLLER_STREAM_SINK_STATE_ERROR
    } state;
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;
    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t listener_unique_id;
};

struct jdksavdecc_acmp_controller_manager {
    struct jdksavdecc_state_machine *base;
    struct jdksavdecc_controller_manager *controller_manager;
    int max_stream_sources;
    struct jdksavdecc_acmp_controller_stream_source *stream_sources;
    int max_stream_sinks;
    struct jdksavdecc_acmp_controller_stream_source *stream_sinks;
    int max_connections;
    struct jdksavdecc_acmp_controller_connection *stream_connections;
};

bool jdksavdecc_acmp_controller_manager_init(
        struct jdksavdecc_acmp_controller_manager *self,
        struct jdksavdecc_controller_manager *controller_manager,
        struct jdksavdecc_frame_sender *frame_sender,
        uint32_t tag,
        void *additional);

/// Destroy any resources that the jdksavdecc_acmp_controller_manager uses
void jdksavdecc_acmp_controller_manager_destroy(struct jdksavdecc_state_machine *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_controller_manager_rx_frame(
    struct jdksavdecc_state_machine *self,
    struct jdksavdecc_frame *rx_frame,
    size_t pos
    );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_controller_manager_tick(
    struct jdksavdecc_state_machine *self,
    jdksavdecc_timestamp_in_microseconds timestamp);

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif


