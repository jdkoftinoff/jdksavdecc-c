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
#include "jdksavdecc_util.h"
#include "jdksavdecc_frame.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup pdu AVTP and AVDECC PDU definitions */
/*@{*/

#define JDKSAVDECC_AVTP_ETHERTYPE (0x22f0)     /// See IEEE Std 1722-2011 Clause 5.1.2
#define JDKSAVDECC_AVTP_V0_PAYLOAD_OFFSET (12) /// See IEEE Std 1722-2011 Clause 5.2

/// See IEEE Std 1722-2011 Annex B
#define JDKSAVDECC_MULTICAST_MAAP                                                                                              \
    {                                                                                                                          \
        { 0x91, 0xe0, 0xf0, 0x00, 0xff, 0x00 }                                                                                 \
    }

/// See IEEE Std 1722-2011 Annex B
extern struct jdksavdecc_eui48 jdksavdecc_multicast_maap;

/// See Annex B.1
#define JDKSAVDECC_MULTICAST_ADP_ACMP                                                                                          \
    {                                                                                                                          \
        { 0x91, 0xe0, 0xf0, 0x01, 0x00, 0x00 }                                                                                 \
    }
extern struct jdksavdecc_eui48 jdksavdecc_multicast_adp_acmp;

/// See Annex B.1
#define JDKSAVDECC_MULTICAST_IDENTIFICATION                                                                                    \
    {                                                                                                                          \
        { 0x91, 0xe0, 0xf0, 0x01, 0x00, 0x01 }                                                                                 \
    }

/// See Annex B.1
extern struct jdksavdecc_eui48 jdksavdecc_multicast_identification;

#define JDKSAVDECC_MULTICAST_MAAP_MAC (0x91e0f000ff00ULL)           /// See IEEE 1722a Annex B
#define JDKSAVDECC_MULTICAST_ADP_ACMP_MAC (0x91e0f0010000ULL)       /// See Annex B.1
#define JDKSAVDECC_MULTICAST_IDENTIFICATION_MAC (0x91e0f0010001ULL) /// See Annex B.1

/// See IEEE Std 1722.1-2013 Clause 7.5.1
#define JDKSAVDECC_IDENTIFICATION_NOTIFICATION_CONTROLLER_ENTITY_ID                                                            \
    {                                                                                                                          \
        { 0x90, 0xe0, 0xf0, 0xff, 0xfe, 0x01, 0x00, 0x01 }                                                                     \
    }

/// See IEEE Std 1722.1-2013 Clause 7.5.1
extern struct jdksavdecc_eui64 jdksavdecc_identification_notification_controller_entity_id;

#define JDKSAVDECC_IDENTIFICATION_NOTIFICATION_CONTROLLER_ENTITY_ID_L (0x90e0f0fffe010001ULL) /// See Clause 7.5.1

#define JDKSAVDECC_STRING_REFERENCE_OFFSET(a) ((a >> 3) & 0x1fff)                    /// See Clause 7.3.6
#define JDKSAVDECC_STRING_REFERENCE_INDEX(a) (a & 0x7)                               /// See Clause 7.3.6
#define JDKSAVDECC_STRING_REFERENCE(offset, index) (((offset) << 3) | (index & 0x7)) /// See Clause 7.3.6
#define JDKSAVDECC_NO_STRING ((0x1fff << 3) + 7)                                     /// See Clause 7.3.6

/** \addtogroup subtype AVTP Subtype definitions - See IEEE P1722a D5 */
/*@{*/

#define JDKSAVDECC_SUBTYPE_61883_IIDC (0x00)
#define JDKSAVDECC_SUBTYPE_MMA (0x01)
#define JDKSAVDECC_SUBTYPE_AVTP_AUDIO (0x02)
#define JDKSAVDECC_SUBTYPE_AVTP_VIDEO (0x03)
#define JDKSAVDECC_SUBTYPE_AVTP_CONTROL (0x04)
#define JDKSAVDECC_SUBTYPE_VENDOR (0x6f)
#define JDKSAVDECC_SUBTYPE_ADP (0x7a)
#define JDKSAVDECC_SUBTYPE_AECP (0x7b)
#define JDKSAVDECC_SUBTYPE_ACMP (0x7c)
#define JDKSAVDECC_SUBTYPE_MAAP (0x7e)
#define JDKSAVDECC_SUBTYPE_EXPERIMENTAL (0x7f)

/*@}*/

/** \addtogroup jdksavdecc_subtype_data AVTP subtype_data field - See IEEE Std 1722-2011 Clause 5.3 */
/*@{*/

#define JDKSAVDECC_SUBTYPE_DATA_CD_BIT (0)
#define JDKSAVDECC_SUBTYPE_DATA_CD (0x80000000UL)
#define JDKSAVDECC_SUBTYPE_DATA_CD_MASK (~0x80000000UL)

static inline uint32_t jdksavdecc_subtype_data_get_cd(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_CD) >> (31 - JDKSAVDECC_SUBTYPE_DATA_CD_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_cd(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_CD_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_CD_BIT)) & JDKSAVDECC_SUBTYPE_DATA_CD);
}

#define JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_BIT (7)
#define JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH (7)
#define JDKSAVDECC_SUBTYPE_DATA_SUBTYPE (0x7f000000UL)
#define JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_MASK (~0x7f000000UL)

static inline uint32_t jdksavdecc_subtype_data_get_subtype(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_SUBTYPE) >> (31 - JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_subtype(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_BIT)) & JDKSAVDECC_SUBTYPE_DATA_SUBTYPE);
}

#define JDKSAVDECC_SUBTYPE_DATA_SV_BIT (8)
#define JDKSAVDECC_SUBTYPE_DATA_SV (0x00800000UL)
#define JDKSAVDECC_SUBTYPE_DATA_SV_MASK (~0x00800000UL)

static inline uint32_t jdksavdecc_subtype_data_get_sv(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_SV) >> (31 - JDKSAVDECC_SUBTYPE_DATA_SV_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_sv(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_SV_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_SV_BIT)) & JDKSAVDECC_SUBTYPE_DATA_SV);
}

#define JDKSAVDECC_SUBTYPE_DATA_VERSION_BIT (11)
#define JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH (3)
#define JDKSAVDECC_SUBTYPE_DATA_VERSION (uint32_t)(0x00700000UL)
#define JDKSAVDECC_SUBTYPE_DATA_VERSION_MASK (uint32_t)(0xFF8FFFFFUL)

static inline uint32_t jdksavdecc_subtype_data_get_version(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_VERSION) >> (31 - JDKSAVDECC_SUBTYPE_DATA_VERSION_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_version(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_VERSION_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_VERSION_BIT)) & JDKSAVDECC_SUBTYPE_DATA_VERSION);
}

#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_BIT (15)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH (4)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA (uint32_t)(0x000f0000UL)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_MASK (uint32_t)(0xFFF0FFFFUL)

static inline uint32_t jdksavdecc_subtype_data_get_control_data(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA) >> (31 - JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_BIT);
}

static inline uint32_t avtp_subtype_data_set_control_data(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_BIT)) & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA);
}

#define JDKSAVDECC_SUBTYPE_DATA_STATUS_BIT (20)
#define JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH (5)
#define JDKSAVDECC_SUBTYPE_DATA_STATUS (uint32_t)(0x0000f800UL)
#define JDKSAVDECC_SUBTYPE_DATA_STATUS_MASK (uint32_t)(0xFFFF07FFUL)

static inline uint32_t jdksavdecc_subtype_data_get_status(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STATUS) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STATUS_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_status(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STATUS_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STATUS_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STATUS);
}

#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_BIT (31)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH (11)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH (uint32_t)(0x000007ffUL)
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_MASK (uint32_t)(0xFFFFF800UL)

static inline uint32_t jdksavdecc_subtype_data_get_control_data_length(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH) >> (31 - JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_control_data_length(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_BIT)) & JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH);
}

#define JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_BIT (12)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_WIDTH (1)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_MR (uint32_t)(0x00080000UL)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_MASK (~JDKSAVDECC_SUBTYPE_DATA_STREAM_MR)

static inline uint32_t jdksavdecc_subtype_data_get_mr(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STREAM_MR) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_mr(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STREAM_MR);
}

#define JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_BIT (14)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_WIDTH (1)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_GV (uint32_t)(0x00020000UL)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_MASK (~JDKSAVDECC_SUBTYPE_DATA_STREAM_GV)

static inline uint32_t jdksavdecc_subtype_data_get_gv(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STREAM_GV) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_gv(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STREAM_GV);
}

#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_BIT (15)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_WIDTH (1)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TV (uint32_t)(0x00010000UL)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_MASK (~JDKSAVDECC_SUBTYPE_DATA_STREAM_TV)

static inline uint32_t jdksavdecc_subtype_data_get_tv(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STREAM_TV) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_tv(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STREAM_TV);
}

#define JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_BIT (22)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_WIDTH (8)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM (uint32_t)(0x0000ff00UL)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_MASK (~JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM)

static inline uint32_t jdksavdecc_subtype_data_get_sequence_num(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_sequence_num(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM);
}

#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_BIT (31)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_WIDTH (1)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TU (uint32_t)(0x00000001UL)
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_MASK (~JDKSAVDECC_SUBTYPE_DATA_STREAM_TU)

static inline uint32_t jdksavdecc_subtype_data_get_tu(uint32_t v) {
    return (v & JDKSAVDECC_SUBTYPE_DATA_STREAM_TU) >> (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_BIT);
}

static inline uint32_t jdksavdecc_subtype_data_set_tu(uint32_t subtype_data, uint32_t v) {
    return (subtype_data & JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_MASK)
           | ((v << (31 - JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_BIT)) & JDKSAVDECC_SUBTYPE_DATA_STREAM_TU);
}

/*@}*/

/** \addtogroup avtp_common_control_header AVTP common control header - See IEEE 1722-2011 Clause 5.3 */
/*@{*/

#define JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_SUBTYPE_DATA (0)
#define JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID (4)
#define JDKSAVDECC_COMMON_CONTROL_HEADER_LEN (12)

static inline uint32_t jdksavdecc_common_control_header_get_subtype_data(void const *base, size_t pos) {
    uint32_t subtype_data;
    jdksavdecc_uint32_read(&subtype_data, base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_SUBTYPE_DATA);
    return subtype_data;
}

static inline void jdksavdecc_common_control_header_set_subtype_data(uint32_t subtype_data, void *base, size_t pos) {
    jdksavdecc_uint32_set(subtype_data, base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_SUBTYPE_DATA);
}

static inline uint32_t jdksavdecc_common_control_header_get_cd(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_cd(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_cd(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_cd(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_subtype(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_subtype(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_subtype(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_subtype(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_sv(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_sv(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_sv(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_sv(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_version(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_version(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_version(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_version(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_control_data(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_control_data(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_control_data(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = avtp_subtype_data_set_control_data(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_status(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_status(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_status(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_status(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_control_header_get_control_data_length(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_control_data_length(jdksavdecc_common_control_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_control_header_set_control_data_length(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_control_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_control_data_length(subtype_data, v);
    jdksavdecc_common_control_header_set_subtype_data(subtype_data, base, pos);
}

static inline struct jdksavdecc_eui64 jdksavdecc_common_control_header_get_stream_id(void const *base, size_t pos) {
    return jdksavdecc_eui64_get(base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID);
}

static inline void jdksavdecc_common_control_header_set_stream_id(struct jdksavdecc_eui64 v, void *base, size_t pos) {
    jdksavdecc_eui64_set(v, base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID);
}

struct jdksavdecc_common_control_header {
    uint32_t cd : 1;
    uint32_t subtype : JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv : 1;
    uint32_t version : JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t control_data : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t status : JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t control_data_length : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 stream_id;
};

ssize_t jdksavdecc_common_control_header_read(struct jdksavdecc_common_control_header *p,
                                              void const *base,
                                              ssize_t pos,
                                              size_t len);
ssize_t jdksavdecc_common_control_header_write(struct jdksavdecc_common_control_header const *p,
                                               void *base,
                                               ssize_t pos,
                                               size_t len);

/*@}*/

/** \addtogroup avtp_common_stream_header AVTP common stream header - See IEEE Std 1722-2011 Clause 5.4 */
/*@{*/

#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA (0)
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID (4)
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP (12)
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO (16)
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH (20)
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER (22)
#define JDKSAVDECC_COMMON_STREAM_HEADER_LEN (24)

static inline uint32_t jdksavdecc_common_stream_header_get_subtype_data(void const *base, size_t pos) {
    uint32_t subtype_data;
    jdksavdecc_uint32_read(&subtype_data, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA);
    return subtype_data;
}

static inline void jdksavdecc_common_stream_header_set_subtype_data(uint32_t subtype_data, void *base, size_t pos) {
    jdksavdecc_uint32_set(subtype_data, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA);
}

static inline uint32_t jdksavdecc_common_stream_header_get_cd(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_cd(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_cd(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_cd(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_subtype(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_subtype(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_subtype(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_subtype(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_sv(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_sv(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_sv(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_sv(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_version(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_version(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_version(uint32_t v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_version(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_mr(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_mr(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_mr(int v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_mr(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_gv(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_gv(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_gv(int v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_gv(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_tv(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_tv(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_tv(int v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_tv(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_sequence_num(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_sequence_num(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_sequence_num(int v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_sequence_num(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline uint32_t jdksavdecc_common_stream_header_get_tu(void const *base, size_t pos) {
    return jdksavdecc_subtype_data_get_tu(jdksavdecc_common_stream_header_get_subtype_data(base, pos));
}

static inline void jdksavdecc_common_stream_header_set_tu(int v, void *base, size_t pos) {
    uint32_t subtype_data = jdksavdecc_common_stream_header_get_subtype_data(base, pos);
    subtype_data = jdksavdecc_subtype_data_set_tu(subtype_data, v);
    jdksavdecc_common_stream_header_set_subtype_data(subtype_data, base, pos);
}

static inline struct jdksavdecc_eui64 jdksavdecc_common_stream_header_get_stream_id(void const *base, size_t pos) {
    return jdksavdecc_eui64_get(base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID);
}

static inline void jdksavdecc_common_stream_header_set_stream_id(struct jdksavdecc_eui64 v, void *base, size_t pos) {
    jdksavdecc_eui64_set(v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID);
}

static inline uint32_t jdksavdecc_common_stream_header_get_avtp_timestamp(void const *base, size_t pos) {
    return jdksavdecc_uint32_get(base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP);
}

static inline void jdksavdecc_common_stream_header_set_avtp_timestamp(uint32_t v, void *base, size_t pos) {
    jdksavdecc_uint32_set(v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP);
}

static inline uint32_t jdksavdecc_common_stream_header_get_gateway_info(void const *base, size_t pos) {
    return jdksavdecc_uint32_get(base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO);
}

static inline void jdksavdecc_common_stream_header_set_avtp_gateway_info(uint32_t v, void *base, size_t pos) {
    jdksavdecc_uint32_set(v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO);
}

static inline uint16_t jdksavdecc_common_stream_header_get_stream_data_length(void const *base, size_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH);
}

static inline void jdksavdecc_common_stream_header_set_stream_data_length(uint16_t v, void *base, size_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH);
}

static inline uint16_t jdksavdecc_common_stream_header_get_protocol_specific_header(void const *base, size_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER);
}

static inline void jdksavdecc_common_stream_header_set_protocol_specific_header(uint16_t v, void *base, size_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER);
}

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
