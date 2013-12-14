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

/** \addtogroup appdu_dns_sd APPDU DNS-SD definitions - See IEEE Std 1722.1-2013 Annex C.2 */
/*@{*/
#define JDKSAVDECC_APPDU_DNS_SD_SERVICE_NAME                                                                                   \
    "_avdecc._tcp."                                  /// The assigned MDNS-SD service name - See IEEE Std 1722.1-2013 Annex C.2
#define JDKSAVDECC_APPDU_IANA_SERVICE_NAME "avdecc"  /// The assigned IANA service name
#define JDKSAVDECC_APPDU_TCP_PORT_STRING "17221"     /// Port as an ascii string - See IEEE Std 1722.1-2013 Annex C.2
#define JDKSAVDECC_APPDU_TCP_PORT 17221              /// Port as an integer See IEEE Std 1722.1-2013 Annex C.2
#define JDKSAVDECC_APPDU_TXT_FIELD_VERSION "Version" /// See IEEE Std 1722.1-2013 Annex C.3.1
#define JDKSAVDECC_APPDU_TXT_FIELD_PRIORITY "Priority"         /// See IEEE Std 1722.1-2013 Annex C.3.2
#define JDKSAVDECC_APPDU_TXT_FIELD_DESCRIPTION "Description"   /// See IEEE Std 1722.1-2013 Annex C.3.3
#define JDKSAVDECC_APPDU_TXT_FIELD_MANUFACTURER "Manufacturer" /// See IEEE Std 1722.1-2013 Annex C.3.4
#define JDKSAVDECC_APPDU_TXT_FIELD_PATH "path"                 /// See IEEE Std 1722.1-2013 Annex C.3.5
                                                               /*@}*/

/**\addtogroup appdu_offset APPDU Offsets - See IEEE Std 1722.1-2013 Annex C.4 */
/*@{*/
#define JDKSAVDECC_APPDU_OFFSET_VERSION (0)        /// See IEEE Std 1722.1-2013 Annex C.4.1
#define JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE (1)   /// See IEEE Std 1722.1-2013 Annex C.4.2
#define JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH (2) /// See IEEE Std 1722.1-2013 Annex C.4.3
#define JDKSAVDECC_APPDU_OFFSET_ADDRESS (4)        /// See IEEE Std 1722.1-2013 Annex C.4.4
#define JDKSAVDECC_APPDU_OFFSET_RESERVED (10)      /// See IEEE Std 1722.1-2013 Annex C.4
#define JDKSAVDECC_APPDU_OFFSET_PAYLOAD (12)       /// See IEEE Std 1722.1-2013 Annex C.4.5
#define JDKSAVDECC_APPDU_HEADER_LEN (12)           /// See IEEE Std 1722.1-2013 Annex C.4
                                                   /*@}*/

/**\addtogroup appdu_constants - See IEEE Std 1722.1-2013 Annex C.4 */
/*@{*/
#define JDKSAVDECC_APPDU_VERSION (0)                         /// See IEEE Std 1722.1-2013 Annex C.4.1
#define JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH (1500)           /// See IEEE Std 1722.1-2013 Annex C.4.3
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP (0)                /// See IEEE Std 1722.1-2103 Annex C.5.1.1
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST (1)  /// See IEEE Std 1722.1-2103 Annex C.5.1.2
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE (2) /// See IEEE Std 1722.1-2103 Annex C.5.1.3
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP (3)            /// See IEEE Std 1722.1-2103 Annex C.5.1.4
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN (4)          /// See IEEE Std 1722.1-2103 Annex C.5.1.5
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS (5)    /// See IEEE Std 1722.1-2103 Annex C.5.1.6
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC (6)    /// See IEEE Std 1722.1-2103 Annex C.5.1.7
#define JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR (0xff)          /// See IEEE Std 1722.1-2103 Annex C.5.1.8
                                                             /*@}*/

/**\addtogroup appdu_errors - See IEEE Std 1722.1-2013 Annex C.4 */
/*@{*/
#define JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT (-1) /// The buffer length is insufficent
#define JDKSAVDECC_APPDU_ERROR_PAYLOAD_INCOMPLETE                                                                              \
    (-2)                                           /// The network buffer does not contain enough bytes for the declared payload
#define JDKSAVDECC_APPDU_ERROR_INVALID_HEADER (-3) /// The parsed data does not contain valid data
                                                   /*@}*/

/// The APPDU
/// Note: payload always points to an existing packet buffer
struct jdksavdecc_appdu {
    uint8_t version;                 /// See IEEE Std 1722.1-2013 Annex C.4.1
    uint8_t message_type;            /// See IEEE Std 1722.1-2013 Annex C.4.2
    uint16_t payload_length;         /// See IEEE Std 1722.1-2013 Annex C.4.3
    struct jdksavdecc_eui48 address; /// See IEEE Std 1722.1-2013 Annex C.4
    uint8_t reserved;                /// See IEEE Std 1722.1-2013 Annex C.4
    uint8_t *payload;                /// See IEEE Std 1722.1-2013 Annex C.4.5
};

/**
 * Extract the jdksavdec_appdu structure from a network buffer.
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to appdu structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return
 *         * JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT
 *         * JDKSAVDECC_APPDU_ERROR_PAYLOAD_INCOMPLETE
 *         * JDKSAVDECC_APPDU_ERROR_INVALID_HEADER
 *         * otherwise is the offset of the octet following the structure in the buffer, and the p->payload field is set to
 *point to the raw network buffer directly
 *
 */
static inline ssize_t jdksavdec_appdu_read(struct jdksavdecc_appdu *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_HEADER_LEN);
    if (r >= 0) {
        p->version = jdksavdecc_uint8_get(base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION);
        if (p->version == JDKSAVDECC_APPDU_VERSION) {
            p->message_type = jdksavdecc_uint8_get(base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE);
            p->payload_length = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH);
            p->address = jdksavdecc_eui48_get(base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS);
            p->reserved = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED);

            // make sure that the payload_length is a reasonable number
            if (p->payload_length <= JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH) {
                // make sure we have enough data in the incoming buffer for the entire payload
                r = jdksavdecc_validate_range(pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, len, p->payload_length);

                if (r >= 0) {
                    // The payload is complete.
                    // Make payload pointer point directly within incoming raw buffer
                    p->payload = ((uint8_t *)base) + JDKSAVDECC_APPDU_OFFSET_PAYLOAD;
                } else {
                    // the raw buffer is incomplete.
                    p->payload = 0;
                    r = JDKSAVDECC_APPDU_ERROR_PAYLOAD_INCOMPLETE;
                }
            } else {
                // The payload_length field is out of range.
                r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
            }
        } else {
            // The protocol version is unsupported
            r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
        }
    }
    return r;
}

/**
 * Store the jdksavdecc_appdu_write structure to a network buffer.
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to appdu structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT if the buffer length is insufficent
 *         otherwise the offset of the octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_appdu_write(struct jdksavdecc_appdu const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_HEADER_LEN);
    if (r >= 0) {
        jdksavdecc_uint8_set(p->version, base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION);
        jdksavdecc_uint8_set(p->message_type, base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE);
        jdksavdecc_uint16_set(p->payload_length, base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH);
        jdksavdecc_eui48_set(p->address, base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS);
        jdksavdecc_uint16_set(p->reserved, base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED);
        if (p->payload_length > 0) {
            if (p->payload && p->payload_length <= JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH) {
                // We have a payload and the payload length is non zero, make sure we have space in the output buffer
                r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_APPDU_OFFSET_PAYLOAD + p->payload_length);
                if (r > 0) {
                    // we have space so copy it over
                    memcpy(((uint8_t *)base) + pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, p->payload, p->payload_length);
                } else {
                    // we don't have space, so return error
                    r = JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT;
                }
            } else {
                // we have payload length but no payload? that is invalid.
                r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
            }
        }
    }
    return r;
}

/*@}*/
#ifdef __cplusplus
}
#endif
