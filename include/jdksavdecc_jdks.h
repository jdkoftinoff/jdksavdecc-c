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
#include "jdksavdecc_util.h"
#include "jdksavdecc_pdu.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup jdks Publically usable definitions and types under JDKS OUI-36
 *
 * J.D. Koftinoff Software, Ltd.'s MAC-S (OUI-36) is: 70-B3-D5-ED-C
 *
 * JDKS reserves the MAC range from 70:b3:d5:ed:cf:f0 to 70:b3:d5:ed:cf:f7 inclusive for experimental devices only
 *
 * The following Multicast MAC addresses owned by J.D. Koftinoff Software, Ltd.
 * are available to be used by anyone as long as their usage conforms to the recommendations
 * defined in this file.
 *
 *    71:b3:d5:ed:cf:ff = JDKSAVDECC_JDKS_MULTICAST_LOG for multicasting entity log messages
 *
 * All other MAC addresses are for use by J.D. Koftinoff Software Ltd. only.
 *
 * The following 1722.1-2013 vendor control types are defined here for use by anyone:
 *
 *    70:b3:d5:ed:c0:00:00:00 = JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT for a logging string value control.
 *    70:b3:d5:ed:c0:00:00:01 = JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS for setting IPv4 ethernet parameters.
 */
/*@{*/

/** \addtogroup jdks_log Logging mechanism using multicast AECP AEM Unsolicited SET_CONTROL Response
 *  to the jdks notifications controller entity id (70:b3:d5:ed:cf:ff:ff:ff) with
 *  a vendor defined blob control type.
 *  Any AEM SET_CONTROL Response sent to the multicast MAC address 71:b3:d5:ed:cf:ff and controller_entity_id
 *  of 70:b3:d5:ff:ff:ed:cf:ff may be interpreted as a vendor specific blob control value (See Clause 7.3.5.2.9)
 *  if the vendor_eui64 field is 70:b3:d5:ed:c0:00:00:00 then the message is a logging message
 *  and shall be interpreted as defined:
 *
 *      Offset  0:  EUI64: vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT ( 70:b3:d5:ed:c0:00:00:00 )
 *      Offset  8:  Quadlet: blob_length is 2+text_length
 *      Offset 12:  Octet: log_priority { 0 = error, 1=warning, 2=info, 3..0x7f = debug/trace, 0xff=console data }
 *      Offset 13:  Octet: reserved
 *      Offset 14:  Octet array: utf8_chars[0..356]
 *
 * There can be a path back from the logging console to the logging source as well.  In this case,
 * the AECP SET_CONTROL Command is sent from the actual controller entity id, to the
 * targets entity id via the targets unicast MAC address.  The content is the same as the response except
 * the source_descriptor information is now target_descriptor and the log_priority shall be 0xff for console data.
 *
 *      Offset  0:  EUI64: vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT ( 70:b3:d5:ed:c0:00:00:00 )
 *      Offset  8:  Quadlet: blob_length is 2+text_length
 *      Offset 12:  Octet: log_priority { 0xff=console data }
 *      Offset 13:  Octet: reserved
 *      Offset 14:  Octet array: utf8_chars[0..356]
 *
 */
/*@{*/

#define JDKSAVDECC_JDKS_LOG_ERROR ( 0 )
#define JDKSAVDECC_JDKS_LOG_WARNING ( 1 )
#define JDKSAVDECC_JDKS_LOG_INFO ( 2 )
#define JDKSAVDECC_JDKS_LOG_DEBUG1 ( 3 )
#define JDKSAVDECC_JDKS_LOG_DEBUG2 ( 4 )
#define JDKSAVDECC_JDKS_LOG_DEBUG3 ( 5 )
#define JDKSAVDECC_JDKS_LOG_CONSOLE ( 0xff )

/* Special controller entity id used for JDKS notifications - only for use with
 * controls with value_type set to CONTROL_VENDOR.
 */
#define JDKSAVDECC_JDKS_NOTIFICATIONS_CONTROLLER_ENTITY_ID                                                                     \
    {                                                                                                                          \
        {                                                                                                                      \
            0x70, 0xb3, 0xd5, 0xff, 0xff, 0xed, 0xcf, 0xff                                                                     \
        }                                                                                                                      \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_notifications_controller_entity_id;

/* Multicast MAC address 71:b3:d5:ed:cf:ff is reserved for logging via
 * unsolicited SET_CONTROL of control descriptor of control type JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT
 */
#define JDKSAVDECC_JDKS_MULTICAST_LOG                                                                                          \
    {                                                                                                                          \
        {                                                                                                                      \
            0x71, 0xb3, 0xd5, 0xed, 0xcf, 0xff                                                                                 \
        }                                                                                                                      \
    }

extern struct jdksavdecc_eui48 jdksavdecc_jdks_multicast_log;

#define JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT                                                                                   \
    {                                                                                                                          \
        {                                                                                                                      \
            0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x00                                                                     \
        }                                                                                                                      \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_log_text;

#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 0 )
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 8 )
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 12 )
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 13 )
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 14 )
#define JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT
#define JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN ( JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE - 2 )

/**
 * @brief The jdksavdecc_jdks_log_control struct is a high level representation of the data transported
 *        in a log message to a controller from an entity via an AEM SET_CONTROL unsolicited response.
 */
struct jdksavdecc_jdks_log_control
{
    struct jdksavdecc_aem_command_set_control_response cmd;
    struct jdksavdecc_eui64 vendor_eui64;
    uint32_t blob_size;
    uint8_t log_detail;
    uint8_t reserved;
    uint8_t text[JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN + 1];
};

/**
 * @brief The jdksavdecc_jdks_log_console_command struct is a high level representation of the data transported
 *        in a console message to an entity from a controller via an AEM SET_CONTROL command.
 */
struct jdksavdecc_jdks_log_console_command
{
    struct jdksavdecc_aem_command_set_control cmd;
    struct jdksavdecc_eui64 vendor_eui64;
    uint32_t blob_size;
    uint8_t log_detail;
    uint8_t reserved;
    uint8_t text[JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN + 1];
};

/** jdksavdecc_jdks_log_control_generate generates a JDKS Log PDU as an AEM_RESPONSE unsolicited SET_CONTROL message.
 *
 * @param my_entity_id
 *        Pointer to the source's entity id.
 *
 * @param descriptor_index
 *        index of the CONTROL descriptor that we are using for this data
 *
 * @param sequence_id
 *        The pointer to the uint16_t of the variable used to track unsolicited response sequence_id.
 *        This variable will be incremented on success
 *
 * @param log_detail
 *        The logging detail of this message:
 *        @item 0 = Error
 *        @item 1 = Warning
 *        @item 2 = Info
 *        @item 3 = Debug1
 *        @item 4 = Debug2
 *        @item 5 = Debug3
 *        @item 6..0xfe = reserved
 *        @item 0xff = Console
 *
 * @param reserved
 *        reserved value
 *
 * @param utf8_log_string
 *        The utf8 data for the string to be sent. Limited to 352 bytes, not including null termination.
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return ssize_t length of the data filled in at buf, or -1 on error.
 *
 */
static inline ssize_t jdksavdecc_jdks_log_control_generate( struct jdksavdecc_eui64 const *my_entity_id,
                                                            uint16_t descriptor_index,
                                                            uint16_t *sequence_id,
                                                            uint8_t log_detail,
                                                            uint8_t reserved,
                                                            const char *utf8_log_string,
                                                            void *buf,
                                                            size_t len )
{
    int pos = 14;
    ssize_t text_len = (ssize_t)strlen( utf8_log_string );
    ssize_t expected_length = JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN + text_len;
    ssize_t r = jdksavdecc_validate_range( pos, len, expected_length );
    if ( r >= 0 )
    {
        struct jdksavdecc_aem_command_set_control_response setctrl;
        setctrl.aem_header.aecpdu_header.header.cd = true;
        setctrl.aem_header.aecpdu_header.header.subtype = JDKSAVDECC_SUBTYPE_AECP;
        setctrl.aem_header.aecpdu_header.header.sv = false;
        setctrl.aem_header.aecpdu_header.header.version = 0;
        setctrl.aem_header.aecpdu_header.header.message_type = JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE;
        setctrl.aem_header.aecpdu_header.header.status = JDKSAVDECC_AEM_STATUS_SUCCESS;
        setctrl.aem_header.aecpdu_header.header.control_data_length
            = (uint16_t)text_len + JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 2;
        setctrl.aem_header.aecpdu_header.header.target_entity_id = *my_entity_id;
        setctrl.aem_header.aecpdu_header.controller_entity_id = jdksavdecc_jdks_notifications_controller_entity_id;
        setctrl.aem_header.aecpdu_header.sequence_id = *sequence_id;
        setctrl.aem_header.command_type = JDKSAVDECC_AEM_COMMAND_SET_CONTROL | 0x8000;
        setctrl.descriptor_type = JDKSAVDECC_DESCRIPTOR_CONTROL;
        setctrl.descriptor_index = descriptor_index;
        jdksavdecc_aem_command_set_control_response_write( &setctrl, buf, pos, len );
        jdksavdecc_eui64_write(
            &jdksavdecc_jdks_aem_control_log_text, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64, len );
        jdksavdecc_uint32_write( (uint32_t)text_len + 2, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE, len );
        jdksavdecc_uint8_write( log_detail, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL, len );
        jdksavdecc_uint8_write( reserved, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED, len );
        memcpy( ( (uint8_t *)buf ) + pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT, utf8_log_string, text_len );
        memcpy( ( (uint8_t *)buf ) + JDKSAVDECC_FRAME_HEADER_DA_OFFSET, jdksavdecc_jdks_multicast_log.value, 6 );
        jdksavdecc_uint16_set( JDKSAVDECC_AVTP_ETHERTYPE, buf, JDKSAVDECC_FRAME_HEADER_ETHERTYPE_OFFSET );

        *sequence_id = *sequence_id + 1;
    }
    return r;
}

/** jdksavdecc_jdks_log_console_generate generates a JDKS Log PDU as an AEM_RESPONSE unsolicited SET_CONTROL message.
 *
 * @param target_entity_id
 *        Pointer to the targets entity id.
 *
 * @param my_entity_id
 *        Pointer to the controllers entity id.
 *
 * @param descriptor_index
 *        index of the CONTROL descriptor that we are using for this data
 *
 * @param sequence_id
 *        The pointer to the uint16_t of the variable used to track unsolicited response sequence_id.
 *        This variable will be incremented on success
 *
 * @param log_detail
 *        The logging detail of this message:
 *        @item 0 = Error
 *        @item 1 = Warning
 *        @item 2 = Info
 *        @item 3 = Debug1
 *        @item 4 = Debug2
 *        @item 5 = Debug3
 *        @item 6..0xfe = reserved
 *        @item 0xff = Console
 *
 * @param reserved
 *        reserved value
 *
 * @param utf8_log_string
 *        The utf8 data for the string to be sent. Limited to 352 bytes, not including null termination.
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return ssize_t length of the data filled in at buf, or -1 on error.
 *
 */
static inline ssize_t jdksavdecc_jdks_log_console_generate( struct jdksavdecc_eui64 const *my_entity_id,
                                                            struct jdksavdecc_eui64 const *target_entity_id,
                                                            uint16_t descriptor_index,
                                                            uint16_t *sequence_id,
                                                            uint8_t log_detail,
                                                            uint8_t reserved,
                                                            const char *utf8_log_string,
                                                            uint8_t *buf,
                                                            size_t len )
{
    int pos = 14;
    ssize_t text_len = (ssize_t)strlen( utf8_log_string );
    ssize_t expected_length = JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN + text_len;
    ssize_t r = jdksavdecc_validate_range( pos, len, expected_length );
    if ( r >= 0 )
    {
        struct jdksavdecc_aem_command_set_control_response setctrl;
        setctrl.aem_header.aecpdu_header.header.cd = true;
        setctrl.aem_header.aecpdu_header.header.subtype = JDKSAVDECC_SUBTYPE_AECP;
        setctrl.aem_header.aecpdu_header.header.sv = false;
        setctrl.aem_header.aecpdu_header.header.version = 0;
        setctrl.aem_header.aecpdu_header.header.message_type = JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND;
        setctrl.aem_header.aecpdu_header.header.status = JDKSAVDECC_AEM_STATUS_SUCCESS;
        setctrl.aem_header.aecpdu_header.header.control_data_length
            = (uint16_t)text_len + JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 2;
        setctrl.aem_header.aecpdu_header.header.target_entity_id = *target_entity_id;
        setctrl.aem_header.aecpdu_header.controller_entity_id = *my_entity_id;
        setctrl.aem_header.aecpdu_header.sequence_id = *sequence_id;
        setctrl.aem_header.command_type = JDKSAVDECC_AEM_COMMAND_SET_CONTROL;
        setctrl.descriptor_type = JDKSAVDECC_DESCRIPTOR_CONTROL;
        setctrl.descriptor_index = descriptor_index;
        jdksavdecc_aem_command_set_control_response_write( &setctrl, buf, pos, len );
        jdksavdecc_eui64_write(
            &jdksavdecc_jdks_aem_control_log_text, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64, len );
        jdksavdecc_uint32_write( (uint32_t)text_len + 2, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE, len );
        jdksavdecc_uint8_write( log_detail, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL, len );
        jdksavdecc_uint8_write( reserved, buf, pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED, len );
        memcpy( ( (uint8_t *)buf ) + pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT, utf8_log_string, text_len );
        memcpy( ( (uint8_t *)buf ) + JDKSAVDECC_FRAME_HEADER_DA_OFFSET, jdksavdecc_jdks_multicast_log.value, 6 );
        jdksavdecc_uint16_set( JDKSAVDECC_AVTP_ETHERTYPE, buf, JDKSAVDECC_FRAME_HEADER_ETHERTYPE_OFFSET );

        *sequence_id = *sequence_id + 1;
    }
    return r;
}

/**
 * @brief jdksavdecc_jdks_is_log checks to see if an etherent frame is a log message unsolicited response.
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_log_control structure that will be partially filled in on success
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return true if the PDU is a JDKS log message and it is safe to call jdksavdecc_jdks_log_control_read
 */
static inline bool jdksavdecc_jdks_is_log( struct jdksavdecc_jdks_log_control *p, void const *buf, size_t len )
{
    bool is_log_response = false;
    int pos = 14;
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN );
    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_response_read( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_read( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
        if ( jdksavdecc_eui64_compare( &jdksavdecc_jdks_aem_control_log_text, &p->vendor_eui64 ) == 0 )
        {
            jdksavdecc_uint32_read( &p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE + pos, len );
            if ( p->blob_size > ( JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT - JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN )
                 && p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE )
            {
                is_log_response = true;
            }
        }
    }
    return is_log_response;
}

/**
 * @brief jdksavdecc_jdks_is_console_command checks to see if an etherent frame is a log console command.
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_log_console_command structure that will be partially filled in on success
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return true if the PDU is a JDKS log message and it is safe to call jdksavdecc_jdks_log_console_read
 */
static inline bool
    jdksavdecc_jdks_is_console_command( struct jdksavdecc_jdks_log_console_command *p, void const *buf, size_t len )
{
    bool is_console = false;
    int pos = 14;
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN );
    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_read( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_read( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
        if ( jdksavdecc_eui64_compare( &jdksavdecc_jdks_aem_control_log_text, &p->vendor_eui64 ) == 0 )
        {
            jdksavdecc_uint32_read( &p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE + pos, len );
            if ( p->blob_size > ( JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT - JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN )
                 && p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE )
            {
                is_console = true;
            }
        }
    }
    return is_console;
}

/**
 * @brief jdksavdecc_jdks_log_control_read parses all the data in a JDKS LOG unsolicited response
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_log_control structure that will be partially filled in on success
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return The length of the data parsed, or -1 on error
 */

static inline ssize_t jdksavdecc_jdks_log_control_read( struct jdksavdecc_jdks_log_control *p, void const *buf, size_t len )
{
    int pos = 14;
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN );
    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_response_read( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_read( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
        if ( jdksavdecc_eui64_compare( &jdksavdecc_jdks_aem_control_log_text, &p->vendor_eui64 ) == 0 )
        {
            jdksavdecc_uint32_read( &p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE + pos, len );
            if ( p->blob_size >= 2 && p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE )
            {
                uint32_t text_len = p->blob_size - 2;

                jdksavdecc_uint8_read( &p->log_detail, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL + pos, len );

                jdksavdecc_uint8_read( &p->reserved, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED + pos, len );

                if ( text_len < JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN )
                {
                    r = pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT;
                    if ( text_len > 0 )
                    {
                        memcpy( p->text, (uint8_t const *)buf + r, text_len );
                        p->text[text_len] = '\0';
                    }
                    r = text_len;
                }
                else
                {
                    r = -1;
                }
            }
            else
            {
                r = -1;
            }
        }
        else
        {
            r = -1;
        }
    }
    return r;
}

/**
 * @brief jdksavdecc_jdks_log_console_read parses all the data in a JDKS LOG unsolicited response
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_log_console_command structure that will be filled in on success
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype *
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return The length of the data parsed, or -1 on error
 */

static inline ssize_t
    jdksavdecc_jdks_log_console_read( struct jdksavdecc_jdks_log_console_command *p, void const *buf, size_t len )
{
    int pos = 14;
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN );
    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_read( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_read( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
        if ( jdksavdecc_eui64_compare( &jdksavdecc_jdks_aem_control_log_text, &p->vendor_eui64 ) == 0 )
        {
            jdksavdecc_uint32_read( &p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE + pos, len );
            if ( p->blob_size >= 2 && p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE )
            {
                uint32_t text_len = p->blob_size - 2;

                jdksavdecc_uint8_read( &p->log_detail, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL + pos, len );

                jdksavdecc_uint8_read( &p->reserved, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED + pos, len );

                if ( text_len < JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN )
                {
                    r = pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT;
                    if ( text_len > 0 )
                    {
                        memcpy( p->text, (uint8_t const *)buf + r, text_len );
                        p->text[text_len] = '\0';
                    }
                    r = text_len;
                }
                else
                {
                    r = -1;
                }
            }
            else
            {
                r = -1;
            }
        }
        else
        {
            r = -1;
        }
    }
    return r;
}

/*@}*/

/** \addtogroup jdks_ipv4 JDKS Vendor specific blob control type for setting/getting ethernet port IPv4 parameters
 */
/*@{*/

/**
 Control type for setting IPv4 parameters
///
 vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS ( 70:b3:d5:ed:c0:00:00:01 )
///
 BLOB contains:
     Doublet interface_descriptor_type
     Doublet interface_descriptor_index
     Quadlet flags:
         bit 0 = static_enable
         bit 1 = link_local_enable
         bit 2 = dhcp_enable
         bit 3 = ipv4_address_valid
         bit 4 = ipv4_netmask_valid
         bit 5 = ipv4_gateway_valid
         bit 6 = ipv4_broadcast_valid
         bit 7 = dnsserver1_valid
         bit 8 = dnsserver2_valid
     Quadlet ipv4_address
     Quadlet ipv4_netmask
     Quadlet ipv4_gateway
     Quadlet ipv4_broadcast
     Quadlet ipv4_dnsserver1
     Quadlet ipv4_dnsserver2
*/
    
/** Control type for setting/getting network IPV4 parameters */
#define JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS                                                                            \
    {                                                                                                                          \
        {                                                                                                                      \
            0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x01                                                                     \
        }                                                                                                                      \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_ipv4_parameters;

/** Gain control is a extention over part of SET CONTROL.
 *	AEM COMMAND SET_CONTROL(0X18) [IEEE 1722.1 7.4 Commands and Responses]
 *	Offset is considered as per IEEE 1722.1 7.3.4 Control Types
 *      Offset  0:  EUI64: vendor_eui64 is (90:e0:f0:00:00:00:00:04 )
 *      Offset  8:  GAIN/Volume value of 2 bytes length
*/
#define JDKSAVDECC_JDKS_GAIN_CONTROL_OFFSET_VENDOR_EUI64 ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 0 )
#define JDKSAVDECC_JDKS_CONTROL_OFFSET_GAIN ( JDKSAVDECC_JDKS_GAIN_CONTROL_OFFSET_VENDOR_EUI64 + 8 )
#define JDKSAVDECC_JDKS_CONTROL_HEADER_LEN JDKSAVDECC_JDKS_CONTROL_OFFSET_GAIN
#define JDKSAVDECC_JDKS_GAIN_CONTROL_RESPONSE_OFFSET_VENDOR_EUI64 ( JDKSAVDECC_AEM_COMMAND_SET_CONTROL_COMMAND_LEN + 0 )
#define JDKSAVDECC_JDKS_CONTROL_RESPONSE_OFFSET_GAIN ( JDKSAVDECC_JDKS_GAIN_CONTROL_RESPONSE_OFFSET_VENDOR_EUI64 + 8 )
#define JDKSAVDECC_JDKS_CONTROL_RESPONSE_HEADER_LEN JDKSAVDECC_JDKS_CONTROL_RESPONSE_OFFSET_GAIN

/**
 * @brief The jdksavdecc_jdks_gain_control struct is a high level representation of the data transported
 *        to send SET control message for gain/volume.
 */
struct jdksavdecc_jdks_gain_control
{
    struct jdksavdecc_aem_command_set_control cmd;
    struct jdksavdecc_eui64 vendor_eui64;
	uint16_t gain;
};

/**
 * @brief The jdksavdecc_jdks_gain_control_response struct is a high level representation of the data transported
 *        to send SET control response message for gain/volume.
*/
struct jdksavdecc_jdks_gain_control_response
{
    struct jdksavdecc_aem_command_set_control_response cmd;
    struct jdksavdecc_eui64 vendor_eui64;
	uint16_t gain;
};

/**
 * @brief jdksavdecc_aem_command_set_control_gain_read parses all the data in a SET CONTROL command received
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_gain_control structure
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return The length of the data parsed, or -1 on error
 */
static inline ssize_t jdksavdecc_aem_command_set_control_gain_read( struct jdksavdecc_jdks_gain_control *p, void *buf, size_t pos, size_t len)
{
	struct jdksavdecc_eui64 vendorid;

	ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_CONTROL_HEADER_LEN);

    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_response_read( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_read( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_GAIN_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
        if (jdksavdecc_eui64_compare( &vendorid, &p->vendor_eui64 ) == 0)
        {
            jdksavdecc_uint16_read( &p->gain, buf, JDKSAVDECC_JDKS_CONTROL_OFFSET_GAIN + pos,len);
            r = 2;
        }
    }
    return r;
}

/**
 * @brief jdksavdecc_aem_command_set_control_gain_write fills frame with SET CONTROL command for gain value
 *
 * @param p
 *        Pointer to the jdksavdecc_jdks_gain_control structure
 *
 * @param buf
 *        The raw ethernet frame packet, starting at DA,SA,Ethertype
 *
 * @param len
 *        The length of the memory at buf
 *
 * @return The length of the data parsed, or -1 on error
 */
static inline ssize_t jdksavdecc_aem_command_set_control_gain_write( struct jdksavdecc_jdks_gain_control *p, void *buf, size_t pos, size_t len)
{
	ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_JDKS_CONTROL_HEADER_LEN);

    if ( r >= 0 )
    {
        jdksavdecc_aem_command_set_control_response_write( &p->cmd, buf, pos, len );
        jdksavdecc_eui64_write( &p->vendor_eui64, buf, JDKSAVDECC_JDKS_GAIN_CONTROL_OFFSET_VENDOR_EUI64 + pos, len );
		jdksavdecc_uint16_write( p->gain, buf, JDKSAVDECC_JDKS_CONTROL_OFFSET_GAIN + pos, len );
    }
    return r;
}
/*@}*/

#ifdef __cplusplus
}
#endif

