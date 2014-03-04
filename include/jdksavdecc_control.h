#pragma once

/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
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
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"
#include "jdksavdecc_entity_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup aem_control_value AEM Clause 7.3.5 - Control Value Types */
/*@{*/

#define JDKSAVDECC_CONTROL_VALUE_LINEAR_INT8 (0x0000)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_UINT8 (0x0001)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_INT16 (0x0002)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_UINT16 (0x0003)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_INT32 (0x0004)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_UINT32 (0x0005)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_INT64 (0x0006)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_UINT64 (0x0007)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_FLOAT (0x0008)
#define JDKSAVDECC_CONTROL_VALUE_LINEAR_DOUBLE (0x0009)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_INT8 (0x000a)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_UINT8 (0x000b)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_INT16 (0x000c)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_UINT16 (0x000d)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_INT32 (0x000e)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_UINT32 (0x000f)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_INT64 (0x0010)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_UINT64 (0x0011)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_FLOAT (0x0012)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_DOUBLE (0x0013)
#define JDKSAVDECC_CONTROL_VALUE_SELECTOR_STRING (0x0014)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_INT8 (0x0015)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_UINT8 (0x0016)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_INT16 (0x0017)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_UINT16 (0x0018)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_INT32 (0x0019)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_UINT32 (0x001a)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_INT64 (0x001b)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_UINT64 (0x001c)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_FLOAT (0x001d)
#define JDKSAVDECC_CONTROL_VALUE_ARRAY_DOUBLE (0x001e)
#define JDKSAVDECC_CONTROL_VALUE_UTF8 (0x001f)
#define JDKSAVDECC_CONTROL_VALUE_BODE_PLOT (0x0020)
#define JDKSAVDECC_CONTROL_VALUE_SMPTE_TIME (0x0021)
#define JDKSAVDECC_CONTROL_VALUE_SAMPLE_RATE (0x0022)
#define JDKSAVDECC_CONTROL_VALUE_GPTP_TIME (0x0023)
#define JDKSAVDECC_CONTROL_VALUE_VENDOR (0x3ffe)
#define JDKSAVDECC_CONTROL_VALUE_EXPANSION (0x3fff)


/// See IEEE Std 1722.1-2013 Clause 7.3.5.1
#define JDKSAVDECC_CONTROL_VALUE_MASK (0x3fff)

/// See IEEE Std 1722.1-2013 Clause 7.3.5.1.1
#define JDKSAVDECC_CONTROL_VALUE_MASK_READONLY (0x8000)

/// See IEEE Std 1722.1-2013 Clause 7.3.5.1.2
#define JDKSAVDECC_CONTROL_VALUE_MASK_UNKNOWN (0x4000)

/*@}*/

/** \addtogroup aem_control_value_helpers Helper functions to determine general type of control contents */
/*@{*/

/// bode plot point: See IEEE Std 1722.1-2013 Clause 7.3.5.2.5
struct jdksavdecc_control_bode_plot_point {
    float frequency_hz;
    float magnitude_db;
    float phase_rad;
};

#define JDKSAVDECC_CONTROL_VENDOR_BLOB_MAX_LEN (JDKSAVDECC_AEM_DESCRIPTOR_SIZE-JDKSAVDECC_DESCRIPTOR_CONTROL_LEN )

struct jdksavdecc_control_vendor_blob {
    struct jdksavdecc_eui64 vendor_eui64;
    uint16_t blob_len;
    uint8_t blob_data[ JDKSAVDECC_CONTROL_VENDOR_BLOB_MAX_LEN ];
};

struct jdksavdecc_control_info {
    void const *descriptor_data;
    uint16_t descriptor_len;
};

bool jdksavdecc_control_init(
        struct jdksavdecc_control_info *self,
        void const *descriptor_data,
        uint16_t descriptor_len
        );

static inline
struct jdksavdecc_eui64 jdksavdecc_control_get_control_type(
        struct jdksavdecc_control_info const *control_info )  {
    struct jdksavdecc_eui64 r;
    jdksavdecc_eui64_init(&r);
    if( control_info->descriptor_data!=0 && control_info->descriptor_len >= JDKSAVDECC_DESCRIPTOR_CONTROL_LEN ) {
        r=jdksavdecc_descriptor_control_get_control_type(control_info->descriptor_data,0);
    }
    return r;
}

static inline uint16_t jdksavdecc_control_get_control_value_type(
        struct jdksavdecc_control_info const *control_info )  {
    uint16_t r=JDKSAVDECC_CONTROL_VALUE_EXPANSION;
    if( control_info->descriptor_data!=0 && control_info->descriptor_len >= JDKSAVDECC_DESCRIPTOR_CONTROL_LEN ) {
        r=jdksavdecc_descriptor_control_get_control_value_type(control_info->descriptor_data,0) & JDKSAVDECC_CONTROL_VALUE_MASK;
    }
    return r;
}

static inline bool jdksavdecc_control_is_value_readonly(
        struct jdksavdecc_control_info const *control_info ) {
    bool r=false;
    uint16_t v;
    if( control_info->descriptor_len >= JDKSAVDECC_DESCRIPTOR_CONTROL_LEN ) {
        v=jdksavdecc_descriptor_control_get_control_value_type(control_info->descriptor_data,0);
        r=((v&JDKSAVDECC_CONTROL_VALUE_MASK_READONLY)!=0);
    }
    return r;
}

static inline bool jdksavdecc_control_is_value_unknown(
        struct jdksavdecc_control_info const *control_info ) {
    bool r=false;
    uint16_t v;
    if( control_info->descriptor_len >= JDKSAVDECC_DESCRIPTOR_CONTROL_LEN ) {
        v=jdksavdecc_descriptor_control_get_control_value_type(control_info->descriptor_data,0);
        r=((v&JDKSAVDECC_CONTROL_VALUE_MASK_UNKNOWN)!=0);
    }
    return r;
}


bool jdksavdecc_control_get_localized_description(
        struct jdksavdecc_control_info const *control_info,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t configuration_index,
        uint16_t locale_id,
        struct jdksavdecc_string *result
        );

uint16_t jdksavdecc_control_get_num_items(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_get_item_localized_description(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t configuration_index,
        uint16_t locale_id,
        struct jdksavdecc_string *result
        );

bool jdksavdecc_control_is_numeric(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_integer(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_uses_multiplier(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_floating_point(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_selector(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_linear(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_array(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_is_vendor_blob(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_get_vendor_id(
        struct jdksavdecc_control_info const *control_info,
        struct jdksavdecc_eui64 *result_vendor_eui64 );

uint16_t jdksavdecc_control_get_vendor_blob_length(
        struct jdksavdecc_control_info const *control_info );

bool jdksavdecc_control_get_vendor_blob(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        uint8_t *blob_buf,
        size_t blob_buf_max_len );

bool jdksavdecc_control_set_vendor_blob(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        uint8_t const *blob_buf,
        size_t blob_buf_max_len );

int jdksavdecc_control_get_item_multiplier_power(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item );

double jdksavdecc_control_get_item_multiplier(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item );

char const *jdksavdecc_control_get_item_units_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item );

bool jdksavdecc_control_get_item_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id );

bool jdksavdecc_control_set_item_from_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        char const *string_buf,
        size_t string_buf_max_len );

bool jdksavdecc_control_get_item_current_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id  );

bool jdksavdecc_control_get_item_minimum_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id  );

bool jdksavdecc_control_get_item_maximum_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id  );

bool jdksavdecc_control_get_item_step_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id  );

bool jdksavdecc_control_get_item_default_as_string(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        char *string_buf,
        size_t string_buf_max_len,
        struct jdksavdecc_entity_model *entity_model,
        uint16_t locale_id  );

///
bool jdksavdecc_control_get_item_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        int8_t *result );

bool jdksavdecc_control_set_item_from_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        int8_t new_value );

bool jdksavdecc_control_get_item_current_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int8_t *result );

bool jdksavdecc_control_get_item_minimum_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int8_t *result );

bool jdksavdecc_control_get_item_maximum_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int8_t *result );

bool jdksavdecc_control_get_item_step_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int8_t *result );

bool jdksavdecc_control_get_item_default_as_int8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int8_t *result );

///
bool jdksavdecc_control_get_item_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        uint8_t *result );

bool jdksavdecc_control_set_item_from_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        uint8_t new_value );

bool jdksavdecc_control_get_item_current_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *result );

bool jdksavdecc_control_get_item_minimum_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *result );

bool jdksavdecc_control_get_item_maximum_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *result );

bool jdksavdecc_control_get_item_step_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *result );

bool jdksavdecc_control_get_item_default_as_uint8(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *result );

///
bool jdksavdecc_control_get_item_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        int16_t *result );

bool jdksavdecc_control_set_item_from_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        int16_t new_value );

bool jdksavdecc_control_get_item_current_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int16_t *result );

bool jdksavdecc_control_get_item_minimum_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int16_t *result );

bool jdksavdecc_control_get_item_maximum_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int16_t *result );

bool jdksavdecc_control_get_item_step_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int16_t *result );

bool jdksavdecc_control_get_item_default_as_int16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int16_t *result );

///
bool jdksavdecc_control_get_item_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        uint16_t *result );

bool jdksavdecc_control_set_item_from_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        uint16_t new_value );

bool jdksavdecc_control_get_item_current_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint16_t *result );

bool jdksavdecc_control_get_item_minimum_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint16_t *result );

bool jdksavdecc_control_get_item_maximum_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint16_t *result );

bool jdksavdecc_control_get_item_step_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint16_t *result );

bool jdksavdecc_control_get_item_default_as_uint16(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint16_t *result );

///
bool jdksavdecc_control_get_item_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        int32_t *result );

bool jdksavdecc_control_set_item_from_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        int32_t new_value );

bool jdksavdecc_control_get_item_current_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int32_t *result );

bool jdksavdecc_control_get_item_minimum_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int32_t *result );

bool jdksavdecc_control_get_item_maximum_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int32_t *result );

bool jdksavdecc_control_get_item_step_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int32_t *result );

bool jdksavdecc_control_get_item_default_as_int32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int32_t *result );

///
bool jdksavdecc_control_get_item_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        uint32_t *result );

bool jdksavdecc_control_set_item_from_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        uint32_t new_value );

bool jdksavdecc_control_get_item_current_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint32_t *result );

bool jdksavdecc_control_get_item_minimum_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint32_t *result );

bool jdksavdecc_control_get_item_maximum_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint32_t *result );

bool jdksavdecc_control_get_item_step_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint32_t *result );

bool jdksavdecc_control_get_item_default_as_uint32(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint32_t *result );


///
bool jdksavdecc_control_get_item_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        int64_t *result );

bool jdksavdecc_control_set_item_from_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        int64_t new_value );

bool jdksavdecc_control_get_item_current_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int64_t *result );

bool jdksavdecc_control_get_item_minimum_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int64_t *result );

bool jdksavdecc_control_get_item_maximum_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int64_t *result );

bool jdksavdecc_control_get_item_step_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int64_t *result );

bool jdksavdecc_control_get_item_default_as_int64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        int64_t *result );

///
bool jdksavdecc_control_get_item_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        uint64_t *result );

bool jdksavdecc_control_set_item_from_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        uint64_t new_value );

bool jdksavdecc_control_get_item_current_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint64_t *result );

bool jdksavdecc_control_get_item_minimum_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint64_t *result );

bool jdksavdecc_control_get_item_maximum_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint64_t *result );

bool jdksavdecc_control_get_item_step_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint64_t *result );

bool jdksavdecc_control_get_item_default_as_uint64(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint64_t *result );

///
bool jdksavdecc_control_get_bode_plot_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_control_bode_plot_point *result );

bool jdksavdecc_control_set_bode_plot_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_control_bode_plot_point const *new_value );

bool jdksavdecc_control_get_bode_plot_layout(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_values_bode_plot *result );

bool jdksavdecc_control_get_current_bode_plot_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_control_bode_plot_point *result );

///
bool jdksavdecc_control_get_smpte_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_smpte_time *result );

bool jdksavdecc_control_set_smpte_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_smpte_time const *new_value );

bool jdksavdecc_control_get_current_smpte_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_values_smpte_time *result );

///
bool jdksavdecc_control_get_sample_rate_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_sample_rate *result );

bool jdksavdecc_control_set_sample_rate_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_sample_rate const *new_value );

bool jdksavdecc_control_get_current_sample_rate_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_values_sample_rate *result );

///
bool jdksavdecc_control_get_gptp_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t const *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_gptp_time *result );

bool jdksavdecc_control_set_gptp_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        uint8_t *control_data,
        uint16_t control_data_len,
        struct jdksavdecc_values_gptp_time const *new_value );

bool jdksavdecc_control_get_current_gptp_time_item(
        struct jdksavdecc_control_info const *control_info,
        uint16_t item,
        struct jdksavdecc_values_gptp_time *result );


/*@}*/

#ifdef __cplusplus
}
#endif
