
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

void jdksavdecc_state_machine_init(struct jdksavdecc_state_machine *self,
                                   struct jdksavdecc_frame_sender *frame_sender,
                                   uint32_t tag,
                                   void *additional) {
    self->additional = 0;
    self->tag = 0;
    self->destroy = jdksavdecc_state_machine_destroy;
    self->tick = jdksavdecc_state_machine_tick;
    self->rx_frame = jdksavdecc_state_machine_rx_frame;
    self->tx_frame = jdksavdecc_state_machine_tx_frame;
    self->frame_sender = frame_sender;
    self->terminated = 0;
    self->tag = tag;
    self->additional = additional;
    self->do_early_tick = 0;
}

void jdksavdecc_state_machine_destroy(struct jdksavdecc_state_machine *self) {
    // zero all fields
    memset(self, 0, sizeof(*self));
}

void jdksavdecc_state_machine_terminate(struct jdksavdecc_state_machine *self) { self->terminated = 1; }

int jdksavdecc_state_machine_tick(struct jdksavdecc_state_machine *self, jdksavdecc_timestamp_in_microseconds timestamp) {
    int r = 0;

    // default is to ignore ticks
    (void)timestamp;

    // Reset the flag to trigger an early tick
    self->do_early_tick = 0;

    // A terminated state machine causes us to return -1
    if (self->terminated) {
        r = -1;
    } else {
        r = 0;
    }
    return r;
}

ssize_t
jdksavdecc_state_machine_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos) {
    // Nothing to do - default is to ignore rx_frame
    (void)self;
    (void)rx_frame;
    (void)pos;
    return 0;
}

void jdksavdecc_state_machine_tx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame const *frame) {
    /* Default is to give the frame to the frame_sender if there is one */
    log_enter();
    if (self->frame_sender) {
        self->frame_sender->send(self->frame_sender, frame);
    }
    log_exit();
}
