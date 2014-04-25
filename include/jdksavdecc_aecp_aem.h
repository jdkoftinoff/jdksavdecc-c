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
#include "jdksavdecc_aecp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup aecp AECP - Clause 9 */
/*@{*/

/** \addtogroup aecpdu_aem AECPDU AEM - Clause 9.2.1.2 */
/*@{*/

/** \addtogroup aecpdu_aem AECPDU AEM - Clause 9.2.1.2 */
/*@{*/

#define JDKSAVDECC_AECPDU_AEM_OFFSET_CONTROLLER_ENTITY_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 0)
#define JDKSAVDECC_AECPDU_AEM_OFFSET_SEQUENCE_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 8)
#define JDKSAVDECC_AECPDU_AEM_OFFSET_COMMAND_TYPE (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 10)
#define JDKSAVDECC_AECPDU_AEM_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 12)

/*@}*/

/** \addtogroup aecpdu_aem_status AECPDU AEM status field - Clause 7.4  */
/*@{*/

#define JDKSAVDECC_AEM_STATUS_SUCCESS (0)
#define JDKSAVDECC_AEM_STATUS_NOT_IMPLEMENTED (1)
#define JDKSAVDECC_AEM_STATUS_NO_SUCH_DESCRIPTOR (2)
#define JDKSAVDECC_AEM_STATUS_ENTITY_LOCKED (3)
#define JDKSAVDECC_AEM_STATUS_ENTITY_ACQUIRED (4)
#define JDKSAVDECC_AEM_STATUS_NOT_AUTHENTICATED (5)
#define JDKSAVDECC_AEM_STATUS_AUTHENTICATION_DISABLED (6)
#define JDKSAVDECC_AEM_STATUS_BAD_ARGUMENTS (7)
#define JDKSAVDECC_AEM_STATUS_NO_RESOURCES (8)
#define JDKSAVDECC_AEM_STATUS_IN_PROGRESS (9)
#define JDKSAVDECC_AEM_STATUS_ENTITY_MISBEHAVING (10)
#define JDKSAVDECC_AEM_STATUS_NOT_SUPPORTED (11)
#define JDKSAVDECC_AEM_STATUS_STREAM_IS_RUNNING (12)

/*@}*/

/** \addtogroup aecpdu_aem_timeouts AECP AEM timeouts - Clause 9.2.1.2.5 */
/*@{*/
#define JDKSAVDECC_AEM_TIMEOUT_IN_MS (250)
#define JDKSAVDECC_AEM_IN_PROGRESS_TIMEOUT_IN_MS (120)
/*@}*/

/**
 * Extract the eui64 value of the controller_entity_id field of the AECPDU_AEM
 *object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui64 controller_entity_id value
 */
static inline struct jdksavdecc_eui64 jdksavdecc_aecpdu_aem_get_controller_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Store a eui64 value to the controller_entity_id field of the AECPDU_AEM
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
static inline void jdksavdecc_aecpdu_aem_set_controller_entity_id(struct jdksavdecc_eui64 v, void *base, ssize_t pos) {
    jdksavdecc_eui64_set(v, base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Extract the uint16 value of the sequence_id field of the AECPDU_AEM object
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
static inline uint16_t jdksavdecc_aecpdu_aem_get_sequence_id(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_SEQUENCE_ID);
}

/**
 * Store a uint16 value to the sequence_id field of the AECPDU_AEM object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t sequence_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecpdu_aem_set_sequence_id(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_SEQUENCE_ID);
}

/**
 * Extract the uint16 value of the command_type field of the AECPDU_AEM object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t command_type value
 */
static inline uint16_t jdksavdecc_aecpdu_aem_get_command_type(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_COMMAND_TYPE);
}

/**
 * Store a uint16 value to the command_type field of the AECPDU_AEM object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t command_type value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecpdu_aem_set_command_type(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_AEM_OFFSET_COMMAND_TYPE);
}

/*@}*/

/** \addtogroup aecpdu_aem AECPDU AEM - Clause 9.2.1.2 */
/*@{*/

/// AECPDU AEM - Clause 9.2.1.2
struct jdksavdecc_aecpdu_aem {
    struct jdksavdecc_aecpdu_common aecpdu_header;
    uint16_t command_type;
};

/**
 * Extract the avdecc_aecpdu_aem_t structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to aecpdu_aem structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_aecpdu_aem_read(struct jdksavdecc_aecpdu_aem *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AEM_LEN);
    if (r >= 0) {
        if( jdksavdecc_aecpdu_common_read(&p->aecpdu_header, base, pos, len) >= 0 ) {
            p->command_type = jdksavdecc_aecpdu_aem_get_command_type(base, pos);
        }
    }
    return r;
}

/**
 * Store the avdecc_aecpdu_aem_t structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to aecpdu_aem structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_aecpdu_aem_write(struct jdksavdecc_aecpdu_aem const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AEM_LEN);
    if (r >= 0) {
        jdksavdecc_aecpdu_common_write(&p->aecpdu_header, base, pos, len);
        jdksavdecc_aecpdu_aem_set_command_type(p->command_type, base, pos);
    }
    return r;
}

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
