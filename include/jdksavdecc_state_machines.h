#pragma once
#ifndef JDKSAVDECC_STATE_MACHINES_H
#define JDKSAVDECC_STATE_MACHINES_H

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

#include "jdksavdecc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_maap_state_machine;
struct jdksavdecc_adp_discovery_state_machine;
struct jdksavdecc_adp_advertise_interface_state_machine;
struct jdksavdecc_adp_advertise_entity_state_machine;
struct jdksavdecc_acmp_talker_state_machine;
struct jdksavdecc_acmp_listener_state_machine;
struct jdksavdecc_acmp_controller_state_machine;
struct jdksavdecc_aem_entity_state_machine;
struct jdksavdecc_descriptor_dispatch;

struct jdksavdecc_state_machines
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;

    void (*tick)( struct jdksavdecc_state_machines *self, jdksavdecc_time timestamp );

    struct jdksavdecc_command_dispatch *aecp_aem_command;
    struct jdksavdecc_command_dispatch *aecp_aem_response;

    struct jdksavdecc_descriptor_dispatch *aecp_aem_descriptor_write;
    struct jdksavdecc_descriptor_dispatch *aecp_aem_descriptor_read;
    struct jdksavdecc_descriptor_dispatch *aecp_aem_descriptor_response;

    struct jdksavdecc_acmp_talker_state_machine *acmp_talker_state_machine;
    struct jdksavdecc_acmp_listener_state_machine *acmp_listener_state_machine;
    struct jdksavdecc_acmp_controller_state_machine *acmp_controller_state_machine;

    struct jdksavdecc_adp_discovery_state_machine *adp_discovery_state_machine;
    struct jdksavdecc_adp_advertise_interface_state_machine *adp_advertise_interface_state_machine;
    struct jdksavdecc_adp_advertise_entity_state_machine *adp_advertise_entity_state_machine;

    struct jdksavdecc_aem_entity_state_machine *aem_entity_state_machine;

    struct jdksavdecc_maap_state_machine *maap_state_machine;
};

void jdksavdecc_state_machines_init( struct jdksavdecc_state_machines *self );
void jdksavdecc_state_machines_tick( struct jdksavdecc_state_machines *self, jdksavdecc_time timestamp );



#ifdef __cplusplus
}
#endif

#endif


