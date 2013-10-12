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


/*@{*/



/** \addtogroup descriptor_storage_header Descriptor Storage Header
 *
 */

/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER { 0x41, 0x45, 0x4d, 0x31, 0x00, 0x00, 0x00, 0x00 }  /// file header: "AEM1\0\0\0\0"
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SIZE (0x8)

/**@}*/

/** \addtogroup descriptor_storage_toc Descriptor Storage Table of Contents
 *
 *  table of contents chunk:
 *
 *    offset   size    name
 *  0x0000   4       length  = 8 + (num_entity_models * 0xc) + length of all entity_data chunks
 *  0x0004   2       num_entity_models
 *  0x0006   2       reserved1
 *  0x0008   4       entity_data_offset[0]
 *  0x000c   8       entity_model_id[0]
 *  0x0014   4       entity_data_offset[1]
 *  0x0018   8       entity_model_id[1]
 *  ....etc...
 *
 *
 */

/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_TOC_LENGTH_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_TOC_NUM_ENTITY_MODELS_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_TOC_ITEM_OFFSET (0x0008)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_TOC_ITEM_SIZE (0x000c)

/**@}*/


/** \addtogroup descriptor_storage_entities entity_data chunk
 *  entity_data chunk:
 *
 *    offset   size    name
 *  0x0000   4       length  = 8 + (num_configurations * 0x4) + length of all configuration_data chunks
 *  0x0004   2       num_configurations
 *  0x0006   2       reserved1
 *  0x0008   4       configuration_data_offset[0]
 *  0x000c   4       configuration_data_offset[1]
 *  0x0010   4       configuration_data_offset[2]
 *  ..etc..
 *  content of all configuration_data chunks
 *  ....
 */

/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_ENTITY_DATA_LENGTH_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ENTITY_DATA_NUM_CONFIGURATIONS_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ENTITY_DATA_ITEM_OFFSET (0x0008)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ENTITY_DATA_ITEM_SIZE (0x0004)

/**@}*/


/** \addtogroup descriptor_storage_configurations configuration_data chunk
 *  configuration_data chunk:
 *
 *    offset   size    name
 *  0x0000   4       length  = 8 + (num_descriptor_list_types * 0x6) + length of all descriptor_list_data chunks
 *  0x0004   2       num_descriptor_list_types
 *  0x0006   2       reserved1
 *  0x0008   4       descriptor_list_data_offset[0]
 *  0x000c   2       descriptor_list_data_type[0]
 *  0x000e   4       descriptor_list_data_offset[1]
 *  0x0012   2       descriptor_list_data_type[1]
 *  ..etc..
 *  content of all descriptor_list_data chunks
 *  ....
 */

/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_DATA_LENGTH_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_DATA_NUM_CONFIGURATIONS_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_DATA_ITEM_OFFSET (0x0008)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_CONFIGURATION_DATA_ITEM_SIZE (0x0006)

/**@}*/


/** \addtogroup descriptor_storage_descriptors descriptor_list_data chunk
 *  descriptor_list_data chunk:
 *    offset   size    name
 *  0x0000   4       length  = 8 + (num_descriptors * 0x6) + length of all descriptor_data chunks
 *  0x0004   2       num_descriptors
 *  0x0006   2       reserved1
 *  0x0008   4       descriptor_data_offset[0]
 *  0x000c   2       descriptor_data_length[0]
 *  0x000e   4       descriptor_data_offset[1]
 *  0x0012   2       descriptor_data_length[1]
 *  ..etc..
 *  ...content of all descriptor data...
 */

/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_DESCRIPTOR_LIST_DATA_LENGTH_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_DESCRIPTOR_LIST_DATA_NUM_CONFIGURATIONS_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_DESCRIPTOR_LIST_DATA_ITEM_OFFSET (0x0008)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_DESCRIPTOR_LIST_DATA_ITEM_SIZE (0x0006)

/**@}*/

/// jdksavdecc_descriptor_storage holds the information about how to read the storage item
struct jdksavdecc_descriptor_storage
{
    /// Destroy the object
    void (*destroy)( struct jdksavdecc_descriptor_storage *self );

    /// Read some data at offset of length length into buffer. Return length of data read.
    uint32_t (*read_data)( struct jdksavdecc_descriptor_storage *self, void *buffer, uint32_t offset, uint32_t length );

    /// generic pointer for accessing data
    void const *user_ptr;

    /// data file length
    uint32_t storage_length;
};

/// Initialize descriptor_storage object with user_ptr and storage_length.
/// user_ptr's use is dependant on subclass definition
int jdksavdecc_descriptor_storage_init(
        struct jdksavdecc_descriptor_storage *self,
        void const *user_ptr,
        uint32_t storage_length
        );

/// Destroy descriptor_storage object
void jdksavdecc_descriptor_storage_destroy(
        struct jdksavdecc_descriptor_storage *self
        );

/// Initialize a descriptor_storage buffer object with a pointer to actual read-only data
int jdksavdecc_descriptor_storage_buffer_init(
        struct jdksavdecc_descriptor_storage *self,
        void const *user_ptr,
        uint32_t storage_length
        );

/// Read data from a locally accessible read only data buffer
uint32_t jdksavdecc_descriptor_storage_buffer_read_data(
        struct jdksavdecc_descriptor_storage *self,
        void *buffer,
        uint32_t offset,
        uint32_t length
        );

/// Destroy a descriptor_storate buffer object
void jdksavdecc_descriptor_storage_buffer_destroy(
        struct jdksavdecc_descriptor_storage *self
        );

#ifdef FOPEN_MAX

/// Initialize a descriptor_storage file object with a specified read-only file via the file_name
int jdksavdecc_descriptor_storage_file_init(
        struct jdksavdecc_descriptor_storage *self,
        const char *file_name
        );

/// Read data from a descriptor_storage file object
uint32_t jdksavdecc_descriptor_storage_file_read_data(
        struct jdksavdecc_descriptor_storage *self,
        void *buffer,
        uint32_t offset,
        uint32_t length
        );

/// Close the file and destroy the descriptor_storage file object
void jdksavdecc_descriptor_storage_file_destroy(
        struct jdksavdecc_descriptor_storage *self
        );

#endif



/// Read the count of entity models in the storage object
uint16_t jdksavdecc_descriptor_storage_get_entity_model_count(
        struct jdksavdecc_descriptor_storage *self
        );

/// Read the model_id for a entity model in the storage object
struct jdksavdecc_eui64 jdksavdecc_descriptor_storage_get_entity_model_id(
        struct jdksavdecc_descriptor_storage *self,
        uint16_t entity_number
        );

/// Read the count of configurations for the specified entity number in the storage object
uint16_t jdksavdecc_descriptor_storage_get_configuration_count(
        uint16_t entity_number
        );

/// Read the count of descriptor lists used in the specified entity_number and configuration number
uint16_t jdksavdecc_descriptor_storage_get_configuration_descriptor_list_count(
        uint16_t entity_number,
        uint16_t configuration_number
        );

/// Read the descriptor_type and descriptor count for one entry in the descriptor list in a configuration of an entity
/// Returns the descriptor count, or 0 if there are none.
/// Fills in *result_descriptor_type with the descriptor type
uint16_t jdksavdecc_descriptor_storage_get_descriptor_types_count_and_type(
        struct jdksavdecc_descriptor_storage *self,
        uint16_t configuration_number,
        uint16_t descriptor_type_number,
        uint16_t *result_descriptor_type
        );


/// Read a descriptor for the specified entity, configuration, descriptor_type and descriptor_index into result buffer which has a length of result_buffer_len.
/// Returns the length of the descriptor, or 0 if no descriptor.
uint16_t jdksavdecc_descriptor_storage_read_descriptor(
        struct jdksavdecc_descriptor_storage *self,
        uint16_t entity_number,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint16_t *result_buffer,
        uint16_t result_buffer_len
        );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif

