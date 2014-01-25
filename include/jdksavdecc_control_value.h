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


/** \addtogroup aem_control_value_helpers Helper functions to determine general type of control contents */
/*@{*/

bool jdksavdecc_control_value_is_numeric(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

bool jdksavdecc_control_value_is_floating_point(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

bool jdksavdecc_control_value_is_textual(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

bool jdksavdecc_control_value_is_selector(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

bool jdksavdecc_control_value_is_linear(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

bool jdksavdecc_control_value_is_array(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      int item );

/*@}*/

/** \addtogroup aem_control_as_string Helper functions to determine values of an item in a control descriptor as strings */
/*@{*/

bool jdksavdecc_control_value_get_item_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      uint8_t const *control_data,
      uint16_t control_data_len,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_value_set_item_from_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      uint8_t const *control_data,
      uint16_t control_data_len,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_descriptor_get_item_current_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_descriptor_get_item_minimum_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_descriptor_get_item_maximum_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_descriptor_get_item_step_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      char *string_buf,
      size_t string_buf_max_len );

bool jdksavdecc_control_descriptor_get_item_default_as_string(
      uint8_t const *descriptor,
      uint16_t descriptor_len,
      uint16_t item,
      char *string_buf,
      size_t string_buf_max_len );

/*@}*/


/*@}*/

#ifdef __cplusplus
}
#endif
