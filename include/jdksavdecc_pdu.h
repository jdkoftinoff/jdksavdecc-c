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

#define JDKSAVDECC_FRAME_HEADER_DA_OFFSET ( 0 )
#define JDKSAVDECC_FRAME_HEADER_SA_OFFSET ( 6 )
#define JDKSAVDECC_FRAME_HEADER_ETHERTYPE_OFFSET ( 12 )
#define JDKSAVDECC_FRAME_HEADER_LEN ( 14 )
#define JDKSAVDECC_AECP_FRAME_MAX_SIZE                                                                                         \
    ( JDKSAVDECC_FRAME_HEADER_LEN + JDKSAVDECC_COMMON_CONTROL_HEADER_LEN + JDKSAVDECC_AECP_MAX_CONTROL_DATA_LENGTH )

#define JDKSAVDECC_AVTP_ETHERTYPE ( 0x22f0 )     /** See IEEE Std 1722-2011 Clause 5.1.2 */
#define JDKSAVDECC_AVTP_V0_PAYLOAD_OFFSET ( 12 ) /** See IEEE Std 1722-2011 Clause 5.2 */

/** See IEEE Std 1722-2011 Annex B */
#define JDKSAVDECC_MULTICAST_MAAP                                                                                              \
    {                                                                                                                          \
        {                                                                                                                      \
            0x91, 0xe0, 0xf0, 0x00, 0xff, 0x00                                                                                 \
        }                                                                                                                      \
    }

/** See IEEE Std 1722-2011 Annex B */
extern struct jdksavdecc_eui48 jdksavdecc_multicast_maap;

/** See Annex B.1 */
#define JDKSAVDECC_MULTICAST_ADP_ACMP                                                                                          \
    {                                                                                                                          \
        {                                                                                                                      \
            0x91, 0xe0, 0xf0, 0x01, 0x00, 0x00                                                                                 \
        }                                                                                                                      \
    }
extern struct jdksavdecc_eui48 jdksavdecc_multicast_adp_acmp;

/** See Annex B.1 */
#define JDKSAVDECC_MULTICAST_IDENTIFICATION                                                                                    \
    {                                                                                                                          \
        {                                                                                                                      \
            0x91, 0xe0, 0xf0, 0x01, 0x00, 0x01                                                                                 \
        }                                                                                                                      \
    }

/** See Annex B.1 */
extern struct jdksavdecc_eui48 jdksavdecc_multicast_identification;

#define JDKSAVDECC_MULTICAST_MAAP_MAC ( 0x91e0f000ff00ULL )           /** See IEEE 1722a Annex B */
#define JDKSAVDECC_MULTICAST_ADP_ACMP_MAC ( 0x91e0f0010000ULL )       /** See Annex B.1 */
#define JDKSAVDECC_MULTICAST_IDENTIFICATION_MAC ( 0x91e0f0010001ULL ) /** See Annex B.1 */

/** See IEEE Std 1722.1-2013 Clause 7.5.1 */
#define JDKSAVDECC_IDENTIFICATION_NOTIFICATION_CONTROLLER_ENTITY_ID                                                            \
    {                                                                                                                          \
        {                                                                                                                      \
            0x90, 0xe0, 0xf0, 0xff, 0xfe, 0x01, 0x00, 0x01                                                                     \
        }                                                                                                                      \
    }

/** See IEEE Std 1722.1-2013 Clause 7.5.1 */
extern struct jdksavdecc_eui64 jdksavdecc_identification_notification_controller_entity_id;

#define JDKSAVDECC_IDENTIFICATION_NOTIFICATION_CONTROLLER_ENTITY_ID_L ( 0x90e0f0fffe010001ULL ) /** See Clause 7.5.1 */

#define JDKSAVDECC_STRING_REFERENCE_OFFSET( a ) ( ( a >> 3 ) & 0x1fff )                        /** See Clause 7.3.6 */
#define JDKSAVDECC_STRING_REFERENCE_INDEX( a ) ( a & 0x7 )                                     /** See Clause 7.3.6 */
#define JDKSAVDECC_STRING_REFERENCE( offset, index ) ( ( ( offset ) << 3 ) | ( index & 0x7 ) ) /** See Clause 7.3.6 */
#define JDKSAVDECC_NO_STRING ( ( 0x1fff << 3 ) + 7 )                                           /** See Clause 7.3.6 */

/** \addtogroup subtype AVTP 2011 Subtype definitions - See IEEE 1722-2011 and IEEE 1722.1-2013 */
/*@{*/

#define JDKSAVDECC_SUBTYPE_61883_IIDC ( 0x00 )
#define JDKSAVDECC_SUBTYPE_MMA ( 0x01 )
#define JDKSAVDECC_SUBTYPE_ADP ( 0x7a )
#define JDKSAVDECC_SUBTYPE_AECP ( 0x7b )
#define JDKSAVDECC_SUBTYPE_ACMP ( 0x7c )
#define JDKSAVDECC_SUBTYPE_MAAP ( 0x7e )
#define JDKSAVDECC_SUBTYPE_EXPERIMENTAL ( 0x7f )

/*@}*/

/** \addtogroup subtype AVTP p1722a Subtype definitions - See IEEE p1722a D7 */
/*@{*/

#define JDKSAVDECC_1722A_SUBTYPE_61883_IIDC ( 0x00 )
#define JDKSAVDECC_1722A_SUBTYPE_MMA_STREAM ( 0x01 )
#define JDKSAVDECC_1722A_SUBTYPE_AAF ( 0x02 )
#define JDKSAVDECC_1722A_SUBTYPE_CVF ( 0x03 )
#define JDKSAVDECC_1722A_SUBTYPE_CRF ( 0x04 )
#define JDKSAVDECC_1722A_SUBTYPE_TSCF ( 0x05 )
#define JDKSAVDECC_1722A_SUBTYPE_SDI ( 0x06 )
#define JDKSAVDECC_1722A_SUBTYPE_RAW ( 0x07 )
#define JDKSAVDECC_1722A_SUBTYPE_AEF_STREAM ( 0x6e )
#define JDKSAVDECC_1722A_SUBTYPE_VENDOR_STREAM ( 0x6f )
#define JDKSAVDECC_1722A_SUBTYPE_EXPERIMENTAL_STREAM ( 0x7f )
#define JDKSAVDECC_1722A_SUBTYPE_MMA_CONTROL ( 0x81 )
#define JDKSAVDECC_1722A_SUBTYPE_NTSCF ( 0x82 )
#define JDKSAVDECC_1722A_SUBTYPE_ECC_SIGNED_CONTROL ( 0xec )
#define JDKSAVDECC_1722A_SUBTYPE_ECC_ENC_CONTROL ( 0xed )
#define JDKSAVDECC_1722A_SUBTYPE_AEF_CONTROL ( 0xee )
#define JDKSAVDECC_1722A_SUBTYPE_VENDOR_CONTROL ( 0xef )
#define JDKSAVDECC_1722A_SUBTYPE_ADP ( 0xfa )
#define JDKSAVDECC_1722A_SUBTYPE_AECP ( 0xfb )
#define JDKSAVDECC_1722A_SUBTYPE_ACMP ( 0xfc )
#define JDKSAVDECC_1722A_SUBTYPE_MAAP ( 0xfe )
#define JDKSAVDECC_1722A_SUBTYPE_EXPERIMENTAL_CONTROL ( 0xff )

/*@}*/

/** \addtogroup jdksavdecc_subtype_data AVTP subtype_data field - See IEEE Std 1722-2011 Clause 5.3 */
/*@{*/

#define JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH ( 7 )
#define JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH ( 3 )
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH ( 4 )
#define JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH ( 5 )
#define JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH ( 11 )
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_MR_WIDTH ( 1 )
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_GV_WIDTH ( 1 )
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TV_WIDTH ( 1 )
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_SEQUENCE_NUM_WIDTH ( 8 )
#define JDKSAVDECC_SUBTYPE_DATA_STREAM_TU_WIDTH ( 1 )

static inline bool jdksavdecc_subtype_data_get_cd( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( ( p[0] >> 7 ) & 1 ) != 0 );
}

static inline void jdksavdecc_subtype_data_set_cd( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    uint8_t n = v ? 0x80 : 0x00;
    p[0] = ( p[0] & 0x7f ) | n;
}

static inline uint8_t jdksavdecc_subtype_data_get_subtype( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return ( p[0] & 0x7f );
}

static inline void jdksavdecc_subtype_data_set_subtype( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[0] = ( p[0] & 0x80 ) | v;
}

static inline ssize_t jdksavdecc_1722a_read_subtype( uint8_t *host_value, void const *base, ssize_t pos, size_t len )
{
    ssize_t r = jdksavdecc_validate_range( pos, len, 1 );
    if ( r >= 0 )
    {
        uint8_t const *b = (uint8_t const *)base;
        *host_value = b[pos + 0];
    }

    return r;
}

static inline ssize_t jdksavdecc_1722a_write_subtype( uint8_t const *host_value, void *base, ssize_t pos, size_t len )
{
    ssize_t r = jdksavdecc_validate_range( pos, len, 1 );
    if ( r >= 0 )
    {
        uint8_t *b = (uint8_t *)base;
        b[pos + 0] = *host_value;
    }
    return r;
}

static inline bool jdksavdecc_subtype_data_get_sv( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( ( p[1] >> 7 ) & 1 ) != 0 );
}

static inline void jdksavdecc_subtype_data_set_sv( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0x7f ) | ( v ? 0x80 : 0x00 );
}

static inline uint8_t jdksavdecc_subtype_data_get_version( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return ( p[1] & 0x70 ) >> 4;
}

static inline void jdksavdecc_subtype_data_set_version( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0x8f ) | ( ( v & 0x7 ) << 4 );
}

static inline uint8_t jdksavdecc_subtype_data_get_control_data( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return ( p[1] & 0xf ) >> 0;
}

static inline void jdksavdecc_avtp_subtype_data_set_control_data( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0xf0 ) | ( ( v & 0xf ) << 0 );
}

static inline uint8_t jdksavdecc_subtype_data_get_status( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return ( p[2] & 0xf8 ) >> 3;
}

static inline void jdksavdecc_subtype_data_set_status( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[2] = ( p[2] & 0x07 ) | ( ( v & 0x1f ) << 3 );
}

static inline uint16_t jdksavdecc_subtype_data_get_control_data_length( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    uint16_t v = ( (uint16_t)p[2] ) + ( ( (uint16_t)p[3] ) & 0x3ff );
    return v;
}

static inline void jdksavdecc_subtype_data_set_control_data_length( uint16_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[2] = ( p[2] & 0xf8 ) + ( uint8_t )( ( v >> 8 ) & 0x07 );
    p[3] = ( uint8_t )( v & 0xff );
}

static inline bool jdksavdecc_subtype_data_get_mr( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( p[1] >> 3 ) & 1 );
}

static inline void jdksavdecc_subtype_data_set_mr( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0xf7 ) | ( v ? 0x08 : 0x00 );
}

static inline bool jdksavdecc_subtype_data_get_gv( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( p[1] >> 1 ) & 1 );
}

static inline void jdksavdecc_subtype_data_set_gv( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0xfd ) | ( v ? 0x02 : 0x00 );
}

static inline bool jdksavdecc_subtype_data_get_tv( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( p[1] >> 0 ) & 1 );
}

static inline void jdksavdecc_subtype_data_set_tv( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[1] = ( p[1] & 0xfe ) | ( v ? 0x01 : 0x00 );
}

static inline uint8_t jdksavdecc_subtype_data_get_sequence_num( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return p[2];
}

static inline void jdksavdecc_subtype_data_set_sequence_num( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[2] = v;
}

static inline bool jdksavdecc_subtype_data_get_tu( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return (bool)( ( p[3] >> 0 ) & 1 );
}

static inline void jdksavdecc_subtype_data_set_tu( bool v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[3] = ( p[3] & 0xfe ) | ( v ? 0x01 : 0x00 );
}

/*@}*/

/** \addtogroup jdksavdecc_avtp_common_control_header AVTP common control header - See IEEE 1722-2011 Clause 5.3 */
/*@{*/

#define JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_SUBTYPE_DATA ( 0 )
#define JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID ( 4 )
#define JDKSAVDECC_COMMON_CONTROL_HEADER_LEN ( 12 )

static inline bool jdksavdecc_common_control_header_get_cd( void const *base, size_t pos )
{

    return jdksavdecc_subtype_data_get_cd( base, pos );
}

static inline void jdksavdecc_common_control_header_set_cd( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_cd( v, base, pos );
}

static inline uint32_t jdksavdecc_common_control_header_get_subtype( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_subtype( base, pos );
}

static inline void jdksavdecc_common_control_header_set_subtype( uint8_t v, void *base, size_t pos )
{
    uint8_t *p = ( (uint8_t *)base ) + pos;
    p[0] = ( p[0] & 0x80 ) | ( v & 0x7f );
}

static inline uint32_t jdksavdecc_common_control_header_get_sv( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_sv( base, pos );
}

static inline void jdksavdecc_common_control_header_set_sv( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_sv( v, base, pos );
}

static inline uint32_t jdksavdecc_common_control_header_get_version( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_version( base, pos );
}

static inline void jdksavdecc_common_control_header_set_version( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_version( v, base, pos );
}

static inline uint8_t jdksavdecc_common_control_header_get_control_data( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_control_data( base, pos );
}

static inline void jdksavdecc_common_control_header_set_control_data( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_avtp_subtype_data_set_control_data( v, base, pos );
}

static inline uint32_t jdksavdecc_common_control_header_get_status( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_status( base, pos );
}

static inline void jdksavdecc_common_control_header_set_status( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_status( v, base, pos );
}

static inline uint16_t jdksavdecc_common_control_header_get_control_data_length( void const *base, size_t pos )
{
    uint8_t const *p = ( (uint8_t const *)base ) + pos;
    return ( ( ( uint16_t )( p[2] & 0x07 ) ) << 8 ) + p[3];
}

static inline void jdksavdecc_common_control_header_set_control_data_length( uint16_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_control_data_length( v, base, pos );
}

static inline struct jdksavdecc_eui64 jdksavdecc_common_control_header_get_stream_id( void const *base, size_t pos )
{
    return jdksavdecc_eui64_get( base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID );
}

static inline void jdksavdecc_common_control_header_set_stream_id( struct jdksavdecc_eui64 v, void *base, size_t pos )
{
    jdksavdecc_eui64_set( v, base, pos + JDKSAVDECC_COMMON_CONTROL_HEADER_OFFSET_STREAM_ID );
}

struct jdksavdecc_common_control_header
{
    uint32_t cd : 1;
    uint32_t subtype : JDKSAVDECC_SUBTYPE_DATA_SUBTYPE_WIDTH;
    uint32_t sv : 1;
    uint32_t version : JDKSAVDECC_SUBTYPE_DATA_VERSION_WIDTH;
    uint32_t control_data : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_WIDTH;
    uint32_t status : JDKSAVDECC_SUBTYPE_DATA_STATUS_WIDTH;
    uint32_t control_data_length : JDKSAVDECC_SUBTYPE_DATA_CONTROL_DATA_LENGTH_WIDTH;
    struct jdksavdecc_eui64 stream_id;
};

ssize_t jdksavdecc_common_control_header_read( struct jdksavdecc_common_control_header *p,
                                               void const *base,
                                               ssize_t pos,
                                               size_t len );
ssize_t jdksavdecc_common_control_header_write( struct jdksavdecc_common_control_header const *p,
                                                void *base,
                                                ssize_t pos,
                                                size_t len );

/*@}*/

/** \addtogroup jdksavdecc_avtp_common_stream_header AVTP common stream header - See IEEE Std 1722-2011 Clause 5.4 */
/*@{*/

#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA ( 0 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID ( 4 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP ( 12 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO ( 16 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH ( 20 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER ( 22 )
#define JDKSAVDECC_COMMON_STREAM_HEADER_LEN ( 24 )

static inline uint32_t jdksavdecc_common_stream_header_get_subtype_data( void const *base, size_t pos )
{
    uint32_t subtype_data;
    jdksavdecc_uint32_read( &subtype_data,
                            base,
                            pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA,
                            JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA );
    return subtype_data;
}

static inline void jdksavdecc_common_stream_header_set_subtype_data( uint32_t subtype_data, void *base, size_t pos )
{
    jdksavdecc_uint32_set( subtype_data, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_SUBTYPE_DATA );
}

static inline uint32_t jdksavdecc_common_stream_header_get_cd( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_cd( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_cd( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_cd( v, base, pos );
}

static inline uint32_t jdksavdecc_common_stream_header_get_subtype( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_subtype( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_subtype( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_subtype( v, base, pos );
}

static inline uint32_t jdksavdecc_common_stream_header_get_sv( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_sv( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_sv( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_sv( v, base, pos );
}

static inline uint32_t jdksavdecc_common_stream_header_get_version( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_version( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_version( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_version( v, base, pos );
}

static inline bool jdksavdecc_common_stream_header_get_mr( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_mr( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_mr( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_mr( v, base, pos );
}

static inline bool jdksavdecc_common_stream_header_get_gv( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_gv( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_gv( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_gv( v, base, pos );
}

static inline bool jdksavdecc_common_stream_header_get_tv( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_tv( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_tv( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_tv( v, base, pos );
}

static inline uint8_t jdksavdecc_common_stream_header_get_sequence_num( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_sequence_num( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_sequence_num( uint8_t v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_sequence_num( v, base, pos );
}

static inline bool jdksavdecc_common_stream_header_get_tu( void const *base, size_t pos )
{
    return jdksavdecc_subtype_data_get_tu( base, pos );
}

static inline void jdksavdecc_common_stream_header_set_tu( bool v, void *base, size_t pos )
{
    jdksavdecc_subtype_data_set_tu( v, base, pos );
}

static inline struct jdksavdecc_eui64 jdksavdecc_common_stream_header_get_stream_id( void const *base, size_t pos )
{
    return jdksavdecc_eui64_get( base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID );
}

static inline void jdksavdecc_common_stream_header_set_stream_id( struct jdksavdecc_eui64 v, void *base, size_t pos )
{
    jdksavdecc_eui64_set( v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_ID );
}

static inline uint32_t jdksavdecc_common_stream_header_get_avtp_timestamp( void const *base, size_t pos )
{
    return jdksavdecc_uint32_get( base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP );
}

static inline void jdksavdecc_common_stream_header_set_avtp_timestamp( uint32_t v, void *base, size_t pos )
{
    jdksavdecc_uint32_set( v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_AVTP_TIMESTAMP );
}

static inline uint32_t jdksavdecc_common_stream_header_get_gateway_info( void const *base, size_t pos )
{
    return jdksavdecc_uint32_get( base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO );
}

static inline void jdksavdecc_common_stream_header_set_avtp_gateway_info( uint32_t v, void *base, size_t pos )
{
    jdksavdecc_uint32_set( v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_GATEWAY_INFO );
}

static inline uint16_t jdksavdecc_common_stream_header_get_stream_data_length( void const *base, size_t pos )
{
    return jdksavdecc_uint16_get( base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH );
}

static inline void jdksavdecc_common_stream_header_set_stream_data_length( uint16_t v, void *base, size_t pos )
{
    jdksavdecc_uint16_set( v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_STREAM_DATA_LENGTH );
}

static inline uint16_t jdksavdecc_common_stream_header_get_protocol_specific_header( void const *base, size_t pos )
{
    return jdksavdecc_uint16_get( base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER );
}

static inline void jdksavdecc_common_stream_header_set_protocol_specific_header( uint16_t v, void *base, size_t pos )
{
    jdksavdecc_uint16_set( v, base, pos + JDKSAVDECC_COMMON_STREAM_HEADER_OFFSET_PROTOCOL_SPECIFIC_HEADER );
}

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
