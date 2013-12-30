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

/** \addtogroup aecp AECP - Clause 9 */
/*@{*/

/** \addtogroup aecpdu AECPDU - Clause 9.2 */
/*@{*/

struct jdksavdecc_aecpdu_common_control_header {
    uint32_t cd : 1;
    uint32_t subtype : JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv : 1;
    uint32_t version : JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t message_type : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t status : JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t control_data_length : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 target_entity_id;
};

static inline ssize_t jdksavdecc_aecpdu_common_control_header_read(struct jdksavdecc_aecpdu_common_control_header *p,
                                                                   void const *base,
                                                                   ssize_t pos,
                                                                   size_t len) {
    return jdksavdecc_common_control_header_read((struct jdksavdecc_common_control_header *)p, base, pos, len);
}

static inline ssize_t jdksavdecc_aecpdu_common_control_header_write(struct jdksavdecc_aecpdu_common_control_header const *p,
                                                                    void *base,
                                                                    ssize_t pos,
                                                                    size_t len) {
    return jdksavdecc_common_control_header_write((struct jdksavdecc_common_control_header const *)p, base, pos, len);
}

#define JDKSAVDECC_AECPDU_COMMON_OFFSET_CONTROLLER_ENTITY_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 0)
#define JDKSAVDECC_AECPDU_COMMON_OFFSET_SEQUENCE_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 8)
#define JDKSAVDECC_AECPDU_COMMON_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 10)
#define JDKSAVDECC_AECP_MAX_CONTROL_DATA_LENGTH (524) /// Clause 9.2.1.1.7

/*@}*/

/** \addtogroup aecp_message_type AECPDU message_type field
 * See Clause 9.2.1.1.5  */
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

/** \addtogroup aecp_status AECPDU status field - Clause 9.2.1.1.6  */
/*@{*/

#define JDKSAVDECC_AECP_STATUS_SUCCESS (0)
#define JDKSAVDECC_AECP_STATUS_NOT_IMPLEMENTED (1)

/*@}*/

/** \addtogroup aecpdu_common AECPDU Common - Clause 9.2.1.1 */
/*@{*/

/**
 * Extract the eui64 value of the controller_entity_id field of the
 *aecpdu_common object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui64 controller_entity_id value
 */
static inline struct jdksavdecc_eui64 jdksavdecc_aecpdu_common_get_controller_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(base, pos + JDKSAVDECC_AECPDU_COMMON_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Store a eui64 value to the controller_entity_id field of the aecpdu_common
 *object to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui64 controller_entity_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecpdu_common_set_controller_entity_id(struct jdksavdecc_eui64 v, void *base, ssize_t pos) {
    jdksavdecc_eui64_set(v, base, pos + JDKSAVDECC_AECPDU_COMMON_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Extract the uint16 value of the sequence_id field of the aecpdu_common object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t sequence_id value
 */
static inline uint16_t jdksavdecc_aecpdu_common_get_sequence_id(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_COMMON_OFFSET_SEQUENCE_ID);
}

/**
 * Store a uint16 value to the sequence_id field of the aecpdu_common object to
 *a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t sequence_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecpdu_common_set_sequence_id(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_COMMON_OFFSET_SEQUENCE_ID);
}

/*@}*/

/** \addtogroup aecpdu_common AECPDU Common - Clause 9.2.1.1 */
/*@{*/

/// AECPDU Common - Clause 9.2.1.1
struct jdksavdecc_aecpdu_common {
    struct jdksavdecc_aecpdu_common_control_header header;
    struct jdksavdecc_eui64 controller_entity_id;
    uint16_t sequence_id;
};

/**
 * Extract the jdksavdecc_aecpdu_common_t structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to aecpdu_common structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t
jdksavdecc_aecpdu_common_read(struct jdksavdecc_aecpdu_common *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_COMMON_LEN);
    if (r >= 0) {
        jdksavdecc_aecpdu_common_control_header_read(&p->header, base, pos, len);
        p->controller_entity_id = jdksavdecc_aecpdu_common_get_controller_entity_id(base, pos);
        p->sequence_id = jdksavdecc_aecpdu_common_get_sequence_id(base, pos);
    }
    return r;
}

/**
 * Store the jdksavdecc_aecpdu_common_t structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to aecpdu_common structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t
jdksavdecc_aecpdu_common_write(struct jdksavdecc_aecpdu_common const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_COMMON_LEN);
    if (r >= 0) {
        jdksavdecc_aecpdu_common_control_header_write(&p->header, base, pos, len);
        jdksavdecc_aecpdu_common_set_controller_entity_id(p->controller_entity_id, base, pos);
        jdksavdecc_aecpdu_common_set_sequence_id(p->sequence_id, base, pos);
    }
    return r;
}

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
