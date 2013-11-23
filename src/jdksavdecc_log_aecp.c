
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
#include "jdksavdecc_log_aecp.h"
#include "jdksavdecc_pdu.h"
#include "jdksavdecc_aecp_aem.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

struct jdksavdecc_log_aecp_context *jdksavdecc_log_aecp = 0;
struct jdksavdecc_frame_sender *jdksavdecc_log_aecp_frame_sender = 0;
struct jdksavdecc_frame *jdksavdecc_log_aecp_frame_for_logging = 0;
uint16_t jdksavdecc_log_aecp_sequence_id = 0;

void jdksavdecc_log_aecp_init(struct jdksavdecc_log_aecp_context *context,
                              struct jdksavdecc_frame_sender *frame_sender,
                              struct jdksavdecc_frame *frame_for_logging) {
    jdksavdecc_log_aecp = context;
    jdksavdecc_log_aecp_frame_sender = frame_sender;
    jdksavdecc_log_aecp_frame_for_logging = frame_for_logging;

    // Pre-fill in all frame details
    jdksavdecc_log_aecp_frame_for_logging->dest_address =
        context->destination_mac;
    jdksavdecc_eui48_init(&jdksavdecc_log_aecp_frame_for_logging->src_address);
    jdksavdecc_log_aecp_frame_for_logging->ethertype =
        JDKSAVDECC_AVTP_ETHERTYPE;
    jdksavdecc_log_aecp_frame_for_logging->tpid = 0;
    jdksavdecc_log_aecp_frame_for_logging->dei = 0;
    jdksavdecc_log_aecp_frame_for_logging->pcp = 0;
    jdksavdecc_log_aecp_frame_for_logging->vid = 0;
    jdksavdecc_log_aecp_frame_for_logging->time = 0;

    jdksavdecc_log_debug = jdksavdecc_log_aecp_debug;
    jdksavdecc_log_error = jdksavdecc_log_aecp_error;
    jdksavdecc_log_warning = jdksavdecc_log_aecp_warning;
    jdksavdecc_log_info = jdksavdecc_log_aecp_info;
}

void jdksavdecc_log_aecp_fill_and_send(uint32_t descriptor_index,
                                       const char *fmt, va_list args) {
    size_t pos = JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_OFFSET_VALUES;
    // uint8_t payload[
    // JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_OFFSET_VALUES +
    // JDKSAVDECC_DESCRIPTOR_CONTROL_VALUE_DETAILS_MAX_LENGTH ];
    // jdksavdecc_log_aecp_frame_for_logging->payload = payload;
    uint8_t *payload = jdksavdecc_log_aecp_frame_for_logging->payload;
    pos += vsnprintf(
        (char *)&jdksavdecc_log_aecp_frame_for_logging->payload[pos],
        JDKSAVDECC_DESCRIPTOR_CONTROL_VALUE_DETAILS_MAX_LENGTH, fmt, args);

    jdksavdecc_common_control_header_set_cd(JDKSAVDECC_SUBTYPE_DATA_CD, payload,
                                            0);
    jdksavdecc_common_control_header_set_subtype(JDKSAVDECC_SUBTYPE_AECP,
                                                 payload, 0);
    jdksavdecc_common_control_header_set_sv(0, payload, 0);
    jdksavdecc_common_control_header_set_version(0, payload, 0);
    jdksavdecc_common_control_header_set_control_data(
        JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE, payload, 0);
    jdksavdecc_common_control_header_set_status(JDKSAVDECC_AECP_STATUS_SUCCESS,
                                                payload, 0);
    jdksavdecc_common_control_header_set_control_data_length(
        pos - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN, payload, 0);
    jdksavdecc_common_control_header_set_stream_id(
        jdksavdecc_log_aecp->entity_id, payload, 0);

    jdksavdecc_aem_command_set_control_set_controller_entity_id(
        jdksavdecc_log_aecp->controller_id, payload, 0);
    jdksavdecc_aem_command_set_control_set_sequence_id(
        jdksavdecc_log_aecp_sequence_id++, payload, 0);
    jdksavdecc_aem_command_set_control_set_command_type(
        JDKSAVDECC_AEM_COMMAND_SET_CONTROL | 0x8000, payload,
        0); // Unsolicited response
    jdksavdecc_aem_command_set_control_set_descriptor_type(
        jdksavdecc_log_aecp->descriptor_type, payload, 0);
    jdksavdecc_aem_command_set_control_set_descriptor_index(descriptor_index,
                                                            payload, 0);
    jdksavdecc_log_aecp_frame_for_logging->length = pos;

    jdksavdecc_log_aecp_frame_sender->send(
        jdksavdecc_log_aecp_frame_sender,
        jdksavdecc_log_aecp_frame_for_logging);
}

void jdksavdecc_log_aecp_debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    jdksavdecc_log_aecp_fill_and_send(
        jdksavdecc_log_aecp->debug_descriptor_index, fmt, args);

    va_end(args);
}

void jdksavdecc_log_aecp_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    jdksavdecc_log_aecp_fill_and_send(
        jdksavdecc_log_aecp->error_descriptor_index, fmt, args);

    va_end(args);
}

void jdksavdecc_log_aecp_warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    jdksavdecc_log_aecp_fill_and_send(
        jdksavdecc_log_aecp->warning_descriptor_index, fmt, args);

    va_end(args);
}

void jdksavdecc_log_aecp_info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    jdksavdecc_log_aecp_fill_and_send(
        jdksavdecc_log_aecp->info_descriptor_index, fmt, args);

    va_end(args);
}
