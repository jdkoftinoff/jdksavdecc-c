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
#include "jdksavdecc_frame.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup jdks Publically usable definitions and types under 
 * J.D. Koftinoff Software, Ltd.'s MAC-S (OUI-36) 70-B3-D5-ED-C
 */
/*@{*/

/** \addtogroup jdks_log Logging mechanism using multicast AECP AEM Unsolicited SET_CONTROL Response
 *  with a vendor defined blob control type
 */
/*@{*/

/// Multicast MAC address 71:b3:d5:ed:cf:ff is reserved for logging via
/// unsolicited SET_CONTROL of control descriptor of control type JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT
#define JDKSAVDECC_JDKS_MULTICAST_LOG                                                                                          \
    {                                                                                                                          \
        { 0x71, 0xb3, 0xd5, 0xed, 0xcf, 0xff }                                                                                 \
    }

extern struct jdksavdecc_eui48 jdksavdecc_jdks_multicast_log;

/// Control type value used for logging information
//      
//      Offset  0: vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT ( 70:b3:d5:ed:c0:00:00:00 )
//      Offset  8: blob_length is 8+text_length  
///     Offset 10: Doublet: source_descriptor_type
///     Offset 12:  Doublet: source_descriptor_index
///     Offset 14:  Doublet: log_sequence_id log message number from this source
///     Offset 16:  Octet: log_priority { 0 = error, 1=warning, 2=info, 3..0xffff = debug/trace
///     Offset 17:  Octet: reserved
///     Offset 18:  Octet array: utf8_chars[0..352] with no LF

#define JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT \
    { \
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x00 } \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_log_text;

#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 0)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 8)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_TYPE (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 10)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_INDEX (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 12)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_SEQUENCE_ID (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 14)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 16)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 17)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 18)
#define JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT
#define JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN (JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE - JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN)


struct jdksavdecc_jdks_log_control {
    struct jdksavdecc_aem_command_set_control_response cmd;
    struct jdksavdecc_eui64 vendor_eui64;
    uint16_t blob_size;
    uint16_t source_descriptor_type;
    uint16_t source_descriptor_index;
    uint16_t log_sequence_id;
    uint8_t log_detail;
    uint8_t reserved;
    uint8_t text[JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN+1];
};

ssize_t jdksavdecc_jdks_log_control_read(
    struct jdksavdecc_jdks_log_control *p,
    void const *buf,
    ssize_t pos,
    size_t len);

/*@}*/

/** \addtogroup jdks_ipv4 JDKS Vendor specific blob control type for setting/getting ethernet port IPv4 parameters
 */
/*@{*/

/// Control type for setting IPv4 parameters
///
/// vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS ( 70:b3:d5:ed:c0:00:00:01 )
///
/// BLOB contains:
///     Doublet interface_descriptor_type
///     Doublet interface_descriptor_index
///     Quadlet flags:
///         bit 0 = static_enable
///         bit 1 = link_local_enable
///         bit 2 = dhcp_enable
///         bit 3 = ipv4_address_valid
///         bit 4 = ipv4_netmask_valid
///         bit 5 = ipv4_gateway_valid
///         bit 6 = ipv4_broadcast_valid
///         bit 7 = dnsserver1_valid
///         bit 8 = dnsserver2_valid
///     Quadlet ipv4_address
///     Quadlet ipv4_netmask
///     Quadlet ipv4_gateway
///     Quadlet ipv4_broadcast
///     Quadlet ipv4_dnsserver1
///     Quadlet ipv4_dnsserver2


/// Control type for setting/getting network IPV4 parameters
#define JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS \
    {\
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x01 } \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_ipv4_parameters;


#ifdef __cplusplus
}
#endif
