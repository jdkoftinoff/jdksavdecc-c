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
#include "jdksavdecc_descriptor_storage.h"
#include "jdksavdecc_entity_model.h"

#ifdef TODO

bool
jdksavdecc_descriptor_storage_init(struct jdksavdecc_descriptor_storage *self, void const *user_ptr, uint32_t storage_length) {
    jdksavdecc_entity_model_init(&self->base);
    self->base.destroy = jdksavdecc_descriptor_storage_destroy;
    self->read_data = 0;
    self->user_ptr = user_ptr;
    self->storage_length = storage_length;
    self->base.get_configuration_count = 0;
    self->base.read_descriptor = 0;
    self->read_symbol = 0;
    return true;
}

void jdksavdecc_descriptor_storage_destroy(struct jdksavdecc_entity_model *self)
{
    jdksavdecc_entity_model_destroy(self);
}

bool jdksavdecc_descriptor_storage_buffer_init(struct jdksavdecc_descriptor_storage *self,
                                              void const *user_ptr,
                                              uint32_t storage_length) {
    bool r=false;
    jdksavdecc_descriptor_storage_init( self, user_ptr, storage_length );

    self->base.destroy = jdksavdecc_descriptor_storage_buffer_destroy;
    self->read_data = jdksavdecc_descriptor_storage_buffer_read_data;
    self->base.get_configuration_count =
        jdksavdecc_descriptor_storage_buffer_get_configuration_count;
    self->base.read_descriptor =
        jdksavdecc_descriptor_storage_buffer_read_descriptor;
    self->read_symbol =
        jdksavdecc_descriptor_storage_buffer_read_symbol;

    if( jdksavdecc_descriptor_storage_buffer_read_header(self) ) {
        if( self->header.magic == JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_VALUE ) {
            r = true;
        }
    }

    return r;
}

uint32_t jdksavdecc_descriptor_storage_buffer_read_data(struct jdksavdecc_descriptor_storage *self,
                                                        void *buffer,
                                                        uint32_t offset,
                                                        uint32_t length) {
    uint32_t r = 0;
    if (self->storage_length >= offset + length) {
        r = length;
        memcpy(buffer, (uint8_t *)(self->user_ptr) + offset, length);
    }
    return r;
}

void jdksavdecc_descriptor_storage_buffer_destroy(struct jdksavdecc_entity_model *self) {
    jdksavdecc_descriptor_storage_destroy(self);
}



bool jdksavdecc_descriptor_storage_buffer_read_header(struct jdksavdecc_descriptor_storage *self) {
    bool r=false;
    uint8_t buf[JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH];
    uint32_t l = self->read_data( self, buf, 0, sizeof(buf) );
    if( l==JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH ) {
        ssize_t pos = jdksavdecc_descriptor_storage_header_read(&self->header, self->user_ptr, 0, self->storage_length );
        if( pos==l ) {
            r=true;
        }
    }
    return r;
}

uint16_t jdksavdecc_descriptor_storage_buffer_get_configuration_count(struct jdksavdecc_entity_model *self_) {
    uint16_t r=0;
    struct jdksavdecc_descriptor_storage *self = (struct jdksavdecc_descriptor_storage *)self_;
    uint32_t num_items = self->header.toc_count;

    if( num_items>0 ) {
        // Find the offset for the last item
        uint32_t item=num_items-1;
        uint32_t offset = self->header.toc_offset
                          + sizeof( struct jdksavdecc_descriptor_storage_item ) * item;
        if( offset+JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CONFIGURATION_INDEX_OFFSET <= self->storage_length ) {
            // Read the configuration number from this last item
            r = jdksavdecc_uint16_get(self->user_ptr, offset + JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_CONFIGURATION_INDEX_OFFSET);
            // the count of configurations is one larger than the last configuration number
            r=r+1;
        }
    }

    return r;
}

static int jdksavdecc_descriptor_storage_buffer_compare_item(
    const void *lhs_,
    const void *rhs_) {
    int r=0;
    struct jdksavdecc_descriptor_storage_item lhs;
    struct jdksavdecc_descriptor_storage_item rhs;
    uint64_t lhsv;
    uint64_t rhsv;

    jdksavdecc_descriptor_storage_item_read(&lhs, lhs_, 0, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
    jdksavdecc_descriptor_storage_item_read(&rhs, rhs_, 0, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);

    // items are expected to be ordered by configuration, then descriptor type, then descriptor index
    lhsv =  (((uint64_t)lhs.configuration_index) << 32)
            + (((uint64_t)lhs.descriptor_type) << 16)
            + (lhs.descriptor_index);

    rhsv =  (((uint64_t)rhs.configuration_index) << 32)
            + (((uint64_t)rhs.descriptor_type) << 16)
            + (rhs.descriptor_index);

    if( lhsv < rhsv ) {
        r=-1;
    } else if( lhsv>rhsv ) {
        r=1;
    }
    return r;
}

uint16_t jdksavdecc_descriptor_storage_buffer_read_descriptor(
        struct jdksavdecc_entity_model *self_,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint8_t *result_buffer,
        uint16_t result_buffer_len) {
    uint16_t r=0;
    struct jdksavdecc_descriptor_storage *self = (struct jdksavdecc_descriptor_storage *)self_;
    void *p;
    void *descriptor_items;
    struct jdksavdecc_descriptor_storage_item key;

    descriptor_items = ((uint8_t *)self->user_ptr) + self->header.toc_offset;
    key.configuration_index = configuration_number;
    key.descriptor_type = descriptor_type;
    key.descriptor_index = descriptor_index;
    key.length = 0;
    key.offset = 0;

    p=bsearch(&key, descriptor_items, self->header.toc_count, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH, jdksavdecc_descriptor_storage_buffer_compare_item);

    if( p ) {
        // found the match, now get the item offset and length and give it to the caller
        jdksavdecc_descriptor_storage_item_read(&key,p,0,JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
        if( key.length <= result_buffer_len ) {
            r=key.length;
            memcpy(result_buffer,((uint8_t *)self->user_ptr) + key.offset, key.length );
        }
    }
    return r;
}

static int jdksavdecc_descriptor_storage_buffer_compare_symbol(
        const void *lhs_,
        const void *rhs_) {
    int r=0;
    struct jdksavdecc_descriptor_storage_symbol lhs;
    struct jdksavdecc_descriptor_storage_symbol rhs;
    uint64_t lhsv;
    uint64_t rhsv;

    jdksavdecc_descriptor_storage_symbol_read(&lhs, lhs_, 0, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
    jdksavdecc_descriptor_storage_symbol_read(&rhs, rhs_, 0, JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);

    // items are expected to be ordered by configuration, then descriptor type, then descriptor index
    lhsv =  (((uint64_t)lhs.configuration_index) << 32)
            + (((uint64_t)lhs.descriptor_type) << 16)
            + (lhs.descriptor_index);

    rhsv =  (((uint64_t)rhs.configuration_index) << 32)
            + (((uint64_t)rhs.descriptor_type) << 16)
            + (rhs.descriptor_index);

    if( lhsv < rhsv ) {
        r=-1;
    } else if( lhsv>rhsv ) {
        r=1;
    }
    return r;
}


bool jdksavdecc_descriptor_storage_buffer_read_symbol(
        struct jdksavdecc_descriptor_storage *self,
        uint16_t configuration_number,
        uint16_t descriptor_type,
        uint16_t descriptor_index,
        uint32_t *result_symbol) {
    bool r=false;
    void *p;
    void *descriptor_items;
    struct jdksavdecc_descriptor_storage_symbol key;

    descriptor_items = ((uint8_t *)self->user_ptr) + self->header.toc_offset;
    key.configuration_index = configuration_number;
    key.descriptor_type = descriptor_type;
    key.descriptor_index = descriptor_index;
    key.symbol = 0;

    p=bsearch(&key, descriptor_items, self->header.toc_count, JDKSAVDECC_DESCRIPTOR_STORAGE_SYMBOL_LENGTH, jdksavdecc_descriptor_storage_buffer_compare_symbol);

    if( p ) {
        // found the match, now get the item offset and length and give it to the caller
        jdksavdecc_descriptor_storage_symbol_read(&key,p,0,JDKSAVDECC_DESCRIPTOR_STORAGE_ITEM_LENGTH);
        *result_symbol = key.symbol;
        r=true;
    }
    return r;
}



#ifdef FOPEN_MAX

bool jdksavdecc_descriptor_storage_file_init(struct jdksavdecc_descriptor_storage *self, const char *file_name) {
    bool r = false;
#if defined(WIN32)
    FILE *f;
    fopen_s(&f,file_name,"rb");
#else
    FILE *f = fopen(file_name, "rb");
#endif
    self->base.destroy = jdksavdecc_descriptor_storage_file_destroy;
    self->read_data = jdksavdecc_descriptor_storage_file_read_data;
    if (f) {
        self->user_ptr = (void *)f;
        if (fseek(f, 0, SEEK_END) == 0) {
            long pos = ftell(f);
            if (pos >= 0) {
                self->storage_length = (uint32_t)pos;
                if( jdksavdecc_descriptor_storage_file_read_header(self) ) {
                    if( self->header.magic == JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_MAGIC_VALUE ) {
                        r = true;
                    }
                }
            }
        }
        if( f && !r ) {
            fclose(f);
        }
    }
    return r;
}

uint32_t jdksavdecc_descriptor_storage_file_read_data(struct jdksavdecc_descriptor_storage *self,
                                                      void *buffer,
                                                      uint32_t offset,
                                                      uint32_t length) {
    uint32_t r = 0;
    if (self->user_ptr) {
        FILE *f = (FILE *)self->user_ptr;

        if (self->storage_length >= offset + length) {
            if (fseek(f, SEEK_SET, (int)offset) == 0) {
                if (fread(buffer, 1, length, f) == length) {
                    r = length;
                }
            }
        }
    }
    return r;
}

void jdksavdecc_descriptor_storage_file_destroy(struct jdksavdecc_entity_model *self_) {
    struct jdksavdecc_descriptor_storage *self = (struct jdksavdecc_descriptor_storage *)self_;

    if (self->user_ptr) {
        FILE *f = (FILE *)self->user_ptr;
        if( f ) {
            fclose(f);
            self->user_ptr = 0;
        }
    }
}

bool jdksavdecc_descriptor_storage_file_read_header(struct jdksavdecc_descriptor_storage *self) {
    bool r=false;
    uint8_t buf[JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH];
    uint32_t l = self->read_data( self, buf, 0, sizeof(buf) );
    if( l==JDKSAVDECC_DESCRIPTOR_STORAGE_HEADER_LENGTH ) {
        ssize_t pos = jdksavdecc_descriptor_storage_header_read(&self->header, buf, 0, l );
        if( pos==l ) {
            r=true;
        }
    }
    return r;
}

#endif

int jdksavdecc_descriptor_storage_symbol_dispatch_item_compare(
        const void *lhs_,
        const void *rhs_ ) {
    int r=0;
    struct jdksavdecc_descriptor_storage_symbol_dispatch_item const *lhs;
    struct jdksavdecc_descriptor_storage_symbol_dispatch_item const *rhs;
    uint64_t lhsv;
    uint64_t rhsv;

    lhs = (struct jdksavdecc_descriptor_storage_symbol_dispatch_item const *)lhs_;
    rhs = (struct jdksavdecc_descriptor_storage_symbol_dispatch_item const *)rhs_;

    lhsv = (((uint64_t)lhs->symbol)<<32)
            + (((uint32_t)lhs->aecp_message_type)<<16)
            + lhs->aem_command_type;

    rhsv = (((uint64_t)rhs->symbol)<<32)
            + (((uint32_t)rhs->aecp_message_type)<<16)
            + rhs->aem_command_type;

    if( lhsv < rhsv ) {
        r=-1;
    } else if( lhsv > rhsv ) {
        r=1;
    }
    return r;
}

bool jdksavdecc_descriptor_storage_symbols_add(
        struct jdksavdecc_descriptor_storage_symbols *self,
        bool sort,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type,
        jdksavdecc_descriptor_storage_symbol_dispatch_proc handler ) {
    bool r=false;
    if( self->num_items < self->max_items ) {
        struct jdksavdecc_descriptor_storage_symbol_dispatch_item *item;
        // append the new symbol at the end
        item=&self->dispatch_items[self->num_items];
        item->symbol = symbol;
        item->aecp_message_type = aecp_message_type;
        item->aem_command_type = aem_command_type;
        item->handler = handler;
        self->num_items++;
        // then qsort it into position
        if( sort ) {
            qsort(self->dispatch_items, self->num_items, sizeof(*item), jdksavdecc_descriptor_storage_symbol_dispatch_item_compare );
        }
    }
    return r;
}

jdksavdecc_descriptor_storage_symbol_dispatch_proc jdksavdecc_descriptor_storage_symbols_find(
        struct jdksavdecc_descriptor_storage_symbols *self,
        uint32_t symbol,
        uint16_t aecp_message_type,
        uint16_t aem_command_type ) {
    jdksavdecc_descriptor_storage_symbol_dispatch_proc r=0;
    struct jdksavdecc_descriptor_storage_symbol_dispatch_item key;
    void *p;

    key.symbol = symbol;
    key.aecp_message_type = aecp_message_type;
    key.aem_command_type = aem_command_type;

    p = bsearch(&key, self->dispatch_items, self->num_items, sizeof(key), jdksavdecc_descriptor_storage_symbol_dispatch_item_compare );

    if( p ) {
        struct jdksavdecc_descriptor_storage_symbol_dispatch_item *result;
        result = (struct jdksavdecc_descriptor_storage_symbol_dispatch_item *)p;
        r=result->handler;
    }

    return r;
}



#else
const char *jdksavdecc_descriptor_storage_file = __FILE__;

#endif

