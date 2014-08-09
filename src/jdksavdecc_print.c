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
#include "jdksavdecc_print.h"

char jdksavdecc_printer_hexdig[16] = "0123456789ABCDEF";

void jdksavdecc_printer_print( struct jdksavdecc_printer *self, char const *v )
{
    while ( *v )
    {
        jdksavdecc_printer_printc( self, *v++ );
    }
}

void jdksavdecc_printer_print_label( struct jdksavdecc_printer *self, char const *v )
{
    size_t padded_size = 40;
    size_t len = strlen( v );
    size_t padding = 0;
    size_t total_len = len;

    if ( len < padded_size )
    {
        padding = padded_size - len;
        total_len = 64;
    }

    if ( self->max_len - self->pos > total_len + 1 )
    {
        size_t i;
        for ( i = 0; i < padding; ++i )
        {
            self->buf[self->pos++] = ' ';
        }

        while ( *v )
        {
            jdksavdecc_printer_printc( self, *v++ );
        }
    }
    jdksavdecc_printer_printc( self, ':' );
}

void jdksavdecc_printer_print_block(
    struct jdksavdecc_printer *self, const uint8_t *p, size_t sz, size_t start_pos, size_t end_pos )
{
    size_t pos;
    for ( pos = start_pos; pos < end_pos && pos < sz; ++pos )
    {
        jdksavdecc_printer_print_hexdigits( self, p[pos] );
        jdksavdecc_printer_printc( self, ' ' );
    }
    jdksavdecc_printer_print_eol( self );
}

void jdksavdecc_printer_print_hexdigits( struct jdksavdecc_printer *self, uint8_t v )
{
    if ( self->max_len - self->pos > 3 )
    {
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v >> 4];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print_uint8( struct jdksavdecc_printer *self, uint8_t v )
{
    if ( self->max_len - self->pos > 5 )
    {
        self->buf[self->pos++] = '0';
        self->buf[self->pos++] = 'x';
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v >> 4];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print_uint16( struct jdksavdecc_printer *self, uint16_t v )
{
    if ( self->max_len - self->pos > 7 )
    {
        self->buf[self->pos++] = '0';
        self->buf[self->pos++] = 'x';
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 12 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 8 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 4 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print_uint32( struct jdksavdecc_printer *self, uint32_t v )
{
    if ( self->max_len - self->pos > 11 )
    {
        self->buf[self->pos++] = '0';
        self->buf[self->pos++] = 'x';
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 28 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 24 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 20 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 16 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 12 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 8 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 4 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print_uint64( struct jdksavdecc_printer *self, uint64_t v )
{
    if ( self->max_len - self->pos > 19 )
    {
        self->buf[self->pos++] = '0';
        self->buf[self->pos++] = 'x';
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 60 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 56 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 52 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 48 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 44 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 40 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 36 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 32 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 28 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 24 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 20 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 16 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 12 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 8 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 4 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print_eui48( struct jdksavdecc_printer *self, struct jdksavdecc_eui48 v )
{
    jdksavdecc_printer_print_hexdigits( self, v.value[0] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[1] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[2] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[3] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[4] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[5] );
}

void jdksavdecc_printer_print_eui64( struct jdksavdecc_printer *self, struct jdksavdecc_eui64 v )
{
    jdksavdecc_printer_print_hexdigits( self, v.value[0] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[1] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[2] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[3] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[4] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[5] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[6] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[7] );
}

void jdksavdecc_printer_print_streamid( struct jdksavdecc_printer *self, struct jdksavdecc_eui64 v )
{
    jdksavdecc_printer_print_hexdigits( self, v.value[0] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[1] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[2] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[3] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[4] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[5] );
    jdksavdecc_printer_print( self, ":" );
    jdksavdecc_printer_print_hexdigits( self, v.value[6] );
    jdksavdecc_printer_print( self, "-" );
    jdksavdecc_printer_print_hexdigits( self, v.value[7] );
}

void jdksavdecc_printer_print_string( struct jdksavdecc_printer *self, struct jdksavdecc_string const *v )
{
    size_t i = 0;
    size_t len = jdksavdecc_string_length( v );
    jdksavdecc_printer_printc( self, '\"' );
    for ( i = 0; i < len; ++i )
    {
        int8_t c = (int8_t)v->value[i];
        switch ( c )
        {
        case '\"':
            jdksavdecc_printer_printc( self, '\\' );
            jdksavdecc_printer_printc( self, '\"' );
            break;
        case '\t':
            jdksavdecc_printer_printc( self, '\\' );
            jdksavdecc_printer_printc( self, 't' );
            break;
        case '\r':
            jdksavdecc_printer_printc( self, '\\' );
            jdksavdecc_printer_printc( self, 'r' );
            break;
        case '\n':
            jdksavdecc_printer_printc( self, '\\' );
            jdksavdecc_printer_printc( self, 'n' );
            break;
        default:
            if ( c < 0x20 )
            {
                jdksavdecc_printer_printc( self, '\\' );
                jdksavdecc_printer_printc( self, 'x' );
                jdksavdecc_printer_print_hexdigits( self, (uint8_t)c );
            }
            else
            {
                jdksavdecc_printer_printc( self, c );
            }
        }
    }
    jdksavdecc_printer_printc( self, '\"' );
}

void jdksavdecc_printer_print_gptp_seconds( struct jdksavdecc_printer *self, struct jdksavdecc_gptp_seconds p )
{
    uint64_t v = p.seconds;
    if ( self->max_len - self->pos > 15 )
    {
        self->buf[self->pos++] = '0';
        self->buf[self->pos++] = 'x';
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 44 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 40 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 36 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 32 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 28 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 24 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 20 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 16 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 12 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 8 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[( v >> 4 ) & 0xf];
        self->buf[self->pos++] = jdksavdecc_printer_hexdig[v & 0xf];
        self->buf[self->pos] = '\0';
    }
}

char const *jdksavdecc_get_name_for_16bit_value( struct jdksavdecc_16bit_name const names[], uint16_t v )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( names[i].bit_value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

int jdksavdecc_get_16bit_value_for_name( struct jdksavdecc_16bit_name const names[], char const *name, uint16_t *result )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            *result = names[i].bit_value;
            return 1;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_32bit_value( struct jdksavdecc_32bit_name const names[], uint32_t v )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( names[i].bit_value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

int jdksavdecc_get_32bit_value_for_name( struct jdksavdecc_32bit_name const names[], char const *name, uint32_t *result )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            *result = names[i].bit_value;
            return 1;
        }
        ++i;
    }
    return 0;
}

int jdksavdecc_get_uint16_value_for_name( struct jdksavdecc_uint16_name const names[], char const *name, uint16_t *result )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            *result = names[i].value;
            return 1;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_uint16_value( struct jdksavdecc_uint16_name const names[], uint16_t v )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

int jdksavdecc_get_uint32_value_for_name( struct jdksavdecc_uint32_name const names[], char const *name, uint32_t *result )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            *result = names[i].value;
            return 1;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_uint32_value( struct jdksavdecc_uint32_name const names[], uint32_t v )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

int jdksavdecc_get_uint64_value_for_name( struct jdksavdecc_uint64_name const names[], char const *name, uint64_t *result )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            *result = names[i].value;
            return 1;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_uint64_value( struct jdksavdecc_uint64_name const names[], uint64_t v )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

struct jdksavdecc_eui48 const *jdksavdecc_get_eui48_value_for_name( struct jdksavdecc_eui48_name const names[],
                                                                    char const *name )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            return &names[i].value;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_eui48_value( struct jdksavdecc_eui48_name const names[], struct jdksavdecc_eui48 v )
{
    int i = 0;

    while ( names[i].name )
    {
        int found = 1;
        size_t j;
        for ( j = 0; j < sizeof( v.value ); ++j )
        {
            if ( names[i].value.value[j] != v.value[j] )
            {
                found = 0;
            }
        }

        if ( found )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

struct jdksavdecc_eui64 const *jdksavdecc_get_eui64_value_for_name( struct jdksavdecc_eui64_name const names[],
                                                                    char const *name )
{
    int i = 0;

    while ( names[i].name )
    {
        if ( strcmp( name, names[i].name ) == 0 )
        {
            return &names[i].value;
        }
        ++i;
    }
    return 0;
}

char const *jdksavdecc_get_name_for_eui64_value( struct jdksavdecc_eui64_name const names[], struct jdksavdecc_eui64 v )
{
    int i = 0;

    while ( names[i].name )
    {
        int found = 1;
        size_t j;
        for ( j = 0; j < sizeof( v.value ); ++j )
        {
            if ( names[i].value.value[j] != v.value[j] )
            {
                found = 0;
            }
        }

        if ( found )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

void jdksavdecc_printer_print_16bit_names( struct jdksavdecc_printer *self,
                                           struct jdksavdecc_16bit_name const names[],
                                           uint16_t v )
{
    size_t i = 0;

    jdksavdecc_printer_print( self, "[ " );
    while ( names[i].name )
    {
        if ( names[i].bit_value & v )
        {
            jdksavdecc_printer_print( self, names[i].name );
            jdksavdecc_printer_print( self, " " );
        }
        ++i;
    }
    jdksavdecc_printer_print( self, "]" );
}

void jdksavdecc_printer_print_32bit_names( struct jdksavdecc_printer *self,
                                           struct jdksavdecc_32bit_name const names[],
                                           uint32_t v )
{
    size_t i = 0;

    jdksavdecc_printer_print( self, "[ " );
    while ( names[i].name )
    {
        if ( names[i].bit_value & v )
        {
            jdksavdecc_printer_print( self, names[i].name );
            jdksavdecc_printer_print( self, " " );
        }
        ++i;
    }
    jdksavdecc_printer_print( self, "]" );
}

void jdksavdecc_printer_print_uint16_name( struct jdksavdecc_printer *self,
                                           struct jdksavdecc_uint16_name const names[],
                                           uint16_t v )
{
    char const *s = jdksavdecc_get_name_for_uint16_value( names, v );
    if ( s )
    {
        jdksavdecc_printer_print( self, s );
    }
    else
    {
        jdksavdecc_printer_print_uint16( self, v );
    }
}

void jdksavdecc_printer_print_uint32_name( struct jdksavdecc_printer *self,
                                           struct jdksavdecc_uint32_name const names[],
                                           uint32_t v )
{
    char const *s = jdksavdecc_get_name_for_uint32_value( names, v );
    if ( s )
    {
        jdksavdecc_printer_print( self, s );
    }
    else
    {
        jdksavdecc_printer_print_uint32( self, v );
    }
}

void jdksavdecc_printer_print_uint64_name( struct jdksavdecc_printer *self,
                                           struct jdksavdecc_uint64_name const names[],
                                           uint64_t v )
{
    char const *s = jdksavdecc_get_name_for_uint64_value( names, v );
    if ( s )
    {
        jdksavdecc_printer_print( self, s );
    }
    else
    {
        jdksavdecc_printer_print_uint64( self, v );
    }
}

void jdksavdecc_printer_print_eui48_name( struct jdksavdecc_printer *self,
                                          struct jdksavdecc_eui48_name const names[],
                                          struct jdksavdecc_eui48 v )
{
    char const *s = jdksavdecc_get_name_for_eui48_value( names, v );
    if ( s )
    {
        jdksavdecc_printer_print( self, s );
    }
}

void jdksavdecc_printer_print_eui64_name( struct jdksavdecc_printer *self,
                                          struct jdksavdecc_eui64_name const names[],
                                          struct jdksavdecc_eui64 v )
{
    char const *s = jdksavdecc_get_name_for_eui64_value( names, v );
    if ( s )
    {
        jdksavdecc_printer_print( self, s );
    }
}
