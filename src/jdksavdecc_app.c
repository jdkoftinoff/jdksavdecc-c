
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
#include "jdksavdecc_app.h"

ssize_t jdksavdecc_appdu_read( struct jdksavdecc_appdu *p, void const *base, ssize_t pos, size_t len )
{
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_APPDU_HEADER_LEN );
    // clear the structure
    memset( p, 0, sizeof( *p ) );
    if ( r >= 0 )
    {
        p->version = jdksavdecc_uint8_get( base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION );
        if ( p->version == JDKSAVDECC_APPDU_VERSION )
        {
            p->message_type = jdksavdecc_uint8_get( base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE );

            if ( p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC
                 || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR )
            {

                p->payload_length = jdksavdecc_uint16_get( base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH );
                p->address = jdksavdecc_eui48_get( base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS );
                p->reserved = jdksavdecc_uint16_get( base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED );

                // make sure that the payload_length is a reasonable number
                if ( p->payload_length <= JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH )
                {
                    // make sure we have enough data in the incoming buffer for the entire payload
                    r = jdksavdecc_validate_range( pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, len, p->payload_length );

                    if ( r >= 0 )
                    {
                        // The payload is complete.
                        // Make payload pointer point directly within incoming raw buffer
                        p->payload = ( (uint8_t *)base ) + JDKSAVDECC_APPDU_OFFSET_PAYLOAD;
                    }
                    else
                    {
                        // the raw buffer is incomplete.
                        p->payload = 0;
                        r = JDKSAVDECC_APPDU_ERROR_PAYLOAD_INCOMPLETE;
                    }
                }
                else
                {
                    // The payload_length field is out of range.
                    r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
                }
            }
            else
            {
                // The message type is unrecognized.
                r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
            }
        }
        else
        {
            // The protocol version is unsupported
            r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
        }
    }
    return r;
}

ssize_t jdksavdecc_appdu_write( struct jdksavdecc_appdu const *p, void *base, size_t pos, size_t len )
{
    ssize_t r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_APPDU_HEADER_LEN );
    if ( r >= 0 )
    {
        jdksavdecc_uint8_set( p->version, base, pos + JDKSAVDECC_APPDU_OFFSET_VERSION );
        if ( p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC
             || p->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR )
        {

            jdksavdecc_uint8_set( p->message_type, base, pos + JDKSAVDECC_APPDU_OFFSET_MESSAGE_TYPE );
            jdksavdecc_uint16_set( p->payload_length, base, pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD_LENGTH );
            jdksavdecc_eui48_set( p->address, base, pos + JDKSAVDECC_APPDU_OFFSET_ADDRESS );
            jdksavdecc_uint16_set( p->reserved, base, pos + JDKSAVDECC_APPDU_OFFSET_RESERVED );
            if ( p->payload_length > 0 )
            {
                if ( p->payload && p->payload_length <= JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH )
                {
                    // We have a payload and the payload length is non zero, make sure we have space in the output buffer
                    r = jdksavdecc_validate_range( pos, len, JDKSAVDECC_APPDU_OFFSET_PAYLOAD + p->payload_length );
                    if ( r > 0 )
                    {
                        // we have space so copy it over
                        memcpy( ( (uint8_t *)base ) + pos + JDKSAVDECC_APPDU_OFFSET_PAYLOAD, p->payload, p->payload_length );
                    }
                    else
                    {
                        // we don't have space, so return error
                        r = JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT;
                    }
                }
                else
                {
                    // we have payload length but no payload? that is invalid.
                    r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
                }
            }
        }
        else
        {
            // The message type is unrecognized.
            r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;
        }
    }
    return r;
}

#if JDKSAVDECC_ENABLE_MICROSUPPORT == 1

ssize_t jdksavdecc_appdu_parse_buffer( struct jdksavdecc_appdu *self, us_buffer_t *buffer )
{
    ssize_t r = JDKSAVDECC_APPDU_ERROR_BUFFER_LENGTH_INSUFFICIENT;
    // store the current buffer position in case parsing fails
    size_t pos = buffer->m_next_out;

    // is there enough bytes in the buffer for a full appdu heade?
    if ( us_buffer_readable_count( buffer ) >= 12 )
    {

        // now validate the header
        r = JDKSAVDECC_APPDU_ERROR_INVALID_HEADER;

        // extract version
        self->version = us_buffer_read_byte( buffer );

        // validate version
        if ( self->version == JDKSAVDECC_APPDU_VERSION )
        {

            // extract message_type
            self->message_type = us_buffer_read_byte( buffer );

            // validate message_type
            if ( self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC
                 || self->message_type == JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR )
            {

                size_t cnt = 0;

                // read the payload length field
                if ( us_buffer_read_uint16( buffer, &self->payload_length ) )
                {

                    // validate the payload length is sane
                    if ( self->payload_length <= JDKSAVDECC_APPDU_MAX_PAYLOAD_LENGTH )
                    {

                        // read the 6 byte address field
                        us_buffer_read_data( buffer, self->address.value, 6, &cnt );
                        if ( cnt == 6 )
                        {

                            // read the reserved field
                            if ( us_buffer_read_uint16( buffer, &self->reserved ) )
                            {

                                // check to see if the buffer contains all the required payload data
                                r = JDKSAVDECC_APPDU_ERROR_PAYLOAD_INCOMPLETE;

                                // apparently it has the data
                                if ( us_buffer_readable_count( buffer ) >= self->payload_length )
                                {

                                    // read the data into the payload buffer
                                    us_buffer_read_data( buffer, self->payload, self->payload_length, &cnt );

                                    if ( cnt == self->payload_length )
                                    {

                                        // success reading! return how many bytes in total were parsed
                                        r = JDKSAVDECC_APPDU_HEADER_LEN + self->payload_length;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if ( r < 0 )
    {
        // parsing failed, rewind the buffer
        buffer->m_next_out = pos;
    }
    return r;
}

ssize_t jdksavdecc_appdu_flatten_to_buffer( struct jdksavdecc_appdu const *self, us_buffer_t *buffer ) { return 0; }

#endif

/** Extract a 64 bit entity_id from the payload */
bool jdksavdecc_appdu_get_entity_id_from_payload( struct jdksavdecc_appdu const *self, struct jdksavdecc_eui64 *result )
{
    bool r = false;

    if ( jdksavdecc_eui64_read( result, self->payload, 0, self->payload_length ) > 0 )
    {
        r = true;
    }
    return r;
}

/** Create and flatten a NOP message - See Annex C.5.1.1 */
bool jdksavdecc_appdu_set_nop( struct jdksavdecc_appdu *self )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_NOP;
    self->payload_length = 0;
    jdksavdecc_eui48_init( &self->address );
    self->reserved = 0;
    return true;
}

/** Create an ENTITY_ID_REQUEST message - See Annex C.5.1.2 */
bool jdksavdecc_appdu_set_entity_id_request( struct jdksavdecc_appdu *self,
                                             struct jdksavdecc_eui48 apc_primary_mac,
                                             struct jdksavdecc_eui64 entity_id )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_REQUEST;
    self->payload_length = 8;
    self->address = apc_primary_mac;
    self->reserved = 0;
    jdksavdecc_eui64_set( entity_id, self->payload, 0 );
    return true;
}

/** Create an ENTITY_ID_RESPONSE message - See Annex C.5.1.3 */
bool jdksavdecc_appdu_set_entity_id_response( struct jdksavdecc_appdu *self,
                                              struct jdksavdecc_eui48 apc_primary_mac,
                                              struct jdksavdecc_eui64 entity_id )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_ENTITY_ID_RESPONSE;
    self->payload_length = 8;
    self->address = apc_primary_mac;
    self->reserved = 0;
    jdksavdecc_eui64_set( entity_id, self->payload, 0 );
    return true;
}

/** Create a LINK_UP message - See Annex C.5.1.4 */
bool jdksavdecc_appdu_set_link_up( struct jdksavdecc_appdu *self, struct jdksavdecc_eui48 network_port_mac )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_UP;
    self->payload_length = 0;
    self->address = network_port_mac;
    self->reserved = 0;
    return true;
}

/** Create a LINK_DOWN message - See Annex C.5.1.5 */
bool jdksavdecc_appdu_set_link_down( struct jdksavdecc_appdu *self, struct jdksavdecc_eui48 network_port_mac )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_LINK_DOWN;
    self->payload_length = 0;
    self->address = network_port_mac;
    self->reserved = 0;
    return true;
}

/** Create an AVDECC_FROM_APS message - See Annex C.5.1.6 */
bool jdksavdecc_appdu_set_avdecc_from_aps( struct jdksavdecc_appdu *self,
                                           struct jdksavdecc_eui48 original_source_address,
                                           uint16_t payload_length,
                                           uint8_t const *payload )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APS;
    self->payload_length = payload_length;
    self->address = original_source_address;
    self->reserved = 0;
    memcpy( self->payload, payload, payload_length );
    return true;
}

/** Create a AVDECC_FROM_APC message - See Annex C.5.1.7 */
bool jdksavdecc_appdu_set_avdecc_from_apc( struct jdksavdecc_appdu *self,
                                           struct jdksavdecc_eui48 destination_address,
                                           uint16_t payload_length,
                                           uint8_t const *payload )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_AVDECC_FROM_APC;
    self->payload_length = payload_length;
    self->address = destination_address;
    self->reserved = 0;
    memcpy( self->payload, payload, payload_length );
    return true;
}

/** Create a VENDOR message - See Annex C.5.1.8 */
bool jdksavdecc_appdu_set_vendor( struct jdksavdecc_appdu *self,
                                  struct jdksavdecc_eui48 vendor_message_type,
                                  uint16_t payload_length,
                                  uint8_t const *payload )
{
    self->version = JDKSAVDECC_APPDU_VERSION;
    self->message_type = JDKSAVDECC_APPDU_MESSAGE_TYPE_VENDOR;
    self->payload_length = payload_length;
    self->address = vendor_message_type;
    self->reserved = 0;
    memcpy( self->payload, payload, payload_length );
    return true;
}
