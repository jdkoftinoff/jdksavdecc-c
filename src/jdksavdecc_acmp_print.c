
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
#include "jdksavdecc_acmp_print.h"

struct jdksavdecc_uint16_name jdksavdecc_acmpdu_print_message_type[] = {
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_COMMAND, "CONNECT_TX_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_RESPONSE, "CONNECT_TX_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_COMMAND, "DISCONNECT_TX_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_RESPONSE, "DISCONNECT_TX_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_COMMAND, "GET_TX_STATE_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_RESPONSE, "GET_TX_STATE_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND, "CONNECT_RX_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_RESPONSE, "CONNECT_RX_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_RX_COMMAND, "DISCONNECT_RX_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_RX_RESPONSE, "DISCONNECT_RX_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_RX_STATE_COMMAND, "GET_RX_STATE_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_RX_STATE_RESPONSE, "GET_RX_STATE_RESPONSE"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_COMMAND, "GET_TX_CONNECTION_COMMAND"},
    {JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_RESPONSE, "GET_TX_CONNECTION_RESPONSE"},
    {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_acmpdu_print_status[] = {
    {JDKSAVDECC_ACMP_STATUS_SUCCESS, "SUCCESS"},
    {JDKSAVDECC_ACMP_STATUS_LISTENER_UNKNOWN_ID, "LISTENER_UNKNOWN_ID"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_UNKNOWN_ID, "TALKER_UNKNOWN_ID"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_DEST_MAC_FAIL, "TALKER_DEST_MAC_FAIL"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_NO_STREAM_INDEX, "TALKER_NO_STREAM_INDEX"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_NO_BANDWIDTH, "TALKER_NO_BANDWIDTH"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_EXCLUSIVE, "TALKER_EXCLUSIVE"},
    {JDKSAVDECC_ACMP_STATUS_LISTENER_TALKER_TIMEOUT, "LISTENER_TALKER_TIMEOUT"},
    {JDKSAVDECC_ACMP_STATUS_LISTENER_EXCLUSIVE, "LISTENER_EXCLUSIVE"},
    {JDKSAVDECC_ACMP_STATUS_STATE_UNAVAILABLE, "STATE_UNAVAILABLE"},
    {JDKSAVDECC_ACMP_STATUS_NOT_CONNECTED, "NOT_CONNECTED"},
    {JDKSAVDECC_ACMP_STATUS_NO_SUCH_CONNECTION, "NO_SUCH_CONNECTION"},
    {JDKSAVDECC_ACMP_STATUS_COULD_NOT_SEND_MESSAGE, "COULD_NOT_SEND_MESSAGE"},
    {JDKSAVDECC_ACMP_STATUS_TALKER_MISBEHAVING, "TALKER_MISBEHAVING"},
    {JDKSAVDECC_ACMP_STATUS_LISTENER_MISBEHAVING, "LISTENER_MISBEHAVING"},
    {JDKSAVDECC_ACMP_STATUS_RESERVED, "RESERVED"},
    {JDKSAVDECC_ACMP_STATUS_CONTROLLER_NOT_AUTHORIZED, "CONTROLLER_NOT_AUTHORIZED"},
    {JDKSAVDECC_ACMP_STATUS_INCOMPATIBLE_REQUEST, "INCOMPATIBLE_REQUEST"},
    {JDKSAVDECC_ACMP_STATUS_NOT_SUPPORTED, "NOT_SUPPORTED"},
    {0, 0}};

struct jdksavdecc_16bit_name jdksavdecc_acmpdu_print_flags[] = {
    {JDKSAVDECC_ACMP_FLAG_CLASS_B, "CLASS B"},                       {JDKSAVDECC_ACMP_FLAG_FAST_CONNECT, "FAST_CONNECT"},
    {JDKSAVDECC_ACMP_FLAG_SAVED_STATE, "SAVED_STATE"},               {JDKSAVDECC_ACMP_FLAG_STREAMING_WAIT, "STREAMING_WAIT"},
    {JDKSAVDECC_ACMP_FLAG_SUPPORTS_ENCRYPTED, "SUPPORTS_ENCRYPTED"}, {JDKSAVDECC_ACMP_FLAG_ENCRYPTED_PDU, "ENCRYPTED_PDU"},
    {JDKSAVDECC_ACMP_FLAG_TALKER_FAILED, "TALKER_FAILED"},           {0, 0}};

void jdksavdecc_acmpdu_print_common_control_header(FILE *f, struct jdksavdecc_acmpdu_common_control_header const *p) {
    jdksavdecc_print_label(f, "message_type");
    jdksavdecc_print_uint16_name(f, jdksavdecc_acmpdu_print_message_type, p->message_type);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "status");
    jdksavdecc_print_uint16_name(f, jdksavdecc_acmpdu_print_status, p->status);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "control_data_length");
    jdksavdecc_print_uint16(f, p->control_data_length);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "stream_id");
    jdksavdecc_print_streamid(f, p->stream_id);
    jdksavdecc_print_eol(f);
}

void jdksavdecc_acmpdu_print(FILE *f, struct jdksavdecc_acmpdu const *p) {
    jdksavdecc_acmpdu_print_common_control_header(f, &p->header);

    jdksavdecc_print_label(f, "controller_entity_id");
    jdksavdecc_print_eui64(f, p->controller_entity_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "controller_entity_id");
    jdksavdecc_print_eui64(f, p->talker_entity_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "listener_entity_id");
    jdksavdecc_print_eui64(f, p->listener_entity_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "talker_unique_id");
    jdksavdecc_print_uint16(f, p->talker_unique_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "listener_unique_id");
    jdksavdecc_print_uint16(f, p->listener_unique_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "stream_dest_mac");
    jdksavdecc_print_eui48(f, p->stream_dest_mac);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "connection_count");
    jdksavdecc_print_uint16(f, p->connection_count);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "sequence_id");
    jdksavdecc_print_uint16(f, p->sequence_id);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "flags");
    jdksavdecc_print_16bit_names(f, jdksavdecc_acmpdu_print_flags, p->flags);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f, "stream_vlan_id");
    jdksavdecc_print_uint16(f, p->stream_vlan_id);
    jdksavdecc_print_eol(f);
}
