#pragma once
#ifndef JDKSAVDECC_LOG_AECP_H
#define JDKSAVDECC_LOG_AECP_H

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

#ifndef JDKSAVDECC_WORLD_H
#include "jdksavdecc_world.h"
#endif

#include "jdksavdecc_log.h"
#include "jdksavdecc_pdu.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup log logging
*/
/*@{*/

struct jdksavdecc_log_aecp_context {
    struct jdksavdecc_eui64 entity_id;
    struct jdksavdecc_eui64 controller_id;
    struct jdksavdecc_eui48 destination_mac;
    uint16_t descriptor_type;
    uint16_t debug_descriptor_index;
    uint16_t info_descriptor_index;
    uint16_t warning_descriptor_index;
    uint16_t error_descriptor_index;
};

void jdksavdecc_log_aecp_debug(const char *fmt, ...);
void jdksavdecc_log_aecp_info(const char *fmt, ...);
void jdksavdecc_log_aecp_warning(const char *fmt, ...);
void jdksavdecc_log_aecp_error(const char *fmt, ...);

void jdksavdecc_log_aecp_init(struct jdksavdecc_log_aecp_context *context, struct jdksavdecc_frame_sender *frame_sender,
                              struct jdksavdecc_frame *frame_for_logging);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
