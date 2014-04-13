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
#include "jdksavdecc_aem_descriptor.h"
#include "jdksavdecc_entity_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup descriptor_storage Descriptor Storage */
/**@{*/

/** \addtogroup descriptor_storage_header Descriptor Storage Header
 *
 *  | offset | size  | symbol           | Description                                  |
 *  | ------ | ----- | ---------------- | -------------------------------------------- |
 *  | 0x0000 |   4   |   magic          | Magic number "AEM1" (0x41 0x45 0x4d 0x31)    |
 *  | 0x0004 |   4   |   toc_count      | Count of descriptors                         |
 *  | 0x0008 |   4   |   toc_offset     | Offset of descriptors table of contents      |
 *  | 0x000c |   4   |   symbol_count   | Count of symbols                             |
 *  | 0x0010 |   4   |   symbol_offset  | Offset of symbol table                       |
 *
 */

/**@{*/

/// "AEM1", as a network byte order uint32_t: 0x41454d31
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_VALUE (0x41454d31)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH (0x0014)

#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_COUNT_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_OFFSET_OFFSET (0x0008)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_COUNT_OFFSET (0x000c)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_OFFSET_OFFSET (0x0010)

struct jdksavdecc_descriptor_storage_header {
    uint32_t magic;
    uint32_t toc_count;
    uint32_t toc_offset;
    uint32_t symbol_count;
    uint32_t symbol_offset;
};

/**
 * Read the descriptor_storage_header from raw memory
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to jdksavdecc_descriptor_storage_header structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_header_read(struct jdksavdecc_descriptor_storage_header *p,
                                                                void const *base,
                                                                ssize_t pos,
                                                                size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH);
    if (r >= 0) {
        p->magic = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_OFFSET);
        p->toc_count = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_COUNT_OFFSET);
        p->toc_offset = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_OFFSET_OFFSET);
        p->symbol_count = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_COUNT_OFFSET);
        p->symbol_offset = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_OFFSET_OFFSET);
    }
    return r;
}

/**
 * Store the descriptor_storage_header structure to a memory.
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to jdksavdecc_descriptor_storage_header structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_header_write(struct jdksavdecc_descriptor_storage_header const *p,
                                                                 void *base,
                                                                 ssize_t pos,
                                                                 size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH);
    if (r >= 0) {
        jdksavdecc_uint32_set(p->magic, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_OFFSET);
        jdksavdecc_uint32_set(p->toc_count, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_COUNT_OFFSET);
        jdksavdecc_uint32_set(p->toc_offset, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_TOC_OFFSET_OFFSET);
        jdksavdecc_uint32_set(p->symbol_count, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_COUNT_OFFSET);
        jdksavdecc_uint32_set(p->symbol_offset, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_SYMBOL_OFFSET_OFFSET);
    }
    return r;
}

/**@}*/

/** \addtogroup descriptor_storage_item Descriptor item
 *
 *  | offset |  size |     name             |       Description                            |
 *  | ------ | ----- | -------------------- | -------------------------------------------- |
 *  | 0x0000 |    2  |  descriptor_type     |  Descriptor type                             |
 *  | 0x0002 |    2  |  descriptor_index    |  Descriptor index                            |
 *  | 0x0004 |    2  |  configuration_index |  Configuration index                         |
 *  | 0x0006 |    2  |  length              |  Length of descriptor                        |
 *  | 0x0008 |    4  |  offset              |  Offset of descriptor from start of file     |
 *
 */
/**@{*/

#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH (0x000c)

#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_TYPE_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_INDEX_OFFSET (0x0002)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CONFIGURATION_INDEX_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH_OFFSET (0x0006)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_OFFSET_OFFSET (0x0008)

struct jdksavdecc_descriptor_storage_item {
    uint16_t descriptor_type;
    uint16_t descriptor_index;
    uint16_t configuration_index;
    uint16_t length;
    uint32_t offset;
};

/**
 * Read the jdksavdecc_descriptor_storage_item from raw memory
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to jdksavdecc_descriptor_storage_item structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_item_read(struct jdksavdecc_descriptor_storage_item *p,
                                                              void const *base,
                                                              ssize_t pos,
                                                              size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
    if (r >= 0) {
        p->descriptor_type = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_TYPE_OFFSET);
        p->descriptor_index = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_INDEX_OFFSET);
        p->configuration_index
            = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CONFIGURATION_INDEX_OFFSET);
        p->length = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH_OFFSET);
        p->offset = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_OFFSET_OFFSET);
    }
    return r;
}

/**
 * Store the jdksavdecc_descriptor_storage_item structure to a memory.
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to jdksavdecc_descriptor_storage_item structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_item_write(struct jdksavdecc_descriptor_storage_item const *p,
                                                               void *base,
                                                               ssize_t pos,
                                                               size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
    if (r >= 0) {
        jdksavdecc_uint16_set(p->descriptor_type, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_TYPE_OFFSET);
        jdksavdecc_uint16_set(p->descriptor_index, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_DESCRIPTOR_INDEX_OFFSET);
        jdksavdecc_uint16_set(
            p->configuration_index, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CONFIGURATION_INDEX_OFFSET);
        jdksavdecc_uint16_set(p->length, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH_OFFSET);
        jdksavdecc_uint32_set(p->offset, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_OFFSET_OFFSET);
    }
    return r;
}

/**@}*/

/** \addtogroup descriptor_storage_symbol Symbol
 *
 *  | offset  | size   |    name               |    Descriptrion          |
 *  | ------- | ------ | --------------------- | ------------------------ |
 *  | 0x0000  |  2     |   descriptor_type     |  Descriptor type         |
 *  | 0x0002  |  2     |   descriptor_index    |  Descriptor index        |
 *  | 0x0004  |  2     |   configuration_index |  Configuration index     |
 *  | 0x0006  |  4     |   symbol              |  Symbol code             |
 *
 */
/**@{*/
#define JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_LENGTH (0x000a)

#define JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_TYPE_OFFSET (0x0000)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_INDEX_OFFSET (0x0002)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_CONFIGURATION_INDEX_OFFSET (0x0004)
#define JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_SYMBOL_OFFSET (0x0006)

struct jdksavdecc_descriptor_storage_symbol {
    uint16_t descriptor_type;
    uint16_t descriptor_index;
    uint16_t configuration_index;
    uint32_t symbol;
};

/**
 * Read the jdksavdecc_descriptor_storage_symbol from raw memory
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p pointer to jdksavdecc_descriptor_storage_symbol structure to fill in.
 * @param base pointer to raw memory buffer to read from.
 * @param pos offset from base to read the field from;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_symbol_read(struct jdksavdecc_descriptor_storage_symbol *p,
                                                                void const *base,
                                                                ssize_t pos,
                                                                size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_LENGTH);
    if (r >= 0) {
        p->descriptor_type = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_TYPE_OFFSET);
        p->descriptor_index = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_INDEX_OFFSET);
        p->configuration_index
            = jdksavdecc_uint16_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_CONFIGURATION_INDEX_OFFSET);
        p->symbol = jdksavdecc_uint32_get(base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_SYMBOL_OFFSET);
    }
    return r;
}

/**
 * Store the jdksavdecc_descriptor_storage_symbol structure to a memory.
 *
 * Bounds checking of the buffer size is done.
 *
 * @param p const pointer to jdksavdecc_descriptor_storage_symbol structure to read from.
 * @param base pointer to raw memory buffer to write to.
 * @param pos offset from base to write the field to;
 * @param len length of the raw memory buffer;
 * @return -1 if the buffer length is insufficent, otherwise the offset of the
 *octet following the structure in the buffer.
 */
static inline ssize_t jdksavdecc_descriptor_storage_symbol_write(struct jdksavdecc_descriptor_storage_symbol const *p,
                                                                 void *base,
                                                                 ssize_t pos,
                                                                 size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos, len, JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_LENGTH);
    if (r >= 0) {
        jdksavdecc_uint16_set(p->descriptor_type, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_TYPE_OFFSET);
        jdksavdecc_uint16_set(p->descriptor_index, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_DESCRIPTOR_INDEX_OFFSET);
        jdksavdecc_uint16_set(
            p->configuration_index, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_CONFIGURATION_INDEX_OFFSET);
        jdksavdecc_uint32_set(p->symbol, base, pos + JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_SYMBOL_OFFSET);
    }
    return r;
}

/**@}*/

/** \addtogroup jdksavdecc_descriptor_storage */
/**@{*/

/// jdksavdecc_descriptor_storage holds the information about how to read the
/// storage item
struct jdksavdecc_descriptor_storage {
    struct jdksavdecc_entity_model base;

    /// Read some data at offset of length length into buffer. Return length of
    /// data read.
    uint32_t (*read_data)(struct jdksavdecc_descriptor_storage *self, void *buffer, uint32_t offset, uint32_t length);

    /// Host ordered cache of header
    struct jdksavdecc_descriptor_storage_header header;

    /// generic pointer for accessing data
    void const *user_ptr;

    /// data file length
    uint32_t storage_length;

};

/// Initialize descriptor_storage object with user_ptr and storage_length.
/// user_ptr's use is dependant on subclass definition
bool jdksavdecc_descriptor_storage_init(
                struct jdksavdecc_descriptor_storage *self,
                void const *user_ptr,
                uint32_t storage_length);

/// Destroy descriptor_storage object
void jdksavdecc_descriptor_storage_destroy(struct jdksavdecc_entity_model *self);

/// Initialize a descriptor_storage buffer object with a pointer to actual
/// read-only data
bool jdksavdecc_descriptor_storage_buffer_init(
                struct jdksavdecc_descriptor_storage *self,
                void const *user_ptr,
                uint32_t storage_length);

/// Read data from a locally accessible read only data buffer
uint32_t jdksavdecc_descriptor_storage_buffer_read_data(
                struct jdksavdecc_descriptor_storage *self,
                void *buffer,
                uint32_t offset,
                uint32_t length);

/// Destroy a descriptor_storate buffer object
void jdksavdecc_descriptor_storage_buffer_destroy(struct jdksavdecc_entity_model *self);

#ifdef FOPEN_MAX

/// Initialize a descriptor_storage file object with a specified read-only file
/// via the file_name
bool jdksavdecc_descriptor_storage_file_init(struct jdksavdecc_descriptor_storage *self, const char *file_name);

/// Read data from a descriptor_storage file object
uint32_t jdksavdecc_descriptor_storage_file_read_data(
                struct jdksavdecc_descriptor_storage *self,
                void *buffer,
                uint32_t offset,
                uint32_t length);

/// Close the file and destroy the descriptor_storage file object
void jdksavdecc_descriptor_storage_file_destroy(struct jdksavdecc_entity_model *self);

#endif

/// Read the file header. Returns true on success and false if the header is not
/// recognized or unable to read.
bool jdksavdecc_descriptor_storage_file_read_header(struct jdksavdecc_descriptor_storage *self);

/// Read the header from the buffer. Returns true on success and false if the header is not
/// recognized or unable to read.
bool jdksavdecc_descriptor_storage_buffer_read_header(struct jdksavdecc_descriptor_storage *self);

/// Read the count of configurations in the storage object
uint16_t jdksavdecc_descriptor_storage_buffer_get_configuration_count(struct jdksavdecc_entity_model *self);


/// Read a descriptor for the specified configuration, descriptor_type and
/// descriptor_index into result buffer which has a length of
/// result_buffer_len.
/// Returns the length of the descriptor, or 0 if no descriptor.
uint16_t jdksavdecc_descriptor_storage_buffer_read_descriptor(
        struct jdksavdecc_entity_model *self,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t *result_buffer,
        uint16_t result_buffer_len);

/// Read a symbol for the specified configuration, descriptor_type and
/// descriptor_index. Returns true on success
bool jdksavdecc_descriptor_storage_buffer_read_symbol(
        struct jdksavdecc_entity_model *self,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint32_t *result_symbol);

/*@}*/

/** \addtogroup jdksavdecc_descriptor_storage_symbol_dispatch */
/*@{*/


/**
 jdksavdecc_descriptor_storage_symbol_dispatch_proc is a pointer to a function that
 is expected to handle an incoming message for a specific symbol.

 It is given the configuration number, the descriptor type and index,
 and the incoming frame.

 It is expected to return an AEM Status code ( See IEEE Std 1722.1 Clause 7.126 )
*/
typedef uint16_t (*jdksavdecc_descriptor_storage_symbol_dispatch_proc)(
        void *context,
        struct jdksavdecc_descriptor_storage *storage,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t *aecpdu,
        ssize_t pos,
        ssize_t len );


struct jdksavdecc_descriptor_storage_symbol_dispatch_item {
    /// The opaque symbol that this item is for
    uint32_t symbol;

    /// See IEEE Std 1722.1-2013 Clause 9.2.1.1.5
    uint16_t aecp_message_type;

    /// aem_command_type includes the 'u' bit to allow for differentiation between
    /// solicited responses and unsolicited responses
    /// See IEEE Std 1722.1-2013 Clause 9.2.1
    uint16_t aem_command_type;

    /// The function that handles messages of these types for this symbol
    jdksavdecc_descriptor_storage_symbol_dispatch_proc handler;
};


struct jdksavdecc_descriptor_storage_symbols {
    struct jdksavdecc_descriptor_storage_symbol_dispatch_item *dispatch_items;
    int max_items;
    int num_items;
};

static inline bool jdksavdecc_descriptor_storage_symbols_init(
        struct jdksavdecc_descriptor_storage_symbols *self,
        struct jdksavdecc_descriptor_storage_symbol_dispatch_item *items,
        int max_items,
        int num_items ) {
    self->dispatch_items = items;
    self->max_items = max_items;
    self->num_items = num_items;
    return true;
}


bool jdksavdecc_descriptor_storage_symbols_add(
        struct jdksavdecc_descriptor_storage_symbols *self,
        bool sort,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type,
        jdksavdecc_descriptor_storage_symbol_dispatch_proc handler );

jdksavdecc_descriptor_storage_symbol_dispatch_proc jdksavdecc_descriptor_storage_find_symbol(
        struct jdksavdecc_descriptor_storage_symbols *self,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type );

/*@}*/

/*@}*/
#ifdef __cplusplus
}
#endif
