#pragma once
#ifndef JDKSAVDECC_MAAP_H
#define JDKSAVDECC_MAAP_H

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

/** \addtogroup maap MAAP - IEEE Std 1722-2011 Annex B.2 */
/*@{*/

struct jdksavdecc_maap_common_control_header
{
    uint32_t cd:1;
    uint32_t subtype:JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv:1;
    uint32_t version:JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t message_type:JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t maap_version:JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t maap_data_length:JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 stream_id;
};


static inline ssize_t jdksavdecc_maap_common_control_header_read( struct jdksavdecc_maap_common_control_header *p, void const *base, ssize_t pos, size_t len )
{
    return jdksavdecc_common_control_header_read( (struct jdksavdecc_common_control_header *)p, base, pos, len );
}

static inline ssize_t jdksavdecc_maap_common_control_header_write( struct jdksavdecc_maap_common_control_header const *p, void *base, ssize_t pos, size_t len )
{
    return jdksavdecc_common_control_header_write( (struct jdksavdecc_common_control_header const *)p, base, pos, len );
}


#define JDKSAVDECC_MAAP_PROBE (1)
#define JDKSAVDECC_MAAP_DEFEND (2)
#define JDKSAVDECC_MAAP_ANNOUNCE (3)


#define JDKSAVDECC_MAAP_OFFSET_REQUESTED_START_ADDRESS (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+0)
#define JDKSAVDECC_MAAP_OFFSET_REQUESTED_COUNT (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+6)
#define JDKSAVDECC_MAAP_OFFSET_CONFLICT_START_ADDRESS (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+8)
#define JDKSAVDECC_MAAP_OFFSET_CONFLICT_COUNT (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+14)
#define JDKSAVDECC_MAAP_LEN (JDKSAVDECC_COMMON_CONTROL_HEADER_LEN+16)


/**
 * Extract the eui48 value of the requested_start_address field of the MAAP object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui48_t requested_start_address value
 */
static inline struct jdksavdecc_eui48 jdksavdecc_maap_get_requested_start_address( void const *base, ssize_t pos )
{
    return jdksavdecc_eui48_get( base, pos + JDKSAVDECC_MAAP_OFFSET_REQUESTED_START_ADDRESS);
}


/**
 * Store a eui48 value to the requested_start_address field of the MAAP object to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui48_t requested_start_address value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_maap_set_requested_start_address( struct jdksavdecc_eui48 v, void *base, ssize_t pos )
{
    jdksavdecc_eui48_set( v, base, pos + JDKSAVDECC_MAAP_OFFSET_REQUESTED_START_ADDRESS);
}


/**
 * Extract the uint16 value of the requested_count field of the MAAP object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t requested_count value
 */
static inline uint16_t jdksavdecc_maap_get_requested_count( void const *base, ssize_t pos )
{
    return jdksavdecc_uint16_get( base, pos + JDKSAVDECC_MAAP_OFFSET_REQUESTED_COUNT);
}


/**
 * Store a uint16 value to the requested_count field of the MAAP object to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t requested_count value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_maap_set_requested_count( uint16_t v, void *base, ssize_t pos )
{
    jdksavdecc_uint16_set( v, base, pos + JDKSAVDECC_MAAP_OFFSET_REQUESTED_COUNT);
}


/**
 * Extract the eui48 value of the conflict_start_address field of the MAAP object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the struct jdksavdecc_eui48_t conflict_start_address value
 */
static inline struct jdksavdecc_eui48 jdksavdecc_maap_get_conflict_start_address( void const *base, ssize_t pos )
{
    return jdksavdecc_eui48_get( base, pos + JDKSAVDECC_MAAP_OFFSET_CONFLICT_START_ADDRESS);
}


/**
 * Store a eui48 value to the conflict_start_address field of the MAAP object to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The struct jdksavdecc_eui48_t conflict_start_address value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_maap_set_conflict_start_address( struct jdksavdecc_eui48 v, void *base, ssize_t pos )
{
    jdksavdecc_eui48_set( v, base, pos + JDKSAVDECC_MAAP_OFFSET_CONFLICT_START_ADDRESS);
}


/**
 * Extract the uint16 value of the conflict_count field of the MAAP object from a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint16_t conflict_count value
 */
static inline uint16_t jdksavdecc_maap_get_conflict_count( void const *base, ssize_t pos )
{
    return jdksavdecc_uint16_get( base, pos + JDKSAVDECC_MAAP_OFFSET_CONFLICT_COUNT);
}


/**
 * Store a uint16 value to the conflict_count field of the MAAP object to a network buffer.
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The uint16_t conflict_count value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_maap_set_conflict_count( uint16_t v, void *base, ssize_t pos )
{
    jdksavdecc_uint16_set( v, base, pos + JDKSAVDECC_MAAP_OFFSET_CONFLICT_COUNT);
}




/*@}*/


/** \addtogroup maap MAAP - IEEE Std 1722-2011 Annex B.2 */
/*@{*/


/// MAAP - IEEE Std 1722-2011 Annex B.2
struct jdksavdecc_maap
{
    struct jdksavdecc_maap_common_control_header header;
    struct jdksavdecc_eui48 requested_start_address;
    uint16_t requested_count;
    struct jdksavdecc_eui48 conflict_start_address;
    uint16_t conflict_count;
};

/**
 * Extract the jdksavdecc_maap structure from a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to maap structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_maap_read( struct jdksavdecc_maap *p, void const *base, ssize_t pos, size_t len )
{
    ssize_t r=jdksavdecc_validate_range( pos, len, JDKSAVDECC_MAAP_LEN );
    if( r>=0 )
    {
        jdksavdecc_maap_common_control_header_read( &p->header, base, pos, len );
        p->requested_start_address = jdksavdecc_maap_get_requested_start_address( base, pos );
        p->requested_count = jdksavdecc_maap_get_requested_count( base, pos );
        p->conflict_start_address = jdksavdecc_maap_get_conflict_start_address( base, pos );
        p->conflict_count = jdksavdecc_maap_get_conflict_count( base, pos );
    }
    return r;
}

/**
 * Store the jdksavdecc_maap structure to a network buffer.
 *
 *
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to maap structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_maap_write( struct jdksavdecc_maap const *p, void *base, size_t pos, size_t len )
{
    ssize_t r=jdksavdecc_validate_range( pos, len, JDKSAVDECC_MAAP_LEN );
    if( r>=0 )
    {
        jdksavdecc_maap_common_control_header_write( &p->header, base, pos, len );
        jdksavdecc_maap_set_requested_start_address( p->requested_start_address, base, pos );
        jdksavdecc_maap_set_requested_count( p->requested_count, base, pos );
        jdksavdecc_maap_set_conflict_start_address( p->conflict_start_address, base, pos );
        jdksavdecc_maap_set_conflict_count( p->conflict_count, base, pos );
    }
    return r;
}

/*@}*/


/** \addtogroup maap_sm MAAP State Machine - IEEE Std 1722-2011 Annex B.3 */
/*@{*/

#define JDKSAVDECC_MAAP_PROBE_RETRANSMITS (3) /// See IEEE Std 1722-2011 Annex B.3.3
#define JDKSAVDECC_MAAP_PROBE_INTERVAL_BASE (500) /// See IEEE Std 1722-2011 Annex B.3.3
#define JDKSAVDECC_MAAP_PROBE_INTERVAL_VARIATION (100) /// See IEEE Std 1722-2011 Annex B.3.3
#define JDKSAVDECC_MAAP_ANNOUNCE_INTERVAL_BASE (30000) /// See IEEE Std 1722-2011 Annex B.3.3
#define JDKSAVDECC_MAAP_ANNOUNCE_INTERVAL_VARIATION (2000) /// See IEEE Std 1722-2011 Annex B.3.3

/// See IEEE Std 1722-2011 Annex B.3.1.
enum jdksavdecc_maap_event
{
    jdksavdecc_maap_event_begin=0,
    jdksavdecc_maap_event_release,
    jdksavdecc_maap_event_restart,
    jdksavdecc_maap_event_reserve_address,
    jdksavdecc_maap_event_rprobe,
    jdksavdecc_maap_event_rdefend,
    jdksavdecc_maap_event_rannounce,
    jdksavdecc_maap_event_probe_count,
    jdksavdecc_maap_event_announce_timer,
    jdksavdecc_maap_event_probe_timer
};

struct jdksavdecc_maap_state_machine;

/// See IEEE Std 1722-2011 Annex B.3.2
typedef void (*jdksavdecc_maap_state)(
        struct jdksavdecc_maap_state_machine *,
        enum jdksavdecc_maap_event event,
        struct jdksavdecc_maap *received_pdu
        );

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_initial(
        struct jdksavdecc_maap_state_machine *,
        enum jdksavdecc_maap_event event,
        struct jdksavdecc_maap *received_pdu
        );

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_probe(
        struct jdksavdecc_maap_state_machine *,
        enum jdksavdecc_maap_event event,
        struct jdksavdecc_maap *received_pdu
        );

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_defend(
        struct jdksavdecc_maap_state_machine *,
        enum jdksavdecc_maap_event event,
        struct jdksavdecc_maap *received_pdu
        );


/// See IEEE Std 1722-2011 Annex B.3.6.1
void jdksavdecc_maap_action_generate_address(
        struct jdksavdecc_maap_state_machine *,
        struct jdksavdecc_eui48 *start_address,
        uint16_t count
        );

/// See IEEE Std 1722-2011 Annex B.3.6.2
void jdksavdecc_maap_action_init_maap_probe_count(
        struct jdksavdecc_maap_state_machine *
        );

/// See IEEE Std 1722-2011 Annex B.3.6.3
void jdksavdecc_maap_action_dec_maap_probe_count(
        struct jdksavdecc_maap_state_machine *
        );

/// See IEEE Std 1722-2011 Annex B.3.6.4
void jdksavdecc_maap_action_compare_mac(
        struct jdksavdecc_maap_state_machine *,
        struct jdksavdecc_maap *received_pdu
        );

/// See IEEE Std 1722-2011 Annex B.3.6.5
void jdksavdecc_maap_action_sprobe(
        struct jdksavdecc_maap_state_machine *
        );

/// See IEEE Std 1722-2011 Annex B.3.6.6
void jdksavdecc_maap_action_sdefend(
        struct jdksavdecc_maap_state_machine *
        );

/// See IEEE Std 1722-2011 Annex B.3.6.7
void jdksavdecc_maap_action_sannounce(
        struct jdksavdecc_maap_state_machine *
        );

/// @todo implement MAAP state machine
struct jdksavdecc_maap_state_machine
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;
    void (*destroy)( struct jdksavdecc_maap_state_machine * );
    void (*tick)( struct jdksavdecc_maap_state_machine *self, jdksavdecc_millisecond_time timestamp );
    ssize_t (*rx_frame)( struct jdksavdecc_maap_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );

    jdksavdecc_maap_state state;
    struct jdksavdecc_eui48 local_mac;
    uint16_t desired_count;
    jdksavdecc_millisecond_time announce_timer;  /// See IEEE Std 1722-2011 Annex B.3.4.1
    jdksavdecc_millisecond_time probe_timer;  /// See IEEE Std 1722-2011 Annex B.3.4.2
};

void jdksavdecc_maap_state_machine_init(
        struct jdksavdecc_maap_state_machine *,
        jdksavdecc_millisecond_time current_time,
        struct jdksavdecc_eui48 local_mac,
        uint16_t desired_count,
        struct jdksavdecc_frame_sender *frame_sender
        );

void jdksavdecc_maap_state_machine_tick(
        struct jdksavdecc_maap_state_machine *,
        jdksavdecc_millisecond_time current_time
        );

ssize_t jdksavdecc_maap_state_machine_rx_frame(
        struct jdksavdecc_maap_state_machine *,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        );


#define JDKSAVDECC_MAAP_DYNAMIC_ALLOCATION_POOL_START {{0x91,0xe0,0xf0,0x00,0x00,0x00}} /// See IEEE Std 1722-2011 Table B.4
#define JDKSAVDECC_MAAP_DYNAMIC_ALLOCATION_POOL_END {{0x91,0xe0,0xf0,0x00,0xFD,0xFF}} /// See IEEE Std 1722-2011 Table B.4
#define JDKSAVDECC_MAAP_LOCAL_ALLOCATION_POOL_START {{0x91,0xe0,0xf0,0x00,0xFE,0x00}} /// See IEEE Std 1722-2011 Table B.4
#define JDKSAVDECC_MAAP_LOCAL_ALLOCATION_POOL_END {{0x91,0xe0,0xf0,0x00,0xFE,0xFF}} /// See IEEE Std 1722-2011 Table B.4



/*@}*/
#ifdef __cplusplus
}
#endif

#endif


