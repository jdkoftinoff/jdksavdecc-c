#pragma once
#ifndef JDKSAVDECC_DESCRIPTOR_STORAGE_H
#define JDKSAVDECC_DESCRIPTOR_STORAGE_H

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
#include "jdksavdecc_descriptor_dispatch.h"

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup descriptor_storage Descriptor Storage
 *  @todo descriptor_storage
*/
/*@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_TYPE (0) /** All storage objects have a chunk_type code at offset 0 */
#define JDKSAVDECC_DESCRIPTOR_STORAGE_LEN_CHUNK_TYPE (4) /** The chunk_type code is a uint32_t */


/**
 * Extract the uint32 value of the chunk_type field of the descriptor_storage_item object
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint32_t chunk_type value
 */
static inline uint32_t jdksavdecc_descriptor_storage_get_chunk_type( void const *base, ssize_t pos )
{
    return jdksavdecc_uint32_get( base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_TYPE);
}


/**
 * Store a uint32 value to thethe chunk_type field of the descriptor_storage object
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The uint32_t chunk_type value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_descriptor_storage_set_chunk_type( uint32_t v, void *base, ssize_t pos )
{
    jdksavdecc_uint32_set( v, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_TYPE);
}


#define JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_SIZE (4) /** All storage objects have a chunk_size field at offset 4 */
#define JDKSAVDECC_DESCRIPTOR_STORAGE_LEN_CHUNK_SIZE (4) /** the chunk_size field is a uint32_t */

#define JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CONTENT (8) /** All storage objects's content starts at offset 8 */

/**
 * Extract the uint32 value of the block_size field of the descriptor_storage_item object
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @return the uint32_t chunk_size value
 */
static inline uint32_t jdksavdecc_descriptor_storage_get_chunk_size( void const *base, ssize_t pos )
{
    return jdksavdecc_uint32_get( base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_SIZE);
}


/**
 * Store a uint32 value to thethe chunk_size field of the descriptor_storage_item object
 *
 *
 * No bounds checking of the memory buffer is done. It is the caller's responsibility to pre-validate base and pos.
 *
 * @param v The uint32_t chunk_size value.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 */
static inline void jdksavdecc_descriptor_storage_set_chunk_size( uint32_t v, void *base, ssize_t pos )
{
    jdksavdecc_uint32_set( v, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_OFFSET_CHUNK_SIZE);
}



#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_OFFSET_DATA (8)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LEN_DATA (JDKSAVDECC_AEM_DESCRIPTOR_SIZE)

#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CHUNK_TYPE (0x64736370UL) /* 'dscp' */

#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_OFFSET_BLOCK_SIZE (0)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_LEN_BLOCK_SIZE (4)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_OFFSET_DESCRIPTOR_TYPE (4)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_LEN_DESCRIPTOR_TYPE (2)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_OFFSET_DESCRIPTOR_COUNT (6)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_LEN_DESCRIPTOR_COUNT (2)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_OFFSET_ITEMS (8)


#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LIST_CHUNK_TYPE (0x6463706cUL) /* 'dcpl' */

#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_OFFSET_BLOCK_SIZE (0)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_LEN_BLOCK_SIZE (4)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_OFFSET_ITEM_LIST_COUNT (4)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_LEN_ITEM_LIST_COUNT (2)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_OFFSET_ITEM_LIST_RESERVED (6)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_LEN_ITEM_LIST_RESERVED (2)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_OFFSET_ITEM_LIST_ITEMS (8)

#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_CHUNK_TYPE (0x636e6667) /* 'cnfg' */

#define JDKSAVDECC_DESCRIPTOR_STORAGE_CHUNK_TYPE (0x73746f72UL) /* 'stor' */

#ifndef JDKSAVDECC_CONFIGURATION_STORAGE_MAX_CONFIGURATIONS
# define JDKSAVDECC_CONFIGURATION_STORAGE_MAX_CONFIGURATIONS (16)
#endif

struct jdksavdecc_descriptor_storage
{
    void (*destroy)( struct jdksavdecc_descriptor_storage *self );

    uint8_t const *data;
    uint16_t configuration_count;
    uint8_t const *configuration_data[JDKSAVDECC_CONFIGURATION_STORAGE_MAX_CONFIGURATIONS];
};

int jdksavdecc_descriptor_storage_init(
        struct jdksavdecc_descriptor_storage *self,
        void const *data
        );

void jdksavdecc_descriptor_storage_destroy(
        struct jdksavdecc_descriptor_storage *self
        );

struct jdksavdecc_descriptor const *jdksavdecc_descriptor_storage_read(
        struct jdksavdecc_descriptor_storage *self,
        uint16_t config,
        uint16_t descriptor_type,
        uint16_t descriptor_index
        );


/*@}*/

#ifdef __cplusplus
}
#endif

#endif

