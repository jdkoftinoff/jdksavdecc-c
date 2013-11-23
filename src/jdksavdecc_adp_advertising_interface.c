
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
#include "jdksavdecc_adp_advertising_interface.h"

int jdksavdecc_adp_advertising_interface_state_machine_init(struct jdksavdecc_adp_advertising_interface_state_machine *self,
                                                            struct jdksavdecc_adp_advertising_interface_vars *interface_vars,
                                                            uint32_t tag, void *additional) {
    log_enter(JDKSAVDECC_SUBSYSTEM_ADVERTISER);

    jdksavdecc_state_machine_init(&self->base, 0, tag, additional);

    // TODO:
    (void)interface_vars;

    log_exit(JDKSAVDECC_SUBSYSTEM_ADVERTISER);
    return 0;
}

void jdksavdecc_adp_advertising_interface_state_machine_destroy(struct jdksavdecc_state_machine *self_) {
    struct jdksavdecc_adp_advertising_interface_state_machine *self =
        (struct jdksavdecc_adp_advertising_interface_state_machine *)self_;
    jdksavdecc_state_machine_destroy(&self->base);
}

void jdksavdecc_adp_advertising_interface_state_machine_tick(struct jdksavdecc_state_machine *self_,
                                                             jdksavdecc_timestamp_in_microseconds timestamp) {
    struct jdksavdecc_adp_advertising_interface_state_machine *self =
        (struct jdksavdecc_adp_advertising_interface_state_machine *)self_;
    jdksavdecc_state_machine_tick(&self->base, timestamp);
}

ssize_t jdksavdecc_adp_advertising_interface_state_machine_rx_frame(struct jdksavdecc_state_machine *self_,
                                                                    struct jdksavdecc_frame *rx_frame, size_t pos) {
    struct jdksavdecc_adp_advertising_interface_state_machine *self =
        (struct jdksavdecc_adp_advertising_interface_state_machine *)self_;
    (void)self;
    (void)rx_frame;
    (void)pos;
    return 0;
}

void jdksavdecc_adp_advertising_interface_state_machine_tx_entity_available(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_tx_entity_departing(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_goto_initialize(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_initialize(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void
jdksavdecc_adp_advertising_interface_state_machine_goto_waiting(struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void
jdksavdecc_adp_advertising_interface_state_machine_state_waiting(struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void
jdksavdecc_adp_advertising_interface_state_machine_goto_departing(struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_departing(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void
jdksavdecc_adp_advertising_interface_state_machine_goto_advertise(struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_advertise(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_goto_received_discover(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_received_discover(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void
jdksavdecc_adp_advertising_interface_state_machine_goto_update_gm(struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_update_gm(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_goto_link_state_change(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}

void jdksavdecc_adp_advertising_interface_state_machine_state_link_state_change(
    struct jdksavdecc_adp_advertising_interface_state_machine *self) {
    // TODO:
    (void)self;
}
