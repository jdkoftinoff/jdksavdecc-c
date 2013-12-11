#pragma once

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

#ifdef __cplusplus
extern "C" {
#endif

#define JDKSAVDECC_APPDU_DNS_SD_SERVICE_NAME "_avdecc._tcp."
#define JDKSAVDECC_APPDU_TCP_PORT_STRING "17221"
#define JDKSAVDECC_APPDU_TCP_PORT 17221
#define JDKSAVDECC_APPDU_TXT_FIELD_VERSION "Version"
#define JDKSAVDECC_APPDU_TXT_FIELD_PRIORITY "Priority"
#define JDKSAVDECC_APPDU_TXT_FIELD_DESCRIPTION "Description"
#define JDKSAVDECC_APPDU_TXT_FIELD_MANUFACTURER "Manufacturer"
#define JDKSAVDECC_APPDU_TXT_FIELD_PATH "path"

#define JDKSAVDECC_APPDU_OFFSET_VERSION (0)
#define JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE (1)
#define JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH (2)
#define JDKSAVDECC_APPDU_OFFSET_ADDRESS (4)
#define JDKSAVDECC_APPDU_OFFSET_RESERVED (10)
#define JDKSAVDECC_APPDU_OFFSET_PAYLOAD (12)

#define JDKSAVDECC_APPDU_HEADER_LEN (12)

#define JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP (0)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST (1)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE (2)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP (3)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN (4)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS (5)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC (6)
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR (0xff)

struct jdksavdecc_appdu {
    uint8_t version;
    uint8_t message_type;
    uint16_t payload_length;
    struct jdksavdecc_eui48 address;
    uint8_t reserved;
    uint8_t *payload;
};

/**
 * Extract the jdksavdec_appdu structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to appdu structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdec_appdu_read(struct jdksavdecc_appdu *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_HEADER_LEN);
    if (r >= 0) {
        p->version = jdksavdecc_uint8_get(base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION);
        p->message_type = jdksavdecc_uint8_get(base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE);
        p->payload_length = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH);
        p->address = jdksavdecc_eui48_get(base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS);
        p->reserved = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED);
        r = jdksavdecc_validate_range(pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, len, p->payload_length);
        if (r >= 0) {
            p->payload = ((uint8_t *)base) + JDKSAVDECC_APPDU_OFFSET_PAYLOAD;
        } else {
            p->payload = 0;
        }
    }
    return r;
}

/**
 * Store the jdksavdecc_appdu_write structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to appdu structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_appdu_write(struct jdksavdecc_appdu const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_HEADER_LEN);
    if (r >= 0) {
        jdksavdecc_uint8_set(p->version, base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION);
        jdksavdecc_uint8_set(p->message_type, base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE);
        jdksavdecc_uint16_set(p->payload_length, base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH);
        jdksavdecc_eui48_set(p->address, base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS);
        jdksavdecc_uint16_set(p->reserved, base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED);
        r = pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD + p->payload_length;
        if (p->payload_length > 0) {
            if (p->payload != 0 && jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_OFFSET_PAYLOAD + p->payload_length)) {
                memcpy(((uint8_t *)base) + pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, p->payload, p->payload_length);
            } else {
                r = -1;
            }
        }
    }
    return r;
}

/*@}*/
#ifdef __cplusplus
}
#endif
