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

struct jdksavdecc_uint16_name jdksavdecc_pdu_print_cd_subtype[] =
{
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_61883_IIDC, "61883_IIDC_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_MMA, "MMA_DATA_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_AUDIO, "AVTP_AUDIO_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_VIDEO, "AVTP_VIDEO_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_AVTP_CONTROL, "AVTP_CONTROL_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_VENDOR, "VENDOR_DATA" },
    { JDKSAVDECC_CD_BIT_DATA + JDKSAVDECC_SUBTYPE_EXPERIMENTAL, "EXPERIMENTAL_DATA" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_MMA, "MMA_CONTROL" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_VENDOR, "VENDOR_CONTROL" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_ADP, "ADP" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_AECP, "AECP" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_ACMP, "ACMP" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_MAAP, "MAAP" },
    { JDKSAVDECC_CD_BIT_CONTROL + JDKSAVDECC_SUBTYPE_EXPERIMENTAL, "EXPERIMENTAL_CONTROL" },
    { 0, 0 }
};

void jdksavdecc_pdu_print( FILE *f, const uint8_t *p, size_t len, int dump_payload )
{
    if( len>12 )
    {
        int cd = jdksavdecc_common_control_header_get_cd(p,0);
        uint8_t version = (uint8_t)jdksavdecc_common_control_header_get_version(p,0);

        jdksavdecc_print_label(f,"version");
        jdksavdecc_print_uint8(f,version);
        jdksavdecc_print_eol(f);

        jdksavdecc_print_label(f,"cd and subtype");
        jdksavdecc_print_uint16_name(f,jdksavdecc_pdu_print_cd_subtype,p[0]);
        jdksavdecc_print_eol(f);

        if( version==0 )
        {
            jdksavdecc_print_label(f,"sv");
            jdksavdecc_print(f,"%s",jdksavdecc_common_control_header_get_sv(p,0) ? "valid" : "not valid" );
            jdksavdecc_print_eol(f);

            if( cd==0 )  // version 0 stream data
            {
                jdksavdecc_print_label(f,"mr");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_stream_header_get_mr(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"gv");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_stream_header_get_gv(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"tv");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_stream_header_get_tv(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"sequence_num");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_stream_header_get_sequence_num(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"tu");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_stream_header_get_tu(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"stream_id");
                jdksavdecc_print_streamid(f,jdksavdecc_common_stream_header_get_stream_id(p,0));
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"avtp_timestamp");
                jdksavdecc_print_uint32(f,jdksavdecc_common_stream_header_get_avtp_timestamp(p,0));
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"gateway_info");
                jdksavdecc_print_uint32(f,jdksavdecc_common_stream_header_get_gateway_info(p,0));
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"stream_data_length");
                jdksavdecc_print_uint16(f,jdksavdecc_common_stream_header_get_stream_data_length(p,0));
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"protocol_specific_header");
                jdksavdecc_print_uint16(f,jdksavdecc_common_stream_header_get_protocol_specific_header(p,0));
                jdksavdecc_print_eol(f);

                if( dump_payload && len>JDKSAVDECC_COMMON_STREAM_HEADER_LEN )
                {
                    jdksavdecc_print_label(f,"stream_data_payload");
                    jdksavdecc_print_block(f,p,len,JDKSAVDECC_COMMON_STREAM_HEADER_LEN,len );
                }
            }
            else // version 0 control data
            {
                jdksavdecc_print_label(f,"control_data");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_control_header_get_control_data(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"status");
                jdksavdecc_print_uint8(f,(uint8_t)jdksavdecc_common_control_header_get_status(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"control_data_length");
                jdksavdecc_print_uint8(f,(uint16_t)jdksavdecc_common_control_header_get_control_data_length(p,0) );
                jdksavdecc_print_eol(f);

                jdksavdecc_print_label(f,"stream_id");
                jdksavdecc_print_streamid(f,jdksavdecc_common_control_header_get_stream_id(p,0));
                jdksavdecc_print_eol(f);
            }

            if( dump_payload && len>JDKSAVDECC_COMMON_CONTROL_HEADER_LEN )
            {
                jdksavdecc_print_label(f,"payload");
                jdksavdecc_print_block(f,p,len,JDKSAVDECC_COMMON_CONTROL_HEADER_LEN,len );
            }
        }
        else if( version==1 )
        {
            // TODO: Parse version 1 header
            if( dump_payload )
            {
                jdksavdecc_print_label(f,"frame");
                jdksavdecc_print_block(f,p,len,0,len );
            }
        }
    }
}


void jdksavdecc_frame_print( FILE *f, struct jdksavdecc_frame const *p, int dump_payload )
{
    jdksavdecc_print_label(f,"time (seconds)");
    jdksavdecc_print(f,"%0" PRIu64 ".%06" PRIu64, p->time/1000000, p->time%1000000 );
    jdksavdecc_print_eol(f);


    jdksavdecc_print_label(f,"dest_address");
    jdksavdecc_print_eui48(f,p->dest_address);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"src_address");
    jdksavdecc_print_eui48(f,p->src_address);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"ethertype");
    jdksavdecc_print_uint16(f,p->ethertype);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"tpid");
    jdksavdecc_print_uint16(f,p->tpid);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"pcp");
    jdksavdecc_print_uint16(f,p->pcp);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"dei");
    jdksavdecc_print_uint16(f,p->dei);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"vid");
    jdksavdecc_print_uint16(f,p->vid);
    jdksavdecc_print_eol(f);

    jdksavdecc_print_label(f,"length");
    jdksavdecc_print_uint16(f,p->length);
    jdksavdecc_print_eol(f);

    if( dump_payload )
    {
        jdksavdecc_print_label(f,"payload");
        jdksavdecc_print_block(f,p->payload,p->length,0,p->length);
    }
}

