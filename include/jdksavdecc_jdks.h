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

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup jdks Publically usable definitions and types under 
 * J.D. Koftinoff Software, Ltd.'s MAC-S (OUI-36) 70-B3-D5-ED-C
 */
/*@{*/

/// Multicast MAC address for logging via
/// unsolicited SET_CONTROL of control descriptor of
/// control type JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT
#define JDKSAVDECC_JDKS_MULTICAST_LOG                                                                                          \
    {                                                                                                                          \
        { 0x71, 0xb3, 0xd5, 0xed, 0xcf, 0xff }                                                                                 \
    }

/// Control type used for logging information
//      vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT
//      
/// BLOB contains:
///     Offset 0  Doublet: source_descriptor_type
///     Offset 2  Doublet: source_descriptor_index
///     Offset 4  Octet: log_priority { 0 = error, 1=warning, 2=info, 3..0xffff = debug/trace
///     Offset 5  Octet: reserved
///     Offset 6  Octet array: utf8_chars[0..354] with no LF

#define JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT \
    { \
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x00 } \
    }

/// Control type for setting IPv4 parameters
/// BLOB contains:
///     Doublet interface_descriptor_type
///     Doublet interface_descriptor_index
///     Quadlet flags
///     Quadlet ipv4_address
///     Quadlet ipv4_netmask
///     Quadlet ipv4_gateway
#define JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS \
    {\
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x01 } \
    }

/// Control type for setting/getting network PHY parameters
#define JDKSAVDECC_JDKS_AEM_CONTROL_PHY_PARAMETERS \
    {\
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x02 } \
    }


#ifdef __cplusplus
}
#endif
