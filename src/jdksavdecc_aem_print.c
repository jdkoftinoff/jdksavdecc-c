
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
#include "jdksavdecc_aem_print.h"

struct jdksavdecc_uint16_name jdksavdecc_aem_print_command[]
    = {{JDKSAVDECC_AEM_COMMAND_ACQUIRE_ENTITY, "ACQUIRE_ENTITY"},
       {JDKSAVDECC_AEM_COMMAND_LOCK_ENTITY, "LOCK_ENTITY"},
       {JDKSAVDECC_AEM_COMMAND_ENTITY_AVAILABLE, "ENTITY_AVAILABLE"},
       {JDKSAVDECC_AEM_COMMAND_CONTROLLER_AVAILABLE, "CONTROLLER_AVAILABLE"},
       {JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR, "READ_DESCRIPTOR"},
       {JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR, "WRITE_DESCRIPTOR"},
       {JDKSAVDECC_AEM_COMMAND_SET_CONFIGURATION, "SET_CONFIGURATION"},
       {JDKSAVDECC_AEM_COMMAND_GET_CONFIGURATION, "GET_CONFIGURATION"},
       {JDKSAVDECC_AEM_COMMAND_SET_STREAM_FORMAT, "SET_STREAM_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_GET_STREAM_FORMAT, "GET_STREAM_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_SET_VIDEO_FORMAT, "SET_VIDEO_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_GET_VIDEO_FORMAT, "GET_VIDEO_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_SET_SENSOR_FORMAT, "SET_SENSOR_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_GET_SENSOR_FORMAT, "GET_SENSOR_FORMAT"},
       {JDKSAVDECC_AEM_COMMAND_SET_STREAM_INFO, "SET_STREAM_INFO"},
       {JDKSAVDECC_AEM_COMMAND_GET_STREAM_INFO, "GET_STREAM_INFO"},
       {JDKSAVDECC_AEM_COMMAND_SET_NAME, "SET_NAME"},
       {JDKSAVDECC_AEM_COMMAND_GET_NAME, "GET_NAME"},
       {JDKSAVDECC_AEM_COMMAND_SET_ASSOCIATION_ID, "SET_ASSOCIATION_ID"},
       {JDKSAVDECC_AEM_COMMAND_GET_ASSOCIATION_ID, "GET_ASSOCIATION_ID"},
       {JDKSAVDECC_AEM_COMMAND_SET_SAMPLING_RATE, "SET_SAMPLING_RATE"},
       {JDKSAVDECC_AEM_COMMAND_GET_SAMPLING_RATE, "GET_SAMPLING_RATE"},
       {JDKSAVDECC_AEM_COMMAND_SET_CLOCK_SOURCE, "SET_CLOCK_SOURCE"},
       {JDKSAVDECC_AEM_COMMAND_GET_CLOCK_SOURCE, "GET_CLOCK_SOURCE"},
       {JDKSAVDECC_AEM_COMMAND_SET_CONTROL, "SET_CONTROL"},
       {JDKSAVDECC_AEM_COMMAND_GET_CONTROL, "GET_CONTROL"},
       {JDKSAVDECC_AEM_COMMAND_INCREMENT_CONTROL, "INCREMENT_CONTROL"},
       {JDKSAVDECC_AEM_COMMAND_DECREMENT_CONTROL, "DECREMENT_CONTROL"},
       {JDKSAVDECC_AEM_COMMAND_SET_SIGNAL_SELECTOR, "SET_SIGNAL_SELECTOR"},
       {JDKSAVDECC_AEM_COMMAND_GET_SIGNAL_SELECTOR, "GET_SIGNAL_SELECTOR"},
       {JDKSAVDECC_AEM_COMMAND_SET_MIXER, "SET_MIXER"},
       {JDKSAVDECC_AEM_COMMAND_GET_MIXER, "GET_MIXER"},
       {JDKSAVDECC_AEM_COMMAND_SET_MATRIX, "SET_MATRIX"},
       {JDKSAVDECC_AEM_COMMAND_GET_MATRIX, "GET_MATRIX"},
       {JDKSAVDECC_AEM_COMMAND_START_STREAMING, "START_STREAMING"},
       {JDKSAVDECC_AEM_COMMAND_STOP_STREAMING, "STOP_STREAMING"},
       {JDKSAVDECC_AEM_COMMAND_REGISTER_UNSOLICITED_NOTIFICATION, "REGISTER_UNSOLICITED_NOTIFICATION"},
       {JDKSAVDECC_AEM_COMMAND_DEREGISTER_UNSOLICITED_NOTIFICATION, "DEREGISTER_UNSOLICITED_NOTIFICATION"},
       {JDKSAVDECC_AEM_COMMAND_IDENTIFY_NOTIFICATION, "IDENTIFY_NOTIFICATION"},
       {JDKSAVDECC_AEM_COMMAND_GET_AVB_INFO, "GET_AVB_INFO"},
       {JDKSAVDECC_AEM_COMMAND_GET_AS_PATH, "GET_AS_PATH"},
       {JDKSAVDECC_AEM_COMMAND_GET_COUNTERS, "GET_COUNTERS"},
       {JDKSAVDECC_AEM_COMMAND_REBOOT, "REBOOT"},
       {JDKSAVDECC_AEM_COMMAND_GET_AUDIO_MAP, "GET_AUDIO_MAP"},
       {JDKSAVDECC_AEM_COMMAND_ADD_AUDIO_MAPPINGS, "ADD_AUDIO_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_REMOVE_AUDIO_MAPPINGS, "REMOVE_AUDIO_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_GET_VIDEO_MAP, "GET_VIDEO_MAP"},
       {JDKSAVDECC_AEM_COMMAND_ADD_VIDEO_MAPPINGS, "ADD_VIDEO_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_REMOVE_VIDEO_MAPPINGS, "REMOVE_VIDEO_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_GET_SENSOR_MAP, "GET_SENSOR_MAP"},
       {JDKSAVDECC_AEM_COMMAND_ADD_SENSOR_MAPPINGS, "ADD_SENSOR_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_REMOVE_SENSOR_MAPPINGS, "REMOVE_SENSOR_MAPPINGS"},
       {JDKSAVDECC_AEM_COMMAND_START_OPERATION, "START_OPERATION"},
       {JDKSAVDECC_AEM_COMMAND_ABORT_OPERATION, "ABORT_OPERATION"},
       {JDKSAVDECC_AEM_COMMAND_OPERATION_STATUS, "OPERATION_STATUS"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_ADD_KEY, "AUTH_ADD_KEY"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_KEY, "AUTH_DELETE_KEY"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEY_LIST, "AUTH_GET_KEY_LIST"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEY, "AUTH_GET_KEY"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_ADD_KEY_TO_CHAIN, "AUTH_ADD_KEY_TO_CHAIN"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_KEY_FROM_CHAIN, "AUTH_DELETE_KEY_FROM_CHAIN"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEYCHAIN_LIST, "AUTH_GET_KEYCHAIN_LIST"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_GET_IDENTITY, "AUTH_GET_IDENTITY"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_ADD_TOKEN, "AUTH_ADD_TOKEN"},
       {JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_TOKEN, "AUTH_DELETE_TOKEN"},
       {JDKSAVDECC_AEM_COMMAND_AUTHENTICATE, "AUTHENTICATE"},
       {JDKSAVDECC_AEM_COMMAND_DEAUTHENTICATE, "DEAUTHENTICATE"},
       {JDKSAVDECC_AEM_COMMAND_ENABLE_TRANSPORT_SECURITY, "ENABLE_TRANSPORT_SECURITY"},
       {JDKSAVDECC_AEM_COMMAND_DISABLE_TRANSPORT_SECURITY, "DISABLE_TRANSPORT_SECURITY"},
       {JDKSAVDECC_AEM_COMMAND_ENABLE_STREAM_ENCRYPTION, "ENABLE_STREAM_ENCRYPTION"},
       {JDKSAVDECC_AEM_COMMAND_DISABLE_STREAM_ENCRYPTION, "DISABLE_STREAM_ENCRYPTION"},
       {JDKSAVDECC_AEM_COMMAND_SET_MEMORY_OBJECT_LENGTH, "SET_MEMORY_OBJECT_LENGTH"},
       {JDKSAVDECC_AEM_COMMAND_GET_MEMORY_OBJECT_LENGTH, "GET_MEMORY_OBJECT_LENGTH"},
       {JDKSAVDECC_AEM_COMMAND_SET_STREAM_BACKUP, "SET_STREAM_BACKUP"},
       {JDKSAVDECC_AEM_COMMAND_GET_STREAM_BACKUP, "GET_STREAM_BACKUP"},
       {JDKSAVDECC_AEM_COMMAND_EXPANSION, "EXPANSION"},
       {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aem_print_descriptor_type[]
    = {{JDKSAVDECC_DESCRIPTOR_ENTITY, "ENTITY"},
       {JDKSAVDECC_DESCRIPTOR_CONFIGURATION, "CONFIGURATION"},
       {JDKSAVDECC_DESCRIPTOR_AUDIO_UNIT, "AUDIO_UNIT"},
       {JDKSAVDECC_DESCRIPTOR_VIDEO_UNIT, "VIDEO_UNIT"},
       {JDKSAVDECC_DESCRIPTOR_SENSOR_UNIT, "SENSOR_UNIT"},
       {JDKSAVDECC_DESCRIPTOR_STREAM_INPUT, "STREAM_INPUT"},
       {JDKSAVDECC_DESCRIPTOR_STREAM_OUTPUT, "STREAM_OUTPUT"},
       {JDKSAVDECC_DESCRIPTOR_JACK_INPUT, "JACK_INPUT"},
       {JDKSAVDECC_DESCRIPTOR_JACK_OUTPUT, "JACK_OUTPUT"},
       {JDKSAVDECC_DESCRIPTOR_AVB_INTERFACE, "AVB_INTERFACE"},
       {JDKSAVDECC_DESCRIPTOR_CLOCK_SOURCE, "CLOCK_SOURCE"},
       {JDKSAVDECC_DESCRIPTOR_MEMORY_OBJECT, "MEMORY_OBJECT"},
       {JDKSAVDECC_DESCRIPTOR_LOCALE, "LOCALE"},
       {JDKSAVDECC_DESCRIPTOR_STRINGS, "STRINGS"},
       {JDKSAVDECC_DESCRIPTOR_STREAM_PORT_INPUT, "STREAM_PORT_INPUT"},
       {JDKSAVDECC_DESCRIPTOR_STREAM_PORT_OUTPUT, "STREAM_PORT_OUTPUT"},
       {JDKSAVDECC_DESCRIPTOR_EXTERNAL_PORT_INPUT, "EXTERNAL_PORT_INPUT"},
       {JDKSAVDECC_DESCRIPTOR_EXTERNAL_PORT_OUTPUT, "EXTERNAL_PORT_OUTPUT"},
       {JDKSAVDECC_DESCRIPTOR_INTERNAL_PORT_INPUT, "INTERNAL_PORT_INPUT"},
       {JDKSAVDECC_DESCRIPTOR_INTERNAL_PORT_OUTPUT, "INTERNAL_PORT_OUTPUT"},
       {JDKSAVDECC_DESCRIPTOR_AUDIO_CLUSTER, "AUDIO_CLUSTER"},
       {JDKSAVDECC_DESCRIPTOR_VIDEO_CLUSTER, "VIDEO_CLUSTER"},
       {JDKSAVDECC_DESCRIPTOR_SENSOR_CLUSTER, "SENSOR_CLUSTER"},
       {JDKSAVDECC_DESCRIPTOR_AUDIO_MAP, "AUDIO_MAP"},
       {JDKSAVDECC_DESCRIPTOR_VIDEO_MAP, "VIDEO_MAP"},
       {JDKSAVDECC_DESCRIPTOR_SENSOR_MAP, "SENSOR_MAP"},
       {JDKSAVDECC_DESCRIPTOR_CONTROL, "CONTROL"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_SELECTOR, "SIGNAL_SELECTOR"},
       {JDKSAVDECC_DESCRIPTOR_MIXER, "MIXER"},
       {JDKSAVDECC_DESCRIPTOR_MATRIX, "MATRIX"},
       {JDKSAVDECC_DESCRIPTOR_MATRIX_SIGNAL, "MATRIX_SIGNAL"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_SPLITTER, "SIGNAL_SPLITTER"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_COMBINER, "SIGNAL_COMBINER"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_DEMULTIPLEXER, "SIGNAL_DEMULTIPLEXER"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_MULTIPLEXER, "SIGNAL_MULTIPLEXER"},
       {JDKSAVDECC_DESCRIPTOR_SIGNAL_TRANSCODER, "SIGNAL_TRANSCODER"},
       {JDKSAVDECC_DESCRIPTOR_CLOCK_DOMAIN, "CLOCK_DOMAIN"},
       {JDKSAVDECC_DESCRIPTOR_CONTROL_BLOCK, "CONTROL_BLOCK"},
       {JDKSAVDECC_DESCRIPTOR_INVALID, "INVALID"},
       {0, 0}};

void jdksavdecc_aem_descriptor_print( struct jdksavdecc_printer *self, void const *p, ssize_t pos, size_t len )
{
    // All descriptors have descriptor_type and descriptor_index
    uint16_t descriptor_type = jdksavdecc_uint16_get( p, pos + JDKSAVDECC_DESCRIPTOR_ENTITY_OFFSET_DESCRIPTOR_TYPE );
    uint16_t descriptor_index = jdksavdecc_uint16_get( p, pos + JDKSAVDECC_DESCRIPTOR_ENTITY_OFFSET_DESCRIPTOR_INDEX );

    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "content" );
    jdksavdecc_printer_print_block( self, p, len, pos + 4, len );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_write_descriptor_command_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    (void)len;
    jdksavdecc_printer_print_label( self, "configuration_index" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_write_descriptor_get_configuration_index( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "reserved" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_write_descriptor_get_reserved( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_aem_descriptor_print(
        self,
        p,
        pos + JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR_COMMAND_OFFSET_DESCRIPTOR,
        pos + msg->aecpdu_header.header.control_data_length
        - ( JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR_COMMAND_OFFSET_DESCRIPTOR - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
}

void jdksavdecc_aem_read_descriptor_response_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    (void)len;
    jdksavdecc_printer_print_label( self, "configuration_index" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_read_descriptor_response_get_configuration_index( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "reserved" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_read_descriptor_response_get_reserved( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_aem_descriptor_print(
        self,
        p,
        pos + JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR_RESPONSE_OFFSET_DESCRIPTOR,
        pos + msg->aecpdu_header.header.control_data_length
        - ( JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR_RESPONSE_OFFSET_DESCRIPTOR - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
}

void jdksavdecc_aem_write_descriptor_response_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    (void)len;
    jdksavdecc_printer_print_label( self, "configuration_index" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_write_descriptor_response_get_configuration_index( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "reserved" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_write_descriptor_response_get_reserved( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_aem_descriptor_print(
        self,
        p,
        pos + JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR_RESPONSE_OFFSET_DESCRIPTOR,
        pos + msg->aecpdu_header.header.control_data_length
        - ( JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR_RESPONSE_OFFSET_DESCRIPTOR - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
}

void jdksavdecc_aem_read_descriptor_command_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    uint16_t descriptor_type = jdksavdecc_aem_command_read_descriptor_get_descriptor_type( p, pos );
    uint16_t descriptor_index = jdksavdecc_aem_command_read_descriptor_get_descriptor_index( p, pos );
    (void)len;
    (void)msg;
    jdksavdecc_printer_print_label( self, "configuration_index" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_read_descriptor_get_configuration_index( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "reserved" );
    jdksavdecc_printer_print_uint16( self, jdksavdecc_aem_command_read_descriptor_get_reserved( p, pos ) );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_get_control_command_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    uint16_t descriptor_type = jdksavdecc_aem_command_get_control_get_descriptor_type( p, pos );
    uint16_t descriptor_index = jdksavdecc_aem_command_get_control_get_descriptor_index( p, pos );
    (void)msg;
    (void)len;
    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_set_control_command_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    uint16_t descriptor_type = jdksavdecc_aem_command_set_control_get_descriptor_type( p, pos );
    uint16_t descriptor_index = jdksavdecc_aem_command_set_control_get_descriptor_index( p, pos );
    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "content" );
    jdksavdecc_printer_print_block(
        self,
        p,
        len,
        pos + JDKSAVDECC_AEM_COMMAND_SET_CONTROL_COMMAND_OFFSET_VALUES,
        pos + JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + msg->aecpdu_header.header.control_data_length );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_get_control_response_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    uint16_t descriptor_type = jdksavdecc_aem_command_get_control_response_get_descriptor_type( p, pos );
    uint16_t descriptor_index = jdksavdecc_aem_command_get_control_response_get_descriptor_index( p, pos );
    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "content" );
    jdksavdecc_printer_print_block(
        self,
        p,
        len,
        pos + JDKSAVDECC_AEM_COMMAND_GET_CONTROL_RESPONSE_OFFSET_VALUES,
        pos + JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + msg->aecpdu_header.header.control_data_length );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_set_control_response_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    uint16_t descriptor_type = jdksavdecc_aem_command_set_control_get_descriptor_type( p, pos );
    uint16_t descriptor_index = jdksavdecc_aem_command_set_control_get_descriptor_index( p, pos );
    jdksavdecc_printer_print_label( self, "descriptor_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_descriptor_type, descriptor_type );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "descriptor_index" );
    jdksavdecc_printer_print_uint16( self, descriptor_index );
    jdksavdecc_printer_print_eol( self );
    jdksavdecc_printer_print_label( self, "content" );
    jdksavdecc_printer_print_block(
        self,
        p,
        len,
        pos + JDKSAVDECC_AEM_COMMAND_SET_CONTROL_COMMAND_OFFSET_VALUES,
        pos + JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + msg->aecpdu_header.header.control_data_length );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aem_command_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    bool u = false;
    uint16_t command_type = msg->command_type & 0x7fff;
    if ( ( msg->command_type & 0x8000 ) != 0 )
    {
        u = true;
    }
    jdksavdecc_printer_print_label( self, "u (unsolicited)" );
    jdksavdecc_printer_print( self, u ? "true" : "false" );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "command_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_command, command_type );
    jdksavdecc_printer_print_eol( self );

    switch ( command_type )
    {
    case JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR:
        jdksavdecc_aem_read_descriptor_command_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR:
        jdksavdecc_aem_read_descriptor_command_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_SET_CONTROL:
        jdksavdecc_aem_set_control_command_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_GET_CONTROL:
        jdksavdecc_aem_get_control_command_print( self, msg, p, pos, len );
        break;
    default:
        jdksavdecc_printer_print_label( self, "content" );
        jdksavdecc_printer_print_block(
            self,
            p,
            len,
            pos + JDKSAVDECC_AECPDU_AEM_LEN,
            pos + JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + msg->aecpdu_header.header.control_data_length );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_AEM_LEN,
                                        pos + msg->aecpdu_header.header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_AEM_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    }
}

void jdksavdecc_aem_response_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_aem const *msg, void const *p, ssize_t pos, size_t len )
{
    bool u = false;
    uint16_t command_type = msg->command_type & 0x7fff;
    if ( ( msg->command_type & 0x8000 ) != 0 )
    {
        u = true;
    }
    jdksavdecc_printer_print_label( self, "u (unsolicited)" );
    jdksavdecc_printer_print( self, u ? "true" : "false" );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "command_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aem_print_command, command_type );
    jdksavdecc_printer_print_eol( self );

    switch ( command_type )
    {
    case JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR:
        jdksavdecc_aem_read_descriptor_response_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR:
        jdksavdecc_aem_read_descriptor_response_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_SET_CONTROL:
        jdksavdecc_aem_set_control_response_print( self, msg, p, pos, len );
        break;
    case JDKSAVDECC_AEM_COMMAND_GET_CONTROL:
        jdksavdecc_aem_get_control_response_print( self, msg, p, pos, len );
        break;
    default:
        jdksavdecc_printer_print_label( self, "content" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_AEM_LEN,
                                        pos + msg->aecpdu_header.header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_AEM_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    }
}
