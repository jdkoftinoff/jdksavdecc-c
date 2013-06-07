
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
#include "jdksavdecc_aem_descriptor.h"


ssize_t jdksavdecc_aem_write_descriptor_counts( uint16_t descriptor_type, uint16_t count, void *buf, ssize_t pos, ssize_t buf_len )
{
    ssize_t r = pos;
    r = jdksavdecc_uint16_write( descriptor_type, buf, r, buf_len );
    r = jdksavdecc_uint16_write( count,buf, r, buf_len );
    return r;
}

ssize_t jdksavdecc_aem_write_values_format_linear_int8(
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

ssize_t jdksavdecc_aem_write_values_format_linear_uint8(
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

ssize_t jdksavdecc_aem_write_values_format_linear_int16(
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

ssize_t jdksavdecc_aem_write_values_format_linear_uint16(
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

ssize_t jdksavdecc_aem_write_values_format_linear_int32(
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

ssize_t jdksavdecc_aem_write_values_format_linear_uint32(
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

ssize_t jdksavdecc_aem_write_values_format_linear_int64(
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

ssize_t jdksavdecc_aem_write_values_format_linear_uint64(
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

ssize_t jdksavdecc_aem_write_values_format_linear_float(
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


ssize_t jdksavdecc_aem_write_values_format_linear_double(
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

ssize_t jdksavdecc_aem_write_values_format_utf8(
        struct jdksavdecc_string *s,
        void *buf, ssize_t pos, ssize_t buf_len
        )
{
    return jdksavdecc_string_write( s, buf, pos, buf_len );
}

ssize_t jdksavdecc_aem_write_values_format_array_uint16(
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
