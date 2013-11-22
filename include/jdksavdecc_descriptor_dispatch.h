#pragma once
#ifndef JDKSAVDECC_DESCRIPTOR_DISPATCH_H
#define JDKSAVDECC_DESCRIPTOR_DISPATCH_H

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

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_descriptor;

/** \addtogroup descriptor_dispatch Descriptor Dispatch
 *  @todo descriptor_dispatch
*/
/*@{*/
struct jdksavdecc_descriptor_dispatch;

typedef ssize_t (*jdksavdecc_descriptor_dispatch_proc)(struct jdksavdecc_descriptor_dispatch *self, struct jdksavdecc_frame *frame,
                                                       size_t pos);

struct jdksavdecc_descriptor_dispatch {
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;
    jdksavdecc_descriptor_dispatch_proc rx_frame;
    jdksavdecc_descriptor_dispatch_proc command[JDKSAVDECC_NUM_DESCRIPTOR_TYPES];
};

ssize_t jdksavdec_descriptor_dispatch_rx_frame(struct jdksavdecc_descriptor_dispatch *self, struct jdksavdecc_frame *frame,
                                               size_t pos);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
