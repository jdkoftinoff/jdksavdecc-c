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
#include "jdksavdecc_state_machine.h"
#include "jdksavdecc_acmp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup acmp_listener ACMPDU Listener State Machine - Clause 8.2.2.5 */
/*@{*/

/// @todo acmp listener state machine implementation
struct jdksavdecc_acmp_listener_state_machine {
    struct jdksavdecc_state_machine base;
    struct jdksavdecc_eui64 listener_entity_id;
};

void jdksavdecc_acmp_listener_state_machine_init(struct jdksavdecc_acmp_listener_state_machine *self,
                                                 struct jdksavdecc_eui64 listener_entity_id, struct jdksavdecc_frame_sender *sender,
                                                 uint32_t tag, void *additional);

void jdksavdecc_acmp_listener_state_machine_destroy(struct jdksavdecc_state_machine *self);

void jdksavdecc_acmp_listener_state_machine_tick(struct jdksavdecc_state_machine *self,
                                                 jdksavdecc_timestamp_in_microseconds timestamp);

ssize_t jdksavdecc_acmp_listener_state_machine_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame,
                                                        size_t pos);

void jdksavdecc_acmp_listener_state_machine_tx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame const *frame);

/*@}*/
#ifdef __cplusplus
}
#endif
