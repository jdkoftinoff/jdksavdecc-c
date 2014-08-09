
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
#include "jdksavdecc_aecp_print.h"
#include "jdksavdecc_aem_print.h"
#include "jdksavdecc_aecp_aa.h"
#include "jdksavdecc_aecp_aem.h"
#include "jdksavdecc_aecp_avc.h"
#include "jdksavdecc_aecp_hdcp_apm.h"
#include "jdksavdecc_aecp_vendor.h"

struct jdksavdecc_uint16_name jdksavdecc_aecp_print_message_type[]
    = {{JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND, "AEM_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE, "AEM_RESPONSE"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_COMMAND, "ADDRESS_ACCESS_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_RESPONSE, "ADDRESS_ACCESS_RESPONSE"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_COMMAND, "AVC_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_RESPONSE, "AVC_RESPONSE"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_COMMAND, "VENDOR_UNIQUE_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_RESPONSE, "VENDOR_UNIQUE_RESPONSE"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_COMMAND, "HDCP_APM_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_RESPONSE, "HDCP_APM_RESPONSE"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_COMMAND, "EXTENDED_COMMAND"},
       {JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_RESPONSE, "EXTENDED_RESPONSE"},
       {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_print_status[]
    = {{JDKSAVDECC_AECP_STATUS_SUCCESS, "SUCCESS"}, {JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"}, {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_aem_print_status[]
    = {{JDKSAVDECC_AECP_STATUS_SUCCESS, "SUCCESS"}, {JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"}, {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_aa_print_status[]
    = {{JDKSAVDECC_AECP_AA_STATUS_SUCCESS, "SUCCESS"},
       {JDKSAVDECC_AECP_AA_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"},
       {JDKSAVDECC_AECP_AA_STATUS_ADDRESS_TOO_LOW, "ADDRESS_TOO_LOW"},
       {JDKSAVDECC_AECP_AA_STATUS_ADDRESS_TOO_HIGH, "ADDRESS_TOO_HIGH"},
       {JDKSAVDECC_AECP_AA_STATUS_ADDRESS_INVALID, "ADDRESS_INVALID"},
       {JDKSAVDECC_AECP_AA_STATUS_TLV_INVALID, "TLV_INVALID"},
       {JDKSAVDECC_AECP_AA_STATUS_DATA_INVALID, "DATA_INVALID"},
       {JDKSAVDECC_AECP_AA_STATUS_UNSUPPORTED, "UNSUPPORTED"},
       {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_aa_print_mode[] = {{JDKSAVDECC_AECP_AA_MODE_READ, "READ"},
                                                                 {JDKSAVDECC_AECP_AA_MODE_WRITE, "WRITE"},
                                                                 {JDKSAVDECC_AECP_AA_MODE_EXECUTE, "EXECUTE"},
                                                                 {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_avc_print_status[] = {{JDKSAVDECC_AECP_AVC_STATUS_SUCCESS, "SUCCESS"},
                                                                    {JDKSAVDECC_AECP_AVC_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"},
                                                                    {JDKSAVDECC_AECP_AVC_STATUS_FAILURE, "FAILURE"},
                                                                    {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_hdcp_apm_print_status[]
    = {{JDKSAVDECC_AECP_HDCP_APM_STATUS_SUCCESS, "SUCCESS"},
       {JDKSAVDECC_AECP_HDCP_APM_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"},
       {JDKSAVDECC_AECP_HDCP_APM_STATUS_FRAGMENT_MISSING, "FRAGMENT_MISSING"},
       {0, 0}};

struct jdksavdecc_uint16_name jdksavdecc_aecp_vendor_print_status[] = {
    {JDKSAVDECC_AECP_VENDOR_STATUS_SUCCESS, "SUCCESS"}, {JDKSAVDECC_AECP_VENDOR_STATUS_NOT_IMPLEMENTED, "IMPLEMENTED"}, {0, 0}};

void jdksavdecc_aecp_common_control_header_print( struct jdksavdecc_printer *self,
                                                  struct jdksavdecc_aecpdu_common_control_header const *p )
{
    struct jdksavdecc_uint16_name *status_name_table = jdksavdecc_aecp_print_status;
    jdksavdecc_printer_print_label( self, "message_type" );
    jdksavdecc_printer_print_uint16_name( self, jdksavdecc_aecp_print_message_type, p->message_type );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "status" );
    switch ( p->message_type )
    {
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE:
        status_name_table = jdksavdecc_aecp_aem_print_status;
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_RESPONSE:
        status_name_table = jdksavdecc_aecp_aa_print_status;
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_RESPONSE:
        status_name_table = jdksavdecc_aecp_avc_print_status;
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_RESPONSE:
        status_name_table = jdksavdecc_aecp_hdcp_apm_print_status;
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_RESPONSE:
        status_name_table = jdksavdecc_aecp_vendor_print_status;
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_RESPONSE:
        status_name_table = jdksavdecc_aecp_print_status;
        break;
    default:
        status_name_table = jdksavdecc_aecp_print_status;
        break;
    }
    jdksavdecc_printer_print_uint16_name( self, status_name_table, p->status );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "control_data_length" );
    jdksavdecc_printer_print_uint16( self, p->control_data_length );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "target_entity_id" );
    jdksavdecc_printer_print_eui64( self, p->target_entity_id );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aecp_common_print( struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_common const *p )
{
    jdksavdecc_aecp_common_control_header_print( self, &p->header );
    jdksavdecc_printer_print_label( self, "controller_entity_id" );
    jdksavdecc_printer_print_eui64( self, p->controller_entity_id );
    jdksavdecc_printer_print_eol( self );

    jdksavdecc_printer_print_label( self, "sequence_id" );
    jdksavdecc_printer_print_uint16( self, p->sequence_id );
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_aecp_print(
    struct jdksavdecc_printer *self, struct jdksavdecc_aecpdu_common const *msg, void const *p, ssize_t pos, size_t len )
{
    jdksavdecc_aecp_common_print( self, msg );
    switch ( msg->header.message_type )
    {
    // Todo: put more detail into printing of non-aem messages
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND:
    {
        struct jdksavdecc_aecpdu_aem aem;
        if ( jdksavdecc_aecpdu_aem_read( &aem, p, pos, len ) > 0 )
        {
            jdksavdecc_aem_command_print( self, &aem, p, pos, len );
        }
        break;
    }
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE:
    {
        struct jdksavdecc_aecpdu_aem aem;
        if ( jdksavdecc_aecpdu_aem_read( &aem, p, pos, len ) > 0 )
        {
            jdksavdecc_aem_response_print( self, &aem, p, pos, len );
        }
        break;
    }
    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_RESPONSE:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "tlv_count" );
        jdksavdecc_printer_print_uint16( self, jdksavdecc_aecp_aa_get_tlv_count( p, pos ) );
        jdksavdecc_printer_print_eol( self );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_AA_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_AA_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_RESPONSE:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_COMMON_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_COMMON_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_RESPONSE:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_COMMON_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_COMMON_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_RESPONSE:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_COMMON_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_COMMON_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_COMMAND:
    case JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_RESPONSE:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_COMMON_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_COMMON_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    default:
        jdksavdecc_aecp_common_print( self, msg );
        jdksavdecc_printer_print_label( self, "payload" );
        jdksavdecc_printer_print_block( self,
                                        p,
                                        len,
                                        pos + JDKSAVDECC_AECPDU_COMMON_LEN,
                                        pos + msg->header.control_data_length
                                        - ( JDKSAVDECC_AECPDU_COMMON_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ) );
        jdksavdecc_printer_print_eol( self );
        break;
    }
}
