
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
#include "jdksavdecc_maap_sm.h"

#ifndef ENABLE_MAAP_TODO
#define ENABLE_MAAP_TODO (0)
#endif

#if ENABLE_MAAP_TODO

void jdksavdecc_maap_state_machine_init(
    struct jdksavdecc_maap_state_machine *self,
    jdksavdecc_timestamp_in_microseconds current_time,
    struct jdksavdecc_eui48 local_mac, struct jdksavdecc_eui48 base_of_range,
    uint16_t desired_count,
    void (*range_acquired_notification)(struct jdksavdecc_maap_state_machine *,
                                        struct jdksavdecc_eui48 base_of_range,
                                        uint16_t count),
    void (*range_lost_notification)(struct jdksavdecc_maap_state_machine *,
                                    struct jdksavdecc_eui48 base_of_range,
                                    uint16_t count),
    struct jdksavdecc_frame_sender *frame_sender, uint32_t tag,
    void *additional) {
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();

    jdksavdecc_state_machine_init(&self->base, frame_sender, tag, additional);
    self->last_time = current_time;
    self->local_mac = local_mac;
    self->base_of_range = base_of_range;
    self->desired_count = desired_count;
    self->state = jdksavdecc_maap_state_initial;
    self->range_acquired_notification = range_acquired_notification;
    self->range_lost_notification = range_lost_notification;

    self->base.rx_frame = jdksavdecc_maap_state_machine_rx_frame;
    self->base.tick = jdksavdecc_maap_state_machine_tick;
    self->base.tx_frame = jdksavdecc_maap_state_machine_tx_frame;
    self->base.destroy = jdksavdecc_maap_state_machine_destroy;

    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}

void
jdksavdecc_maap_state_machine_destroy(struct jdksavdecc_state_machine *self_) {
    struct jdksavdecc_maap_state_machine *self =
        (struct jdksavdecc_maap_state_machine *)self_;
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();

    jdksavdecc_state_machine_destroy(&self->base);

    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}

int jdksavdecc_maap_state_machine_tick(
    struct jdksavdecc_state_machine *self_,
    jdksavdecc_timestamp_in_microseconds current_time) {
    struct jdksavdecc_maap_state_machine *self =
        (struct jdksavdecc_maap_state_machine *)self_;
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();

    (void)self;
    (void)current_time;

    log_exit();
    JDKSAVDECC_LOG_RESTORE();
    return 0;
}

ssize_t
jdksavdecc_maap_state_machine_rx_frame(struct jdksavdecc_state_machine *self_,
                                       struct jdksavdecc_frame *rx_frame,
                                       size_t pos) {
    struct jdksavdecc_maap_state_machine *self =
        (struct jdksavdecc_maap_state_machine *)self_;
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();

    (void)self;
    (void)rx_frame;
    (void)pos;

    log_exit();
    JDKSAVDECC_LOG_RESTORE();
    return 0;
}

void
jdksavdecc_maap_state_machine_tx_frame(struct jdksavdecc_state_machine *self_,
                                       struct jdksavdecc_frame const *frame) {
    struct jdksavdecc_maap_state_machine *self =
        (struct jdksavdecc_maap_state_machine *)self_;
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();

    (void)self;
    (void)frame;
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}

#if 0

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_initial(
    struct jdksavdecc_maap_state_machine *self,
    enum jdksavdecc_maap_event event,
    struct jdksavdecc_maap *received_pdu
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_probe(
    struct jdksavdecc_maap_state_machine *self,
    enum jdksavdecc_maap_event event,
    struct jdksavdecc_maap *received_pdu
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_defend(
    struct jdksavdecc_maap_state_machine *self,
    enum jdksavdecc_maap_event event,
    struct jdksavdecc_maap *received_pdu
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}



/// See IEEE Std 1722-2011 Annex B.3.6.1
void jdksavdecc_maap_action_generate_address(
    struct jdksavdecc_maap_state_machine *self,
    struct jdksavdecc_eui48 *start_address,
    uint16_t count
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.2
void jdksavdecc_maap_action_init_maap_probe_count(
    struct jdksavdecc_maap_state_machine *self
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.3
void jdksavdecc_maap_action_dec_maap_probe_count(
    struct jdksavdecc_maap_state_machine *self
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.4
void jdksavdecc_maap_action_compare_mac(
    struct jdksavdecc_maap_state_machine *self,
    struct jdksavdecc_maap *received_pdu
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.5
void jdksavdecc_maap_action_sprobe(
    struct jdksavdecc_maap_state_machine *self
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.6
void jdksavdecc_maap_action_sdefend(
    struct jdksavdecc_maap_state_machine *self
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}


/// See IEEE Std 1722-2011 Annex B.3.6.7
void jdksavdecc_maap_action_sannounce(
    struct jdksavdecc_maap_state_machine *self
    )
{
    JDKSAVDECC_LOG_SAVE(JDKSAVDECC_SUBSYSTEM_MAAP);
    log_enter();
    // TODO
    log_exit();
    JDKSAVDECC_LOG_RESTORE();
}
#endif
#else
char const *jdksavdecc_maap_sm_file = __FILE__;
#endif
