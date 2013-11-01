
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
    self->base.tick = jdksavdecc_pdu_dispatch_tick;
    self->set_frame_sender = jdksavdecc_pdu_dispatch_set_frame_sender;
    self->unknown = jdksavdecc_pdu_dispatch_unknown;
    self->rx_frame = jdksavdecc_pdu_dispatch_rx_frame;
    self->avtpv0 = jdksavdecc_pdu_dispatch_avtpv0;
    self->maap = jdksavdecc_pdu_dispatch_maap;
    self->acmpdu = jdksavdecc_pdu_dispatch_acmpdu;
    self->adpdu = jdksavdecc_pdu_dispatch_adpdu;
    self->aecpdu = jdksavdecc_pdu_dispatch_aecpdu;
    self->aecpdu_aem_command = jdksavdecc_pdu_dispatch_aecpdu_aem_command;
    self->aecpdu_aem_response = jdksavdecc_pdu_dispatch_aecpdu_aem_response;
    self->aecpdu_aa_command = jdksavdecc_pdu_dispatch_aecpdu_aa_command;
    self->aecpdu_aa_response = jdksavdecc_pdu_dispatch_aecpdu_aa_response;
    self->aecpdu_vendor_command = jdksavdecc_pdu_dispatch_aecpdu_vendor_command;
    self->aecpdu_vendor_response = jdksavdecc_pdu_dispatch_aecpdu_vendor_response;
    self->aecpdu_avc_command = jdksavdecc_pdu_dispatch_aecpdu_avc_command;
    self->aecpdu_avc_response = jdksavdecc_pdu_dispatch_aecpdu_avc_response;
    self->aecpdu_avc_command = jdksavdecc_pdu_dispatch_aecpdu_hdcp_apm_command;
    self->aecpdu_avc_response = jdksavdecc_pdu_dispatch_aecpdu_hdcp_apm_response;

}


int jdksavdecc_pdu_dispatch_tick( struct jdksavdecc_state_machine *self_, jdksavdecc_timestamp_in_microseconds timestamp )
{
    struct jdksavdecc_pdu_dispatch *self = (struct jdksavdecc_pdu_dispatch *)self_;
    
    struct jdksavdecc_state_machines *sms[] =
    {
        self->maap_state_machines,
        self->acmp_talker_state_machines,
        self->acmp_listener_state_machines,
        self->acmp_controller_state_machines,
        self->adp_advertiser_state_machines,
        self->adp_discovery_state_machines,
        self->aecp_aa_controller_state_machines,
        self->aecp_aa_responder_state_machines,
        self->aecp_aem_controller_state_machines,
        self->aecp_aem_responder_state_machines,
        self->aecp_avc_controller_state_machines,
        self->aecp_avc_responder_state_machines,
        self->aecp_hdcp_apm_controller_state_machines,
        self->aecp_hdcp_apm_responder_state_machines
    };
    unsigned int i;
    
    for( i=0; i<sizeof(sms)/sizeof(*sms); ++i )
    {
        if( sms[i] )
        {
            sms[i]->base.tick( &sms[i]->base, timestamp );
        }
    }
    return 0;
}

void jdksavdecc_pdu_dispatch_set_frame_sender( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame_sender *sender )
{
    struct jdksavdecc_state_machines *sms[] =
    {
        self->maap_state_machines,
        self->acmp_talker_state_machines,
        self->acmp_listener_state_machines,
        self->acmp_controller_state_machines,
        self->adp_advertiser_state_machines,
        self->adp_discovery_state_machines,
        self->aecp_aa_controller_state_machines,
        self->aecp_aa_responder_state_machines,
        self->aecp_aem_controller_state_machines,
        self->aecp_aem_responder_state_machines,
        self->aecp_avc_controller_state_machines,
        self->aecp_avc_responder_state_machines,
        self->aecp_hdcp_apm_controller_state_machines,
        self->aecp_hdcp_apm_responder_state_machines
    };
    unsigned int i;
    
    self->base.frame_sender = sender;
    
    for( i=0; i<sizeof(sms)/sizeof(*sms); ++i )
    {
        if( sms[i] )
        {
            sms[i]->base.frame_sender = sender;
        }
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

    // If no handler was found or the handler returned 0, then call the unknown proc
    if( r==0 && self->unknown )
    {
        r=self->unknown( self, frame, pos );
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_avtpv0( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;

    // handle control frame
    uint8_t cd = jdksavdecc_common_control_header_get_cd( frame->payload, pos );
    
    // Get the subtype
    uint8_t subtype = jdksavdecc_common_control_header_get_subtype( frame->payload, pos );

    // handle control frames
    if( cd==1 )
    {
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
    }
    else
    {
        // handle data frames
        switch( subtype )
        {
        case JDKSAVDECC_SUBTYPE_61883_IIDC:
            break;
        case JDKSAVDECC_SUBTYPE_AVTP_AUDIO:
            break;
        case JDKSAVDECC_SUBTYPE_AVTP_VIDEO:
            break;
        case JDKSAVDECC_SUBTYPE_AVTP_CONTROL:
            break;
        }
        
    }
    

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_maap( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    unsigned int i;
    struct jdksavdecc_state_machines *sms[] =
    {
        self->maap_state_machines
    };

    for( i=0; i<sizeof(sms)/sizeof(*sms); ++i )
    {
        if( sms[i] )
        {
            ssize_t lr = sms[i]->base.rx_frame( &sms[i]->base, frame, pos );
            if( lr>0 )
            {
                r=lr;
            }
        }
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_acmpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    unsigned int i;
    struct jdksavdecc_state_machines *sms[] =
    {
        self->acmp_talker_state_machines,
        self->acmp_listener_state_machines,
        self->acmp_controller_state_machines
    };

    for( i=0; i<sizeof(sms)/sizeof(*sms); ++i )
    {
        if( sms[i] )
        {
            ssize_t lr = sms[i]->base.rx_frame( &sms[i]->base, frame, pos );
            if( lr>0 )
            {
                r=lr;
            }
        }
    }
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_adpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos )
{
    ssize_t r=0;
    unsigned int i;
    struct jdksavdecc_state_machines *sms[] =
    {
        self->adp_advertiser_state_machines,
        self->adp_discovery_state_machines
    };

    for( i=0; i<sizeof(sms)/sizeof(*sms); ++i )
    {
        if( sms[i] )
        {
            ssize_t lr = sms[i]->base.rx_frame( &sms[i]->base, frame, pos );
            if( lr>0 )
            {
                r=lr;
            }
        }
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
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_aem_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    sm = self->aecp_aem_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }
    
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_aem_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    sm = self->aecp_aem_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }
    
    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_aa_command(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_aa_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_aa_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_aa_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}


ssize_t jdksavdecc_pdu_dispatch_aecpdu_avc_command(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_avc_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_avc_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_avc_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}


ssize_t jdksavdecc_pdu_dispatch_aecpdu_vendor_command(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_vendor_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_vendor_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_vendor_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}


ssize_t jdksavdecc_pdu_dispatch_aecpdu_hdcp_apm_command(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_hdcp_apm_responder_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}

ssize_t jdksavdecc_pdu_dispatch_aecpdu_hdcp_apm_response(struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos)
{
    ssize_t r=0;
    struct jdksavdecc_state_machines *sm;
    
    sm = self->aecp_hdcp_apm_controller_state_machines;
    
    if( sm )
    {
        r = sm->base.rx_frame( &sm->base, frame, pos );
    }

    return r;
}


