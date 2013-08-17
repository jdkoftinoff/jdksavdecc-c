
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
#include "jdksavdecc_adp_print.h"
#include "jdksavdecc_print.h"


struct jdksavdecc_uint16_name jdksavdecc_adpdu_print_message_type[] =
{
    {JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_AVAILABLE,"ENTITY_AVAILABLE" },
    {JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DEPARTING,"ENTITY_DEPARTING" },
    {JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DISCOVER,"ENTITY_DISCOVER" },
    {0,0}
};

/// entity_capabilities field bits textual representation
struct jdksavdecc_32bit_name jdksavdecc_adpdu_print_entity_capabilities[] =
{
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_EFU_MODE, "EFU_MODE" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_ADDRESS_ACCESS_SUPPORTED, "ADDRESS_ACCESS_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_GATEWAY_ENTITY, "GATEWAY_ENTITY" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_SUPPORTED, "AEM_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_LEGACY_AVC, "LEGACY_AVC" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_ASSOCIATION_ID_SUPPORTED, "ASSOCIATION_ID_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_ASSOCIATION_ID_VALID, "ASSOCIATION_ID_VALID" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_VENDOR_UNIQUE_SUPPORTED, "VENDOR_UNIQUE_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_CLASS_A_SUPPORTED, "CLASS_A_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_CLASS_B_SUPPORTED, "CLASS_B_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_GPTP_SUPPORTED, "GPTP_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_AUTHENTICATION_SUPPORTED, "AEM_AUTHENTICATION_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_AUTHENTICATION_REQUIRED, "AEM_AUTHENTICATION_REQUIRED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_PERSISTENT_ACQUIRE_SUPPORTED, "AEM_PERSISTENT_ACQUIRE_SUPPORTED" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_IDENTIFY_CONTROL_INDEX_VALID, "AEM_IDENTIFY_CONTROL_INDEX_VALID" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_INTERFACE_INDEX_VALID, "AEM_INTERFACE_INDEX_VALID" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_GENERAL_CONTROLLER_IGNORE, "GENERAL_CONTROLLER_IGNORE" },
    { JDKSAVDECC_ADP_ENTITY_CAPABILITY_ENTITY_NOT_READY, "CAPABILITY_ENTITY_NOT_READY" },
    {0,0}
};

/// talker_capabilities field bits textual representation
struct jdksavdecc_16bit_name jdksavdecc_adpdu_print_talker_capabilities[] =
{
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_IMPLEMENTED, "IMPLEMENTED" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_OTHER_SOURCE, "OTHER_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_CONTROL_SOURCE, "CONTROL_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_MEDIA_CLOCK_SOURCE, "MEDIA_CLOCK_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_SMPTE_SOURCE, "SMPTE_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_MIDI_SOURCE, "MIDI_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_AUDIO_SOURCE, "AUDIO_SOURCE" },
    { JDKSAVDECC_ADP_TALKER_CAPABILITY_VIDEO_SOURCE, "VIDEO_SOURCE" },
    {0,0}
};


/// listener_capabilities field bits textual representation
struct jdksavdecc_16bit_name jdksavdecc_adpdu_print_listener_capabilities[] =
{
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_IMPLEMENTED, "IMPLEMENTED" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_OTHER_SINK, "OTHER_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_CONTROL_SINK, "CONTROL_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_MEDIA_CLOCK_SINK, "MEDIA_CLOCK_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_SMPTE_SINK, "SMPTE_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_MIDI_SINK, "MIDI_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_AUDIO_SINK, "AUDIO_SINK" },
    { JDKSAVDECC_ADP_LISTENER_CAPABILITY_VIDEO_SINK, "VIDEO_SINK" },
    {0,0}
};

/// controller_capabilities field bits textual representation
struct jdksavdecc_32bit_name jdksavdecc_adpdu_print_controller_capabilities[] =
{
    { JDKSAVDECC_ADP_CONTROLLER_CAPABILITY_IMPLEMENTED, "IMPLEMENTED" },
    {0,0}
};


void jdksavdecc_adpdu_print_common_control_header( FILE *f, struct jdksavdecc_adpdu_common_control_header const *p )
{
    jdksavdecc_print_label(f,"message_type");
    jdksavdecc_print_uint16_name( f, jdksavdecc_adpdu_print_message_type, p->message_type );
    jdksavdecc_print_eol( f );

    jdksavdecc_print_label(f,"valid_time (seconds)");
    jdksavdecc_print_uint16(f,p->valid_time * 2 );
    jdksavdecc_print_eol( f );

    jdksavdecc_print_label(f,"control_data_length");
    jdksavdecc_print_uint16(f,p->control_data_length );
    jdksavdecc_print_eol( f );

    jdksavdecc_print_label(f,"entity_id");
    jdksavdecc_print_eui64(f,p->entity_id );
    jdksavdecc_print_eol( f );
}

void jdksavdecc_adpdu_print( FILE *f, struct jdksavdecc_adpdu const *p )
{
    jdksavdecc_adpdu_print_common_control_header( f, &p->header );

    if( p->header.message_type != JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DISCOVER )
    {
        if( p->header.message_type != JDKSAVDECC_ADP_MESSAGE_TYPE_ENTITY_DEPARTING )
        {
            jdksavdecc_print_label(f,"available_index");
            jdksavdecc_print_uint32(f,p->available_index);
            jdksavdecc_print_eol( f );
        }

        jdksavdecc_print_label(f,"entity_model_id");
        jdksavdecc_print_eui64(f,p->entity_model_id );
        jdksavdecc_print_eol( f );

        jdksavdecc_print_label(f,"entity_capabilities");
        jdksavdecc_print_32bit_names( f, jdksavdecc_adpdu_print_entity_capabilities, p->entity_capabilities );
        jdksavdecc_print_eol( f );

        if( p->talker_stream_sources > 0 && (p->talker_capabilities & JDKSAVDECC_ADP_TALKER_CAPABILITY_IMPLEMENTED)!=0 )
        {
            jdksavdecc_print_label(f,"talker_stream_sources");
            jdksavdecc_print_uint16(f,p->talker_stream_sources );
            jdksavdecc_print_eol( f );

            jdksavdecc_print_label(f,"talker_capabilities");
            jdksavdecc_print_16bit_names( f, jdksavdecc_adpdu_print_talker_capabilities, p->talker_capabilities );
            jdksavdecc_print_eol( f );
        }

        if( p->listener_stream_sinks>0 )
        {
            jdksavdecc_print_label(f,"listener_stream_sinks");
            jdksavdecc_print_uint16(f,p->listener_stream_sinks );
            jdksavdecc_print_eol( f );

            jdksavdecc_print_label(f,"listener_capabilities");
            jdksavdecc_print_16bit_names( f, jdksavdecc_adpdu_print_listener_capabilities, p->listener_capabilities );
            jdksavdecc_print_eol( f );
        }

        if( (p->controller_capabilities & JDKSAVDECC_ADP_CONTROLLER_CAPABILITY_IMPLEMENTED) != 0 )
        {
            jdksavdecc_print_label(f,"controller_capabilities");
            jdksavdecc_print_32bit_names( f, jdksavdecc_adpdu_print_controller_capabilities, p->controller_capabilities );
            jdksavdecc_print_eol( f );
        }

        if( (p->entity_capabilities & JDKSAVDECC_ADP_ENTITY_CAPABILITY_GPTP_SUPPORTED) != 0 )
        {
            jdksavdecc_print_label(f,"gptp_grandmaster_id");
            jdksavdecc_print_eui64(f,p->gptp_grandmaster_id );
            jdksavdecc_print_eol( f );

            jdksavdecc_print_label(f,"gptp_domain_number");
            jdksavdecc_print_uint16(f,p->gptp_domain_number );
            jdksavdecc_print_eol( f );
        }

        if( (p->entity_capabilities & JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_IDENTIFY_CONTROL_INDEX_VALID) != 0 )
        {
            jdksavdecc_print_label(f,"identify_control_index");
            jdksavdecc_print_uint16(f,p->identify_control_index );
            jdksavdecc_print_eol( f );
        }

        if( (p->entity_capabilities & JDKSAVDECC_ADP_ENTITY_CAPABILITY_AEM_INTERFACE_INDEX_VALID) != 0 )
        {
            jdksavdecc_print_label(f,"interface_index");
            jdksavdecc_print_uint16(f,p->interface_index );
            jdksavdecc_print_eol( f );
        }

        if( (p->entity_capabilities & JDKSAVDECC_ADP_ENTITY_CAPABILITY_ASSOCIATION_ID_VALID) != 0 )
        {
            jdksavdecc_print_label(f,"association_id");
            jdksavdecc_print_eui64(f,p->association_id );
            jdksavdecc_print_eol( f );
        }
    }
}



