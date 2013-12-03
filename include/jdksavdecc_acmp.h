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

/** \addtogroup acmpdu ACMPDU - Clause 8.2.1 */
/*@{*/

struct jdksavdecc_acmpdu_common_control_header {
    uint32_t cd : 1;
    uint32_t subtype : JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv : 1;
    uint32_t version : JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t message_type : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t status : JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t control_data_length
        : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 stream_id;
};

static inline ssize_t jdksavdecc_acmpdu_common_control_header_read(
    struct jdksavdecc_acmpdu_common_control_header *p, void const *base,
    ssize_t pos, size_t len) {
    return jdksavdecc_common_control_header_read(
        (struct jdksavdecc_common_control_header *)p, base, pos, len);
}

static inline ssize_t jdksavdecc_acmpdu_common_control_header_write(
    struct jdksavdecc_acmpdu_common_control_header const *p, void *base,
    ssize_t pos, size_t len) {
    return jdksavdecc_common_control_header_write(
        (struct jdksavdecc_common_control_header const *)p, base, pos, len);
}

/*@}*/

/** \addtogroup acmp_flag acmp_flag : flags field - Clause 8.2.1.17  */
/*@{*/

#define JDKSAVDECC_ACMP_FLAG_CLASS_B_BIT (15)
#define JDKSAVDECC_ACMP_FLAG_CLASS_B (0x0001)
#define JDKSAVDECC_ACMP_FLAG_CLASS_B_MASK (~0x0001)
#define JDKSAVDECC_ACMP_FLAG_FAST_CONNECT_BIT (14)
#define JDKSAVDECC_ACMP_FLAG_FAST_CONNECT (0x0002)
#define JDKSAVDECC_ACMP_FLAG_FAST_CONNECT_MASK (~0x0002)
#define JDKSAVDECC_ACMP_FLAG_SAVED_STATE_BIT (13)
#define JDKSAVDECC_ACMP_FLAG_SAVED_STATE (0x0004)
#define JDKSAVDECC_ACMP_FLAG_SAVED_STATE_MASK (~0x0004)
#define JDKSAVDECC_ACMP_FLAG_STREAMING_WAIT_BIT (12)
#define JDKSAVDECC_ACMP_FLAG_STREAMING_WAIT (0x0008)
#define JDKSAVDECC_ACMP_FLAG_STREAMING_WAIT_MASK (~0x0008)
#define JDKSAVDECC_ACMP_FLAG_SUPPORTS_ENCRYPTED_BIT (11)
#define JDKSAVDECC_ACMP_FLAG_SUPPORTS_ENCRYPTED (0x0010)
#define JDKSAVDECC_ACMP_FLAG_SUPPORTS_ENCRYPTED_MASK (~0x0010)
#define JDKSAVDECC_ACMP_FLAG_ENCRYPTED_PDU_BIT (10)
#define JDKSAVDECC_ACMP_FLAG_ENCRYPTED_PDU (0x0020)
#define JDKSAVDECC_ACMP_FLAG_ENCRYPTED_PDU_MASK (~0x0020)
#define JDKSAVDECC_ACMP_FLAG_TALKER_FAILED_BIT (9)
#define JDKSAVDECC_ACMP_FLAG_TALKER_FAILED (0x0040)
#define JDKSAVDECC_ACMP_FLAG_TALKER_FAILED_MASK (~0x0040)

/*@}*/

/** \addtogroup acmpdu ACMPDU - Clause 8.2.1 */
/*@{*/

#define JDKSAVDECC_ACMPDU_OFFSET_CONTROLLER_ENTITY_ID                          \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 0)
#define JDKSAVDECC_ACMPDU_OFFSET_TALKER_ENTITY_ID                              \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 8)
#define JDKSAVDECC_ACMPDU_OFFSET_LISTENER_ENTITY_ID                            \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 16)
#define JDKSAVDECC_ACMPDU_OFFSET_TALKER_UNIQUE_ID                              \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 24)
#define JDKSAVDECC_ACMPDU_OFFSET_LISTENER_UNIQUE_ID                            \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 26)
#define JDKSAVDECC_ACMPDU_OFFSET_STREAM_DEST_MAC                               \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 28)
#define JDKSAVDECC_ACMPDU_OFFSET_CONNECTION_COUNT                              \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 34)
#define JDKSAVDECC_ACMPDU_OFFSET_SEQUENCE_ID                                   \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 36)
#define JDKSAVDECC_ACMPDU_OFFSET_FLAGS                                         \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 38)
#define JDKSAVDECC_ACMPDU_OFFSET_STREAM_VLAN_ID                                \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 40)
#define JDKSAVDECC_ACMPDU_OFFSET_RESERVED                                      \
    (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 42)
#define JDKSAVDECC_ACMPDU_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + 44)

/*@}*/

/** \addtogroup acmp_message_type acmp_message_type : message_type field -
 * Clause 8.2.1.5  */
/*@{*/

#define JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_COMMAND (0)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_RESPONSE (1)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_COMMAND (2)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_RESPONSE (3)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_COMMAND (4)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_RESPONSE (5)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_COMMAND (6)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_RX_RESPONSE (7)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_RX_COMMAND (8)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_RX_RESPONSE (9)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_RX_STATE_COMMAND (10)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_RX_STATE_RESPONSE (11)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_COMMAND (12)
#define JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_RESPONSE (13)

/*@}*/

/** \addtogroup acmp_status acmp_status : status field - Clause 8.2.1.6  */
/*@{*/

#define JDKSAVDECC_ACMP_STATUS_SUCCESS (0)
#define JDKSAVDECC_ACMP_STATUS_LISTENER_UNKNOWN_ID (1)
#define JDKSAVDECC_ACMP_STATUS_TALKER_UNKNOWN_ID (2)
#define JDKSAVDECC_ACMP_STATUS_TALKER_DEST_MAC_FAIL (3)
#define JDKSAVDECC_ACMP_STATUS_TALKER_NO_STREAM_INDEX (4)
#define JDKSAVDECC_ACMP_STATUS_TALKER_NO_BANDWIDTH (5)
#define JDKSAVDECC_ACMP_STATUS_TALKER_EXCLUSIVE (6)
#define JDKSAVDECC_ACMP_STATUS_LISTENER_TALKER_TIMEOUT (7)
#define JDKSAVDECC_ACMP_STATUS_LISTENER_EXCLUSIVE (8)
#define JDKSAVDECC_ACMP_STATUS_STATE_UNAVAILABLE (9)
#define JDKSAVDECC_ACMP_STATUS_NOT_CONNECTED (10)
#define JDKSAVDECC_ACMP_STATUS_NO_SUCH_CONNECTION (11)
#define JDKSAVDECC_ACMP_STATUS_COULD_NOT_SEND_MESSAGE (12)
#define JDKSAVDECC_ACMP_STATUS_TALKER_MISBEHAVING (13)
#define JDKSAVDECC_ACMP_STATUS_LISTENER_MISBEHAVING (14)
#define JDKSAVDECC_ACMP_STATUS_RESERVED (15)
#define JDKSAVDECC_ACMP_STATUS_CONTROLLER_NOT_AUTHORIZED (16)
#define JDKSAVDECC_ACMP_STATUS_INCOMPATIBLE_REQUEST (17)
#define JDKSAVDECC_ACMP_STATUS_LISTENER_INVALID_CONNECTION                     \
    (18) /// New: The AVDECC Listener is being asked to connect to something that it cannot listen to, e.g. it is being asked to   \
         /// listen to it's own AVDECC Talker stream.
#define JDKSAVDECC_ACMP_STATUS_NOT_SUPPORTED (31)

/*@}*/

/** \addtogroup acmpdu ACMPDU - Clause 8.2.1 */
/*@{*/

/**
 * Extract the eui64 value of the controller_entity_id field of the ACMPDU
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
static inline struct jdksavdecc_eui64
jdksavdecc_acmpdu_get_controller_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Store a eui64 value to the controller_entity_id field of the ACMPDU object to
 *a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui64 controller_entity_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_controller_entity_id(struct jdksavdecc_eui64 v,
                                           void *base, ssize_t pos) {
    jdksavdecc_eui64_set(v, base,
                         pos + JDKSAVDECC_ACMPDU_OFFSET_CONTROLLER_ENTITY_ID);
}

/**
 * Extract the eui64 value of the talker_entity_id field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui64 talker_entity_id value
 */
static inline struct jdksavdecc_eui64
jdksavdecc_acmpdu_get_talker_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_TALKER_ENTITY_ID);
}

/**
 * Store a eui64 value to the talker_entity_id field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui64 talker_entity_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_talker_entity_id(struct jdksavdecc_eui64 v, void *base,
                                       ssize_t pos) {
    jdksavdecc_eui64_set(v, base,
                         pos + JDKSAVDECC_ACMPDU_OFFSET_TALKER_ENTITY_ID);
}

/**
 * Extract the eui64 value of the listener_entity_id field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui64 listener_entity_id value
 */
static inline struct jdksavdecc_eui64
jdksavdecc_acmpdu_get_listener_entity_id(void const *base, ssize_t pos) {
    return jdksavdecc_eui64_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_LISTENER_ENTITY_ID);
}

/**
 * Store a eui64 value to the listener_entity_id field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui64 listener_entity_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_listener_entity_id(struct jdksavdecc_eui64 v, void *base,
                                         ssize_t pos) {
    jdksavdecc_eui64_set(v, base,
                         pos + JDKSAVDECC_ACMPDU_OFFSET_LISTENER_ENTITY_ID);
}

/**
 * Extract the uint16 value of the talker_unique_id field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t talker_unique_id value
 */
static inline uint16_t jdksavdecc_acmpdu_get_talker_unique_id(void const *base,
                                                              ssize_t pos) {
    return jdksavdecc_uint16_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_TALKER_UNIQUE_ID);
}

/**
 * Store a uint16 value to the talker_unique_id field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t talker_unique_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_talker_unique_id(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base,
                          pos + JDKSAVDECC_ACMPDU_OFFSET_TALKER_UNIQUE_ID);
}

/**
 * Extract the uint16 value of the listener_unique_id field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t listener_unique_id value
 */
static inline uint16_t
jdksavdecc_acmpdu_get_listener_unique_id(void const *base, ssize_t pos) {
    return jdksavdecc_uint16_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_LISTENER_UNIQUE_ID);
}

/**
 * Store a uint16 value to the listener_unique_id field of the ACMPDU object to
 *a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t listener_unique_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_listener_unique_id(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base,
                          pos + JDKSAVDECC_ACMPDU_OFFSET_LISTENER_UNIQUE_ID);
}

/**
 * Extract the eui48 value of the stream_dest_mac field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui48 stream_dest_mac value
 */
static inline struct jdksavdecc_eui48
jdksavdecc_acmpdu_get_stream_dest_mac(void const *base, ssize_t pos) {
    return jdksavdecc_eui48_get(base,
                                pos + JDKSAVDECC_ACMPDU_OFFSET_STREAM_DEST_MAC);
}

/**
 * Store a eui48 value to the stream_dest_mac field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui48 stream_dest_mac value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_stream_dest_mac(struct jdksavdecc_eui48 v, void *base,
                                      ssize_t pos) {
    jdksavdecc_eui48_set(v, base,
                         pos + JDKSAVDECC_ACMPDU_OFFSET_STREAM_DEST_MAC);
}

/**
 * Extract the uint16 value of the connection_count field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t connection_count value
 */
static inline uint16_t jdksavdecc_acmpdu_get_connection_count(void const *base,
                                                              ssize_t pos) {
    return jdksavdecc_uint16_get(
        base, pos + JDKSAVDECC_ACMPDU_OFFSET_CONNECTION_COUNT);
}

/**
 * Store a uint16 value to the connection_count field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t connection_count value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void
jdksavdecc_acmpdu_set_connection_count(uint16_t v, void *base, ssize_t pos) {
    jdksavdecc_uint16_set(v, base,
                          pos + JDKSAVDECC_ACMPDU_OFFSET_CONNECTION_COUNT);
}

/**
 * Extract the uint16 value of the sequence_id field of the ACMPDU object from a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t sequence_id value
 */
static inline uint16_t jdksavdecc_acmpdu_get_sequence_id(void const *base,
                                                         ssize_t pos) {
    return jdksavdecc_uint16_get(base,
                                 pos + JDKSAVDECC_ACMPDU_OFFSET_SEQUENCE_ID);
}

/**
 * Store a uint16 value to the sequence_id field of the ACMPDU object to a
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
static inline void jdksavdecc_acmpdu_set_sequence_id(uint16_t v, void *base,
                                                     ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_ACMPDU_OFFSET_SEQUENCE_ID);
}

/**
 * Extract the uint16 value of the acmp_flags field of the ACMPDU object from a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t acmp_flags value
 */
static inline uint16_t jdksavdecc_acmpdu_get_flags(void const *base,
                                                   ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_ACMPDU_OFFSET_FLAGS);
}

/**
 * Store a uint16 value to the acmp_flags field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t acmp_flags value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_acmpdu_set_flags(uint16_t v, void *base,
                                               ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_ACMPDU_OFFSET_FLAGS);
}

/**
 * Extract the uint16 value of the stream_vlan_id field of the ACMPDU object
 *from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t stream_vlan_id value
 */
static inline uint16_t jdksavdecc_acmpdu_get_stream_vlan_id(void const *base,
                                                            ssize_t pos) {
    return jdksavdecc_uint16_get(base,
                                 pos + JDKSAVDECC_ACMPDU_OFFSET_STREAM_VLAN_ID);
}

/**
 * Store a uint16 value to the stream_vlan_id field of the ACMPDU object to a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t stream_vlan_id value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_acmpdu_set_stream_vlan_id(uint16_t v, void *base,
                                                        ssize_t pos) {
    jdksavdecc_uint16_set(v, base,
                          pos + JDKSAVDECC_ACMPDU_OFFSET_STREAM_VLAN_ID);
}

/**
 * Extract the uint16 value of the reserved field of the ACMPDU object from a
 *network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t reserved value
 */
static inline uint16_t jdksavdecc_acmpdu_get_reserved(void const *base,
                                                      ssize_t pos) {
    return jdksavdecc_uint16_get(base, pos + JDKSAVDECC_ACMPDU_OFFSET_RESERVED);
}

/**
 * Store a uint16 value to the reserved field of the ACMPDU object to a network
 *buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's
 *responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t reserved value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_acmpdu_set_reserved(uint16_t v, void *base,
                                                  ssize_t pos) {
    jdksavdecc_uint16_set(v, base, pos + JDKSAVDECC_ACMPDU_OFFSET_RESERVED);
}

/*@}*/

/** \addtogroup acmpdu ACMPDU - Clause 8.2.1 */
/*@{*/

/// ACMPDU - Clause 8.2.1
struct jdksavdecc_acmpdu {
    struct jdksavdecc_acmpdu_common_control_header header;
    struct jdksavdecc_eui64 controller_entity_id;
    struct jdksavdecc_eui64 talker_entity_id;
    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t talker_unique_id;
    uint16_t listener_unique_id;
    struct jdksavdecc_eui48 stream_dest_mac;
    uint16_t connection_count;
    uint16_t sequence_id;
    uint16_t flags;
    uint16_t stream_vlan_id;
    uint16_t reserved;
};

/**
 * Extract the jdksavdecc_acmpdu structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to acmpdu structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_acmpdu_read(struct jdksavdecc_acmpdu *p,
                                             void const *base, ssize_t pos,
                                             size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_ACMPDU_LEN);
    if (r >= 0) {
        jdksavdecc_acmpdu_common_control_header_read(&p->header, base, pos,
                                                     len);
        p->controller_entity_id =
            jdksavdecc_acmpdu_get_controller_entity_id(base, pos);
        p->talker_entity_id = jdksavdecc_acmpdu_get_talker_entity_id(base, pos);
        p->listener_entity_id =
            jdksavdecc_acmpdu_get_listener_entity_id(base, pos);
        p->talker_unique_id = jdksavdecc_acmpdu_get_talker_unique_id(base, pos);
        p->listener_unique_id =
            jdksavdecc_acmpdu_get_listener_unique_id(base, pos);
        p->stream_dest_mac = jdksavdecc_acmpdu_get_stream_dest_mac(base, pos);
        p->connection_count = jdksavdecc_acmpdu_get_connection_count(base, pos);
        p->sequence_id = jdksavdecc_acmpdu_get_sequence_id(base, pos);
        p->flags = jdksavdecc_acmpdu_get_flags(base, pos);
        p->stream_vlan_id = jdksavdecc_acmpdu_get_stream_vlan_id(base, pos);
        p->reserved = jdksavdecc_acmpdu_get_reserved(base, pos);
    }
    return r;
}

/**
 * Store the jdksavdecc_acmpdu structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to acmpdu structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_acmpdu_write(struct jdksavdecc_acmpdu const *p,
                                              void *base, size_t pos,
                                              size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_ACMPDU_LEN);
    if (r >= 0) {
        jdksavdecc_acmpdu_common_control_header_write(&p->header, base, pos,
                                                      len);
        jdksavdecc_acmpdu_set_controller_entity_id(p->controller_entity_id,
                                                   base, pos);
        jdksavdecc_acmpdu_set_talker_entity_id(p->talker_entity_id, base, pos);
        jdksavdecc_acmpdu_set_listener_entity_id(p->listener_entity_id, base,
                                                 pos);
        jdksavdecc_acmpdu_set_talker_unique_id(p->talker_unique_id, base, pos);
        jdksavdecc_acmpdu_set_listener_unique_id(p->listener_unique_id, base,
                                                 pos);
        jdksavdecc_acmpdu_set_stream_dest_mac(p->stream_dest_mac, base, pos);
        jdksavdecc_acmpdu_set_connection_count(p->connection_count, base, pos);
        jdksavdecc_acmpdu_set_sequence_id(p->sequence_id, base, pos);
        jdksavdecc_acmpdu_set_flags(p->flags, base, pos);
        jdksavdecc_acmpdu_set_stream_vlan_id(p->stream_vlan_id, base, pos);
        jdksavdecc_acmpdu_set_reserved(p->reserved, base, pos);
    }
    return r;
}

/*@}*/

/** \addtogroup acmp_statemachines ACMP State Machines - Clause 8.2.2*/
/*@{*/

/// Clause 8.2.2.2.1
typedef struct jdksavdecc_acmpdu jdksavdecc_acmp_command_response;

/// Clause 8.2.2.2.2
struct jdksavdecc_acmp_listener_stream_info {
    struct jdksavdecc_eui64 talker_entity_id;
    uint16_t talker_unique_id;
    bool connected;
    struct jdksavdecc_eui64 stream_id;
    struct jdksavdecc_eui48 stream_dest_mac;
    struct jdksavdecc_eui64 controller_entity_id;
    uint16_t flags;
    uint16_t stream_vlan_id;
};

/// Clause 8.2.2.2.2
struct jdksavdecc_acmp_listener_stream_infos {
    size_t max_items;
    size_t num_items;
    struct jdksavdecc_acmp_listener_stream_info *items;
};

/// Clause 8.2.2.2.2
static inline void jdksavdecc_acmp_listener_stream_info_set(
    struct jdksavdecc_acmp_listener_stream_info *self,
    struct jdksavdecc_acmpdu *p) {
    self->stream_id = p->header.stream_id;
    self->controller_entity_id = p->controller_entity_id;
    self->talker_entity_id = p->talker_entity_id;
    self->talker_unique_id = p->talker_unique_id;
    self->stream_dest_mac = p->stream_dest_mac;
    self->connected = p->connection_count > 0 ? true : false;
    self->flags = p->flags;
    self->stream_vlan_id = p->stream_vlan_id;
}

/// Clause 8.2.2.2.3
struct jdksavdecc_acmp_listener_pair {
    struct jdksavdecc_eui64 listener_entity_id;
    uint16_t listener_unique_id;
};

/// Clause 8.2.2.2.4
struct jdksavdecc_acmp_talker_stream_info {
    struct jdksavdecc_eui64 stream_id;
    struct jdksavdecc_eui48 stream_dest_mac;
    uint16_t connection_count;
    uint16_t max_connected_listeners;
    struct jdksavdecc_acmp_listener_pair *connected_listeners;
    uint16_t stream_vlan_id;
};

/// Clause 8.2.2.2.4
struct jdksavdecc_acmp_talker_stream_infos {
    void (*destroy)(struct jdksavdecc_acmp_talker_stream_infos *);

    uint16_t num_stream_sources;
    struct jdksavdecc_acmp_talker_stream_info *stream_sources;
};

int jdksavdecc_acmp_talker_stream_infos_init(
    struct jdksavdecc_acmp_talker_stream_infos *self,
    uint16_t num_stream_sources, uint16_t max_connected_listeners,
    struct jdksavdecc_eui64 starting_stream_id,
    struct jdksavdecc_eui48 starting_stream_dest_mac, uint16_t stream_vlan_id);

/*@}*/

#ifdef __cplusplus
}
#endif
