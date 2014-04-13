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

bool jdksavdecc_entity_manager_init(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_entity_model *entity_model,
        int symbol_dispatch_table_num_entries,
        struct jdksavdecc_symbol_dispatch *symbol_dispatch_table,
        void *context,
        void (*frame_send)(
            struct jdksavdecc_entity_manager *self,
            void *context,
            uint8_t const *buf,
            uint16_t len ) ) {
    memset(self,0,sizeof(*self));
    self->entity_model = entity_model;
    self->symbol_dispatch_table_num_entries = symbol_dispatch_table_num_entries;
    self->symbol_dispatch_table = symbol_dispatch_table;
    self->context = context;
    self->frame_send = frame_send;
    self->destroy = jdksavdecc_entity_manager_destroy;
    self->tick = jdksavdecc_entity_manager_tick;
    self->receive = jdksavdecc_entity_manager_receive;
    self->command_timed_out = jdksavdecc_entity_manager_command_timed_out;
    self->validate_permissions = jdksavdecc_entity_manager_validate_permissions;
    self->received_aem_command = jdksavdecc_entity_manager_received_aem_command;
    self->received_aa_command = jdksavdecc_entity_manager_received_aa_command;
    self->can_send_command = jdksavdecc_entity_manager_can_send_command;
    self->send_command = jdksavdecc_entity_manager_send_command;
    self->send_responses = jdksavdecc_entity_manager_send_responses;
    self->send_unsolicited_responses = jdksavdecc_entity_manager_send_unsolicited_responses;
    self->receive_acquire_entity_command = jdksavdecc_entity_manager_receive_acquire_entity_command;
    self->receive_lock_entity_command = jdksavdecc_entity_manager_receive_lock_entity_command;
    self->receive_entity_available_command = jdksavdecc_entity_manager_receive_entity_available_command;
    self->send_controller_available = jdksavdecc_entity_manager_send_controller_available;
    self->receive_controller_available_command = jdksavdecc_entity_manager_receive_controller_available_command;
    self->receive_controller_available_response = jdksavdecc_entity_manager_receive_controller_available_response;
    self->receive_read_descriptor_command = jdksavdecc_entity_manager_receive_read_descriptor_command;
    self->receive_set_configuration_command = jdksavdecc_entity_manager_receive_set_configuration_command;
    self->receive_get_configuration_command = jdksavdecc_entity_manager_receive_get_configuration_command;
    self->receive_set_name_command = jdksavdecc_entity_manager_receive_set_name_command;
    self->receive_get_name_command = jdksavdecc_entity_manager_receive_get_name_command;
    self->send_set_control_unsolicited_response = jdksavdecc_entity_manager_send_set_control_unsolicited_response;
    self->receive_set_control_command = jdksavdecc_entity_manager_receive_set_control_command;
    self->receive_get_control_command = jdksavdecc_entity_manager_receive_get_control_command;
    self->receive_register_unsolicited_notification_command = jdksavdecc_entity_manager_receive_register_unsolicited_notification_command;
    self->receive_deregister_unsolicited_notification_command = jdksavdecc_entity_manager_receive_deregister_unsolicited_notification_command;
    self->read_descriptor_entity = jdksavdecc_entity_manager_read_descriptor_entity;
    self->read_descriptor_configuration = jdksavdecc_entity_manager_read_descriptor_configuration;
    self->read_descriptor_control = jdksavdecc_entity_manager_read_descriptor_control;
    self->read_descriptor_locale = jdksavdecc_entity_manager_read_descriptor_locale;
    self->read_descriptor_strings = jdksavdecc_entity_manager_read_descriptor_strings;
    self->read_descriptor_memory = jdksavdecc_entity_manager_read_descriptor_memory;
    self->receive_aa_read = jdksavdecc_entity_manager_receive_aa_read;
    self->receive_aa_write = jdksavdecc_entity_manager_receive_aa_write;
    self->receive_aa_execute = jdksavdecc_entity_manager_receive_aa_execute;
    return true;
}

/// Destroy an entity manager
void jdksavdecc_entity_manager_destroy( struct jdksavdecc_entity_manager *self ) {
    (void)self;
}

struct jdksavdecc_symbol_dispatch *jdksavdecc_entity_manager_find_symbol(
        struct jdksavdecc_entity_manager *self,
        uint16_t configuration_number,
        uint32_t symbol ) {

}

/// The pdu contains a valid Read Descriptor Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_dispatch_symbol_receive_read_descriptor_command(
        struct jdksavdecc_entity_manager *self,
        uint32_t symbol,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {

}

/// The pdu contains a valid Command to set or change something
/// SET_NAME, SET_CONTROL, INCREMENT_CONTROL, DECREMENT_CONTROL, SET_MIXER,
/// SET_MATRIX, SET_SIGNAL_SELECTOR, etc
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_dispatch_symbol_set_command(
        struct jdksavdecc_entity_manager *self,
        uint32_t symbol,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {

}

/// The pdu contains a valid Command to get something
/// GET_NAME, GET_CONTROL, GET_MIXER, GET_MATRIX, GET_SIGNAL_SELECTOR, etc
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_dispatch_symbol_receive_get_command(
        struct jdksavdecc_entity_manager *self,
        uint32_t symbol,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {

}

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_entity_manager_tick(
        struct jdksavdecc_entity_manager *self,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms ) {
    // TODO: Run Entity State Machines
    (void)self;
    (void)cur_time_in_ms;
    // TODO: Run Tick for all Talker/Listener state machines
    // TODO: Run Tick for all symbols in the current configuration
}

/// The function that is to be called when an incoming AECPDU is received
/// returns true if the message was recognized and handled.
/// When the message is handeld, this function is
/// allowed to modify the data pointed to by buf for sending responses
bool jdksavdecc_entity_manager_receive(
        struct jdksavdecc_entity_manager *self,
        void *context,
        jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)context;
    (void)time_in_milliseconds;
    (void)buf;
    (void)len;
    return false;
}


/// Notification that a command to a target entity timed out
void jdksavdecc_entity_manager_command_timed_out(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        uint16_t command_type,
        uint16_t sequence_id) {
    // TODO
    (void)self;
    (void)target_entity_id;
    (void)command_type;
    (void)sequence_id;
}

/// Check to make sure the command is allowed or disallowed due to acquire or locking
uint8_t jdksavdecc_entity_manager_validate_permissions(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem
        ) {
    // TODO
    (void)self;
    (void)aem;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The received pdu contains a valid AEM command for me.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_received_aem_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The received pdu contains a valid AA command for me.
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_received_aa_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aa;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// Can we send a command now? i.e. are there no in-flight commands waiting to be acknowledged?
bool jdksavdecc_entity_manager_can_send_command(
        struct jdksavdecc_entity_manager *self
        ) {
    // TODO
    (void)self;
    return false;
}

void jdksavdecc_entity_manager_send_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_entity_id,
        struct jdksavdecc_eui48 const *target_mac_address,
        uint16_t aem_command_type,
        bool track_for_ack,
        uint8_t const *additional_data1,
        uint16_t additional_data_length1,
        uint8_t const *additional_data2,
        uint16_t additional_data_length2 ) {
    // TODO
    (void)self;
    (void)target_entity_id;
    (void)target_mac_address;
    (void)aem_command_type;
    (void)track_for_ack;
    (void)additional_data1;
    (void)additional_data_length1;
    (void)additional_data2;
    (void)additional_data_length2;

}

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
        uint16_t additional_data_length2 ) {
    // TODO
    (void)self;
    (void)internally_generated;
    (void)send_to_registered_controllers;
    (void)buf;
    (void)len;
    (void)additional_data1;
    (void)additional_data_length1;
    (void)additional_data2;
    (void)additional_data_length2;

}


/// Formulate an AEM Unsolicited response of specified command_type with the
/// specified additional data as payload, and send it to all interested controllers
void jdksavdecc_entity_manager_send_unsolicited_responses(
        struct jdksavdecc_entity_manager *self,
        uint16_t aem_command_type,
        uint8_t const *additional_data1,
        uint16_t additional_data_length1,
        uint8_t const *additional_data2,
        uint16_t additional_data_length2 ) {
    // TODO
    (void)self;
    (void)aem_command_type;
    (void)additional_data1;
    (void)additional_data_length1;
    (void)additional_data2;
    (void)additional_data_length2;

}

/// The pdu contains a valid Acquire Entity command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_acquire_entity_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Lock Entity command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_lock_entity_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Entity Available command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_entity_available_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

// Formulate and send a CONTROLLER_AVAILABLE command to a target controller
void jdksavdecc_entity_manager_send_controller_available(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_eui64 const *target_controller_entity_id,
        struct jdksavdecc_eui48 const *target_mac_address ) {
    // TODO
    (void)self;
    (void)target_controller_entity_id;
    (void)target_mac_address;
}

/// The pdu contains a valid Controller Available command.
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_controller_available_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Controller Available response.
/// return true if the response is handled
bool jdksavdecc_entity_manager_receive_controller_available_response(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return false;
}

/// The pdu contains a valid Read Descriptor Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_read_descriptor_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Set Configuration Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_configuration_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Get Configuration Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_configuration_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Set Name Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_name_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;

    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Get Name Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_name_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// Formulate and send a SET_CONTROL unsolicited response to all subscribed controllers
void jdksavdecc_entity_manager_send_set_control_unsolicited_response(
        struct jdksavdecc_entity_manager *self,
        uint16_t target_descriptor_index,
        uint8_t *control_value,
        uint16_t control_value_len) {
    // TODO
    (void)self;
    (void)target_descriptor_index;
    (void)control_value;
    (void)control_value_len;
}

/// The pdu contains a valid Set Control Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_set_control_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Get Control Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_get_control_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Register for Unsolicited Notifications Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_register_unsolicited_notification_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid De-Register for Unsolicited Notifications Command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_receive_deregister_unsolicited_notification_command(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}


/// The pdu contains a valid Read Entity Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_entity(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Configuration Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_configuration(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Control Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_control(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Locale Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_locale(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Strings Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_strings(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Memory Descriptor command
/// Fill in the response in place in the pdu and return an AECP AEM status code
uint8_t jdksavdecc_entity_manager_read_descriptor_memory(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecpdu_aem const *aem,
        jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
        uint8_t *buf,
        uint16_t len) {
    // TODO
    (void)self;
    (void)aem;
    (void)cur_time_in_ms;
    (void)buf;
    (void)len;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Read Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_read(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t *response ) {
    // TODO
    (void)self;
    (void)aa;
    (void)virtual_base_address;
    (void)length;
    (void)response;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Write Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_write(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t const *request ) {
    // TODO
    (void)self;
    (void)aa;
    (void)virtual_base_address;
    (void)length;
    (void)request;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}

/// The pdu contains a valid Execute Address Access TLV command
/// Fill in the response in place in the pdu and return an AECP AA status code
uint8_t jdksavdecc_entity_manager_receive_aa_execute(
        struct jdksavdecc_entity_manager *self,
        struct jdksavdecc_aecp_aa const *aa,
        uint32_t virtual_base_address,
        uint16_t length,
        uint8_t const *request ) {
    // TODO
    (void)self;
    (void)aa;
    (void)virtual_base_address;
    (void)length;
    (void)request;
    return JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED;
}
