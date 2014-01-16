
/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
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
#include "jdksavdecc_adp_manager.h"

/// Form the entity available message and send it
static void jdksavdecc_adp_manager_send_entity_available( struct jdksavdecc_adp_manager *self );

/// Form the entity departing message and send it
static void jdksavdecc_adp_manager_send_entity_departing( struct jdksavdecc_adp_manager *self );

/// Form the entity discover message and send it
static void jdksavdecc_adp_manager_send_entity_discover( struct jdksavdecc_adp_manager *self );


bool jdksavdecc_adp_manager_init(
    struct jdksavdecc_adp_manager *self,
    void *context,
    void (*frame_send)(
        struct jdksavdecc_adp_manager *self,
        void *context,
        uint8_t const *buf,
        uint16_t len ),
    void (*received_entity_available_or_departing)(
        struct jdksavdecc_adp_manager *self,
        void *context,
        struct jdksavdecc_adpdu *adpdu )
    ) {
    self->last_time_in_ms = 0;
    self->early_tick = true;
    self->do_send_entity_available = true;
    self->do_send_entity_departing = false;
    self->do_send_entity_discover = false;
    self->context = context;
    self->frame_send = frame_send;
    self->received_entity_available_or_departing = received_entity_available_or_departing;
    self->stopped = false;

    memset(&self->adpdu, 0, sizeof(self->adpdu));
    self->adpdu.header.cd = 1;
    self->adpdu.header.subtype = JDKSAVDECC_SUBTYPE_ADP;
    self->adpdu.header.version = 0;
    self->adpdu.header.sv = 0;
    self->adpdu.header.message_type = JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_AVAILABLE;
    self->adpdu.header.valid_time = 10;
    self->adpdu.header.control_data_length = JDKSAVDECC_ADPDU_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN;

    return true;
}

void jdksavdecc_adp_manager_destroy(
    struct jdksavdecc_adp_manager *self ) {
    (void)self;
}

bool jdksavdecc_adp_manager_receive(
    struct jdksavdecc_adp_manager *self,
    uint64_t time_in_milliseconds,
    uint8_t const *buf,
    uint16_t len ) {
    struct jdksavdecc_adpdu incoming;
    bool r=false;
    (void)time_in_milliseconds;
    if( jdksavdecc_adpdu_read(&incoming, buf, 0, len)>0 ) {
        r=true;
        switch(incoming.header.message_type) {
        case JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DISCOVER:
            // only respond to discover messages if we are not stopped
            if( !self->stopped ) {
                // handle the case where the discover message references our entity id or 0
                if( jdksavdecc_eui64_compare(&incoming.header.entity_id, &self->adpdu.header.entity_id )
                    || jdksavdecc_eui64_convert_to_uint64(&incoming.header.entity_id)==0 ) {
                    self->do_send_entity_available = true;
                    self->early_tick = true;
                }
            }
            break;
        case JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_AVAILABLE:
            // only handle incoming available messages if we have a place to give them to
            if( self->received_entity_available_or_departing ) {
                self->received_entity_available_or_departing( self, self->context, &incoming );
            }
            break;
        case JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DEPARTING:
            // only handle incoming departing messages if we have a place to give them to
            if( self->received_entity_available_or_departing ) {
                self->received_entity_available_or_departing( self, self->context, &incoming );
            }
            break;
        default:
            break;
        }
    }
    return r;
}

void jdksavdecc_adp_manager_tick(
    struct jdksavdecc_adp_manager *self,
    uint64_t cur_time_in_ms ) {

    // calculate the time since the last send
    uint64_t difftime = cur_time_in_ms - self->last_time_in_ms;

    uint64_t valid_time_in_ms = self->adpdu.header.valid_time;

    // calculate the time in milliseconds between sends.
    // header.valid_time is in 2 second increments. We are to send
    // 4 available messages per valid_time.
    valid_time_in_ms = (valid_time_in_ms*1000) / 2;

    // limit it to be at most one send per second
    if( valid_time_in_ms <1000 ) {
        valid_time_in_ms = 1000;
    }

    // clear any early tick flag
    self->early_tick = false;

    // only send messages available/departing messages if we are not stopped
    
    if( !self->stopped ) {
        if( ( difftime > valid_time_in_ms )
            || (self->do_send_entity_available || self->do_send_entity_departing) ) {

            // are we departing?
            if( self->do_send_entity_departing ) {

                // yes, we are sending an entity departing message.
                // clear any do_send flags

                self->do_send_entity_departing = false;
                self->do_send_entity_available = false;

                // change into pause state

                self->stopped = true;

                // record the time we send it

                self->last_time_in_ms = cur_time_in_ms;

                // send the departing

                jdksavdecc_adp_manager_send_entity_departing(self);

                // reset the available_index to 0

                self->adpdu.available_index = 0;
            } else if( self->do_send_entity_available ) {

                // we are to send entity available message
                // clear the request flag

                self->do_send_entity_available = false;

                // record the time we send it

                self->last_time_in_ms = cur_time_in_ms;

                // send the available

                jdksavdecc_adp_manager_send_entity_available(self);
            }
        }
    }

    // are we asked to send an entity discover message?

    if( self->do_send_entity_discover ) {

        // yes, clear the flag and send it

        self->do_send_entity_discover = false;
        jdksavdecc_adp_manager_send_entity_discover(self);
    }
}

void jdksavdecc_adp_manager_trigger_send_discover(
    struct jdksavdecc_adp_manager *self ) {

    self->early_tick = true;
    self->do_send_entity_discover = true;
}

void jdksavdecc_adp_manager_trigger_send_available(
    struct jdksavdecc_adp_manager *self ) {
    self->early_tick = true;
    self->do_send_entity_available = true;
    self->stopped = false;
}

void jdksavdecc_adp_manager_trigger_send_departing(
    struct jdksavdecc_adp_manager *self ) {
    self->early_tick = true;
    self->do_send_entity_departing = true;
}


static void jdksavdecc_adp_manager_send_entity_available( struct jdksavdecc_adp_manager *self ) {
    uint8_t buf[128];
    ssize_t len;
    self->adpdu.header.message_type = JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_AVAILABLE;
    len = jdksavdecc_adpdu_write(&self->adpdu, buf, 0, sizeof(buf) );

    if( len>0 ) {
        self->frame_send( self, self->context, buf, (uint16_t)len );
        self->adpdu.available_index++;
    }
}


static void jdksavdecc_adp_manager_send_entity_departing( struct jdksavdecc_adp_manager *self ) {
    uint8_t buf[128];
    ssize_t len;
    self->adpdu.header.message_type = JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DEPARTING;
    len = jdksavdecc_adpdu_write(&self->adpdu, buf, 0, sizeof(buf) );

    if( len>0 ) {
        self->frame_send( self, self->context, buf, (uint16_t)len );
        self->adpdu.available_index++;
    }
}

static void jdksavdecc_adp_manager_send_entity_discover( struct jdksavdecc_adp_manager *self ) {
    uint8_t buf[128];
    ssize_t len;
    struct jdksavdecc_adpdu adpdu;
    memset( &adpdu, 0, sizeof(adpdu) );
    adpdu.header.cd = 1;
    adpdu.header.subtype = JDKSAVDECC_SUBTYPE_ADP;
    adpdu.header.control_data_length = JDKSAVDECC_ADPDU_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN;
    adpdu.header.message_type = JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DISCOVER;
    adpdu.header.sv = 0;
    adpdu.header.version = 0;
    adpdu.header.valid_time = 0;
    jdksavdecc_eui64_init_from_uint64(&adpdu.header.entity_id, 0 );

    len = jdksavdecc_adpdu_write(&adpdu, buf, 0, sizeof(buf) );

    if( len>0 ) {
        self->frame_send( self, self->context, buf, (uint16_t)len );
        self->adpdu.available_index++;
    }
}



