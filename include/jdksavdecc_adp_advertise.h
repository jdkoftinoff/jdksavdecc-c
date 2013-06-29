#pragma once
#ifndef JDKSAVDECC_ADP_ADVERTISE_H
#define JDKSAVDECC_ADP_ADVERTISE_H

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
#include "jdksavdecc_adp.h"
#include "jdksavdecc_aem_entity.h"
#include "jdksavdecc_state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup adp_advertise ADP Advertising Entity State Machine - Clause 6.2.4 */
/*@{*/

#ifndef JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG
# define JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG (1)
#endif

#if JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG
# define jdksavdecc_adp_advertising_entity_log(fmt, ...) jdksavdecc_do_log("jdksavdecc_adp_advertising_entity_state_machine:%p:%s:",fmt, self, __FUNCTION__, ## __VA_ARGS__ )
# ifndef jdksavdecc_adp_advertising_entity_log_enter
#  define jdksavdecc_adp_advertising_entity_log_enter() jdksavdecc_adp_advertising_entity_log("Enter")
# endif
# ifndef jdksavdecc_adp_advertising_entity_log_exit
#  define jdksavdecc_adp_advertising_entity_log_exit() jdksavdecc_adp_advertising_entity_log("Exit")
# endif
#else
# define jdksavdecc_adp_advertising_entity_log(fmt, ...)
# define jdksavdecc_adp_advertising_entity_log_enter()
# define jdksavdecc_adp_advertising_entity_log_exit()
#endif

/// See Clause 6.2.3
struct jdksavdecc_adp_advertising_global_vars
{
    jdksavdecc_millisecond_time current_time;
    struct jdksavdecc_entity *entity_info;
};

/// See Clause 6.2.4.1
struct jdksavdecc_adp_advertising_entity_vars
{
    /// See Clause 6.2.3
    struct jdksavdecc_adp_advertising_global_vars *global;

    /// See Clause 6.2.4.1.1
    jdksavdecc_millisecond_time reannounce_timer_timeout;

    /// See Clause 6.2.4.1.2
    int needs_advertise;
};

struct jdksavdecc_adp_advertising_entity_state_machine;

// Pointer to a state machine state procedure
typedef void (*jdksavdecc_adp_advertising_entity_state)(
        struct jdksavdecc_adp_advertising_entity_state_machine *
        );

// Pointer to a state machine state transition procedure
typedef void (*jdksavdecc_adp_advertising_entity_state_transition)(
        struct jdksavdecc_adp_advertising_entity_state_machine *
        );


struct jdksavdecc_adp_advertising_entity_state_machine
{
    /// Base class for a state machine
    struct jdksavdecc_state_machine base;

    /// The variables of the advertising entity state machine
    struct jdksavdecc_adp_advertising_entity_vars vars;

    /// The current state procedure
    jdksavdecc_adp_advertising_entity_state state;

    /// Overridable method for triggering all advertising interface state machines to send an advertise
    /// See Clause 6.2.4.2.1
    void (*send_available)( struct jdksavdecc_adp_advertising_entity_state_machine * );

    /// Pointer to the state transition procedure to call when transitioning into the INITIALIZE state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state_transition goto_initialize;

    /// Pointer to the state procedure to call when in the INITIALIZE state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state state_initialize;

    /// Pointer to the state transition procedure to call when transitioning into the ADVERTISE state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state_transition goto_advertise;

    /// Pointer to the state procedure to call when in the ADVERTISE state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state state_advertise;

    /// Pointer to the state transition procedure to call when transitioning into the WAITING state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state_transition goto_waiting;

    /// Pointer to the state procedure to call when in the WAITING state
    /// See Clause 6.2.4.3
    jdksavdecc_adp_advertising_entity_state state_waiting;
};

/// Initialize the ADP Advertising Entity State Machine
///
/// @param self Pointer to jdksavdecc_adp_advertising_interface_state_machine to initialize
/// @param entity_info Pointer to jdksavdecc_entity object representing the entity
/// @param tag uint32_t general purpose tag value for high level use
/// @param additional void * general purpose pointer for high level use
/// @returns 0 on success
///
int jdksavdecc_adp_advertising_entity_state_machine_init(
        struct jdksavdecc_adp_advertising_entity_state_machine *self,
        struct jdksavdecc_entity *entity_info,
        uint32_t tag,
        void *additional
        );

/// Destroy the state machine. Frees any allocated data
///
/// @param self Pointer to state_machine base class
/// @returns void
///
void jdksavdecc_adp_advertising_interface_state_machine_destroy(
        struct jdksavdecc_state_machine *self
        );

/// Run the state machine current state
///
/// @param self Pointer to state_machine base class
/// @param timestamp millisecond_time current time
/// @returns integer 0 on success, -1 on state machine terminated
///
int jdksavdecc_advertising_interface_state_machine_tick(
        struct jdksavdecc_state_machine *self,
        jdksavdecc_millisecond_time timestamp
        );

/// Tell the state machine that an ethernet frame was received
///
/// @param self Pointer to state_machine base class
/// @param rx_frame The frame that received
/// @param pos The starting position of the message within the frame
/// @returns ssize_t byte position that the message was parsed up to; 0 for none, or -1 for other error
///
ssize_t jdksavdecc_advertising_interface_state_machine_rx_frame(
        struct jdksavdecc_state_machine *self,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        );

/// trigger all advertise interface state machines to send an advertise
///
/// See Clause 6.2.4.2.1
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_send_available(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Transition to the INITIALIZE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_initialize(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Process the INITIALIZE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_initialize(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Transition to the ADVERTISE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_advertise(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Process the ADVERTISE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_advertise(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Transition to the WAITING state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_waiting(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/// Process the WAITING state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_waiting(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        );

/*@}*/

/** \addtogroup adp_advertise ADP Advertising Interface State Machine - Clause 6.2.5 */
/*@{*/

#ifndef JDKSAVDECC_ADP_ADVERTISING_INTERFACE_ENABLE_LOG
# define JDKSAVDECC_ADP_ADVERTISING_INTERFACE_ENABLE_LOG (1)
#endif

#if JDKSAVDECC_ADP_ADVERTISING_INTERFACE_ENABLE_LOG
# define jdksavdecc_adp_advertising_interface_log(fmt, ...) jdksavdecc_do_log("jdksavdecc_adp_advertising_interface_state_machine:%p:%s:",fmt, self, __FUNCTION__, ## __VA_ARGS__ )
# ifndef jdksavdecc_adp_advertising_interface_log_enter
#  define jdksavdecc_adp_advertising_interface_log_enter() jdksavdecc_adp_advertising_interface_log("Enter")
# endif
# ifndef jdksavdecc_adp_advertising_interface_log_exit
#  define jdksavdecc_adp_advertising_interface_log_exit() jdksavdecc_adp_advertising_interface_log("Exit")
# endif
#else
# define jdksavdecc_adp_advertising_interface_log(fmt, ...)
# define jdksavdecc_adp_advertising_interface_log_enter()
# define jdksavdecc_adp_advertising_interface_log_exit()
#endif

/// See Clause 6.2.5.1
struct jdksavdecc_adp_advertising_interface_vars
{
    struct jdksavdecc_adp_advertising_global_vars *global;
    struct jdksavdecc_eui64 advertised_grandmaster_id;
    int rcvd_discover;
    struct jdksavdecc_eui64 entity_id;
    int do_advertise;
    int link_is_up;
    int last_link_is_up;
};


struct jdksavdecc_adp_advertising_interface_state_machine;

typedef void (*jdksavdecc_adp_advertising_interface_state)( struct jdksavdecc_adp_advertising_interface_state_machine * );
typedef void (*jdksavdecc_adp_advertising_interface_state_transition)( struct jdksavdecc_adp_advertising_interface_state_machine * );


struct jdksavdecc_adp_advertising_interface_state_machine
{
    struct jdksavdecc_state_machine base;

    jdksavdecc_adp_advertising_interface_state state;
    struct jdksavdecc_adp_advertising_interface_vars *vars;
    struct jdksavdecc_eui48 interface_mac;

    jdksavdecc_adp_advertising_interface_state_transition goto_initialize;
    jdksavdecc_adp_advertising_interface_state state_initialize;

    jdksavdecc_adp_advertising_interface_state_transition goto_waiting;
    jdksavdecc_adp_advertising_interface_state state_waiting;

    jdksavdecc_adp_advertising_interface_state_transition goto_departing;
    jdksavdecc_adp_advertising_interface_state state_departing;

    jdksavdecc_adp_advertising_interface_state_transition goto_advertise;
    jdksavdecc_adp_advertising_interface_state state_advertise;

    jdksavdecc_adp_advertising_interface_state_transition goto_received_discover;
    jdksavdecc_adp_advertising_interface_state state_received_discover;

    jdksavdecc_adp_advertising_interface_state_transition goto_update_gm;
    jdksavdecc_adp_advertising_interface_state state_update_gm;

    jdksavdecc_adp_advertising_interface_state_transition goto_link_state_change;
    jdksavdecc_adp_advertising_interface_state state_link_state_change;
};


void jdksavdecc_adp_advertising_interface_tick( struct jdksavdecc_state_machine *self, jdksavdecc_millisecond_time timestamp );
ssize_t jdksavdecc_adp_advertising_interface_rx_frame( struct jdksavdecc_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );

/// Clause 6.2.5.2 entity state machine functions
void jdksavdecc_adp_advertising_interface_tx_entity_available( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_tx_entity_departing( struct jdksavdecc_adp_advertising_interface_state_machine * );

/// Clause 6.2.5.3 entity state machine states
void jdksavdecc_adp_advertising_interface_goto_initialize( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_initialize( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_waiting( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_waiting( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_departing( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_departing( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_advertise( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_advertise( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_received_discover( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_received_discover( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_update_gm( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_update_gm( struct jdksavdecc_adp_advertising_interface_state_machine * );

void jdksavdecc_adp_advertising_interface_goto_link_state_change( struct jdksavdecc_adp_advertising_interface_state_machine * );
void jdksavdecc_adp_advertising_interface_state_link_state_change( struct jdksavdecc_adp_advertising_interface_state_machine * );

/*@}*/


#ifdef __cplusplus
}
#endif

#endif

