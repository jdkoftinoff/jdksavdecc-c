#pragma once
#ifndef JDKSAVDECC_MAAP_SM_H
#define JDKSAVDECC_MAAP_SM_H

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
#include "jdksavdecc_maap.h"
#include "jdksavdecc_state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup maap MAAP - IEEE Std 1722-2011 Annex B.2 */
/*@{*/

#ifndef JDKSAVDECC_MAAP_SM_ENABLE_LOG
#define JDKSAVDECC_MAAP_SM_ENABLE_LOG (1)
#endif

#if JDKSAVDECC_MAAP_SM_ENABLE_LOG
#define jdksavdecc_maap_sm_log jdksavdecc_log_info
#ifndef jdksavdecc_maap_sm_log_enter
#define jdksavdecc_maap_sm_log_enter() jdksavdecc_maap_sm_log("Enter:%s:%d", __FUNCTION__, __LINE__)
#endif
#ifndef jdksavdecc_maap_sm_log_exit
#define jdksavdecc_maap_sm_log_exit() jdksavdecc_maap_sm_log("Exit:%s:%d", __FUNCTION__, __LINE__)
#endif
#else
#define jdksavdecc_maap_sm_log(fmt, ...)
#define jdksavdecc_maap_sm_log_enter()
#define jdksavdecc_maap_sm_log_exit()
#endif

/** \addtogroup maap_sm MAAP State Machine - IEEE Std 1722-2011 Annex B.3 */
/*@{*/

/// See IEEE Std 1722-2011 Annex B.3.1.
enum jdksavdecc_maap_event {
    jdksavdecc_maap_event_begin = 0,
    jdksavdecc_maap_event_release,
    jdksavdecc_maap_event_restart,
    jdksavdecc_maap_event_reserve_address,
    jdksavdecc_maap_event_rprobe,
    jdksavdecc_maap_event_rdefend,
    jdksavdecc_maap_event_rannounce,
    jdksavdecc_maap_event_probe_count,
    jdksavdecc_maap_event_announce_timer,
    jdksavdecc_maap_event_probe_timer
};

struct jdksavdecc_maap_state_machine;

/// See IEEE Std 1722-2011 Annex B.3.2
typedef void (*jdksavdecc_maap_state)(struct jdksavdecc_maap_state_machine *, enum jdksavdecc_maap_event event,
                                      struct jdksavdecc_maap *received_pdu);

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_initial(struct jdksavdecc_maap_state_machine *, enum jdksavdecc_maap_event event,
                                   struct jdksavdecc_maap *received_pdu);

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_probe(struct jdksavdecc_maap_state_machine *, enum jdksavdecc_maap_event event,
                                 struct jdksavdecc_maap *received_pdu);

/// See IEEE Std 1722-2011 Annex B.3.2
void jdksavdecc_maap_state_defend(struct jdksavdecc_maap_state_machine *, enum jdksavdecc_maap_event event,
                                  struct jdksavdecc_maap *received_pdu);

/// See IEEE Std 1722-2011 Annex B.3.6.1
void jdksavdecc_maap_action_generate_address(struct jdksavdecc_maap_state_machine *, struct jdksavdecc_eui48 *start_address,
                                             uint16_t count);

/// See IEEE Std 1722-2011 Annex B.3.6.2
void jdksavdecc_maap_action_init_maap_probe_count(struct jdksavdecc_maap_state_machine *);

/// See IEEE Std 1722-2011 Annex B.3.6.3
void jdksavdecc_maap_action_dec_maap_probe_count(struct jdksavdecc_maap_state_machine *);

/// See IEEE Std 1722-2011 Annex B.3.6.4
void jdksavdecc_maap_action_compare_mac(struct jdksavdecc_maap_state_machine *, struct jdksavdecc_maap *received_pdu);

/// See IEEE Std 1722-2011 Annex B.3.6.5
void jdksavdecc_maap_action_sprobe(struct jdksavdecc_maap_state_machine *);

/// See IEEE Std 1722-2011 Annex B.3.6.6
void jdksavdecc_maap_action_sdefend(struct jdksavdecc_maap_state_machine *);

/// See IEEE Std 1722-2011 Annex B.3.6.7
void jdksavdecc_maap_action_sannounce(struct jdksavdecc_maap_state_machine *);

/// The MAAP state machine - See IEEE Std 1722-2011 Annex B.3
struct jdksavdecc_maap_state_machine {
    /// Base class for a state machine
    struct jdksavdecc_state_machine base;

    jdksavdecc_maap_state state;
    struct jdksavdecc_eui48 local_mac;
    struct jdksavdecc_eui48 base_of_range;
    uint16_t desired_count;

    void (*range_acquired_notification)(struct jdksavdecc_maap_state_machine *, struct jdksavdecc_eui48 base_of_range,
                                        uint16_t count);
    void (*range_lost_notification)(struct jdksavdecc_maap_state_machine *, struct jdksavdecc_eui48 base_of_range, uint16_t count);

    jdksavdecc_timestamp_in_microseconds last_time;
    jdksavdecc_timestamp_in_microseconds announce_timer; /// See IEEE Std 1722-2011 Annex B.3.4.1
    jdksavdecc_timestamp_in_microseconds probe_timer;    /// See IEEE Std 1722-2011 Annex B.3.4.2
};

void jdksavdecc_maap_state_machine_init(struct jdksavdecc_maap_state_machine *self,
                                        jdksavdecc_timestamp_in_microseconds current_time, struct jdksavdecc_eui48 local_mac,
                                        struct jdksavdecc_eui48 base_of_range, uint16_t desired_count,
                                        void (*range_acquired_notification)(struct jdksavdecc_maap_state_machine *,
                                                                            struct jdksavdecc_eui48 base_of_range, uint16_t count),
                                        void (*range_lost_notification)(struct jdksavdecc_maap_state_machine *,
                                                                        struct jdksavdecc_eui48 base_of_range, uint16_t count),
                                        struct jdksavdecc_frame_sender *frame_sender, uint32_t tag, void *additional);

void jdksavdecc_maap_state_machine_destroy(struct jdksavdecc_state_machine *self);

int jdksavdecc_maap_state_machine_tick(struct jdksavdecc_state_machine *self, jdksavdecc_timestamp_in_microseconds current_time);

ssize_t jdksavdecc_maap_state_machine_rx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame,
                                               size_t pos);

/// Transmit a frame to a network port
///
/// @param self Pointer to state_machine base class
/// @param frame The frame that received
/// @returns void
void jdksavdecc_maap_state_machine_tx_frame(struct jdksavdecc_state_machine *self, struct jdksavdecc_frame const *frame);

/*@}*/
#ifdef __cplusplus
}
#endif

#endif
