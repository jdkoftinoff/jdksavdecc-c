  
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
#include "jdksavdecc_adp_advertising_entity.h"

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
        struct jdksavdecc_adp_advertising_global_vars *global,
        uint32_t tag,
        void *additional
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    // Initialize base class without a frame sender since the interface state machine sends the frames
    jdksavdecc_state_machine_init( &self->base, 0, tag, additional );

    self->base.destroy = jdksavdecc_adp_advertising_entity_state_machine_destroy;
    self->base.tick = jdksavdecc_adp_advertising_entity_state_machine_tick;

    self->vars.global = global;
    self->vars.needs_advertise = 0;
    self->vars.reannounce_timer_timeout = 0;

    self->send_available = jdksavdecc_adp_advertising_entity_state_machine_send_available;

    self->goto_initialize = jdksavdecc_adp_advertising_entity_state_machine_goto_initialize;
    self->state_initialize = jdksavdecc_adp_advertising_entity_state_machine_state_initialize;

    self->goto_advertise = jdksavdecc_adp_advertising_entity_state_machine_goto_advertise;
    self->state_advertise = jdksavdecc_adp_advertising_entity_state_machine_state_advertise;

    self->goto_waiting = jdksavdecc_adp_advertising_entity_state_machine_goto_waiting;
    self->state_waiting = jdksavdecc_adp_advertising_entity_state_machine_state_waiting;

    self->state = self->state_initialize;

    // Go to the initialize state
    self->goto_initialize( self );

    jdksavdecc_adp_advertising_entity_log_exit();
    return 0;
}

/// Destroy the state machine. Frees any allocated data
///
/// @param self Pointer to state_machine base class
/// @returns void
///
void jdksavdecc_adp_advertising_entity_state_machine_destroy(
        struct jdksavdecc_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();
    jdksavdecc_state_machine_destroy(self);
    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Run the state machine current state
///
/// @param self Pointer to state_machine base class
/// @param timestamp millisecond_time current time
/// @returns integer 0 on success, -1 on state machine terminated
///
int jdksavdecc_advertising_entity_state_machine_tick(
        struct jdksavdecc_state_machine *self_,
        jdksavdecc_millisecond_time timestamp
        )
{
    int r=-1;
    struct jdksavdecc_adp_advertising_entity_state_machine *self = (struct jdksavdecc_adp_advertising_entity_state_machine *)self_;

    jdksavdecc_adp_advertising_entity_log_enter();
    self->vars.global->current_time = timestamp;
    if( jdksavdecc_state_machine_tick(&self->base, timestamp)==0 )
    {
        if( self->state )
        {
            self->state( self );

            r=0;
        }
    }
    jdksavdecc_adp_advertising_entity_log_exit();
    return r;
}


/// trigger all advertise interface state machines to send an advertise
///
/// See Clause 6.2.4.2.1
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_send_available(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Transition to the INITIALIZE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_initialize(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Process the INITIALIZE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_initialize(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Transition to the ADVERTISE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_advertise(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Process the ADVERTISE state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_advertise(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Transition to the WAITING state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_goto_waiting(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

/// Process the WAITING state
///
/// See Clause 6.2.4.4
///
/// @param self Pointer to jdksavdecc_adp_advertising_entity_state_machine object
///
void jdksavdecc_adp_advertising_entity_state_machine_state_waiting(
        struct jdksavdecc_adp_advertising_entity_state_machine *self
        )
{
    jdksavdecc_adp_advertising_entity_log_enter();

    jdksavdecc_adp_advertising_entity_log_exit();
}

