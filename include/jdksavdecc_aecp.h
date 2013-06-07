#pragma once
#ifndef JDKSAVDECC_AECP_H
#define JDKSAVDECC_AECP_H

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
#include "jdksavdecc_pdu.h"



/** \addtogroup aecpdu AECPDU - Clause 9.2 */
/*@{*/


struct jdksavdecc_aecpdu_common_control_header
{
    uint32_t cd:1;
    uint32_t subtype:JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv:1;
    uint32_t version:JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t message_type:JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t status:JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t control_data_length:JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 target_guid;
};


static inline ssize_t jdksavdecc_aecpdu_common_control_header_read( struct jdksavdecc_aecpdu_common_control_header *p, void const *base, ssize_t pos, size_t len )
{
    return jdksavdecc_common_control_header_read( (struct jdksavdecc_common_control_header *)p, base, pos, len );
}

static inline ssize_t jdksavdecc_aecpdu_common_control_header_write( struct jdksavdecc_aecpdu_common_control_header const *p, void *base, ssize_t pos, size_t len )
{
    return jdksavdecc_common_control_header_write( (struct jdksavdecc_common_control_header const *)p, base, pos, len );
}

#define JDKSAVDECC_AECPDU_COMMON_OFFSET_CONTROLLER_GUID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+0)
#define JDKSAVDECC_AECPDU_COMMON_OFFSET_SEQUENCE_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+8)
#define JDKSAVDECC_AECPDU_COMMON_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+10)


/*@}*/


/** \addtogroup aecp_message_type aecp_message_type : message_type field - Clause 9.2.1.1.5  */
/*@{*/

#define JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND (0)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE (1)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_COMMAND (2)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_RESPONSE (3)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_COMMAND (4)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_RESPONSE (5)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_COMMAND (6)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_RESPONSE (7)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_COMMAND (8)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_RESPONSE (9)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_COMMAND (14)
#define JDKSAVDECC_AECP_MESSAGE_TYPE_EXTENDED_RESPONSE (15)

/*@}*/

/** \addtogroup aecp_status aecp_status : status field - Clause 9.2.1.1.6  */
/*@{*/

#define JDKSAVDECC_AECP_STATUS_SUCCESS (0)
#define JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED (1)

/*@}*/

#endif


