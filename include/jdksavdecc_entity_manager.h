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
#include "jdksavdecc_adp.h"
#include "jdksavdecc_adp_manager.h"
#include "jdksavdecc_aecp.h"
#include "jdksavdecc_aecp_aa.h"
#include "jdksavdecc_aecp_aem.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup aem AEM Clause 7 */
/*@{*/

/** \addtogroup entity_manager  */
/*@{*/

#ifndef JDKSAVDECC_ENTITY_MANAGER_MAX_REGISTERED_CONTROLLERS
#define JDKSAVDECC_ENTITY_MANAGER_MAX_REGISTERED_CONTROLLERS (8)
#endif

#ifndef JDKSAVDECC_ENTITY_MANAGER_MAX_INFLIGHT_COMMANDS
#define JDKSAVDECC_ENTITY_MANAGER_MAX_INFLIGHT_COMMANDS (1)
#endif


struct jdksavdecc_entity_manager_inflight_command_info {
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
            struct jdksavdecc_entity_manager_inflight_command_info *self,
            void *context );
};

int jdksavdecc_entity_manager_inflight_command_info_compare(
        void const *lhs,
        void const *rhs );

struct jdksavdecc_entity_manager_inflight_commands {
    int num_inflight_commands;
    struct jdksavdecc_entity_manager_inflight_command_info inflight_commands[ JDKSAVDECC_ENTITY_MANAGER_MAX_INFLIGHT_COMMANDS ];
};

void jdksavdecc_entity_manager_inflight_commands_init( struct jdksavdecc_entity_manager_inflight_commands *self );

bool jdksacdecc_entity_manager_inflight_commands_full( struct jdksavdecc_entity_manager_inflight_commands *self );

void jdksavdecc_entity_manager_inflight_commands_sort(
        struct jdksavdecc_entity_manager_inflight_commands *self );

bool jdksavdecc_entity_manager_inflight_commands_add(
        struct jdksavdecc_entity_manager_inflight_commands *self,
        struct jdksavdecc_entity_manager_inflight_command_info const *info );

int jdksavdecc_entity_manager_inflight_commands_find(
        struct jdksavdecc_entity_manager_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        uint16_t sequence_id );

void jdksavdecc_entity_manager_inflight_commands_tick(
        struct jdksavdecc_entity_manager_inflight_commands *self,
        jdksavdecc_timestamp_in_milliseconds cur_time,
        void *context );

void jdksavdecc_entity_manager_inflight_commands_remove(
        struct jdksavdecc_entity_manager_inflight_commands *self,
        int num );

void jdksavdecc_entity_manager_inflight_commands_remove_target(
        struct jdksavdecc_entity_manager_inflight_commands *self,
        struct jdksavdecc_eui64 const *target_entity_id );


/// jdksavdecc_entity_manager is a base class for an AEM entity
struct jdksavdecc_entity_manager {

    /// A flag to notify higher level code that the state machine is requesting an immediate tick again
    bool early_tick;

    /// The current ADP manager that advertises for us
    struct jdksavdecc_adp_manager *adp_manager;

    /// The context that the entity is used in.
    void *context;

    /// The seqeunce_id of the last send outgoing command
    uint16_t outgoing_sequence_id;

    /// If we are acquired by a controller, then this is set to the controller's entity id.
    /// If we are not acquired, then this will be FF:FF:FF:FF:FF:FF:FF:FF
    struct jdksavdecc_eui64 acquired_by_controller_entity_id;

    /// If we are acquired by a controller, then this is the MAC address of the controller
    struct jdksavdecc_eui48 acquired_by_controller_mac_address;

    /// If we are acquired by one controller and another controller is trying to acquire
    /// this entity, then this contains the new controller's entity_id during the
    /// controller available negotiation mechanism
    struct jdksavdecc_eui64 acquire_in_progress_by_controller_entity_id;

    /// If we are currently interrogating a controller with a controller available, then
    /// this is the timestamp of when we started the controller available negotiation mechanism
    jdksavdecc_timestamp_in_milliseconds acquire_in_progress_time;

    /// If we are locked by a controller, then this contains the controller's entity id which
    /// locked us
    struct jdksavdecc_eui64 locked_by_controller_entity_id;

    /// If we are locked by a controller, then this contains the timestamp of when the lock first
    /// ocurred
    jdksavdecc_timestamp_in_milliseconds locked_time;

    /// This contains the unordered list of controller entity id's that are currently registered
    /// via the register for unsolicited notifications command. The entity id is FF:FF:FF:FF:FF:FF:FF:FF
    /// If the the slot is not in use
    struct jdksavdecc_eui64 registered_controllers_entity_id[JDKSAVDECC_ENTITY_MANAGER_MAX_REGISTERED_CONTROLLERS];

    /// This contains the associated MAC address of the controller's that are currently registered
    struct jdksavdecc_eui48 registered_controllers_mac_address[JDKSAVDECC_ENTITY_MANAGER_MAX_REGISTERED_CONTROLLERS];

    /// The map of inflight commands
    struct jdksavdecc_entity_manager_inflight_commands inflight_commands;

    /// Destroy an entity manager
    void (*destroy)( struct jdksavdecc_entity_manager *self );

    /// Notify the state machine that time has passed. Call asap if early_tick is true.
    void (*tick)(
            struct jdksavdecc_entity_manager *self,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms );

    /// The function that the jdksavdecc_entity_manager calls in order to send an AECPDU.
    void (*frame_send)(
            struct jdksavdecc_entity_manager *self,
            void *context,
            uint8_t const *buf,
            uint16_t len );

    /// The function that is to be called when an incoming AECPDU is received
    /// returns true if the message was recognized and handled.
    /// When the message is handeld, this function is
    /// allowed to modify the data pointed to by buf for sending responses
    bool (*receive)(
            struct jdksavdecc_entity_manager *self,
            void *context,
            jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
            uint8_t *buf,
            uint16_t len);


    /// Notification that a command to a target entity timed out
    void (*command_timed_out)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_eui64 const *target_entity_id,
            uint16_t command_type,
            uint16_t sequence_id);

    /// Check to make sure the command is allowed or disallowed due to acquire or locking
    uint8_t (*validate_permissions)( struct jdksavdecc_aecpdu_aem const *aem );

    /// The received pdu contains a valid AEM command for me.
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*received_aem_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The received pdu contains a valid AA command for me.
    /// Fill in the response in place in the pdu and return an AECP AA status code
    uint8_t (*received_aa_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecp_aa const *aa,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// Can we send a command now? i.e. are there no in-flight commands waiting to be acknowledged?
    bool (*can_send_command)(
            struct jdksavdecc_entity_manager *self
            );

    void (*send_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_eui64 const *target_entity_id,
            struct jdksavdecc_eui48 const *target_mac_address,
            uint16_t aem_command_type,
            bool track_for_ack,
            uint8_t const *additional_data1,
            uint16_t additional_data_length1,
            uint8_t const *additional_data2,
            uint16_t additional_data_length2 );

    /// Send a direct response to the target entity id, and unsolicited
    /// responses to all other subscribed controllers
    void (*send_responses)(
            struct jdksavdecc_entity_manager *self,
            bool internally_generated,
            bool send_to_registered_controllers,
            uint8_t *buf,
            uint16_t len,
            uint8_t const *additional_data1,
            uint16_t additional_data_length1,
            uint8_t const *additional_data2,
            uint16_t additional_data_length2 );


    /// Formulate an AEM Unsolicited response of specified command_type with the
    /// specified additional data as payload, and send it to all interested controllers
    void (*send_unsolicited_responses)(
            struct jdksavdecc_entity_manager *self,
            uint16_t aem_command_type,
            uint8_t const *additional_data1,
            uint16_t additional_data_length1,
            uint8_t const *additional_data2,
            uint16_t additional_data_length2 );

    /// The pdu contains a valid Acquire Entity command.
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_acquire_entity_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Lock Entity command.
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_lock_entity_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Entity Available command.
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_entity_available_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// Formulate and send a CONTROLLER_AVAILABLE command to a target controller
    void (*send_controller_available)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_eui64 const *target_controller_entity_id,
            struct jdksavdecc_eui48 const *target_mac_address );

    /// The pdu contains a valid Controller Available command.
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_controller_available_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Controller Available response.
    /// return true if the response is handled
    bool (*receive_controller_available_response)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Descriptor Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_read_descriptor_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Set Configuration Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_set_configuration_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Get Configuration Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_get_configuration_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Set Name Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_set_name_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Get Name Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_get_name_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// Formulate and send a SET_CONTROL unsolicited response to all subscribed controllers
    void (*send_set_control_unsolicited_response)(
            struct jdksavdecc_entity_manager *self,
            uint16_t target_descriptor_index,
            uint8_t *control_value,
            uint16_t control_value_len);

    /// The pdu contains a valid Set Control Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_set_control_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Get Control Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_get_control_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Register for Unsolicited Notifications Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_register_unsolicited_notification_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid De-Register for Unsolicited Notifications Command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*receive_deregister_unsolicited_notification_command)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);


    /// The pdu contains a valid Read Entity Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_entity)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Configuration Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_configuration)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Control Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_control)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Locale Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_locale)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Strings Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_strings)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Memory Descriptor command
    /// Fill in the response in place in the pdu and return an AECP AEM status code
    uint8_t (*read_descriptor_memory)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecpdu_aem const *aem,
            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
            uint8_t *buf,
            uint16_t len);

    /// The pdu contains a valid Read Address Access TLV command
    /// Fill in the response in place in the pdu and return an AECP AA status code
    uint8_t (*receive_aa_read)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecp_aa const *aa,
            uint32_t virtual_base_address,
            uint16_t length,
            uint8_t *response );

    /// The pdu contains a valid Write Address Access TLV command
    /// Fill in the response in place in the pdu and return an AECP AA status code
    uint8_t (*receive_aa_write)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecp_aa const *aa,
            uint32_t virtual_base_address,
            uint16_t length,
            uint8_t const *request );

    /// The pdu contains a valid Execute Address Access TLV command
    /// Fill in the response in place in the pdu and return an AECP AA status code
    uint8_t (*receive_aa_execute)(
            struct jdksavdecc_entity_manager *self,
            struct jdksavdecc_aecp_aa const *aa,
            uint32_t virtual_base_address,
            uint16_t length,
            uint8_t const *request );

};

/// Initialize an entity manager with the context and frame sender procedure
bool jdksavdecc_entity_manager_init(
        struct jdksavdecc_entity_manager *self,
        void *context,
        void (*frame_send)(
            struct jdksavdecc_entity_manager *self,
            void *context,
            uint8_t const *buf,
            uint16_t len )
        );

/// Destroy any resources that the jdksavdecc_adp_manager uses
void jdksavdecc_entity_manager_destroy(
        struct jdksavdecc_entity_manager *self );

/// Receive an ADPU and process it
bool jdksavdecc_entity_manager_receive(
        struct jdksavdecc_entity_manager *self,
        void *context,
        jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
        uint8_t *buf,
        uint16_t len );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_entity_manager_tick(
        struct jdksavdecc_entity_manager *self,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms );

/// Notification that a command to a target entity timed out
void jdksavdecc_entity_manager_command_timed_out(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        uint16_t command_type,
        uint16_t sequence_id);

/// Check to make sure the command is allowed or disallowed due to acquire or locking
uint8_t jdksavdecc_entity_manager_validate_permissions( struct jdksavdecc_aecpdu_aem const *aem );

/// The received pdu contains a valid AEM command for me.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_received_aem_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The received pdu contains a valid AA command for me.
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_received_aa_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// Can we send a command now? i.e. are there no in-flight commands waiting to be acknowledged?
bool jdksavdecc_entity_manager_can_send_command(
        struct jdksavdecc_entity_manager *self
        );

void jdksavdecc_entity_manager_send_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        struct jdksavdecc_eui48 const *target_mac_address,
        uint16_t aem_command_type,
        bool track_for_ack,
        uint8_t const *additional_data1,
        uint16_t additional_data_length1,
        uint8_t const *additional_data2,
        uint16_t additional_data_length2 );

/// Send a direct response to the target entity id, and unsolicited
/// responses to all other subscribed controllers
void jdksavdecc_entity_manager_send_responses(
        struct jdksavdecc_entity_manager *self,
        bool internally_generated,
        bool send_to_registered_controllers,
        uint8_t *buf,
        uint16_t len,
        uint8_t const *additional_data1,
        uint16_t additional_data_length1,
        uint8_t const *additional_data2,
        uint16_t additional_data_length2 );


/// Formulate an AEM Unsolicited response of specified command_type with the
/// specified additional data as payload, and send it to all interested controllers
void jdksavdecc_entity_manager_send_unsolicited_responses(
        struct jdksavdecc_entity_manager *self,
        uint16_t aem_command_type,
        uint8_t const *additional_data1,
        uint16_t additional_data_length1,
        uint8_t const *additional_data2,
        uint16_t additional_data_length2 );

/// The pdu contains a valid Acquire Entity command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_acquire_entity_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Lock Entity command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_lock_entity_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Entity Available command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_entity_available_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

// Formulate and send a CONTROLLER_AVAILABLE command to a target controller
void jdksavdecc_entity_manager_send_controller_available(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_controller_entity_id,
        struct jdksavdecc_eui48 const *target_mac_address );

/// The pdu contains a valid Controller Available command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_controller_available_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Controller Available response.
/// return true if the response is handled
bool jdksavdecc_entity_manager_receive_controller_available_response(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Descriptor Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_read_descriptor_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Set Configuration Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_configuration_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Get Configuration Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_configuration_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Set Name Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_name_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Get Name Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_name_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// Formulate and send a SET_CONTROL unsolicited response to all subscribed controllers
void jdksavdecc_entity_manager_send_set_control_unsolicited_response(
        struct jdksavdecc_entity_manager *self,
        uint16_t target_descriptor_index,
        uint8_t *control_value,
        uint16_t control_value_len);

/// The pdu contains a valid Set Control Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_control_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Get Control Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_control_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Register for Unsolicited Notifications Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_register_unsolicited_notification_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid De-Register for Unsolicited Notifications Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_deregister_unsolicited_notification_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);


/// The pdu contains a valid Read Entity Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_entity(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Configuration Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_configuration(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Control Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_control(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Locale Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_locale(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Strings Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_strings(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Memory Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_memory(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len);

/// The pdu contains a valid Read Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_read(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t *response );

/// The pdu contains a valid Write Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_write(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t const *request );

/// The pdu contains a valid Execute Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_execute(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t const *request );

/*@}*/

/*@}*/


