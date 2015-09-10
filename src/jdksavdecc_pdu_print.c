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

#define JDKSAVDECC_CD_BIT_CONTROL ( 0x80 >> JDKSAVDECC_SUBTYPE_DATA_CD_BIT )
#define JDKSAVDECC_CD_BIT_DATA ( 0 )

#define JDKSAVDECC_1722A_SUBTYPE_SVF ( 0x06 )
#define JDKSAVDECC_1722A_SUBTYPE_RVF ( 0x07 )
#define JDKSAVDECC_1722A_SUBTYPE_AEF_CONTINUOUS ( 0x6e )
#define JDKSAVDECC_1722A_SUBTYPE_VSF_STREAM ( 0x6f )
#define JDKSAVDECC_1722A_SUBTYPE_EF_STREAM ( 0x7f )
#define JDKSAVDECC_1722A_SUBTYPE_NTSCF ( 0x82 )
#define JDKSAVDECC_1722A_SUBTYPE_ESCF ( 0xec )
#define JDKSAVDECC_1722A_SUBTYPE_EECF ( 0xed )
#define JDKSAVDECC_1722A_SUBTYPE_AEF_DISCRETE ( 0xee )
#define JDKSAVDECC_1722A_SUBTYPE_ADP ( 0xfa )
#define JDKSAVDECC_1722A_SUBTYPE_AECP ( 0xfb )
#define JDKSAVDECC_1722A_SUBTYPE_ACMP ( 0xfc )
#define JDKSAVDECC_1722A_SUBTYPE_MAAP ( 0xfe )
#define JDKSAVDECC_1722A_SUBTYPE_EF_CONTROL ( 0xff )


struct jdksavdecc_uint16_name jdksavdecc_pdu_print_cd_subtype[]
    = {{JDKSAVDECC_1722A_SUBTYPE_61883_IIDC, "61883_IIDC"},
       {JDKSAVDECC_1722A_SUBTYPE_MMA_STREAM, "MMA_STREAM"},
       {JDKSAVDECC_1722A_SUBTYPE_AAF, "AAF"},
       {JDKSAVDECC_1722A_SUBTYPE_CVF, "CVF"},
       {JDKSAVDECC_1722A_SUBTYPE_CRF, "CRF"},
       {JDKSAVDECC_1722A_SUBTYPE_TSCF, "TSCF"},
       {JDKSAVDECC_1722A_SUBTYPE_SVF, "SVF"},
       {JDKSAVDECC_1722A_SUBTYPE_RVF, "RVF"},
       {JDKSAVDECC_1722A_SUBTYPE_EF_STREAM, "EF_STREAM"},
       {JDKSAVDECC_1722A_SUBTYPE_VSF_STREAM, "VSF_STREAM"},
       {JDKSAVDECC_1722A_SUBTYPE_EF_STREAM, "EF_STREAM"},
       {JDKSAVDECC_1722A_SUBTYPE_NTSCF, "NTSCF"},
       {JDKSAVDECC_1722A_SUBTYPE_ESCF, "ESCF},
       {JDKSAVDECC_1722A_SUBTYPE_EECF, "EECF"},
       {JDKSAVDECC_1722A_SUBTYPE_AEF_DISCRETE, "AEF_DISCRETE"},
       {JDKSAVDECC_1722A_SUBTYPE_ADP, "ADP"},
       {JDKSAVDECC_1722A_SUBTYPE_AECP, "AECP"},
       {JDKSAVDECC_1722A_SUBTYPE_ACMP, "ACMP"},
       {JDKSAVDECC_1722A_SUBTYPE_MAAP, "MAAP"},
       {JDKSAVDECC_1722A_SUBTYPE_EF_CONTROL, "EF_CONTROL"},
       {0, 0}};

void jdksavdecc_pdu_print( struct jdksavdecc_printer *self, const uint8_t *p, size_t len, int dump_payload )
{
    if ( len > 12 )
    {
        int cd = jdksavdecc_common_control_header_get_cd( p, 0 );
        uint8_t version = (uint8_t)jdksavdecc_common_control_header_get_version( p, 0 );

        jdksavdecc_printer_print_label( self, "version" );
        jdksavdecc_printer_print_uint8( self, version );
        jdksavdecc_printer_print_eol( self );

        jdksavdecc_printer_print_label( self, "cd and subtype" );
        jdksavdecc_printer_print_uint16_name( self, jdksavdecc_pdu_print_cd_subtype, p[0] );
        jdksavdecc_printer_print_eol( self );

        if ( version == 0 )
        {
            jdksavdecc_printer_print_label( self, "sv" );
            if ( jdksavdecc_common_control_header_get_sv( p, 0 ) )
            {
                jdksavdecc_printer_print( self, "valid" );
            }
            else
            {
                jdksavdecc_printer_print( self, "not valid" );
            }
            jdksavdecc_printer_print_eol( self );

            if ( cd == 0 ) // version 0 stream data
            {
                jdksavdecc_printer_print_label( self, "mr" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_stream_header_get_mr( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "gv" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_stream_header_get_gv( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "tv" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_stream_header_get_tv( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "sequence_num" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_stream_header_get_sequence_num( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "tu" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_stream_header_get_tu( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "stream_id" );
                jdksavdecc_printer_print_streamid( self, jdksavdecc_common_stream_header_get_stream_id( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "avtp_timestamp" );
                jdksavdecc_printer_print_uint32( self, jdksavdecc_common_stream_header_get_avtp_timestamp( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "gateway_info" );
                jdksavdecc_printer_print_uint32( self, jdksavdecc_common_stream_header_get_gateway_info( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "stream_data_length" );
                jdksavdecc_printer_print_uint16( self, jdksavdecc_common_stream_header_get_stream_data_length( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "protocol_specific_header" );
                jdksavdecc_printer_print_uint16( self, jdksavdecc_common_stream_header_get_protocol_specific_header( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                if ( dump_payload && len > JDKSAVDECC_COMMON_STREAM_HEADER_LEN )
                {
                    jdksavdecc_printer_print_label( self, "stream_data_payload" );
                    jdksavdecc_printer_print_block( self, p, len, JDKSAVDECC_COMMON_STREAM_HEADER_LEN, len );
                }
            }
            else // version 0 control data
            {
                jdksavdecc_printer_print_label( self, "control_data" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_control_header_get_control_data( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "status" );
                jdksavdecc_printer_print_uint8( self, (uint8_t)jdksavdecc_common_control_header_get_status( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "control_data_length" );
                jdksavdecc_printer_print_uint16( self,
                                                 (uint16_t)jdksavdecc_common_control_header_get_control_data_length( p, 0 ) );
                jdksavdecc_printer_print_eol( self );

                jdksavdecc_printer_print_label( self, "stream_id" );
                jdksavdecc_printer_print_streamid( self, jdksavdecc_common_control_header_get_stream_id( p, 0 ) );
                jdksavdecc_printer_print_eol( self );
            }

            if ( dump_payload && len > JDKSAVDECC_COMMON_CONTROL_HEADER_LEN )
            {
                jdksavdecc_printer_print_label( self, "payload" );
                jdksavdecc_printer_print_block( self, p, len, JDKSAVDECC_COMMON_CONTROL_HEADER_LEN, len );
            }
        }
    }
}
