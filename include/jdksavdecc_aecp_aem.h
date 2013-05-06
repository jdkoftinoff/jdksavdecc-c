#pragma once
#ifndef JDKSAVDECC_AECP_AEM_H
#define JDKSAVDECC_AECP_AEM_H

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

#define JDKSAVDECC_AEM_VALUES_TYPE_FLAG_READ_ONLY  (0x8000)
#define JDKSAVDECC_AEM_VALUES_TYPE_FLAG_UNKNOWN (0x4000)

#define JDKSAVDECC_AEM_UNITS( multiplier, code ) ((multiplier<<8) + code)

/** \addtogroup command command : Command Codes - Clause 7.4  */
/*@{*/

#define JDKSAVDECC_AEM_COMMAND_ACQUIRE_ENTITY (0x0000)
#define JDKSAVDECC_AEM_COMMAND_LOCK_ENTITY (0x0001)
#define JDKSAVDECC_AEM_COMMAND_ENTITY_AVAILABLE (0x0002)
#define JDKSAVDECC_AEM_COMMAND_CONTROLLER_AVAILABLE (0x0003)
#define JDKSAVDECC_AEM_COMMAND_READ_DESCRIPTOR (0x0004)
#define JDKSAVDECC_AEM_COMMAND_WRITE_DESCRIPTOR (0x0005)
#define JDKSAVDECC_AEM_COMMAND_SET_CONFIGURATION (0x0006)
#define JDKSAVDECC_AEM_COMMAND_GET_CONFIGURATION (0x0007)
#define JDKSAVDECC_AEM_COMMAND_SET_STREAM_FORMAT (0x0008)
#define JDKSAVDECC_AEM_COMMAND_GET_STREAM_FORMAT (0x0009)
#define JDKSAVDECC_AEM_COMMAND_SET_VIDEO_FORMAT (0x000a)
#define JDKSAVDECC_AEM_COMMAND_GET_VIDEO_FORMAT (0x000b)
#define JDKSAVDECC_AEM_COMMAND_SET_SENSOR_FORMAT (0x000c)
#define JDKSAVDECC_AEM_COMMAND_GET_SENSOR_FORMAT (0x000e)
#define JDKSAVDECC_AEM_COMMAND_SET_STREAM_INFO (0x000d)
#define JDKSAVDECC_AEM_COMMAND_GET_STREAM_INFO (0x000f)
#define JDKSAVDECC_AEM_COMMAND_SET_NAME (0x0010)
#define JDKSAVDECC_AEM_COMMAND_GET_NAME (0x0011)
#define JDKSAVDECC_AEM_COMMAND_SET_ASSOCIATION_ID (0x0012)
#define JDKSAVDECC_AEM_COMMAND_GET_ASSOCIATION_ID (0x0013)
#define JDKSAVDECC_AEM_COMMAND_SET_SAMPLING_RATE (0x0014)
#define JDKSAVDECC_AEM_COMMAND_GET_SAMPLING_RATE (0x0015)
#define JDKSAVDECC_AEM_COMMAND_SET_CLOCK_SOURCE (0x0016)
#define JDKSAVDECC_AEM_COMMAND_GET_CLOCK_SOURCE (0x0017)
#define JDKSAVDECC_AEM_COMMAND_SET_CONTROL (0x0018)
#define JDKSAVDECC_AEM_COMMAND_GET_CONTROL (0x0019)
#define JDKSAVDECC_AEM_COMMAND_INCREMENT_CONTROL (0x001a)
#define JDKSAVDECC_AEM_COMMAND_DECREMENT_CONTROL (0x001b)
#define JDKSAVDECC_AEM_COMMAND_SET_SIGNAL_SELECTOR (0x001c)
#define JDKSAVDECC_AEM_COMMAND_GET_SIGNAL_SELECTOR (0x001d)
#define JDKSAVDECC_AEM_COMMAND_SET_MIXER (0x001e)
#define JDKSAVDECC_AEM_COMMAND_GET_MIXER (0x001f)
#define JDKSAVDECC_AEM_COMMAND_SET_MATRIX (0x0020)
#define JDKSAVDECC_AEM_COMMAND_GET_MATRIX (0x0021)
#define JDKSAVDECC_AEM_COMMAND_START_STREAMING (0x0022)
#define JDKSAVDECC_AEM_COMMAND_STOP_STREAMING (0x0023)
#define JDKSAVDECC_AEM_COMMAND_REGISTER_UNSOLICITED_NOTIFICATION (0x0024)
#define JDKSAVDECC_AEM_COMMAND_DEREGISTER_UNSOLICITED_NOTIFICATION (0x0025)
#define JDKSAVDECC_AEM_COMMAND_IDENTIFY_NOTIFICATION (0x0026)
#define JDKSAVDECC_AEM_COMMAND_GET_AVB_INFO (0x0027)
#define JDKSAVDECC_AEM_COMMAND_GET_AS_PATH (0x0028)
#define JDKSAVDECC_AEM_COMMAND_GET_COUNTERS (0x0029)
#define JDKSAVDECC_AEM_COMMAND_REBOOT (0x002a)
#define JDKSAVDECC_AEM_COMMAND_GET_AUDIO_MAP (0x002b)
#define JDKSAVDECC_AEM_COMMAND_ADD_AUDIO_MAPPINGS (0x002c)
#define JDKSAVDECC_AEM_COMMAND_REMOVE_AUDIO_MAPPINGS (0x002d)
#define JDKSAVDECC_AEM_COMMAND_GET_VIDEO_MAP (0x002e)
#define JDKSAVDECC_AEM_COMMAND_ADD_VIDEO_MAPPINGS (0x002f)
#define JDKSAVDECC_AEM_COMMAND_REMOVE_VIDEO_MAPPINGS (0x0030)
#define JDKSAVDECC_AEM_COMMAND_GET_SENSOR_MAP (0x0031)
#define JDKSAVDECC_AEM_COMMAND_ADD_SENSOR_MAPPINGS (0x0032)
#define JDKSAVDECC_AEM_COMMAND_REMOVE_SENSOR_MAPPINGS (0x0033)
#define JDKSAVDECC_AEM_COMMAND_START_OPERATION (0x0034)
#define JDKSAVDECC_AEM_COMMAND_ABORT_OPERATION (0x0035)
#define JDKSAVDECC_AEM_COMMAND_OPERATION_STATUS (0x0036)
#define JDKSAVDECC_AEM_COMMAND_AUTH_ADD_KEY (0x0037)
#define JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_KEY (0x0038)
#define JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEY_LIST (0x0039)
#define JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEY (0x003a)
#define JDKSAVDECC_AEM_COMMAND_AUTH_ADD_KEY_TO_CHAIN (0x003b)
#define JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_KEY_FROM_CHAIN (0x003c)
#define JDKSAVDECC_AEM_COMMAND_AUTH_GET_KEYCHAIN_LIST (0x003d)
#define JDKSAVDECC_AEM_COMMAND_AUTH_GET_IDENTITY (0x003e)
#define JDKSAVDECC_AEM_COMMAND_AUTH_ADD_TOKEN (0x003f)
#define JDKSAVDECC_AEM_COMMAND_AUTH_DELETE_TOKEN (0x0040)
#define JDKSAVDECC_AEM_COMMAND_AUTHENTICATE (0x0041)
#define JDKSAVDECC_AEM_COMMAND_DEAUTHENTICATE (0x0042)
#define JDKSAVDECC_AEM_COMMAND_ENABLE_TRANSPORT_SECURITY (0x0043)
#define JDKSAVDECC_AEM_COMMAND_DISABLE_TRANSPORT_SECURITY (0x0044)
#define JDKSAVDECC_AEM_COMMAND_ENABLE_STREAM_ENCRYPTION (0x0045)
#define JDKSAVDECC_AEM_COMMAND_DISABLE_STREAM_ENCRYPTION (0x0046)
#define JDKSAVDECC_AEM_COMMAND_SET_MEMORY_OBJECT_LENGTH (0x0047)
#define JDKSAVDECC_AEM_COMMAND_GET_MEMORY_OBJECT_LENGTH (0x0048)
#define JDKSAVDECC_AEM_COMMAND_SET_STREAM_BACKUP (0x0049)
#define JDKSAVDECC_AEM_COMMAND_GET_STREAM_BACKUP (0x004a)
#define JDKSAVDECC_AEM_COMMAND_EXPANSION (0x7fff)

/*@}*/

/** \addtogroup control_type control_type : Control Types - Clause 7.3.4  */
/*@{*/
#define JDKSAVDECC_AEM_CONTROL_TYPE_ENABLE 0x90e0f00000000000ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_IDENTIFY 0x90e0f00000000001ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MUTE 0x90e0f00000000002ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_INVERT 0x90e0f00000000003ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_GAIN 0x90e0f00000000004ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ATTENUATE 0x90e0f00000000005ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_DELAY 0x90e0f00000000006ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_SRC_MODE 0x90e0f00000000007ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_SNAPSHOT 0x90e0f00000000008ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_POW_LINE_FREQ 0x90e0f00000000009ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_POWER_STATUS 0x90e0f0000000000aULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_FAN_STATUS 0x90e0f0000000000bULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_TEMPERATURE 0x90e0f0000000000cULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ALTITUDE 0x90e0f0000000000dULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ABSOLUTE_HUMIDITY 0x90e0f0000000000eULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_RELATIVE_HUMIDITY 0x90e0f0000000000fULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ORIENTATION 0x90e0f00000000010ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_VELOCITY 0x90e0f00000000011ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ACCELERATION 0x90e0f00000000012ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_FILTER_RESPONSE 0x90e0f00000000013ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_PANPOT 0x90e0f00000010000ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_PHANTOM 0x90e0f00000100001ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_AUDIO_SCALE 0x90e0f00000100002ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_AUDIO_METERS 0x90e0f00000100003ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_AUDIO_SPECTRUM 0x90e0f00000100004ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_SCANNING_MODE 0x90e0f00000200000ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_AUTO_EXP_MODE 0x90e0f00000200001ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_AUTO_EXP_PRIO 0x90e0f00000200002ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_EXP_TIME 0x90e0f00000200003ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_FOCUS 0x90e0f00000200004ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_FOCUS_AUTO 0x90e0f00000200005ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_IRIS 0x90e0f00000200006ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_ZOOM 0x90e0f00000200007ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_PRIVACY 0x90e0f00000200008ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_BACKLIGHT 0x90e0f00000200009ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_BRIGHTNESS 0x90e0f0000020000aULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_CONTRAST 0x90e0f0000020000bULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_HUE 0x90e0f0000020000cULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_SATURATION 0x90e0f0000020000dULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_SHARPNESS 0x90e0f0000020000eULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_GAMMA 0x90e0f0000020000fULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_WHITE_BAL_TEMP 0x90e0f00000200010ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_WHITE_BAL_TEMP_AUTO 0x90e0f00000200011ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_WHITE_BAL_COMP 0x90e0f00000200012ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_WHITE_BAL_COMP_AUTO 0x90e0f00000200013ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_DIGITAL_ZOOM 0x90e0f00000200014ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_PLAYLIST 0x90e0f00000300000ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_PLAYLIST_NAME 0x90e0f00000300001ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_DISK 0x90e0f00000300002ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_DISK_NAME 0x90e0f00000300003ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_TRACK 0x90e0f00000300004ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_TRACK_NAME 0x90e0f00000300005ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_SPEED 0x90e0f00000300006ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_SAMPLE_POSITION 0x90e0f00000300007ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_PLAYBACK_TRANSPORT 0x90e0f00000300008ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MEDIA_RECORD_TRANSPORT 0x90e0f00000300009ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_FREQUENCY 0x90e0f00000400000ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_MODULATION 0x90e0f00000400001ULL
#define JDKSAVDECC_AEM_CONTROL_TYPE_POLARIZATION 0x90e0f00000400002ULL

/*@}*/

/** \addtogroup units Units */
/*@{*/

#define JDKSAVDECC_AEM_UNIT_UNITLESS (0x00)
#define JDKSAVDECC_AEM_UNIT_COUNT (0x01)
#define JDKSAVDECC_AEM_UNIT_PERCENT (0x02)
#define JDKSAVDECC_AEM_UNIT_FSTOP (0x03)


#define JDKSAVDECC_AEM_UNIT_TIME_SECONDS (0x08)
#define JDKSAVDECC_AEM_UNIT_TIME_MINUTES (0x09)
#define JDKSAVDECC_AEM_UNIT_TIME_HOURS (0x0a)
#define JDKSAVDECC_AEM_UNIT_TIME_DAYS (0x0b)
#define JDKSAVDECC_AEM_UNIT_TIME_MONTHS (0x0c)
#define JDKSAVDECC_AEM_UNIT_TIME_YEARS (0x0d)
#define JDKSAVDECC_AEM_UNIT_TIME_SAMPLES (0x0e)
#define JDKSAVDECC_AEM_UNIT_TIME_FRAMES (0x0f)


#define JDKSAVDECC_AEM_UNIT_FREQUENCY_HERTZ (0x10)
#define JDKSAVDECC_AEM_UNIT_FREQUENCY_SEMITONES (0x11)
#define JDKSAVDECC_AEM_UNIT_FREQUENCY_CENTS (0x12)
#define JDKSAVDECC_AEM_UNIT_FREQUENCY_OCTAVES (0x13)
#define JDKSAVDECC_AEM_UNIT_FREQUENCY_FPS (0x14)


#define JDKSAVDECC_AEM_UNIT_DISTANCE_METRES (0x18)


#define JDKSAVDECC_AEM_UNIT_TEMPERATURE_KELVIN (0x20)


#define JDKSAVDECC_AEM_UNIT_MASS_GRAMS (0x28)


#define JDKSAVDECC_AEM_UNIT_VOLTAGE_VOLTS (0x30)
#define JDKSAVDECC_AEM_UNIT_VOLTAGE_DBV (0x31)
#define JDKSAVDECC_AEM_UNIT_VOLTAGE_DBU (0x32)


#define JDKSAVDECC_AEM_UNIT_CURRENT_AMPS (0x38)


#define JDKSAVDECC_AEM_UNIT_POWER_WATTS (0x40)
#define JDKSAVDECC_AEM_UNIT_POWER_DBM (0x41)
#define JDKSAVDECC_AEM_UNIT_POWER_DBW (0x42)


#define JDKSAVDECC_AEM_UNIT_PRESSURE_PASCALS (0x48)


#define JDKSAVDECC_AEM_UNIT_MEMORY_BITS (0x50)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BYTES (0x51)
#define JDKSAVDECC_AEM_UNIT_MEMORY_KIBIBYTES (0x52)
#define JDKSAVDECC_AEM_UNIT_MEMORY_MEBIBYTES (0x53)
#define JDKSAVDECC_AEM_UNIT_MEMORY_GIBIBYTES (0x54)
#define JDKSAVDECC_AEM_UNIT_MEMORY_TEBIBYTES (0x55)


#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_BITS_PER_SEC (0x58)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_BYTES_PER_SEC (0x59)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_KIBIBYTES_PER_SEC (0x5a)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_MEBIBYTES_PER_SEC (0x5b)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_GIGIBYTES_PER_SEC (0x5c)
#define JDKSAVDECC_AEM_UNIT_MEMORY_BANDWIDTH_TEBIBYTES_PER_SEC (0x5d)


#define JDKSAVDECC_AEM_UNIT_LUMINOSITY_CANDELAS (0x60)


#define JDKSAVDECC_AEM_UNIT_ENERGY_JOULES (0x68)


#define JDKSAVDECC_AEM_UNIT_ANGLE_RADIANS (0x70)


#define JDKSAVDECC_AEM_UNIT_FORCE_NEWTONS (0x78)


#define JDKSAVDECC_AEM_UNIT_RESISTANCE_OHMS (0x80)


#define JDKSAVDECC_AEM_UNIT_VELOCITY_METRES_PER_SEC (0x88)
#define JDKSAVDECC_AEM_UNIT_VELOCITY_RADIANS_PER_SEC (0x89)


#define JDKSAVDECC_AEM_UNIT_ACCELERATION_METRES_PER_SEC_SQUARED (0x90)
#define JDKSAVDECC_AEM_UNIT_ACCELERATION_RADIANS_PER_SEC_SQUARED (0x91)


#define JDKSAVDECC_AEM_UNIT_MAGNETIC_FLUX_TESLAS (0x98)


#define JDKSAVDECC_AEM_UNIT_AREA_METERS_SQUARED (0xa0)


#define JDKSAVDECC_AEM_UNIT_VOLUME_METERS_CUBED (0xa8)
#define JDKSAVDECC_AEM_UNIT_VOLUME_LITRES (0xa9)


#define JDKSAVDECC_AEM_UNIT_LEVEL_DB (0xb0)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_PEAK (0xb1)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_RMS (0xb2)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DBFS (0xb3)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DBFS_PEAK (0xb4)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DBFS_RMS (0xb5)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DBTP (0xb6)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_A (0xb7)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_B (0xb8)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_C (0xb9)
#define JDKSAVDECC_AEM_UNIT_LEVEL_DB_SPL (0xba)
#define JDKSAVDECC_AEM_UNIT_LEVEL_LU (0xbb)
#define JDKSAVDECC_AEM_UNIT_LEVEL_LUFS (0xbc)

/*@}*/

/** \addtogroup descriptor */
/*@{*/

#define JDKSAVDECC_AEM_DESCRIPTOR_SIZE (508) /// Clause 7.2

/*@}*/

/** \addtogroup command */
/*@{*/

#define JDKSAVDECC_AEM_COMMAND_SIZE (524) /// Clause 9.2.1.1.7

/*@}*/

/** \addtogroup pull Sample Rate Pull field - See Clause 7.3.1.1 */
/*@{*/

#define JDKSAVDECC_AEM_SAMPLE_RATE_PULL_MULTIPLY_1 (0x0)
#define JDKSAVDECC_AEM_SAMPLE_RATE_PULL_MULTIPLY_1_DIV_1_001 (0x1)
#define JDKSAVDECC_AEM_SAMPLE_RATE_PULL_MULTIPLY_1_001 (0x2)
#define JDKSAVDECC_AEM_SAMPLE_RATE_PULL_MULTIPLY_24_DIV_25 (0x3)
#define JDKSAVDECC_AEM_SAMPLE_RATE_PULL_MULTIPLY_25_DIV_24 (0x4)

/*@}*/

/** \addtogroup aecpdu_aem AECPDU AEM - Clause 9.2.1.2 */
/*@{*/


#define JDKSAVDECC_AECPDU_AEM_OFFSET_CONTROLLER_GUID (0)
#define JDKSAVDECC_AECPDU_AEM_OFFSET_SEQUENCE_ID (8)
#define JDKSAVDECC_AECPDU_AEM_OFFSET_COMMAND_TYPE (10)
#define JDKSAVDECC_AECPDU_AEM_LEN (12)

/*@}*/

static inline ssize_t jdksavdecc_aem_write_descriptor_counts( uint16_t descriptor_type, uint16_t count, void *buf, ssize_t pos, ssize_t buf_len )
{
    ssize_t r = pos;
    r = jdksavdecc_uint16_write( descriptor_type, buf, r, buf_len );
    r = jdksavdecc_uint16_write( count,buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_int8(
        int8_t minimum_value,
        int8_t maximum_value,
        int8_t step_value,
        int8_t default_value,
        int8_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint8_write( (uint8_t)minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( (uint8_t)maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( (uint8_t)step_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( (uint8_t)default_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( (uint8_t)current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_uint8(
        uint8_t minimum_value,
        uint8_t maximum_value,
        uint8_t step_value,
        uint8_t default_value,
        uint8_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint8_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( step_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( default_value, buf, r, buf_len );
    r = jdksavdecc_uint8_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_int16(
        int16_t minimum_value,
        int16_t maximum_value,
        int16_t step_value,
        int16_t default_value,
        int16_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint16_write( (uint16_t)minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)step_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)default_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_uint16(
        uint16_t minimum_value,
        uint16_t maximum_value,
        uint16_t step_value,
        uint16_t default_value,
        uint16_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint16_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( step_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( default_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_int32(
        int32_t minimum_value,
        int32_t maximum_value,
        int32_t step_value,
        int32_t default_value,
        int32_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint32_write( (uint32_t)minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( (uint32_t)maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( (uint32_t)step_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( (uint32_t)default_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( (uint32_t)current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_uint32(
        uint32_t minimum_value,
        uint32_t maximum_value,
        uint32_t step_value,
        uint32_t default_value,
        uint32_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint32_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( step_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( default_value, buf, r, buf_len );
    r = jdksavdecc_uint32_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_int64(
        int64_t minimum_value,
        int64_t maximum_value,
        int64_t step_value,
        int64_t default_value,
        int64_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint64_write( (uint64_t)minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( (uint64_t)maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( (uint64_t)step_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( (uint64_t)default_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( (uint64_t)current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_uint64(
        uint64_t minimum_value,
        uint64_t maximum_value,
        uint64_t step_value,
        uint64_t default_value,
        uint64_t current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_uint64_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( step_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( default_value, buf, r, buf_len );
    r = jdksavdecc_uint64_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

static inline ssize_t jdksavdecc_aem_write_values_format_linear_float(
        float minimum_value,
        float maximum_value,
        float step_value,
        float default_value,
        float current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_float_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_float_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_float_write( step_value, buf, r, buf_len );
    r = jdksavdecc_float_write( default_value, buf, r, buf_len );
    r = jdksavdecc_float_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}


static inline ssize_t jdksavdecc_aem_write_values_format_linear_double(
        double minimum_value,
        double maximum_value,
        double step_value,
        double default_value,
        double current_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r=pos;
    r = jdksavdecc_double_write( minimum_value, buf, r, buf_len );
    r = jdksavdecc_double_write( maximum_value, buf, r, buf_len );
    r = jdksavdecc_double_write( step_value, buf, r, buf_len );
    r = jdksavdecc_double_write( default_value, buf, r, buf_len );
    r = jdksavdecc_double_write( current_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    return r;
}

/** @todo Selector types, array types, utf, bode plot, smpte time, sample rate, gptp time */

static inline ssize_t jdksavdecc_aem_write_values_format_utf8(
        struct jdksavdecc_string *s,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    return jdksavdecc_string_write( s, buf, pos, buf_len );
}

static inline ssize_t jdksavdecc_aem_write_values_format_array_uint16(
        uint16_t minimum_value,
        uint16_t maximum_value,
        uint16_t step_value,
        uint16_t default_value,
        uint8_t multiplier,
        uint8_t unit_code,
        uint16_t localized_string_reference,
        uint8_t* current_values, int16_t num_values,
        void* buf, ssize_t pos, ssize_t buf_len
        )
{
    ssize_t r = pos;
    int i;
    r = jdksavdecc_uint16_write( (uint16_t)minimum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)maximum_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)step_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( (uint16_t)default_value, buf, r, buf_len );
    r = jdksavdecc_uint16_write( JDKSAVDECC_AEM_UNITS(multiplier,unit_code), buf, r, buf_len );
    r = jdksavdecc_uint16_write( localized_string_reference, buf, r, buf_len );
    
    for ( i = 0; i < num_values; i++ )
    {
        r = jdksavdecc_uint16_write( (uint16_t)current_values[ i ], buf, r, buf_len );
    }

    return r;
}

#endif

