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

char jdksavdecc_hexdig[16] = "0123456789ABCDEF";

void jdksacdecc_print_eol( FILE *f )
{
    jdksavdecc_printc(f,'\n');
}

void jdksavdecc_print_label( FILE *f, char const *v )
{
    jdksavdecc_print( f, "%40s: ", v );
}

void jdksavdecc_print_hexdigits( FILE *f, uint8_t v )
{
    jdksavdecc_print( f, "%02" PRIX8, v );
}


void jdksavdecc_print_uint8( FILE *f, uint8_t v )
{
    jdksavdecc_print( f, "0x%02" PRIX8, v );
}

void jdksavdecc_print_uint16( FILE *f, uint16_t v )
{
    jdksavdecc_print( f, "0x%04" PRIX16, v );
}

void jdksavdecc_print_uint32( FILE *f, uint32_t v )
{
    jdksavdecc_print( f, "0x%08" PRIX32, v );
}

void jdksavdecc_print_uint64( FILE *f, uint64_t v )
{
    jdksavdecc_print( f, "0x%016" PRIX64, v );
}

void jdksavdecc_print_eui48( FILE *f, struct jdksavdecc_eui48 v )
{
    jdksavdecc_print_hexdigits(f, v.value[0] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[1] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[2] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[3] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[4] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[5] );
}

void jdksavdecc_print_eui64( FILE *f, struct jdksavdecc_eui64 v )
{
    jdksavdecc_print_hexdigits(f, v.value[0] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[1] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[2] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[3] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[4] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[5] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[6] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[7] );
}

void jdksavdecc_print_streamid( FILE *f, struct jdksavdecc_eui64 v )
{
    jdksavdecc_print_hexdigits(f, v.value[0] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[1] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[2] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[3] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[4] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[5] );
    jdksavdecc_print(f,"%s","-" );
    jdksavdecc_print_hexdigits(f, v.value[6] );
    jdksavdecc_print(f,"%s",":" );
    jdksavdecc_print_hexdigits(f, v.value[7] );
}

void jdksavdecc_print_block( FILE *f, const uint8_t *p, size_t sz, size_t start_pos, size_t end_pos )
{
    size_t pos;
    size_t step=32;
    size_t indent=42;

    for( pos=start_pos; pos<sz && pos<end_pos; pos+=step )
    {
        size_t i=0;

        for( i=0; i<indent; ++i )
        {
            jdksavdecc_printc(f,' ');
        }

        jdksavdecc_print_uint32(f,(uint32_t)pos);
        jdksavdecc_printc(f,':');

        for( i=pos; i<(pos+step) && (i<sz) && (i<end_pos); ++i )
        {
            jdksavdecc_printc(f,' ');
            jdksavdecc_print_hexdigits(f,p[i]);
        }
        jdksavdecc_print_eol(f);
    }
}

void jdksavdecc_print_string( FILE *f, struct jdksavdecc_string const *v )
{
    size_t i=0;
    size_t len=jdksavdecc_string_length( v );
    jdksavdecc_printc( f, '\"' );
    for( i=0; i<len; ++i )
    {
        int8_t c=(int8_t)v->value[i];
        switch( c )
        {
            case '\"':
                jdksavdecc_printc( f, '\\' );
                jdksavdecc_printc( f, '\"' );
                break;
            case '\t':
                jdksavdecc_printc( f, '\\' );
                jdksavdecc_printc( f, 't' );
                break;
            case '\r':
                jdksavdecc_printc( f, '\\' );
                jdksavdecc_printc( f, 'r' );
                break;
            case '\n':
                jdksavdecc_printc( f, '\\' );
                jdksavdecc_printc( f, 'n' );
                break;
            default:
                if( c<0x20 )
                {
                    jdksavdecc_printc( f, '\\' );
                    jdksavdecc_printc( f, 'x' );
                    jdksavdecc_print_hexdigits(f, (uint8_t)c);
                }
                else
                {
                    jdksavdecc_printc( f, c );
                }
        }
    }
    jdksavdecc_printc( f, '\"' );
}

void jdksavdecc_print_gptp_seconds( FILE *f, struct jdksavdecc_gptp_seconds p )
{
    uint64_t v = p.seconds;
    jdksavdecc_print( f, "0x%012" PRIx64, v );
}

char const * jdksavdecc_get_name_for_16bit_value( struct jdksavdecc_16bit_name const names[], uint16_t v )
{
    int i=0;

    while(names[i].name)
    {
        if( names[i].bit_value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}

uint16_t jdksavdecc_get_16bit_value_for_name( struct jdksavdecc_16bit_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return names[i].bit_value;
        }
        ++i;
    }
    return 0;
}



char const * jdksavdecc_get_name_for_32bit_value( struct jdksavdecc_32bit_name const names[], uint32_t v )
{
    int i=0;

    while(names[i].name)
    {
        if( names[i].bit_value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}


uint16_t jdksavdecc_get_32bit_value_for_name( struct jdksavdecc_32bit_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return names[i].bit_value;
        }
        ++i;
    }
    return 0;
}

uint16_t jdksavdecc_get_uint16_value_for_name( struct jdksavdecc_uint16_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return names[i].value;
        }
        ++i;
    }
    return 0;
}

char const * jdksavdecc_get_name_for_uint16_value( struct jdksavdecc_uint16_name const names[], uint16_t v )
{
    int i=0;

    while(names[i].name)
    {
        if( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}


uint32_t jdksavdecc_get_uint32_value_for_name( struct jdksavdecc_uint32_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return names[i].value;
        }
        ++i;
    }
    return 0;
}

char const * jdksavdecc_get_name_for_uint32_value( struct jdksavdecc_uint32_name const names[], uint32_t v )
{
    int i=0;

    while(names[i].name)
    {
        if( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}


uint64_t jdksavdecc_get_uint64_value_for_name( struct jdksavdecc_uint64_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return names[i].value;
        }
        ++i;
    }
    return 0;
}

char const * jdksavdecc_get_name_for_uint64_value( struct jdksavdecc_uint64_name const names[], uint64_t v )
{
    int i=0;

    while(names[i].name)
    {
        if( names[i].value == v )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}


struct jdksavdecc_eui48 const * jdksavdecc_get_eui48_value_for_name( struct jdksavdecc_eui48_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return &names[i].value;
        }
        ++i;
    }
    return 0;
}

char const * jdksavdecc_get_name_for_eui48_value( struct jdksavdecc_eui48_name const names[], struct jdksavdecc_eui48 v )
{
    int i=0;

    while(names[i].name)
    {
        int found=1;
        size_t j;
        for( j=0; j<sizeof( v.value ); ++j )
        {
            if( names[i].value.value[j] != v.value[j] )
            {
                found=0;
            }
        }

        if( found )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}


struct jdksavdecc_eui64 const * jdksavdecc_get_eui64_value_for_name( struct jdksavdecc_eui64_name const names[], char const *name )
{
    int i=0;

    while(names[i].name)
    {
        if( strcmp(name,names[i].name)==0 )
        {
            return &names[i].value;
        }
        ++i;
    }
    return 0;
}

char const * jdksavdecc_get_name_for_eui64_value( struct jdksavdecc_eui64_name const names[], struct jdksavdecc_eui64 v )
{
    int i=0;

    while(names[i].name)
    {
        int found=1;
        size_t j;
        for( j=0; j<sizeof( v.value ); ++j )
        {
            if( names[i].value.value[j] != v.value[j] )
            {
                found=0;
            }
        }

        if( found )
        {
            return names[i].name;
        }
        ++i;
    }
    return 0;
}




void jdksavdecc_print_16bit_names( FILE *f, struct jdksavdecc_16bit_name const names[], uint16_t v )
{
    size_t i=0;

    jdksavdecc_print( f, "%s", "[ " );
    while(names[i].name)
    {
        if( names[i].bit_value & v )
        {
            jdksavdecc_print( f, "%s", names[i].name );
            jdksavdecc_print( f, "%s", " " );
        }
        ++i;
    }
    jdksavdecc_print( f, "%s", "]" );
}

void jdksavdecc_print_32bit_names( FILE *f, struct jdksavdecc_32bit_name const names[], uint32_t v )
{
    size_t i=0;

    jdksavdecc_print( f, "%s", "[ " );
    while(names[i].name)
    {
        if( names[i].bit_value & v )
        {
            jdksavdecc_print( f, "%s", names[i].name );
            jdksavdecc_print( f, "%s", " " );
        }
        ++i;
    }
    jdksavdecc_print( f, "%s", "]" );
}

void jdksavdecc_print_uint16_name( FILE *f, struct jdksavdecc_uint16_name const names[], uint16_t v )
{
    char const *s = jdksavdecc_get_name_for_uint16_value( names, v );
    if( s )
    {
        jdksavdecc_print( f, "%s", s );
    }
    else
    {
        jdksavdecc_print_uint16( f, v );
    }
}

void jdksavdecc_print_uint32_name( FILE *f, struct jdksavdecc_uint32_name const names[], uint32_t v )
{
    char const *s = jdksavdecc_get_name_for_uint32_value( names, v );
    if( s )
    {
        jdksavdecc_print( f, "%s", s );
    }
    else
    {
        jdksavdecc_print_uint32( f, v );
    }
}

void jdksavdecc_print_uint64_name( FILE *f, struct jdksavdecc_uint64_name const names[], uint64_t v )
{
    char const *s = jdksavdecc_get_name_for_uint64_value( names, v );
    if( s )
    {
        jdksavdecc_print( f, "%s", s );
    }
    else
    {
        jdksavdecc_print_uint64( f, v );
    }
}

void jdksavdecc_print_eui48_name( FILE *f, struct jdksavdecc_eui48_name const names[], struct jdksavdecc_eui48 v )
{
    char const *s = jdksavdecc_get_name_for_eui48_value( names, v );
    if( s )
    {
        jdksavdecc_print( f, "%s", s );
    }
}


void jdksavdecc_print_eui64_name( FILE *f, struct jdksavdecc_eui64_name const names[], struct jdksavdecc_eui64 v )
{
    char const *s = jdksavdecc_get_name_for_eui64_value( names, v );
    if( s )
    {
        jdksavdecc_print( f, "%s", s );
    }
}


