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
#include "jdksavdecc_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup frame raw ethernet frame */
/*@{*/

#ifndef JDKSAVDECC_FRAME_MAX_PAYLOAD_SIZE
#define JDKSAVDECC_FRAME_MAX_PAYLOAD_SIZE (640)
#endif

struct jdksavdecc_frame {
    jdksavdecc_timestamp_in_microseconds time;
    struct jdksavdecc_eui48 dest_address;
    struct jdksavdecc_eui48 src_address;
    uint16_t ethertype;
    uint16_t tpid;
    uint16_t pcp : 3;
    uint16_t dei : 1;
    uint16_t vid : 12;
    uint16_t length;
    uint16_t max_payload_length;
    uint8_t *payload;
};

static inline void
jdksavdecc_frame_init(struct jdksavdecc_frame *p, uint8_t *payload_memory, uint16_t max_payload_length, uint16_t length) {
    p->time = 0;
    jdksavdecc_eui48_init(&p->dest_address);
    jdksavdecc_eui48_init(&p->src_address);
    p->ethertype = 0;
    p->length = 0;
    p->tpid = 0;
    p->pcp = 0;
    p->dei = 0;
    p->vid = 0;
    p->max_payload_length = max_payload_length;
    p->length = length;
    p->payload = payload_memory;
    memset(p->payload, 0, max_payload_length);
}

ssize_t jdksavdecc_frame_read(struct jdksavdecc_frame *p, void const *base, ssize_t pos, size_t len);
ssize_t jdksavdecc_frame_write(struct jdksavdecc_frame const *p, void *base, ssize_t pos, size_t len);

/*@}*/

/** frame sender class */
struct jdksavdecc_frame_sender {
    void (*destroy)(struct jdksavdecc_frame_sender *);
    void (*send)(struct jdksavdecc_frame_sender *, struct jdksavdecc_frame const *frame);
};

#ifdef __cplusplus
}
#endif
