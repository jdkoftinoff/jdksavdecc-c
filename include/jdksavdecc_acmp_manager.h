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


/**
 * @brief The jdksavdecc_acmp_talker_stream_source struct
 *
 * Contains the current state of a talker stream source and a context for additional
 * Entity specific information
 */
struct jdksavdecc_acmp_talker_stream_source {
    /**
     * @brief context The context for entity specific info
     */
    void *context;

    /**
     * @brief The stream source's unique id
     */
    uint16_t talker_unique_id;

    /**
     * @brief The stream sources's currently assigned destination_mac_address, or FF:FF:FF:FF:FF:FF if none assigned.
     */
    struct jdksavdecc_eui48 destination_mac_address;

    /**
     * @brief The stream source's currently assigned stream_id, or FF:FF:FF:FF:FF:FF:FF:FF is none assigned
     */
    struct jdksavdecc_eui64 stream_id;

    /**
     * @brief The current talker stream flags, See IEEE Std 1722.1-2013 Clause 8.2.1.17 and JDKSAVDECC_ACMP_FLAG_*
     *
     */
    uint16_t flags;

    /**
     * @brief The currently assigned stream_vlan_id, as assigned by higher layers or MVRP
     */
    uint16_t stream_vlan_id;

    /**
     * @brief The current count of active listeners
     */
    uint16_t connection_count;

    /**
     * @brief The current list the Entity ID's of the listeners that are registered to listen via ACMP
     */
    struct jdksavdecc_eui64 listener_entity_id[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM];

    /**
     * @brief The current list of listener unique ID's for each listener in listener_entity_id
     */
    uint16_t listener_unique_id[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_LISTENERS_PER_STREAM];
};

/**
 * @brief jdksavdecc_acmp_talker_stream_source_init initializes a talker stream source object
 * @param self raw memory to initialize
 * @param context void pointer to entity specific data
 * @param talker_unique_id the talker unique ID of this stream source
 */
void jdksavdecc_acmp_talker_stream_source_init(struct jdksavdecc_acmp_talker_stream_source *self,
        void *context,
        uint16_t talker_unique_id);

/**
 * @brief jdksavdecc_acmp_talker_stream_source_update Update stream ID, destination MAC address and vlan ID.
 * @param self The talker stream source object
 * @param new_stream_id
 * @param new_destination_mac_address
 * @param new_stream_vlan_id
 */
void jdksavdecc_acmp_talker_stream_source_update(
        struct jdksavdecc_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 new_stream_id,
        struct jdksavdecc_eui48 new_destination_mac_address,
        uint16_t new_stream_vlan_id );

/**
 * @brief jdksavdecc_acmp_talker_stream_source_clear_listeners clears the list of active listeners for a stream source
 * @param self
 */
void jdksavdecc_acmp_talker_stream_source_clear_listeners(
        struct jdksavdecc_acmp_talker_stream_source *self);

/**
 * @brief jdksavdecc_acmp_talker_stream_source_add_listener adds a listener to the list of active listeners for a stream source
 * @param self The talker stream source object
 * @param listener_entity_id
 * @param listener_unique_id
 * @return true on success, false if there is no room to add it
 */
bool jdksavdecc_acmp_talker_stream_source_add_listener(
        struct jdksavdecc_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 listener_entity_id,
        uint16_t listener_unique_id
        );

/**
 * @brief jdksavdecc_acmp_talker_stream_source_remove_listener removes the listener from the list of active listeners for a stream source
 *
 * Re-Orders list to be contiguous
 *
 * @param self The talker stream source object
 * @param listener_entity_id
 * @param listener_unique_id
 * @return true on success, false if the listener was not in the list
 */
bool jdksavdecc_acmp_talker_stream_source_remove_listener(
        struct jdksavdecc_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 listener_entity_id,
        uint16_t listener_unique_id
        );


struct jdksavdecc_acmp_talker_manager {
    struct jdksavdecc_state_machine *base;
    struct jdksavdecc_entity_manager *entity_manager;
    uint16_t talker_stream_sources;
    struct jdksavdecc_acmp_talker_stream_source talker_source[JDKSAVDECC_ACMP_TALKER_MANAGER_MAX_STREAMS];
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


