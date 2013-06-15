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

#ifdef __cplusplus
extern "C" {
#endif

/// See Clause 6.2.3
struct jdksavdecc_adp_advertise_global_vars
{
    jdksavdecc_millisecond_time current_time;
    struct jdksavdecc_entity *entity_info;
};

/// See Clause 6.2.4.1
struct jdksavdecc_adp_advertise_entity_vars
{
    struct jdksavdecc_adp_advertise_global_vars *global;
    jdksavdecc_millisecond_time reannounce_timer_timeout;
    int needs_advertise;
    int do_terminate;
};


/// See Clause 6.2.5.1
struct jdksavdecc_adp_advertise_interface_vars
{
    struct jdksavdecc_adp_advertise_global_vars *global;
    struct jdksavdecc_eui64 advertised_grandmaster_id;
    int rcvd_discover;
    struct jdksavdecc_eui64 entity_id;
    int do_terminate;
    int do_advertise;
    int link_is_up;
    int last_link_is_up;
};


struct jdksavdecc_adp_advertise_interface_state_machine;

typedef void (*jdksavdecc_adp_advertise_interface_state)( struct jdksavdecc_adp_advertise_interface_state_machine * );

/// Clause 6.2.5.2 entity state machine functions
void jdksavdecc_adp_advertise_interface_tx_entity_available( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_tx_entity_departing( struct jdksavdecc_adp_advertise_interface_state_machine * );

/// Clause 6.2.5.3 entity state machine states
void jdksavdecc_adp_advertise_interface_state_initialize( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_waiting( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_departing( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_advertise( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_received_discover( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_update_gm( struct jdksavdecc_adp_advertise_interface_state_machine * );
void jdksavdecc_adp_advertise_interface_state_link_state_change( struct jdksavdecc_adp_advertise_interface_state_machine * );

struct jdksavdecc_adp_advertise_interface_state_machine
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;

    void (*destroy)( struct jdksavdecc_adp_advertise_interface_state_machine * );
    void (*tick)( struct jdksavdecc_adp_advertise_interface_state_machine *self, jdksavdecc_millisecond_time timestamp );
    ssize_t (*rx_frame)( struct jdksavdecc_adp_advertise_interface_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );

    jdksavdecc_adp_advertise_interface_state state;
    struct jdksavdecc_adp_advertise_interface_vars *vars;
    struct jdksavdecc_eui48 interface_mac;
};

void jdksavdecc_adp_advertise_interface_tick( struct jdksavdecc_adp_advertise_interface_state_machine *self, jdksavdecc_millisecond_time timestamp );
ssize_t jdksavdecc_adp_advertise_interface_rx_frame( struct jdksavdecc_adp_advertise_interface_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );


struct jdksavdecc_adp_advertise_entity_state_machine;

typedef void (*jdksavdecc_adp_advertise_entity_state)( struct jdksavdecc_adp_advertise_entity_state_machine * );

struct jdksavdecc_adp_advertise_entity_state_machine
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;

    void (*destroy)( struct jdksavdecc_adp_advertise_entity_state_machine * );
    void (*tick)( struct jdksavdecc_adp_advertise_entity_state_machine *self, jdksavdecc_millisecond_time timestamp );
    ssize_t (*rx_frame)( struct jdksavdecc_adp_advertise_entity_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );


    jdksavdecc_adp_advertise_entity_state state;
    struct jdksavdecc_adp_advertise_entity_vars *vars;
};

void jdksavdecc_adp_advertise_entity_tick( struct jdksavdecc_adp_advertise_entity_state_machine *self, jdksavdecc_millisecond_time timestamp );
ssize_t jdksavdecc_adp_advertise_entity_rx_frame( struct jdksavdecc_adp_advertise_entity_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );


/// See Clause 6.2.4.2.1
void jdksavdecc_adp_advertise_entity_send_available( struct jdksavdecc_adp_advertise_entity_state_machine * );

/// See Clause 7.2.4.3
void jdksavdecc_adp_advertise_entity_state_initialize(struct jdksavdecc_adp_advertise_entity_state_machine *);
void jdksavdecc_adp_advertise_entity_state_advertise(struct jdksavdecc_adp_advertise_entity_state_machine *);
void jdksavdecc_adp_advertise_entity_state_waiting(struct jdksavdecc_adp_advertise_entity_state_machine *);


/** @todo adp advertise entity state machine implementation */

/** @todo adp advertise interface state machine implementation */

#ifdef __cplusplus
}
#endif

#endif

