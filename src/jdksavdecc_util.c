
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

int jdksavdecc_util_parse_nibble( uint8_t *result, char d1 )
{
    int r = 0;

    uint8_t d = 0;
    if ( d1 >= '0' && d1 <= '9' )
    {
        d = d1 - '0';
        r = 1;
    }
    else if ( d1 >= 'A' && d1 <= 'F' )
    {
        d = 0xa + d1 - 'A';
        r = 1;
    }
    else if ( d1 >= 'a' && d1 <= 'f' )
    {
        d = 0xa + d1 - 'a';
        r = 1;
    }

    if ( r == 1 )
    {
        *result = *result << 4;
        *result |= d;
    }
    return r;
}

int jdksavdecc_util_parse_byte( uint8_t *result, char d1, char d2 )
{
    return jdksavdecc_util_parse_nibble( result, d1 ) && jdksavdecc_util_parse_nibble( result, d2 );
}

int jdksavdecc_eui48_init_from_cstr( struct jdksavdecc_eui48 *self, const char *str )
{
    return jdksavdecc_util_parse_byte( &self->value[0], str[0], str[1] ) && str[2] == ':'
           && jdksavdecc_util_parse_byte( &self->value[1], str[3], str[4] ) && str[5] == ':'
           && jdksavdecc_util_parse_byte( &self->value[2], str[6], str[7] ) && str[8] == ':'
           && jdksavdecc_util_parse_byte( &self->value[3], str[9], str[10] ) && str[11] == ':'
           && jdksavdecc_util_parse_byte( &self->value[4], str[12], str[13] ) && str[14] == ':'
           && jdksavdecc_util_parse_byte( &self->value[5], str[15], str[16] ) && str[17] == '\0';
}

int jdksavdecc_eui64_init_from_cstr( struct jdksavdecc_eui64 *self, const char *str )
{
    return jdksavdecc_util_parse_byte( &self->value[0], str[0], str[1] ) && str[2] == ':'
           && jdksavdecc_util_parse_byte( &self->value[1], str[3], str[4] ) && str[5] == ':'
           && jdksavdecc_util_parse_byte( &self->value[2], str[6], str[7] ) && str[8] == ':'
           && jdksavdecc_util_parse_byte( &self->value[3], str[9], str[10] ) && str[11] == ':'
           && jdksavdecc_util_parse_byte( &self->value[4], str[12], str[13] ) && str[14] == ':'
           && jdksavdecc_util_parse_byte( &self->value[5], str[15], str[16] ) && str[17] == ':'
           && jdksavdecc_util_parse_byte( &self->value[6], str[18], str[19] ) && str[20] == ':'
           && jdksavdecc_util_parse_byte( &self->value[7], str[21], str[22] ) && str[23] == '\0';
}
