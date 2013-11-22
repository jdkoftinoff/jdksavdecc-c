#pragma once
#ifndef JDKSAVDECC_FRAME_LIST_H
#define JDKSAVDECC_FRAME_LIST_H

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
#include "jdksavdecc_frame.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup frame_list raw ethernet frame list */
/*@{*/

struct jdksavdecc_frame_list_item;

struct jdksavdecc_frame_list {
    struct jdksavdecc_frame_list_item *first;
    struct jdksavdecc_frame_list_item *last;
};

struct jdksavdecc_frame_list_item {
    struct jdksavdecc_frame_list_item *next;
    struct jdksavdecc_frame_list_item *prev;
    struct jdksavdecc_frame frame;
    void *context;
};

int jdksavdecc_frame_list_init(struct jdksavdecc_frame_list *self);

void jdksavdecc_frame_list_destroy(struct jdksavdecc_frame_list *self);

struct jdksavdecc_frame_list_item *jdksavdecc_frame_list_add(struct jdksavdecc_frame_list *self,
                                                             struct jdksavdecc_frame const *frame, void *context);

void jdksavdecc_frame_list_delete(struct jdksavdecc_frame_list *self, struct jdksavdecc_frame_list_item *item);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
