
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
#include "jdksavdecc_state_machines.h"
#include "jdksavdecc_acmp_controller.h"
#include "jdksavdecc_acmp_listener.h"
#include "jdksavdecc_acmp_talker.h"
#include "jdksavdecc_maap.h"
#include "jdksavdecc_aem_entity.h"
#include "jdksavdecc_descriptor_dispatch.h"

void jdksavdecc_state_machines_init( struct jdksavdecc_state_machines *self )
{
    memset( self, 0, sizeof(*self) );
    self->tick = jdksavdecc_state_machines_tick;
    self->set_frame_sender = jdksavdecc_state_machines_set_frame_sender;
}

void jdksavdecc_state_machines_tick( struct jdksavdecc_state_machines *self, jdksavdecc_millisecond_time timestamp )
{
    if( self->acmp_controller_state_machine )
    {
        self->acmp_controller_state_machine->tick( self->acmp_controller_state_machine, timestamp );
    }

    if( self->acmp_listener_state_machine )
    {
        self->acmp_listener_state_machine->tick( self->acmp_listener_state_machine, timestamp );
    }

    if( self->acmp_talker_state_machine )
    {
        self->acmp_talker_state_machine->tick( self->acmp_talker_state_machine, timestamp );
    }

    if( self->adp_discovery_state_machine )
    {
        self->adp_discovery_state_machine->tick( self->adp_discovery_state_machine, timestamp );
    }

    if( self->adp_advertise_entity_state_machine )
    {
        self->adp_advertise_entity_state_machine->tick( self->adp_advertise_entity_state_machine, timestamp );
    }

    if( self->adp_advertise_interface_state_machine )
    {
        self->adp_advertise_interface_state_machine->tick( self->adp_advertise_interface_state_machine, timestamp );
    }

    if( self->aem_entity_state_machine )
    {
        self->aem_entity_state_machine->tick( self->aem_entity_state_machine, timestamp );
    }

    if( self->maap_state_machine )
    {
        self->maap_state_machine->tick( self->maap_state_machine, timestamp );
    }

}

void jdksavdecc_state_machines_set_frame_sender( struct jdksavdecc_state_machines *self, struct jdksavdecc_frame_sender *sender )
{
    if( self->aecp_aem_command )
    {
        self->aecp_aem_command->frame_sender = sender;
    }

    if( self->aecp_aem_response )
    {
        self->aecp_aem_response->frame_sender = sender;
    }

    if( self->aecp_aem_descriptor_write )
    {
        self->aecp_aem_descriptor_write->frame_sender = sender;
    }

    if( self->aecp_aem_descriptor_response )
    {
        self->aecp_aem_descriptor_response->frame_sender = sender;
    }

    if( self->acmp_controller_state_machine )
    {
        self->acmp_controller_state_machine->frame_sender = sender;
    }

    if( self->acmp_listener_state_machine )
    {
        self->acmp_listener_state_machine->frame_sender = sender;
    }

    if( self->acmp_talker_state_machine )
    {
        self->acmp_talker_state_machine->frame_sender = sender;
    }

    if( self->adp_discovery_state_machine )
    {
        self->adp_discovery_state_machine->frame_sender = sender;
    }

    if( self->adp_advertise_entity_state_machine )
    {
        self->adp_advertise_entity_state_machine->frame_sender = sender;
    }

    if( self->adp_advertise_interface_state_machine )
    {
        self->adp_advertise_interface_state_machine->frame_sender = sender;
    }

    if( self->aem_entity_state_machine )
    {
        self->aem_entity_state_machine->frame_sender = sender;
    }

    if( self->maap_state_machine )
    {
        self->maap_state_machine->frame_sender = sender;
    }

}
