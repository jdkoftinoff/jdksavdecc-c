
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
#include "jdksavdecc_pdu_dispatch.h"
#include "jdksavdecc_adp_discover.h"
#include "jdksavdecc_adp_advertise.h"
#include "jdksavdecc_acmp_controller.h"
#include "jdksavdecc_acmp_listener.h"
#include "jdksavdecc_acmp_talker.h"
#include "jdksavdecc_maap.h"
#include "jdksavdecc_aem_entity.h"

void jdksavdecc_pdu_dispatch_init( struct jdksavdecc_pdu_dispatch *self )
{
    memset( self, 0, sizeof(*self) );
    self->tick = jdksavdecc_pdu_dispatch_tick;
    self->unknown = jdksavdecc_pdu_dispatch_unknown;
    self->rx_frame = jdksavdecc_pdu_dispatch_rx_frame;
    self->avtpv0 = jdksavdecc_pdu_dispatch_avtpv0;
    self->acmpdu = jdksavdecc_pdu_dispatch_acmpdu;
    self->adpdu = jdksavdecc_pdu_dispatch_adpdu;
    self->aecpdu = jdksavdecc_pdu_dispatch_aecpdu;
    self->aecpdu_aem_command = jdksavdecc_pdu_dispatch_aecpdu_aem_command;
    self->aecpdu_aem_response = jdksavdecc_pdu_dispatch_aecpdu_aem_response;
}


void jdksavdecc_pdu_dispatch_tick( struct jdksavdecc_pdu_dispatch *self, jdksavdecc_time timestamp )
{
    if( self->state_machines )
    {
        self->state_machines->tick( self->state_machines, timestamp );
    }
}

ssize_t jdksavdecc_pdu_dispatch_unknown( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    (void)self;
    (void)frame;
    (void)pos;
    return 0;
}

ssize_t jdksavdecc_pdu_dispatch_rx_frame( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;

    // Accept the AVTP ethertype only
    if( frame->ethertype == JDKSAVDECC_AVTP_ETHERTYPE )
    {
        // Accept control PDU's only
        if( jdksavdecc_common_control_header_get_cd(frame->payload,pos)==1 )
        {
            uint8_t version = jdksavdecc_common_control_header_get_version(frame->payload,pos);
            if( self->avtpv0 && version==0 )
            {
                // Accept version 0 if we have an avtpv0 proc
                r=self->avtpv0( self, frame, pos );
            }
            else if( self->avtpv1 && version==1 )
            {
                // Accept version 1 if we have an avtpv1 proc
                r=self->avtpv1( self, frame, pos );
            }
        }
    }

    // If no handler was found, then call the unknown proc
    if( r==0 && self->unknown )
    {
        r=self->unknown( self, frame, pos );
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_avtpv0( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;

    // Get the subtype
    uint8_t subtype = jdksavdecc_common_control_header_get_subtype( frame->payload, pos );

    switch( subtype )
    {
    case JDKSAVDECC_SUBTYPE_ADP:
        if( self->adpdu )
        {
            r=self->adpdu( self, frame, pos );
        }
        break;
    case JDKSAVDECC_SUBTYPE_AECP:
        if( self->aecpdu )
        {
            r=self->aecpdu( self, frame, pos );
        }
        break;
    case JDKSAVDECC_SUBTYPE_ACMP:
        if( self->acmpdu )
        {
            r=self->acmpdu( self, frame, pos );
        }
        break;
    case JDKSAVDECC_SUBTYPE_MAAP:
        if( self->maap )
        {
            r=self->maap( self, frame, pos );
        }
        break;
    }

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_acmpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t rt=0;
    ssize_t rl=0;
    ssize_t rc=0;
    ssize_t r=0;

    if( self->state_machines )
    {
        if( self->state_machines->acmp_talker_state_machine )
        {
            rt = self->state_machines->acmp_talker_state_machine->rx_frame( self->state_machines->acmp_talker_state_machine, frame, pos );
        }
        if( self->state_machines->acmp_listener_state_machine )
        {
            rl = self->state_machines->acmp_listener_state_machine->rx_frame( self->state_machines->acmp_listener_state_machine, frame, pos );
        }
        if( self->state_machines->acmp_controller_state_machine )
        {
            rc = self->state_machines->acmp_controller_state_machine->rx_frame( self->state_machines->acmp_controller_state_machine, frame, pos );
        }
    }
    if( rt<0 || rl<0 || rc<0 )
    {
        r=-1;
    }
    if( rt>0 || rl>0 || rc>0 )
    {
        r=frame->length;
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_adpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    ssize_t rae=0;
    ssize_t rai=0;
    ssize_t rd=0;

    if( self->state_machines )
    {
        if( self->state_machines->adp_advertise_entity_state_machine )
        {
            rae=self->state_machines->adp_advertise_entity_state_machine->rx_frame( self->state_machines->adp_advertise_entity_state_machine, frame, pos );
        }
        if( self->state_machines->adp_advertise_interface_state_machine )
        {
            rai=self->state_machines->adp_advertise_interface_state_machine->rx_frame( self->state_machines->adp_advertise_interface_state_machine, frame, pos );
        }
        if( self->state_machines->adp_discovery_state_machine )
        {
            rd=self->state_machines->adp_discovery_state_machine->rx_frame( self->state_machines->adp_discovery_state_machine, frame, pos );
        }
    }

    if( rae<0 || rai<0 || rd<0 )
    {
        r=-1;
    }
    if( rae>0 || rai>0 || rd>0 )
    {
        r=frame->length;
    }
    return r;
}


ssize_t jdksavdecc_pdu_dispatch_aecpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    uint8_t message_type = jdksavdecc_common_control_header_get_control_data(frame->payload, pos );
    switch( message_type )
    {
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_COMMAND:
        if( self->aecpdu_aem_command )
        {
            r=self->aecpdu_aem_command( self, frame, pos );
        }
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE:
        if( self->aecpdu_aem_response )
        {
            r=self->aecpdu_aem_response( self, frame, pos );
        }
        break;

    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_COMMAND:
        if( self->aecpdu_aa_command )
        {
            r=self->aecpdu_aa_command( self, frame, pos );
        }
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_ADDRESS_ACCESS_RESPONSE:
        if( self->aecpdu_aa_response )
        {
            r=self->aecpdu_aa_response( self, frame, pos );
        }
        break;

    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_COMMAND:
        if( self->aecpdu_avc_command )
        {
            r=self->aecpdu_avc_command( self, frame, pos );
        }
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_AVC_RESPONSE:
        if( self->aecpdu_avc_response )
        {
            r=self->aecpdu_avc_response( self, frame, pos );
        }
        break;

    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_COMMAND:
        if( self->aecpdu_vendor_command )
        {
            r=self->aecpdu_vendor_command( self, frame, pos );
        }
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_VENDOR_UNIQUE_RESPONSE:
        if( self->aecpdu_vendor_response )
        {
            r=self->aecpdu_vendor_response( self, frame, pos );
        }
        break;


    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_COMMAND:
        if( self->aecpdu_hdcp_apm_command )
        {
            r=self->aecpdu_hdcp_apm_command( self, frame, pos );
        }
        break;
    case JDKSAVDECC_AECP_MESSAGE_TYPE_HDCP_APM_RESPONSE:
        if( self->aecpdu_hdcp_apm_response)
        {
            r=self->aecpdu_hdcp_apm_response( self, frame, pos );
        }
        break;
    default:
        r=0;
    }

    return r;
}


ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem_command(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    if( self->aem_command_dispatch )
    {
        r=self->aem_command_dispatch->rx_frame( self->aem_command_dispatch, frame, pos );
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    if( self->aem_response_dispatch )
    {
        r=self->aem_response_dispatch->rx_frame( self->aem_response_dispatch, frame, pos );
    }
    return r;
}

