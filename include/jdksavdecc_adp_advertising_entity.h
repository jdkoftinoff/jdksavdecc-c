#pragma once
#ifndef JDKSAVDECC_ADP_ADVERTISING_INTERFACE_H
#define JDKSAVDECC_ADP_ADVERTISING_INTERFACE_H

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

/** \addtogroup adp_advertise_entity ADP Advertising Entity State Machine - Clause 6.2.4 */
/*@{*/

#ifndef JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG
# define JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG (1)
#endif

#if JDKSAVDECC_ADP_ADVERTISING_ENTITY_ENABLE_LOG
# define jdksavdecc_adp_advertising_entity_log jdksavdecc_log_info
# ifndef jdksavdecc_adp_advertising_entity_log_enter
#  define jdksavdecc_adp_advertising_entity_log_enter() jdksavdecc_adp_advertising_entity_log("Enter:%s:%d",__FUNCTION__,__LINE__)
# endif
# ifndef jdksavdecc_adp_advertising_entity_log_exit
#  define jdksavdecc_adp_advertising_entity_log_exit() jdksavdecc_adp_advertising_entity_log(" Exit:%s:%d",__FUNCTION__,__LINE__)
# endif
#else
# define jdksavdecc_adp_advertising_entity_log(...)
# define jdksavdecc_adp_advertising_entity_log_enter()
# define jdksavdecc_adp_advertising_entity_log_exit()
#endif

/// See Clause 6.2.3
struct jdksavdecc_adp_advertising_global_vars
{
    jdksavdecc_microsecond_time current_time;
    struct jdksavdecc_entity_info *entity_info;
};

/// See Clause 6.2.4.1
struct jdksavdecc_adp_advertising_entity_vars
{
    /// See Clause 6.2.3
    struct jdksavdecc_adp_advertising_global_vars *global;

    /// See Clause 6.2.4.1.1
    jdksavdecc_microsecond_time reannounce_timer_timeout;

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


/// See Clause 6.2.4
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
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine to initialize
/// @param global Pointer to jdksavdecc_adp_advertising_global_vars object representing the entity
/// @param tag uint32_t general purpose tag value for high level use
/// @param additional void * general purpose pointer for high level use
/// @returns 0 on success
///
int jdksavdecc_adp_advertising_entity_state_machine_init(
        struct jdksavdecc_adp_advertising_entity_state_machine *self,
        struct jdksavdecc_adp_advertising_global_vars *global,
        uint32_t tag,
        void *additional
        );

/// Destroy the state machine. Frees any allocated data
///
/// @param self Pointer to state_machine base class
/// @returns void
///
void jdksavdecc_adp_advertising_entity_state_machine_destroy(
        struct jdksavdecc_state_machine *self
        );

/// Run the state machine current state
///
/// @param self Pointer to state_machine base class
/// @param timestamp millisecond_time current time
/// @returns integer 0 on success, -1 on state machine terminated
///
int jdksavdecc_adp_advertising_entity_state_machine_tick(
        struct jdksavdecc_state_machine *self,
        jdksavdecc_microsecond_time timestamp
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


#ifdef __cplusplus
}
#endif

#endif

