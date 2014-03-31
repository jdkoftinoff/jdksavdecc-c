#pragma once

/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
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
#include "jdksavdecc_acmp.h"
#include "jdksavdecc_entity_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup acmp ACMP - Clause 8 */
/*@{*/

/** \addtogroup acmp_talker ACMP Talker State Machine */
/*@{*/

struct jdksavdecc_acmp_talker_manager {

    /// A flag used to notify the state machine to pause sending any messages
    bool stopped;

    /// The context that the state machine is used in.
    void *context;

    /// The function that the jdksavdecc_acmp_talker_manager calls in order to send an ACMPDU
    void (*frame_send)(
        struct jdksavdecc_acmp_talker_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len );
};

bool jdksavdecc_acmp_talker_manager_init(
    struct jdksavdecc_acmp_talker_manager *self,
    void *context,
    void (*frame_send)(
        struct jdksavdecc_acmp_talker_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len )
    );

/// Destroy any resources that the jdksavdecc_acmp_talker_manager uses
void jdksavdecc_acmp_talker_manager_destroy(struct jdksavdecc_acmp_talker_manager *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_talker_manager_receive(
    struct jdksavdecc_acmp_talker_manager *self,
    jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
    void const *source_address,
    int source_address_len,
    uint8_t const *buf,
    uint16_t len );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_talker_manager_tick(
    struct jdksavdecc_acmp_talker_manager *self,
    jdksavdecc_timestamp_in_milliseconds cur_time_in_ms );

/// Tell the state machine to stop. Incoming messages will still be reported.
static inline void jdksavdecc_acmp_talker_manager_stop(
    struct jdksavdecc_acmp_talker_manager *self) {
    self->stopped = true;
}

/*@}*/


/** \addtogroup acmp_talker ACMP Listener State Machine */
/*@{*/

struct jdksavdecc_acmp_listener_manager {

    /// A flag used to notify the state machine to pause sending any messages
    bool stopped;

    /// The context that the state machine is used in.
    void *context;

    /// The function that the jdksavdecc_acmp_listener_manager calls in order to send an ACMPDU
    void (*frame_send)(
        struct jdksavdecc_acmp_listener_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len );
};

bool jdksavdecc_acmp_listener_manager_init(
    struct jdksavdecc_acmp_listener_manager *self,
    void *context,
    void (*frame_send)(
        struct jdksavdecc_acmp_listener_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len )
    );

/// Destroy any resources that the jdksavdecc_acmp_listener_manager uses
void jdksavdecc_acmp_listener_manager_destroy(struct jdksavdecc_acmp_listener_manager *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_listener_manager_receive(
    struct jdksavdecc_acmp_listener_manager *self,
    jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
    void const *source_address,
    int source_address_len,
    uint8_t const *buf,
    uint16_t len );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_listener_manager_tick(
    struct jdksavdecc_acmp_listener_manager *self,
    jdksavdecc_timestamp_in_milliseconds cur_time_in_ms );

/// Tell the state machine to stop. Incoming messages will still be reported.
static inline void jdksavdecc_acmp_listener_manager_stop(
    struct jdksavdecc_acmp_listener_manager *self) {
    self->stopped = true;
}

/*@}*/


/** \addtogroup acmp_talker ACMP Controller State Machine */
/*@{*/

struct jdksavdecc_acmp_controller_manager {

    /// A flag used to notify the state machine to pause sending any messages
    bool stopped;

    /// The context that the state machine is used in.
    void *context;

    /// The function that the jdksavdecc_acmp_controller_manager calls in order to send an ACMPDU
    void (*frame_send)(
        struct jdksavdecc_acmp_controller_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len );
};

bool jdksavdecc_acmp_controller_manager_init(
    struct jdksavdecc_acmp_controller_manager *self,
    void *context,
    void (*frame_send)(
        struct jdksavdecc_acmp_controller_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len )
    );

/// Destroy any resources that the jdksavdecc_acmp_controller_manager uses
void jdksavdecc_acmp_controller_manager_destroy(struct jdksavdecc_acmp_controller_manager *self );

/// Receive an ACMPDU and process it
bool jdksavdecc_acmp_controller_manager_receive(
    struct jdksavdecc_acmp_controller_manager *self,
    jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
    void const *source_address,
    int source_address_len,
    uint8_t const *buf,
    uint16_t len );

/// Notify the state machine that time has passed. Call asap if early_tick is true.
void jdksavdecc_acmp_controller_manager_tick(
    struct jdksavdecc_acmp_controller_manager *self,
    jdksavdecc_timestamp_in_milliseconds cur_time_in_ms );

/// Tell the state machine to stop. Incoming messages will still be reported.
static inline void jdksavdecc_acmp_controller_manager_stop(
    struct jdksavdecc_acmp_controller_manager *self) {
    self->stopped = true;
}

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif


