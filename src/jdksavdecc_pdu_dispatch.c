
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
    self->set_frame_sender = jdksavdecc_pdu_dispatch_set_frame_sender;
    self->unknown = jdksavdecc_pdu_dispatch_unknown;
    self->rx_frame = jdksavdecc_pdu_dispatch_rx_frame;
    self->avtpv0 = jdksavdecc_pdu_dispatch_avtpv0;
    self->acmpdu = jdksavdecc_pdu_dispatch_acmpdu;
    self->adpdu = jdksavdecc_pdu_dispatch_adpdu;
    self->aecpdu = jdksavdecc_pdu_dispatch_aecpdu;
    self->aecpdu_aem_command = jdksavdecc_pdu_dispatch_aecpdu_aem_command;
    self->aecpdu_aem_response = jdksavdecc_pdu_dispatch_aecpdu_aem_response;
    self->maap_state_machines = 0;
    self->acmp_state_machines = 0;
    self->adp_state_machines = 0;
    self->aecp_aa_command_state_machines = 0;
    self->aecp_aa_response_state_machines = 0;
    self->aecp_aem_command_state_machines = 0;
    self->aecp_aem_response_state_machines = 0;
    self->aecp_avc_command_state_machines = 0;
    self->aecp_avc_response_state_machines = 0;
    self->aecp_vendor_command_state_machines = 0;
    self->aecp_vendor_response_state_machines = 0;
    self->aecp_hdcp_apm_command_state_machines = 0;
    self->aecp_hdcp_apm_response_state_machines = 0;
}


void jdksavdecc_pdu_dispatch_tick( struct jdksavdecc_pdu_dispatch *self, jdksavdecc_microsecond_time timestamp )
{
    struct jdksavdecc_state_machines *sm = 0;
    
    sm = self->acmp_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }
    
    sm = self->adp_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_aa_command_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_aa_response_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_aem_command_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_aem_response_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_avc_command_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_avc_response_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_vendor_command_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_vendor_response_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_hdcp_apm_command_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }

    sm = self->aecp_hdcp_apm_response_state_machines;
    if( sm )
    {
        sm->base.tick( &sm->base, timestamp );
    }
    
}

void jdksavdecc_pdu_dispatch_set_frame_sender( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame_sender *sender )
{
    self->frame_sender = sender;
    if( self->aem_command_dispatch )
    {
        self->aem_command_dispatch->frame_sender = sender;
    }
    if( self->aem_response_dispatch )
    {
        self->aem_response_dispatch->frame_sender = sender;
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
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm = 0;

    sm = self->acmp_state_machines;
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_adpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm = 0;

    sm = self->adp_state_machines;
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
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

