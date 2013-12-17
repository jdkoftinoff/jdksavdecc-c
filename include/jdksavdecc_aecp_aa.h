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

/** \addtogroup AECP_AA AECP Address Access - Clause 9.2.1.3 */
/*@{*/

/** \addtogroup AECP_AA_offsets AECP Address Access Offsets - Clause 9.2.1.3 */
/*@{*/

#define JDKSAVDECC_AECPDU_AA_OFFSET_CONTROLLER_ENTITY_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 0)
#define JDKSAVDECC_AECPDU_AA_OFFSET_SEQUENCE_ID (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 8)
#define JDKSAVDECC_AECPDU_AA_OFFSET_TLV_COUNT (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 10)
#define JDKSAVDECC_AECPDU_AA_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 12)

/*@}*/

/** \addtogroup AECP_AA_tlv AECP Address Access TLV Offsets - Clause 9.2.1.3.3 */
/*@{*/

#define JDKSAVDECC_AECPDU_AA_TLV_OFFSET_MODE_LENGTH (0)
#define JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_UPPER (2)
#define JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_LOWER (6)
#define JDKSAVDECC_AECPDU_AA_TLV_LEN (10)

/*@}*/

/** \addtogroup AECP_AA_mode AECP Address Access mode - Clause 9.2.1.3.3 */
/*@{*/

#define JDKSAVDECC_AECP_AA_MODE_READ (0)
#define JDKSAVDECC_AECP_AA_MODE_WRITE (1)
#define JDKSAVDECC_AECP_AA_MODE_EXECUTE (2)

/*@}*/

/** \addtogroup AECP_AA_tlv AECP Address Access TLV Status - Clause 9.2.1.3.4 */
/*@{*/

#define JDKSAVDECC_AECP_AA_STATUS_SUCCESS (0)
#define JDKSAVDECC_AECP_AA_STATUS_NOT_IMPLEMENTED (1)
#define JDKSAVDECC_AECP_AA_STATUS_ADDRESS_TOO_LOW (2)
#define JDKSAVDECC_AECP_AA_STATUS_ADDRESS_TOO_HIGH (3)
#define JDKSAVDECC_AECP_AA_STATUS_ADDRESS_INVALID (4)
#define JDKSAVDECC_AECP_AA_STATUS_TLV_INVALID (5)
#define JDKSAVDECC_AECP_AA_STATUS_DATA_INVALID (6)
#define JDKSAVDECC_AECP_AA_STATUS_UNSUPPORTED (7)

/*@}*/

/** \addtogroup AECP_AA_timeouts AECP Address Access timeouts - Clause 9.2.1.3.4 */
/*@{*/
#define JDKSAVDECC_AECP_AA_TIMEOUT_IN_MS (250)
/*@}*/



/**
 * Extract the eui64 value of the controller_entity_id field of the aecp_aa
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
static inline struct jdksavdecc_eui64 jdksavdecc_aecp_aa_get_controller_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Store a eui64 value to the controller_entity_id field of the aecp_aa object
 *to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui64 controller_entity_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecp_aa_set_controller_entity_id(struct jdksavdecc_eui64 v, void *base, ssize_t pos) {
    jdksavdecc_eui64_set(v, base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Extract the uint16 value of the sequence_id field of the aecp_aa object
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
static inline uint16_t jdksavdecc_aecp_aa_get_sequence_id(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_SEQUENCE_ID);
}

/**
 * Store a uint16 value to the sequence_id field of the aecp_aa object to a
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
static inline void jdksavdecc_aecp_aa_set_sequence_id(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_SEQUENCE_ID);
}

/**
 * Extract the uint16 value of the tlv_count field of the aecp_aa object from
 *a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t tlv_count value
 */
static inline uint16_t jdksavdecc_aecp_aa_get_tlv_count(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_TLV_COUNT);
}

/**
 * Store a uint16 value to the tlv_count field of the aecp_aa object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t tlv_count value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecp_aa_set_tlv_count(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_AA_OFFSET_TLV_COUNT);
}

/*@}*/

/** \addtogroup AECP_AA AECPDU Address Access - Clause 9.2.1.3 */
/*@{*/

/// AECPDU Address Access - Clause 9.2.1.3
struct jdksavdecc_aecp_aa {
    struct jdksavdecc_aecpdu_common aecpdu_header;
    struct jdksavdecc_eui64 controller_entity_id;
    uint16_t sequence_id;
    uint16_t tlv_count;
};

/**
 * Extract the jdksavdecc_AECP_AA_t structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to AECP_AA structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_AECP_AA_read(struct jdksavdecc_aecp_aa *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AA_LEN);
    if (r >= 0) {
        jdksavdecc_aecpdu_common_read(&p->aecpdu_header, base, pos, len);
        p->controller_entity_id = jdksavdecc_aecp_aa_get_controller_entity_id(base, pos);
        p->sequence_id = jdksavdecc_aecp_aa_get_sequence_id(base, pos);
        p->tlv_count = jdksavdecc_aecp_aa_get_tlv_count(base, pos);
    }
    return r;
}

/**
 * Store the jdksavdecc_aecp_aa structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to AECP_AA structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_aecp_aa_write(struct jdksavdecc_aecp_aa const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AA_LEN);
    if (r >= 0) {
        jdksavdecc_aecpdu_common_write(&p->aecpdu_header, base, pos, len);
        jdksavdecc_aecp_aa_set_controller_entity_id(p->controller_entity_id, base, pos);
        jdksavdecc_aecp_aa_set_sequence_id(p->sequence_id, base, pos);
        jdksavdecc_aecp_aa_set_tlv_count(p->tlv_count, base, pos);
    }
    return r;
}

/*@}*/

/** \addtogroup aecp_aa_tlv AECPDU Address Access TLV - Clause 9.2.1.3.3 */
/*@{*/

/**
 * Extract the uint16 value of the mode_length field of the AECPDU_TLV object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t mode_length value
 */
static inline uint16_t jdksavdecc_aecp_aa_tlv_get_mode_length(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_MODE_LENGTH);
}

/**
 * Store a uint16 value to the mode_length field of the AECPDU_TLV object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t mode_length value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecp_aa_tlv_set_mode_length(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_MODE_LENGTH);
}

/**
 * Extract the uint32 value of the address_upper field of the AECPDU_TLV object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint32_t address_upper value
 */
static inline uint32_t jdksavdecc_aecp_aa_tlv_get_address_upper(void const *base, ssize_t pos) {
    return jdksavdecc_uint32_get(base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_UPPER);
}

/**
 * Store a uint32 value to the address_upper field of the AECPDU_TLV object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint32_t address_upper value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecp_aa_tlv_set_address_upper(uint32_t v, void *base, ssize_t pos) {
    jdksavdecc_uint32_set(v, base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_UPPER);
}

/**
 * Extract the uint32 value of the address_lower field of the AECPDU_TLV object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint32_t address_lower value
 */
static inline uint32_t jdksavdecc_aecp_aa_tlv_get_address_lower(void const *base, ssize_t pos) {
    return jdksavdecc_uint32_get(base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_LOWER);
}

/**
 * Store a uint32 value to the address_lower field of the AECPDU_TLV object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint32_t address_lower value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_aecp_aa_tlv_set_address_lower(uint32_t v, void *base, ssize_t pos) {
    jdksavdecc_uint32_set(v, base, pos + JDKSAVDECC_AECPDU_AA_TLV_OFFSET_ADDRESS_LOWER);
}

/*@}*/

/** \addtogroup aecp_aa_tlv AECPDU Address Access TLV - Clause 9.2.1.3.3 */
/*@{*/

/// AECPDU Address Access TLV - Clause 9.2.1.3.3
struct jdksavdecc_aecp_aa_tlv {
    uint16_t mode_length;
    uint32_t address_upper;
    uint32_t address_lower;
};

/**
 * Extract the jdksavdecc_aecpdu_tlv_t structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to aecpdu_tlv structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_aecp_aa_tlv_read(struct jdksavdecc_aecp_aa_tlv *p, void const *base, ssize_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AA_TLV_LEN);
    if (r >= 0) {
        p->mode_length = jdksavdecc_aecp_aa_tlv_get_mode_length(base, pos);
        p->address_upper = jdksavdecc_aecp_aa_tlv_get_address_upper(base, pos);
        p->address_lower = jdksavdecc_aecp_aa_tlv_get_address_lower(base, pos);
    }
    return r;
}

/**
 * Store the jdksavdecc_aecpdu_tlv_t structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to aecpdu_tlv structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_aecp_aa_tlv_write(struct jdksavdecc_aecp_aa_tlv const *p, void *base, size_t pos, size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_AECPDU_AA_TLV_LEN);
    if (r >= 0) {
        jdksavdecc_aecp_aa_tlv_set_mode_length(p->mode_length, base, pos);
        jdksavdecc_aecp_aa_tlv_set_address_upper(p->address_upper, base, pos);
        jdksavdecc_aecp_aa_tlv_set_address_lower(p->address_lower, base, pos);
    }
    return r;
}


/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
