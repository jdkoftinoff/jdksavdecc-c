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
#include "jdksavdecc_pdu_print.h"

#define JDKSAVDECC_CD_BIT_CONTROL (0x80 >> JDKSAVDECC_SUBTYPE_DATA_CD_BIT)
#define JDKSAVDECC_CD_BIT_DATA (0)

struct jdksavdecc_uint16_name jdksavdecc_pdu_print_cd_subtype[] = {
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_61883_IIDC, "61883_IIDC_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_MMA, "MMA_DATA_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_AUDIO, "AVTP_AUDIO_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_VIDEO, "AVTP_VIDEO_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_CONTROL,
     "AVTP_CONTROL_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_VENDOR, "VENDOR_DATA"},
    {JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_EXPERIMENTAL,
     "EXPERIMENTAL_DATA"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_MMA, "MMA_CONTROL"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_VENDOR, "VENDOR_CONTROL"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_ADP, "ADP"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_AECP, "AECP"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_ACMP, "ACMP"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_MAAP, "MAAP"},
    {JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_EXPERIMENTAL,
     "EXPERIMENTAL_CONTROL"},
    {0, 0}};

void jdksavdecc_pdu_print(struct jdksavdecc_printer *self, const uint8_t *p,
                          size_t len, int dump_payload) {
    if (len > 12) {
        int cd = jdksavdecc_common_control_header_get_cd(p, 0);
        uint8_t version =
            (uint8_t)jdksavdecc_common_control_header_get_version(p, 0);

        jdksavdecc_printer_print_label(self, "version");
        jdksavdecc_printer_print_uint8(self, version);
        jdksavdecc_printer_print_eol(self);

        jdksavdecc_printer_print_label(self, "cd and subtype");
        jdksavdecc_printer_print_uint16_name(
            self, jdksavdecc_pdu_print_cd_subtype, p[0]);
        jdksavdecc_printer_print_eol(self);

        if (version == 0) {
            jdksavdecc_printer_print_label(self, "sv");
            if (jdksavdecc_common_control_header_get_sv(p, 0)) {
                jdksavdecc_printer_print(self, "valid");
            } else {
                jdksavdecc_printer_print(self, "not valid");
            }
            jdksavdecc_printer_print_eol(self);

            if (cd == 0) // version 0 stream data
                {
                jdksavdecc_printer_print_label(self, "mr");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_stream_header_get_mr(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "gv");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_stream_header_get_gv(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "tv");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_stream_header_get_tv(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "sequence_num");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_stream_header_get_sequence_num(
                        p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "tu");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_stream_header_get_tu(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "stream_id");
                jdksavdecc_printer_print_streamid(
                    self, jdksavdecc_common_stream_header_get_stream_id(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "avtp_timestamp");
                jdksavdecc_printer_print_uint32(
                    self,
                    jdksavdecc_common_stream_header_get_avtp_timestamp(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "gateway_info");
                jdksavdecc_printer_print_uint32(
                    self,
                    jdksavdecc_common_stream_header_get_gateway_info(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "stream_data_length");
                jdksavdecc_printer_print_uint16(
                    self,
                    jdksavdecc_common_stream_header_get_stream_data_length(p,
                                                                           0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self,
                                               "protocol_specific_header");
                jdksavdecc_printer_print_uint16(
                    self,
                    jdksavdecc_common_stream_header_get_protocol_specific_header(
                        p, 0));
                jdksavdecc_printer_print_eol(self);

                if (dump_payload && len > JDKSAVDECC_COMMON_STREAM_HEADER_LEN) {
                    jdksavdecc_printer_print_label(self, "stream_data_payload");
                    jdksavdecc_printer_print_block(
                        self, p, len, JDKSAVDECC_COMMON_STREAM_HEADER_LEN, len);
                }
            } else // version 0 control data
                {
                jdksavdecc_printer_print_label(self, "control_data");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_control_header_get_control_data(
                        p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "status");
                jdksavdecc_printer_print_uint8(
                    self,
                    (uint8_t)jdksavdecc_common_control_header_get_status(p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "control_data_length");
                jdksavdecc_printer_print_uint16(
                    self, (uint16_t)
                    jdksavdecc_common_control_header_get_control_data_length(
                        p, 0));
                jdksavdecc_printer_print_eol(self);

                jdksavdecc_printer_print_label(self, "stream_id");
                jdksavdecc_printer_print_streamid(
                    self, jdksavdecc_common_control_header_get_stream_id(p, 0));
                jdksavdecc_printer_print_eol(self);
            }

            if (dump_payload && len > JDKSAVDECC_COMMON_CONTROL_HEADER_LEN) {
                jdksavdecc_printer_print_label(self, "payload");
                jdksavdecc_printer_print_block(
                    self, p, len, JDKSAVDECC_COMMON_CONTROL_HEADER_LEN, len);
            }
        } else if (version == 1) {
            // TODO: Parse version 1 header
            if (dump_payload) {
                jdksavdecc_printer_print_label(self, "frame");
                jdksavdecc_printer_print_block(self, p, len, 0, len);
            }
        }
    }
}

void jdksavdecc_frame_print(struct jdksavdecc_printer *self,
                            struct jdksavdecc_frame const *p,
                            int dump_payload) {
    jdksavdecc_printer_print_label(self, "time (seconds)");

    jdksavdecc_printer_print_uint64(self, p->time / 1000000);
    jdksavdecc_printer_printc(self, '.');
    jdksavdecc_printer_print_uint64(self, p->time % 1000000);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "dest_address");
    jdksavdecc_printer_print_eui48(self, p->dest_address);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "src_address");
    jdksavdecc_printer_print_eui48(self, p->src_address);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "ethertype");
    jdksavdecc_printer_print_uint16(self, p->ethertype);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "tpid");
    jdksavdecc_printer_print_uint16(self, p->tpid);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "pcp");
    jdksavdecc_printer_print_uint16(self, p->pcp);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "dei");
    jdksavdecc_printer_print_uint16(self, p->dei);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "vid");
    jdksavdecc_printer_print_uint16(self, p->vid);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "length");
    jdksavdecc_printer_print_uint16(self, p->length);
    jdksavdecc_printer_print_eol(self);

    if (dump_payload) {
        jdksavdecc_printer_print_label(self, "payload");
        jdksavdecc_printer_print_block(self, p->payload, p->length, 0,
                                       p->length);
    }
}
