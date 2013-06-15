#pragma once
#ifndef JDKSAVDECC_ADP_DISCOVER_H
#define JDKSAVDECC_ADP_DISCOVER_H

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

#ifdef __cplusplus
extern "C" {
#endif

/// See Clause 6.2.6.1.1
struct jdksavdecc_adp_discovery_entity_info
{
    struct jdksavdecc_eui48 entity_mac;
    struct jdksavdecc_eui48 local_mac;
    struct jdksavdecc_adpdu adpdu;
};

/// See Clause 6.2.6.1.7
struct jdksavdecc_adp_discovery_db
{
    struct jdksavdecc_adp_discovery_entity_info entity_info;
    struct jdksavdecc_adp_discovery_db *prev;
    struct jdksavdecc_adp_discovery_db *next;
};

/// See Clause 6.2.6.1
struct jdksavdecc_adp_discovery_vars
{
    struct jdksavdecc_adp_discovery_entity_info rcvd_entity_info;  /// See Clause 6.2.6.1.1
    int rcvd_available; /// See Clause 6.2.6.1.2
    int rcvd_departing; /// See Clause 6.2.6.1.3
    int do_discover; /// See Clause 6.2.6.1.4
    struct jdksavdecc_eui64 discover_id; /// See Clause 6.2.6.1.5
    int do_terminate; /// See Clause 6.2.6.1.6
    struct jdksavdecc_adp_discovery_db *entities; /// See Clause 6.2.6.1.7
};

struct jdksavdecc_adp_discovery_state_machine;

/// See Clause 6.2.6.2.1
void jdksavdecc_adp_discovery_perform_discover( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.3.1
void jdksavdecc_adp_discovery_tx_discover( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.3.2
void jdksavdecc_adp_discovery_have_entity_id( struct jdksavdecc_adp_discovery_state_machine *, struct jdksavdecc_eui64 entity_id );

/// See Clause 6.2.6.3.2
void jdksavdecc_adp_discovery_update_entity( struct jdksavdecc_adp_discovery_state_machine *, struct jdksavdecc_frame * );

/// See Clause 6.2.6.3.2
void jdksavdecc_adp_discovery_add_entity( struct jdksavdecc_adp_discovery_state_machine *, struct jdksavdecc_frame * );

/// See Clause 6.2.6.3.2
void jdksavdecc_adp_discovery_remove_entity( struct jdksavdecc_adp_discovery_state_machine *, struct jdksavdecc_frame * );

struct jdksavdecc_adp_discovery_state_machine;

typedef void (*jdksavdecc_adp_discovery_state)( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
void jdksavdecc_adp_discovery_state_waiting( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
void jdksavdecc_adp_discovery_state_discover( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
void jdksavdecc_adp_discovery_state_available( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
void jdksavdecc_adp_discovery_state_departing( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
void jdksavdecc_adp_discovery_state_timeout( struct jdksavdecc_adp_discovery_state_machine * );

/// See Clause 6.2.6.4
struct jdksavdecc_adp_discovery_state_machine
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;

    void (*destroy)( struct jdksavdecc_adp_discovery_state_machine * );
    void (*tick)( struct jdksavdecc_adp_discovery_state_machine *self, jdksavdecc_millisecond_time timestamp );
    ssize_t (*rx_frame)( struct jdksavdecc_adp_discovery_state_machine *self, struct jdksavdecc_frame *rx_frame, size_t pos );

    jdksavdecc_adp_discovery_state state;
    struct jdksavdecc_adp_discovery_vars *vars;
};

/// See Clause 6.2.6.3.2
void jdksavdecc_adp_discovery_remove_entity( struct jdksavdecc_adp_discovery_state_machine *, struct jdksavdecc_frame * );

/** @todo adp discovery state machine implementation */
#ifdef __cplusplus
}
#endif

#endif

