
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
#include "jdksavdecc_frame_list.h"

int jdksavdecc_frame_list_init(struct jdksavdecc_frame_list *self,
                               struct jdksavdecc_allocator *allocator) {
    self->allocator = allocator;
    self->first = 0;
    self->last = 0;
    return 0;
}

void jdksavdecc_frame_list_destroy(struct jdksavdecc_frame_list *self) {
    struct jdksavdecc_frame_list_item *item = self->last;

    while (item) {
        struct jdksavdecc_frame_list_item *cur = item;

        if (cur->context) {
            jdksavdecc_delete(self->allocator, cur->context);
            cur->context = 0;
        }

        item = cur->prev;
        jdksavdecc_delete(self->allocator, cur);
    }
}

struct jdksavdecc_frame_list_item *
jdksavdecc_frame_list_add(struct jdksavdecc_frame_list *self,
                          struct jdksavdecc_frame const *frame, void *context) {
    struct jdksavdecc_frame_list_item *new_item =
        jdksavdecc_new(self->allocator, struct jdksavdecc_frame_list_item);

    if (new_item) {
        new_item->prev = self->last;
        new_item->next = 0;
        memcpy(&new_item->frame, frame, sizeof(new_item->frame));
        new_item->context = context;
        if (!self->first) {
            self->first = new_item;
        }

        if (!self->last) {
            self->last = new_item;
        }
    }
    return new_item;
}

void jdksavdecc_frame_list_delete(struct jdksavdecc_frame_list *self,
                                  struct jdksavdecc_frame_list_item *item) {
    if (self->first == item) {
        self->first = item->next;
    }
    if (self->last == item) {
        self->last = item->prev;
    }
    if (item->context) {
        jdksavdecc_delete(self->allocator, item->context);
        item->context = 0;
    }
    jdksavdecc_delete(self->allocator, item);
}

struct jdksavdecc_frame_list_item *
jdksavdecc_frame_list_find(struct jdksavdecc_frame_list *self,
                           jdksavdecc_timestamp_in_microseconds timestamp) {
    struct jdksavdecc_frame_list_item *result = 0;
    struct jdksavdecc_frame_list_item *item = self->first;

    if (self->first && self->last) {
        if (timestamp >= self->first->frame.time &&
            timestamp <= self->last->frame.time) {
            while (item) {
                if (item->frame.time < timestamp) {
                    item = item->next;
                } else {
                    result = item;
                    break;
                }
            }
        }
    }

    return result;
}
