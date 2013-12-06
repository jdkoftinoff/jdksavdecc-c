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
#include "jdksavdecc_pdu.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup state_machine State Machine Base Interface */
/*@{*/

/// Common base class for state machines
struct jdksavdecc_state_machine {
    /// Destructor
    void (*destroy)(struct jdksavdecc_state_machine *self);

    /// Ask the state machine to terminate
    void (*terminate)(struct jdksavdecc_state_machine *self);

    /// Time tick. Returns 0 on success, -1 on state machine terminated
    int (*tick)(struct jdksavdecc_state_machine *self, jdksavdecc_timestamp_in_microseconds timestamp);

    /// Received Frame
    ssize_t (*rx_frame)(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos);

    /// Transmit Frame
    void (*tx_frame)(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame const *frame);

    /// Object to Transmit Frame with
    struct jdksavdecc_frame_sender *frame_sender;

    /// flag to indicate that the state machine was asked to terminate
    int terminated;

    /// Tag for additional identification
    uint32_t tag;

    /// Auxiliary pointer for additional associations
    void *additional;

    /// Flag used to trigger an early tick due to protocol handling message
    /// request
    int do_early_tick;
};

/// Initialize state machine
void jdksavdecc_state_machine_init(struct jdksavdecc_state_machine *self,
                                   struct jdksavdecc_frame_sender *frame_sender,
                                   uint32_t tag,
                                   void *additional);

/// Destroy state machine
void jdksavdecc_state_machine_destroy(struct jdksavdecc_state_machine *self);

/// Ask the state machine to terminate
void jdksavdecc_state_machine_terminate(struct jdksavdecc_state_machine *self);

/// Time tick.  Returns 0 on success, -1 on state machine terminated
int jdksavdecc_state_machine_tick(struct jdksavdecc_state_machine *self, jdksavdecc_timestamp_in_microseconds timestamp);

/// Received Frame
ssize_t jdksavdecc_state_machine_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos);

/// Transmit Frame
void jdksavdecc_state_machine_tx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame const *frame);

/*@}*/

#ifdef __cplusplus
}
#endif
