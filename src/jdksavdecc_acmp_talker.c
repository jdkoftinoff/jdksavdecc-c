  
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
#include "jdksavdecc_acmp_talker.h"

int jdksavdecc_acmp_talker_state_machine_init(
        struct jdksavdecc_acmp_talker_state_machine *self,
        struct jdksavdecc_eui64 talker_entity_id,
        struct jdksavdecc_acmp_talker_stream_infos *talker_stream_infos,
        struct jdksavdecc_frame_sender *sender,
        uint32_t tag,
        void *additional
        )
{
    int r;

    jdksavdecc_state_machine_init(&self->base,sender,tag,additional);

    self->base.destroy = jdksavdecc_acmp_talker_state_machine_destroy;
    self->base.tick = jdksavdecc_acmp_talker_state_machine_tick;
    self->base.rx_frame = jdksavdecc_acmp_talker_state_machine_rx_frame;
    self->base.tx_frame = jdksavdecc_acmp_talker_state_machine_tx_frame;
    self->connect_talker = jdksavdecc_acmp_talker_state_machine_connect_talker;
    self->disconnect_talker = jdksavdecc_acmp_talker_state_machine_disconnect_talker;
    self->get_state = jdksavdecc_acmp_talker_state_machine_get_state;
    self->get_connection = jdksavdecc_acmp_talker_state_machine_get_connection;

    self->goto_waiting = jdksavdecc_acmp_talker_state_machine_goto_state_waiting;
    self->state_waiting = jdksavdecc_acmp_talker_state_machine_state_waiting;

    self->goto_connect = jdksavdecc_acmp_talker_state_machine_goto_state_connect;
    self->state_connect = jdksavdecc_acmp_talker_state_machine_state_connect;

    self->goto_disconnect = jdksavdecc_acmp_talker_state_machine_goto_state_disconnect;
    self->state_disconnect = jdksavdecc_acmp_talker_state_machine_state_disconnect;

    self->goto_get_connection = jdksavdecc_acmp_talker_state_machine_goto_state_get_connection;
    self->state_get_connection = jdksavdecc_acmp_talker_state_machine_state_get_connection;

    self->goto_get_state = jdksavdecc_acmp_talker_state_machine_goto_state_get_state;
    self->state_get_state = jdksavdecc_acmp_talker_state_machine_state_get_state;

    self->vars.do_terminate = 0;
    self->vars.my_id = talker_entity_id;

    self->vars.rcvd_connect_tx = 0;
    self->vars.rcvd_disconnect_tx = 0;
    self->vars.rcvd_get_tx_connection = 0;
    self->vars.rcvd_get_tx_state = 0;
    self->vars.talker_stream_infos = talker_stream_infos;

    self->goto_waiting( self );
    r=0;
    return r;
}


void jdksavdecc_acmp_talker_state_machine_destroy(
        struct jdksavdecc_state_machine *self_
        )
{
    struct jdksavdecc_acmp_talker_state_machine *self = (struct jdksavdecc_acmp_talker_state_machine *)self_;

    jdksavdecc_state_machine_destroy( &self->base );
    memset(self,0,sizeof(*self));
}

void jdksavdecc_acmp_talker_state_machine_tick(
        struct jdksavdecc_state_machine *self_,
        jdksavdecc_millisecond_time timestamp
        )
{
    struct jdksavdecc_acmp_talker_state_machine *self = (struct jdksavdecc_acmp_talker_state_machine *)self_;
    jdksavdecc_state_machine_tick(&self->base,timestamp);
}

ssize_t jdksavdecc_acmp_talker_state_machine_rx_frame(
        struct jdksavdecc_state_machine *self_,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        )
{
    ssize_t r=0;
    struct jdksavdecc_acmp_talker_state_machine *self = (struct jdksavdecc_acmp_talker_state_machine *)self_;

    // Make sure this packet has the correct ethertype and multicast mac address
    if( rx_frame->ethertype == JDKSAVDECC_AVTP_ETHERTYPE
            && jdksavdecc_eui48_compare(&jdksavdecc_multicast_adp_acmp,&rx_frame->dest_address)==0 )
    {
        // Make sure this packet has the appropriate ACMP subtype and header and talker entity id.
        struct jdksavdecc_acmpdu_common_control_header header;
        r=jdksavdecc_acmpdu_common_control_header_read(&header,rx_frame->payload,pos,rx_frame->length);

        if( r>0
                && header.cd == 1
                && header.subtype == JDKSAVDECC_SUBTYPE_ACMP
                && header.version == 0
                && header.status == JDKSAVDECC_ACMP_STATUS_SUCCESS )
        {
            // Okay, read the entire acmpdu into rcvd_cmd_resp
            struct jdksavdecc_acmpdu *acmpdu = &self->vars.rcvd_cmd_resp;
            r=jdksavdecc_acmpdu_read(acmpdu,rx_frame->payload,pos,rx_frame->length);

            // If the message type is one of the few we care about, then parse the frame and set the appropriate flags.
            if( r>0 && jdksavdecc_eui64_compare(&self->vars.my_id, &acmpdu->talker_entity_id )==0 )
            {
                switch( acmpdu->header.message_type )
                {
                case JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_COMMAND:
                    self->vars.rcvd_connect_tx = 1;
                    break;
                case JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_COMMAND:
                    self->vars.rcvd_disconnect_tx = 1;
                    break;
                case JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_COMMAND:
                    self->vars.rcvd_get_tx_state = 1;
                    break;
                case JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_COMMAND:
                    self->vars.rcvd_get_tx_connection = 1;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return r;
}

void jdksavdecc_acmp_talker_state_machine_tx_frame(
        struct jdksavdecc_state_machine *self_,
        struct jdksavdecc_frame const *frame
        )
{
    struct jdksavdecc_acmp_talker_state_machine *self = (struct jdksavdecc_acmp_talker_state_machine *)self_;
    jdksavdecc_state_machine_tx_frame(&self->base,frame);
}

/// See Clause 8.2.2.6.2.1
uint8_t jdksavdecc_acmp_talker_state_machine_valid_talker_unique(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint16_t talker_unique_id
        )
{
    /* Override this method to validate the unique_id */
    (void)self;
    (void)talker_unique_id;
    return JDKSAVDECC_ACMP_STATUS_SUCCESS;
}

/// See Clause 8.2.2.6.2.2
uint8_t jdksavdecc_acmp_talker_state_machine_connect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        )
{
    /* Override this method to actually cause talker to connect */
    return JDKSAVDECC_ACMP_STATUS_SUCCESS;
}

/// See Clause 8.2.2.6.2.3
uint8_t jdksavdecc_acmp_talker_state_machine_tx_response(
        struct jdksavdecc_acmp_talker_state_machine *self,
        uint8_t message_type,
        jdksavdecc_acmp_command_response const *respone,
        uint8_t error
        );

/// See Clause 8.2.2.6.2.4
uint8_t jdksavdecc_acmp_talker_state_machine_disconnect_talker(
        struct jdksavdecc_acmp_talker_state_machine *self,
        jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.5
uint8_t jdksavdecc_acmp_talker_state_machine_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self,
        jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.5
uint8_t jdksavdecc_acmp_talker_state_machine_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self,
        jdksavdecc_acmp_command_response *response,
        struct jdksavdecc_acmpdu const *command
        );

/// See Clause 8.2.2.6.2.6
void jdksavdecc_acmp_talker_state_machine_goto_state_waiting(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    self->vars.rcvd_connect_tx = 0;
    self->vars.rcvd_disconnect_tx = 0;
    self->vars.rcvd_get_tx_state = 0;
    self->vars.rcvd_get_tx_connection = 0;
    self->state = self->state_waiting;
}


/// See Clause 8.2.2.6.2.6
void jdksavdecc_acmp_talker_state_machine_state_waiting(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    if( self->vars.do_terminate )
    {
        self->state = 0;
    }
    else if((self->vars.rcvd_connect_tx==1)
            && (jdksavdecc_eui64_compare( &self->vars.my_id, &self->vars.rcvd_cmd_resp.talker_entity_id)==0 ))
    {
        self->goto_connect(self);
    }
    else if((self->vars.rcvd_disconnect_tx==1)
            && (jdksavdecc_eui64_compare( &self->vars.my_id, &self->vars.rcvd_cmd_resp.talker_entity_id)==0 ))
    {
        self->goto_disconnect(self);
    }
    else if((self->vars.rcvd_get_tx_state==1)
            && (jdksavdecc_eui64_compare( &self->vars.my_id, &self->vars.rcvd_cmd_resp.talker_entity_id)==0 ))
    {
        self->goto_get_state(self);
    }
    else if((self->vars.rcvd_get_tx_connection==1)
            && (jdksavdecc_eui64_compare( &self->vars.my_id, &self->vars.rcvd_cmd_resp.talker_entity_id)==0 ))
    {
        self->goto_get_connection(self);
    }
    else if(
            (self->vars.rcvd_connect_tx
            || self->vars.rcvd_disconnect_tx
            || self->vars.rcvd_get_tx_state
            || self->vars.rcvd_get_tx_connection)
            && jdksavdecc_eui64_compare( &self->vars.my_id, &self->vars.rcvd_cmd_resp.talker_entity_id)!=0)
    {
        self->goto_waiting( self );
    }

}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_connect(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    uint16_t error;

    error = self->valid_talker_unique( self, self->vars.rcvd_cmd_resp.talker_unique_id );

    if( error == JDKSAVDECC_ACMP_STATUS_SUCCESS )
    {
        error = self->connect_talker( self, &self->vars.rcvd_cmd_resp, &self->vars.rcvd_cmd_resp );
    }

    self->tx_response( self, JDKSAVDECC_ACMP_MESSAGE_TYPE_CONNECT_TX_RESPONSE, &self->vars.rcvd_cmd_resp, error );
    
    self->state = self->state_connect;
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_connect(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    self->goto_waiting( self );
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_disconnect(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    uint16_t error;
    error = self->valid_talker_unique( self, self->vars.rcvd_cmd_resp.talker_unique_id );

    if( error == JDKSAVDECC_ACMP_STATUS_SUCCESS )
    {
        error = self->disconnect_talker( self, &self->vars.rcvd_cmd_resp, &self->vars.rcvd_cmd_resp );
    }

    self->tx_response( self, JDKSAVDECC_ACMP_MESSAGE_TYPE_DISCONNECT_TX_RESPONSE, &self->vars.rcvd_cmd_resp, error );
    
    self->state = self->state_disconnect;
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_disconnect(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    self->goto_waiting( self );
}
        

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    uint16_t error;
    error = self->valid_talker_unique( self, self->vars.rcvd_cmd_resp.talker_unique_id );

    if( error == JDKSAVDECC_ACMP_STATUS_SUCCESS )
    {
        error = self->disconnect_talker( self, &self->vars.rcvd_cmd_resp, &self->vars.rcvd_cmd_resp );
    }

    self->tx_response( self, JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_STATE_RESPONSE, &self->vars.rcvd_cmd_resp, error );
    
    self->state = self->state_disconnect;    
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_get_state(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    self->goto_waiting( self );
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_goto_state_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    uint16_t error;
    error = self->valid_talker_unique( self, self->vars.rcvd_cmd_resp.talker_unique_id );

    if( error == JDKSAVDECC_ACMP_STATUS_SUCCESS )
    {
        error = self->get_connection( self, &self->vars.rcvd_cmd_resp, &self->vars.rcvd_cmd_resp );
    }

    self->tx_response( self, JDKSAVDECC_ACMP_MESSAGE_TYPE_GET_TX_CONNECTION_RESPONSE, &self->vars.rcvd_cmd_resp, error );

    self->state = self->state_get_connection;
}

/// See Clause 8.2.2.6.3
void jdksavdecc_acmp_talker_state_machine_state_get_connection(
        struct jdksavdecc_acmp_talker_state_machine *self
        )
{
    self->goto_waiting( self );
}
