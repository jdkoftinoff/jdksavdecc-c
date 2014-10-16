#pragma once

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

#if !defined( JDKSAVDECC_CPP_NO_IOSTREAM )
#include <iostream>
#endif

#if !defined( JDKSAVDECC_CPP_NO_STDIO )
#include <stdio.h>
#endif

#include <memory>
#include <utility>
#include <vector>

#include "jdksavdecc_world.h"
#include "jdksavdecc.h"

#ifdef __cplusplus

namespace jdksavdecc
{

template <typename T>
struct wrap : public T
{
    wrap()
    {
        memset( this, 0, sizeof( *this ) );
    }

    wrap( T const &other )
    {
        if ( &other != this )
        {
            memcpy( this, &other, sizeof( *this ) );
        }
    }

    void reset()
    {
        memset( this, 0, sizeof( *this ) );
    }

    T *get()
    {
        return this;
    }

    T const *get() const
    {
        return this;
    }

    T const &operator=( const T &other )
    {
        if ( &other != this )
        {
            memcpy( this, &other, sizeof( *this ) );
        }
        return *this;
    }

    bool operator==( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) == 0;
    }

    bool operator!=( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) != 0;
    }

    bool operator<( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) < 0;
    }

    bool operator<=( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) <= 0;
    }

    bool operator>=( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) >= 0;
    }

    bool operator>( T const &other )
    {
        return memcmp( this, &other, sizeof( *this ) ) > 0;
    }
};

struct acmpdu : wrap<jdksavdecc_acmpdu>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_acmpdu_read( this, base, pos, len );
    };
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_acmpdu_write( this, base, pos, len );
    }
};

struct acmpdu_common_control_header : wrap<jdksavdecc_acmpdu_common_control_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_acmpdu_common_control_header_read( this, base, pos, len );
    };
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_acmpdu_common_control_header_write( this, base, pos, len );
    }
};

struct adpdu : wrap<jdksavdecc_adpdu>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_adpdu_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_adpdu_write( this, base, pos, len );
    }
};
struct adpdu_common_control_header : wrap<jdksavdecc_adpdu_common_control_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_adpdu_common_control_header_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_adpdu_common_control_header_write( this, base, pos, len );
    }
};
struct aecp_aa : wrap<jdksavdecc_aecp_aa>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aecp_aa_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aecp_aa_write( this, base, pos, len );
    }
};
struct aecp_aa_tlv : wrap<jdksavdecc_aecp_aa_tlv>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aecp_aa_tlv_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aecp_aa_tlv_write( this, base, pos, len );
    }
};
struct aecpdu_aem : wrap<jdksavdecc_aecpdu_aem>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aecpdu_aem_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aecpdu_aem_write( this, base, pos, len );
    }
};
struct aecpdu_common : wrap<jdksavdecc_aecpdu_common>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aecpdu_common_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aecpdu_common_write( this, base, pos, len );
    }
};
struct aecpdu_common_control_header : wrap<jdksavdecc_aecpdu_common_control_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aecpdu_common_control_header_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aecpdu_common_control_header_write( this, base, pos, len );
    }
};

namespace aem_command
{
struct abort_operation : wrap<jdksavdecc_aem_command_abort_operation>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_abort_operation_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_abort_operation_write( this, base, pos, len );
    }
};
struct abort_operation_response : wrap<jdksavdecc_aem_command_abort_operation_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_abort_operation_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_abort_operation_response_write( this, base, pos, len );
    }
};
struct acquire_entity : wrap<jdksavdecc_aem_command_acquire_entity>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_acquire_entity_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_acquire_entity_write( this, base, pos, len );
    }
};
struct acquire_entity_response : wrap<jdksavdecc_aem_command_acquire_entity_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_acquire_entity_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_acquire_entity_response_write( this, base, pos, len );
    }
};
struct add_audio_mappings : wrap<jdksavdecc_aem_command_add_audio_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_audio_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_audio_mappings_write( this, base, pos, len );
    }
};
struct add_audio_mappings_response : wrap<jdksavdecc_aem_command_add_audio_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_audio_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_audio_mappings_response_write( this, base, pos, len );
    }
};
struct add_sensor_mappings : wrap<jdksavdecc_aem_command_add_sensor_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_sensor_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_sensor_mappings_write( this, base, pos, len );
    }
};
struct add_sensor_mappings_response : wrap<jdksavdecc_aem_command_add_sensor_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_sensor_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_sensor_mappings_response_write( this, base, pos, len );
    }
};
struct add_video_mappings : wrap<jdksavdecc_aem_command_add_video_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_video_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_video_mappings_write( this, base, pos, len );
    }
};
struct add_video_mappings_response : wrap<jdksavdecc_aem_command_add_video_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_add_video_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_add_video_mappings_response_write( this, base, pos, len );
    }
};
struct auth_add_key : wrap<jdksavdecc_aem_command_auth_add_key>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_key_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_key_write( this, base, pos, len );
    }
};
struct auth_add_key_response : wrap<jdksavdecc_aem_command_auth_add_key_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_key_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_key_response_write( this, base, pos, len );
    }
};
struct auth_add_key_to_chain : wrap<jdksavdecc_aem_command_auth_add_key_to_chain>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_key_to_chain_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_key_to_chain_write( this, base, pos, len );
    }
};
struct auth_add_key_to_chain_response : wrap<jdksavdecc_aem_command_auth_add_key_to_chain_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_key_to_chain_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_key_to_chain_response_write( this, base, pos, len );
    }
};
struct auth_add_token : wrap<jdksavdecc_aem_command_auth_add_token>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_token_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_token_write( this, base, pos, len );
    }
};
struct auth_add_token_response : wrap<jdksavdecc_aem_command_auth_add_token_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_add_token_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_add_token_response_write( this, base, pos, len );
    }
};
struct auth_delete_key : wrap<jdksavdecc_aem_command_auth_delete_key>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_key_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_key_write( this, base, pos, len );
    }
};
struct auth_delete_key_from_chain : wrap<jdksavdecc_aem_command_auth_delete_key_from_chain>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_key_from_chain_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_key_from_chain_write( this, base, pos, len );
    }
};
struct auth_delete_key_from_chain_response : wrap<jdksavdecc_aem_command_auth_delete_key_from_chain_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_key_from_chain_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_key_from_chain_response_write( this, base, pos, len );
    }
};
struct auth_delete_key_response : wrap<jdksavdecc_aem_command_auth_delete_key_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_key_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_key_response_write( this, base, pos, len );
    }
};
struct auth_delete_token : wrap<jdksavdecc_aem_command_auth_delete_token>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_token_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_token_write( this, base, pos, len );
    }
};
struct auth_delete_token_response : wrap<jdksavdecc_aem_command_auth_delete_token_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_delete_token_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_delete_token_response_write( this, base, pos, len );
    }
};
struct auth_get_identity : wrap<jdksavdecc_aem_command_auth_get_identity>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_identity_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_identity_write( this, base, pos, len );
    }
};
struct auth_get_identity_response : wrap<jdksavdecc_aem_command_auth_get_identity_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_identity_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_identity_response_write( this, base, pos, len );
    }
};
struct auth_get_key : wrap<jdksavdecc_aem_command_auth_get_key>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_key_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_key_write( this, base, pos, len );
    }
};
struct auth_get_key_list : wrap<jdksavdecc_aem_command_auth_get_key_list>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_key_list_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_key_list_write( this, base, pos, len );
    }
};
struct auth_get_key_list_response : wrap<jdksavdecc_aem_command_auth_get_key_list_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_key_list_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_key_list_response_write( this, base, pos, len );
    }
};
struct auth_get_key_response : wrap<jdksavdecc_aem_command_auth_get_key_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_key_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_key_response_write( this, base, pos, len );
    }
};
struct auth_get_keychain_list : wrap<jdksavdecc_aem_command_auth_get_keychain_list>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_keychain_list_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_keychain_list_write( this, base, pos, len );
    }
};
struct auth_get_keychain_list_response : wrap<jdksavdecc_aem_command_auth_get_keychain_list_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_auth_get_keychain_list_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_auth_get_keychain_list_response_write( this, base, pos, len );
    }
};
struct authenticate : wrap<jdksavdecc_aem_command_authenticate>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_authenticate_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_authenticate_write( this, base, pos, len );
    }
};
struct authenticate_response : wrap<jdksavdecc_aem_command_authenticate_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_authenticate_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_authenticate_response_write( this, base, pos, len );
    }
};
struct controller_available : wrap<jdksavdecc_aem_command_controller_available>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_controller_available_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_controller_available_write( this, base, pos, len );
    }
};
struct controller_available_response : wrap<jdksavdecc_aem_command_controller_available_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_controller_available_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_controller_available_response_write( this, base, pos, len );
    }
};
struct deauthenticate : wrap<jdksavdecc_aem_command_deauthenticate>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_deauthenticate_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_deauthenticate_write( this, base, pos, len );
    }
};
struct deauthenticate_response : wrap<jdksavdecc_aem_command_deauthenticate_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_deauthenticate_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_deauthenticate_response_write( this, base, pos, len );
    }
};
struct decrement_control : wrap<jdksavdecc_aem_command_decrement_control>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_decrement_control_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_decrement_control_write( this, base, pos, len );
    }
};
struct decrement_control_response : wrap<jdksavdecc_aem_command_decrement_control_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_decrement_control_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_decrement_control_response_write( this, base, pos, len );
    }
};
struct deregister_unsolicited_notification : wrap<jdksavdecc_aem_command_deregister_unsolicited_notification>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_deregister_unsolicited_notification_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_deregister_unsolicited_notification_write( this, base, pos, len );
    }
};
struct deregister_unsolicited_notification_response : wrap<jdksavdecc_aem_command_deregister_unsolicited_notification_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_deregister_unsolicited_notification_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_deregister_unsolicited_notification_response_write( this, base, pos, len );
    }
};
struct disable_stream_encryption : wrap<jdksavdecc_aem_command_disable_stream_encryption>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_disable_stream_encryption_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_disable_stream_encryption_write( this, base, pos, len );
    }
};
struct disable_stream_encryption_response : wrap<jdksavdecc_aem_command_disable_stream_encryption_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_disable_stream_encryption_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_disable_stream_encryption_response_write( this, base, pos, len );
    }
};
struct disable_transport_security : wrap<jdksavdecc_aem_command_disable_transport_security>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_disable_transport_security_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_disable_transport_security_write( this, base, pos, len );
    }
};
struct disable_transport_security_response : wrap<jdksavdecc_aem_command_disable_transport_security_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_disable_transport_security_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_disable_transport_security_response_write( this, base, pos, len );
    }
};
struct enable_stream_encryption : wrap<jdksavdecc_aem_command_enable_stream_encryption>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_enable_stream_encryption_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_enable_stream_encryption_write( this, base, pos, len );
    }
};
struct enable_stream_encryption_response : wrap<jdksavdecc_aem_command_enable_stream_encryption_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_enable_stream_encryption_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_enable_stream_encryption_response_write( this, base, pos, len );
    }
};
struct enable_transport_security : wrap<jdksavdecc_aem_command_enable_transport_security>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_enable_transport_security_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_enable_transport_security_write( this, base, pos, len );
    }
};
struct enable_transport_security_response : wrap<jdksavdecc_aem_command_enable_transport_security_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_enable_transport_security_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_enable_transport_security_response_write( this, base, pos, len );
    }
};
struct entity_available : wrap<jdksavdecc_aem_command_entity_available>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_entity_available_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_entity_available_write( this, base, pos, len );
    }
};
struct entity_available_response : wrap<jdksavdecc_aem_command_entity_available_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_entity_available_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_entity_available_response_write( this, base, pos, len );
    }
};
struct get_as_path : wrap<jdksavdecc_aem_command_get_as_path>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_as_path_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_as_path_write( this, base, pos, len );
    }
};
struct get_as_path_response : wrap<jdksavdecc_aem_command_get_as_path_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_as_path_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_as_path_response_write( this, base, pos, len );
    }
};
struct get_association_id : wrap<jdksavdecc_aem_command_get_association_id>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_association_id_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_association_id_write( this, base, pos, len );
    }
};
struct get_association_id_response : wrap<jdksavdecc_aem_command_get_association_id_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_association_id_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_association_id_response_write( this, base, pos, len );
    }
};
struct get_audio_map : wrap<jdksavdecc_aem_command_get_audio_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_audio_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_audio_map_write( this, base, pos, len );
    }
};
struct get_audio_map_response : wrap<jdksavdecc_aem_command_get_audio_map_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_audio_map_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_audio_map_response_write( this, base, pos, len );
    }
};
struct get_avb_info : wrap<jdksavdecc_aem_command_get_avb_info>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_avb_info_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_avb_info_write( this, base, pos, len );
    }
};
struct get_avb_info_response : wrap<jdksavdecc_aem_command_get_avb_info_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_avb_info_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_avb_info_response_write( this, base, pos, len );
    }
};
struct get_clock_source : wrap<jdksavdecc_aem_command_get_clock_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_clock_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_clock_source_write( this, base, pos, len );
    }
};
struct get_clock_source_response : wrap<jdksavdecc_aem_command_get_clock_source_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_clock_source_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_clock_source_response_write( this, base, pos, len );
    }
};
struct get_configuration : wrap<jdksavdecc_aem_command_get_configuration>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_configuration_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_configuration_write( this, base, pos, len );
    }
};
struct get_configuration_response : wrap<jdksavdecc_aem_command_get_configuration_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_configuration_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_configuration_response_write( this, base, pos, len );
    }
};
struct get_control : wrap<jdksavdecc_aem_command_get_control>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_control_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_control_write( this, base, pos, len );
    }
};
struct get_control_response : wrap<jdksavdecc_aem_command_get_control_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_control_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_control_response_write( this, base, pos, len );
    }
};
struct get_counters : wrap<jdksavdecc_aem_command_get_counters>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_counters_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_counters_write( this, base, pos, len );
    }
};
struct get_counters_response : wrap<jdksavdecc_aem_command_get_counters_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_counters_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_counters_response_write( this, base, pos, len );
    }
};
struct get_matrix : wrap<jdksavdecc_aem_command_get_matrix>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_matrix_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_matrix_write( this, base, pos, len );
    }
};
struct get_matrix_response : wrap<jdksavdecc_aem_command_get_matrix_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_matrix_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_matrix_response_write( this, base, pos, len );
    }
};
struct get_memory_object_length : wrap<jdksavdecc_aem_command_get_memory_object_length>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_memory_object_length_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_memory_object_length_write( this, base, pos, len );
    }
};
struct get_memory_object_length_response : wrap<jdksavdecc_aem_command_get_memory_object_length_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_memory_object_length_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_memory_object_length_response_write( this, base, pos, len );
    }
};
struct get_mixer : wrap<jdksavdecc_aem_command_get_mixer>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_mixer_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_mixer_write( this, base, pos, len );
    }
};
struct get_mixer_response : wrap<jdksavdecc_aem_command_get_mixer_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_mixer_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_mixer_response_write( this, base, pos, len );
    }
};
struct get_name : wrap<jdksavdecc_aem_command_get_name>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_name_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_name_write( this, base, pos, len );
    }
};
struct get_name_response : wrap<jdksavdecc_aem_command_get_name_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_name_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_name_response_write( this, base, pos, len );
    }
};
struct get_sampling_rate : wrap<jdksavdecc_aem_command_get_sampling_rate>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sampling_rate_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sampling_rate_write( this, base, pos, len );
    }
};
struct get_sampling_rate_response : wrap<jdksavdecc_aem_command_get_sampling_rate_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sampling_rate_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sampling_rate_response_write( this, base, pos, len );
    }
};
struct get_sensor_format : wrap<jdksavdecc_aem_command_get_sensor_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sensor_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sensor_format_write( this, base, pos, len );
    }
};
struct get_sensor_format_response : wrap<jdksavdecc_aem_command_get_sensor_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sensor_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sensor_format_response_write( this, base, pos, len );
    }
};
struct get_sensor_map : wrap<jdksavdecc_aem_command_get_sensor_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sensor_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sensor_map_write( this, base, pos, len );
    }
};
struct get_sensor_map_response : wrap<jdksavdecc_aem_command_get_sensor_map_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_sensor_map_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_sensor_map_response_write( this, base, pos, len );
    }
};
struct get_signal_selector : wrap<jdksavdecc_aem_command_get_signal_selector>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_signal_selector_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_signal_selector_write( this, base, pos, len );
    }
};
struct get_signal_selector_response : wrap<jdksavdecc_aem_command_get_signal_selector_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_signal_selector_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_signal_selector_response_write( this, base, pos, len );
    }
};
// struct get_stream_backup : wrap<jdksavdecc_aem_command_get_stream_backup> {};
// struct get_stream_backup_response : wrap<jdksavdecc_aem_command_get_stream_backup_response> {};
struct get_stream_format : wrap<jdksavdecc_aem_command_get_stream_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_stream_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_stream_format_write( this, base, pos, len );
    }
};
struct get_stream_format_response : wrap<jdksavdecc_aem_command_get_stream_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_stream_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_stream_format_response_write( this, base, pos, len );
    }
};
struct get_stream_info : wrap<jdksavdecc_aem_command_get_stream_info>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_stream_info_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_stream_info_write( this, base, pos, len );
    }
};
struct get_stream_info_response : wrap<jdksavdecc_aem_command_get_stream_info_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_stream_info_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_stream_info_response_write( this, base, pos, len );
    }
};
struct get_video_format : wrap<jdksavdecc_aem_command_get_video_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_video_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_video_format_write( this, base, pos, len );
    }
};
struct get_video_format_response : wrap<jdksavdecc_aem_command_get_video_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_video_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_video_format_response_write( this, base, pos, len );
    }
};
struct get_video_map : wrap<jdksavdecc_aem_command_get_video_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_video_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_video_map_write( this, base, pos, len );
    }
};
struct get_video_map_response : wrap<jdksavdecc_aem_command_get_video_map_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_get_video_map_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_get_video_map_response_write( this, base, pos, len );
    }
};
struct identify_notification : wrap<jdksavdecc_aem_command_identify_notification>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_identify_notification_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_identify_notification_write( this, base, pos, len );
    }
};
struct increment_control : wrap<jdksavdecc_aem_command_increment_control>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_increment_control_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_increment_control_write( this, base, pos, len );
    }
};
struct increment_control_response : wrap<jdksavdecc_aem_command_increment_control_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_increment_control_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_increment_control_response_write( this, base, pos, len );
    }
};
struct lock_entity : wrap<jdksavdecc_aem_command_lock_entity>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_lock_entity_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_lock_entity_write( this, base, pos, len );
    }
};
struct lock_entity_response : wrap<jdksavdecc_aem_command_lock_entity_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_lock_entity_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_lock_entity_response_write( this, base, pos, len );
    }
};
struct operation_status_response : wrap<jdksavdecc_aem_command_operation_status_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_operation_status_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_operation_status_response_write( this, base, pos, len );
    }
};
struct read_descriptor : wrap<jdksavdecc_aem_command_read_descriptor>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_read_descriptor_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_read_descriptor_write( this, base, pos, len );
    }
};
struct read_descriptor_response : wrap<jdksavdecc_aem_command_read_descriptor_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_read_descriptor_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_read_descriptor_response_write( this, base, pos, len );
    }
};
struct reboot : wrap<jdksavdecc_aem_command_reboot>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_reboot_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_reboot_write( this, base, pos, len );
    }
};
struct reboot_response : wrap<jdksavdecc_aem_command_reboot_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_reboot_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_reboot_response_write( this, base, pos, len );
    }
};
struct register_unsolicited_notification : wrap<jdksavdecc_aem_command_register_unsolicited_notification>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_register_unsolicited_notification_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_register_unsolicited_notification_write( this, base, pos, len );
    }
};
struct register_unsolicited_notification_response : wrap<jdksavdecc_aem_command_register_unsolicited_notification_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_register_unsolicited_notification_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_register_unsolicited_notification_response_write( this, base, pos, len );
    }
};
struct remove_audio_mappings : wrap<jdksavdecc_aem_command_remove_audio_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_audio_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_audio_mappings_write( this, base, pos, len );
    }
};
struct remove_audio_mappings_response : wrap<jdksavdecc_aem_command_remove_audio_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_audio_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_audio_mappings_response_write( this, base, pos, len );
    }
};
struct remove_sensor_mappings : wrap<jdksavdecc_aem_command_remove_sensor_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_sensor_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_sensor_mappings_write( this, base, pos, len );
    }
};
struct remove_sensor_mappings_response : wrap<jdksavdecc_aem_command_remove_sensor_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_sensor_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_sensor_mappings_response_write( this, base, pos, len );
    }
};
struct remove_video_mappings : wrap<jdksavdecc_aem_command_remove_video_mappings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_video_mappings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_video_mappings_write( this, base, pos, len );
    }
};
struct remove_video_mappings_response : wrap<jdksavdecc_aem_command_remove_video_mappings_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_remove_video_mappings_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_remove_video_mappings_response_write( this, base, pos, len );
    }
};
struct set_association_id : wrap<jdksavdecc_aem_command_set_association_id>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_association_id_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_association_id_write( this, base, pos, len );
    }
};
struct set_association_id_response : wrap<jdksavdecc_aem_command_set_association_id_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_association_id_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_association_id_response_write( this, base, pos, len );
    }
};
struct set_clock_source : wrap<jdksavdecc_aem_command_set_clock_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_clock_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_clock_source_write( this, base, pos, len );
    }
};
struct set_clock_source_response : wrap<jdksavdecc_aem_command_set_clock_source_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_clock_source_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_clock_source_response_write( this, base, pos, len );
    }
};
struct set_configuration : wrap<jdksavdecc_aem_command_set_configuration>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_configuration_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_configuration_write( this, base, pos, len );
    }
};
struct set_configuration_response : wrap<jdksavdecc_aem_command_set_configuration_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_configuration_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_configuration_response_write( this, base, pos, len );
    }
};
struct set_control : wrap<jdksavdecc_aem_command_set_control>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_control_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_control_write( this, base, pos, len );
    }
};
struct set_control_response : wrap<jdksavdecc_aem_command_set_control_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_control_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_control_response_write( this, base, pos, len );
    }
};
struct set_matrix : wrap<jdksavdecc_aem_command_set_matrix>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_matrix_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_matrix_write( this, base, pos, len );
    }
};
struct set_matrix_response : wrap<jdksavdecc_aem_command_set_matrix_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_matrix_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_matrix_response_write( this, base, pos, len );
    }
};
struct set_memory_object_length : wrap<jdksavdecc_aem_command_set_memory_object_length>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_memory_object_length_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_memory_object_length_write( this, base, pos, len );
    }
};
struct set_memory_object_length_response : wrap<jdksavdecc_aem_command_set_memory_object_length_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_memory_object_length_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_memory_object_length_response_write( this, base, pos, len );
    }
};
struct set_mixer : wrap<jdksavdecc_aem_command_set_mixer>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_mixer_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_mixer_write( this, base, pos, len );
    }
};
struct set_mixer_response : wrap<jdksavdecc_aem_command_set_mixer_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_mixer_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_mixer_response_write( this, base, pos, len );
    }
};
struct set_name : wrap<jdksavdecc_aem_command_set_name>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_name_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_name_write( this, base, pos, len );
    }
};
struct set_name_response : wrap<jdksavdecc_aem_command_set_name_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_name_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_name_response_write( this, base, pos, len );
    }
};
struct set_sampling_rate : wrap<jdksavdecc_aem_command_set_sampling_rate>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_sampling_rate_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_sampling_rate_write( this, base, pos, len );
    }
};
struct set_sampling_rate_response : wrap<jdksavdecc_aem_command_set_sampling_rate_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_sampling_rate_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_sampling_rate_response_write( this, base, pos, len );
    }
};
struct set_sensor_format : wrap<jdksavdecc_aem_command_set_sensor_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_sensor_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_sensor_format_write( this, base, pos, len );
    }
};
struct set_sensor_format_response : wrap<jdksavdecc_aem_command_set_sensor_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_sensor_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_sensor_format_response_write( this, base, pos, len );
    }
};
struct set_signal_selector : wrap<jdksavdecc_aem_command_set_signal_selector>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_signal_selector_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_signal_selector_write( this, base, pos, len );
    }
};
struct set_signal_selector_response : wrap<jdksavdecc_aem_command_set_signal_selector_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_signal_selector_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_signal_selector_response_write( this, base, pos, len );
    }
};
// struct set_stream_backup : wrap<jdksavdecc_aem_command_set_stream_backup;> {};
// struct set_stream_backup_response : wrap<jdksavdecc_aem_command_set_stream_backup_response;> {};
struct set_stream_format : wrap<jdksavdecc_aem_command_set_stream_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_stream_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_stream_format_write( this, base, pos, len );
    }
};
struct set_stream_format_response : wrap<jdksavdecc_aem_command_set_stream_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_stream_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_stream_format_response_write( this, base, pos, len );
    }
};
struct set_stream_info : wrap<jdksavdecc_aem_command_set_stream_info>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_stream_info_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_stream_info_write( this, base, pos, len );
    }
};
struct set_stream_info_response : wrap<jdksavdecc_aem_command_set_stream_info_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_stream_info_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_stream_info_response_write( this, base, pos, len );
    }
};
struct set_video_format : wrap<jdksavdecc_aem_command_set_video_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_video_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_video_format_write( this, base, pos, len );
    }
};
struct set_video_format_response : wrap<jdksavdecc_aem_command_set_video_format_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_set_video_format_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_set_video_format_response_write( this, base, pos, len );
    }
};
struct start_operation : wrap<jdksavdecc_aem_command_start_operation>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_start_operation_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_start_operation_write( this, base, pos, len );
    }
};
struct start_operation_response : wrap<jdksavdecc_aem_command_start_operation_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_start_operation_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_start_operation_response_write( this, base, pos, len );
    }
};
struct start_streaming : wrap<jdksavdecc_aem_command_start_streaming>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_start_streaming_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_start_streaming_write( this, base, pos, len );
    }
};
struct start_streaming_response : wrap<jdksavdecc_aem_command_start_streaming_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_start_streaming_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_start_streaming_response_write( this, base, pos, len );
    }
};
struct stop_streaming : wrap<jdksavdecc_aem_command_stop_streaming>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_stop_streaming_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_stop_streaming_write( this, base, pos, len );
    }
};
struct stop_streaming_response : wrap<jdksavdecc_aem_command_stop_streaming_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_stop_streaming_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_stop_streaming_response_write( this, base, pos, len );
    }
};
struct write_descriptor : wrap<jdksavdecc_aem_command_write_descriptor>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_write_descriptor_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_write_descriptor_write( this, base, pos, len );
    }
};
struct write_descriptor_response : wrap<jdksavdecc_aem_command_write_descriptor_response>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_aem_command_write_descriptor_response_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_aem_command_write_descriptor_response_write( this, base, pos, len );
    }
};
}

// struct aem_ecc_private_256 : wrap<jdksavdecc_aem_ecc_private_256> {};
// struct aem_ecc_public_256 : wrap<jdksavdecc_aem_ecc_public_256 > {};
struct appdu : wrap<jdksavdecc_appdu>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_appdu_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_appdu_write( this, base, pos, len );
    }
};
struct audio_mapping : wrap<jdksavdecc_audio_mapping>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_audio_mapping_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_audio_mapping_write( this, base, pos, len );
    }
};
struct audio_mappings_format : wrap<jdksavdecc_audio_mappings_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_audio_mappings_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_audio_mappings_format_write( this, base, pos, len );
    }
};
struct combiner_map : wrap<jdksavdecc_combiner_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_combiner_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_combiner_map_write( this, base, pos, len );
    }
};
struct common_control_header : wrap<jdksavdecc_common_control_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_common_control_header_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_common_control_header_write( this, base, pos, len );
    }
};

struct demultiplexer_map : wrap<jdksavdecc_demultiplexer_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_demultiplexer_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_demultiplexer_map_write( this, base, pos, len );
    }
};
namespace descriptor
{
struct descriptor : wrap<jdksavdecc_descriptor>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        reset();
        if ( len <= JDKSAVDECC_AEM_DESCRIPTOR_SIZE )
        {
            memcpy( data, base + pos, len );
        }
        return len;
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        if ( len <= JDKSAVDECC_AEM_DESCRIPTOR_SIZE )
        {
            memcpy( base + pos, data, len );
        }
        return len;
    }
};
struct audio : wrap<jdksavdecc_descriptor_audio>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_audio_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_audio_write( this, base, pos, len );
    }
};
struct audio_cluster : wrap<jdksavdecc_descriptor_audio_cluster>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_audio_cluster_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_audio_cluster_write( this, base, pos, len );
    }
};
struct audio_map : wrap<jdksavdecc_descriptor_audio_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_audio_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_audio_map_write( this, base, pos, len );
    }
};
struct avb_interface : wrap<jdksavdecc_descriptor_avb_interface>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_avb_interface_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_avb_interface_write( this, base, pos, len );
    }
};
struct clock_domain : wrap<jdksavdecc_descriptor_clock_domain>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_clock_domain_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_clock_domain_write( this, base, pos, len );
    }
};
struct clock_source : wrap<jdksavdecc_descriptor_clock_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_clock_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_clock_source_write( this, base, pos, len );
    }
};
struct configuration : wrap<jdksavdecc_descriptor_configuration>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_configuration_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_configuration_write( this, base, pos, len );
    }
};
struct control : wrap<jdksavdecc_descriptor_control>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_control_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_control_write( this, base, pos, len );
    }
};
struct control_block : wrap<jdksavdecc_descriptor_control_block>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_control_block_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_control_block_write( this, base, pos, len );
    }
};
struct entity : wrap<jdksavdecc_descriptor_entity>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_entity_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_entity_write( this, base, pos, len );
    }
};
struct external_port : wrap<jdksavdecc_descriptor_external_port>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_external_port_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_external_port_write( this, base, pos, len );
    }
};
struct internal_port : wrap<jdksavdecc_descriptor_internal_port>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_internal_port_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_internal_port_write( this, base, pos, len );
    }
};
struct jack : wrap<jdksavdecc_descriptor_jack>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_jack_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_jack_write( this, base, pos, len );
    }
};
struct locale : wrap<jdksavdecc_descriptor_locale>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_locale_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_locale_write( this, base, pos, len );
    }
};
struct matrix : wrap<jdksavdecc_descriptor_matrix>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_matrix_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_matrix_write( this, base, pos, len );
    }
};
struct matrix_signal : wrap<jdksavdecc_descriptor_matrix_signal>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_matrix_signal_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_matrix_signal_write( this, base, pos, len );
    }
};
struct memory_object : wrap<jdksavdecc_descriptor_memory_object>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_memory_object_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_memory_object_write( this, base, pos, len );
    }
};
struct mixer : wrap<jdksavdecc_descriptor_mixer>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_mixer_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_mixer_write( this, base, pos, len );
    }
};
struct sensor : wrap<jdksavdecc_descriptor_sensor>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_sensor_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_sensor_write( this, base, pos, len );
    }
};
struct sensor_cluster : wrap<jdksavdecc_descriptor_sensor_cluster>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_sensor_cluster_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_sensor_cluster_write( this, base, pos, len );
    }
};
struct sensor_map : wrap<jdksavdecc_descriptor_sensor_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_sensor_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_sensor_map_write( this, base, pos, len );
    }
};
struct signal_combiner : wrap<jdksavdecc_descriptor_signal_combiner>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_signal_combiner_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_signal_combiner_write( this, base, pos, len );
    }
};
struct signal_demultiplexer : wrap<jdksavdecc_descriptor_signal_demultiplexer>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_signal_demultiplexer_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_signal_demultiplexer_write( this, base, pos, len );
    }
};
struct signal_multiplexer : wrap<jdksavdecc_descriptor_signal_multiplexer>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_signal_multiplexer_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_signal_multiplexer_write( this, base, pos, len );
    }
};
struct signal_selector : wrap<jdksavdecc_descriptor_signal_selector>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_signal_selector_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_signal_selector_write( this, base, pos, len );
    }
};
struct signal_splitter : wrap<jdksavdecc_descriptor_signal_splitter>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_signal_splitter_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_signal_splitter_write( this, base, pos, len );
    }
};
struct storage : wrap<jdksavdecc_descriptor_storage>
{
};
struct storage_gen : wrap<jdksavdecc_descriptor_storage_gen>
{
};
struct storage_gen_descriptor : wrap<jdksavdecc_descriptor_storage_gen_descriptor>
{
};
struct storage_gen_symbol : wrap<jdksavdecc_descriptor_storage_gen_symbol>
{
};
struct storage_header : wrap<jdksavdecc_descriptor_storage_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_storage_header_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_storage_header_write( this, base, pos, len );
    }
};
struct storage_item : wrap<jdksavdecc_descriptor_storage_item>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_storage_item_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_storage_item_write( this, base, pos, len );
    }
};
struct storage_symbol : wrap<jdksavdecc_descriptor_storage_symbol>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_storage_symbol_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_storage_symbol_write( this, base, pos, len );
    }
};
struct storage_symbol_dispatch_item : wrap<jdksavdecc_descriptor_storage_symbol_dispatch_item>
{
};
struct storage_symbols : wrap<jdksavdecc_descriptor_storage_symbols>
{
};
struct stream : wrap<jdksavdecc_descriptor_stream>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_stream_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_stream_write( this, base, pos, len );
    }
};
struct stream_port : wrap<jdksavdecc_descriptor_stream_port>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_stream_port_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_stream_port_write( this, base, pos, len );
    }
};
struct strings : wrap<jdksavdecc_descriptor_strings>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_strings_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_strings_write( this, base, pos, len );
    }
};
struct transcoder : wrap<jdksavdecc_descriptor_transcoder>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_transcoder_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_transcoder_write( this, base, pos, len );
    }
};
struct video : wrap<jdksavdecc_descriptor_video>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_video_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_video_write( this, base, pos, len );
    }
};
struct video_cluster : wrap<jdksavdecc_descriptor_video_cluster>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_video_cluster_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_video_cluster_write( this, base, pos, len );
    }
};
struct video_map : wrap<jdksavdecc_descriptor_video_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_descriptor_video_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_descriptor_video_map_write( this, base, pos, len );
    }
};
}
struct entity_model : wrap<jdksavdecc_entity_model>
{
};
struct eui48 : wrap<jdksavdecc_eui48>
{
    eui48()
    {
    }

    eui48( eui48 const &other ) : wrap<jdksavdecc_eui48>( other )
    {
    }

    eui48( uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5 )
    {
        value[0] = v0;
        value[1] = v1;
        value[2] = v2;
        value[3] = v3;
        value[4] = v4;
        value[5] = v5;
    }

    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_eui48_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_eui48_write( this, base, pos, len );
    }
};
struct eui64 : wrap<jdksavdecc_eui64>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_eui64_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_eui64_write( this, base, pos, len );
    }
};
struct frame : wrap<jdksavdecc_frame>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_frame_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_frame_write( this, base, pos, len );
    }
};
struct frame_sender : wrap<jdksavdecc_frame_sender>
{
};
struct fullappdu : wrap<jdksavdecc_fullappdu>
{
};
struct gptp_seconds : wrap<jdksavdecc_gptp_seconds>
{
};
struct jdks_log_console_command : wrap<jdksavdecc_jdks_log_console_command>
{
};
struct jdks_log_control : wrap<jdksavdecc_jdks_log_control>
{
};
struct maap : wrap<jdksavdecc_maap>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_maap_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_maap_write( this, base, pos, len );
    }
};
struct maap_common_control_header : wrap<jdksavdecc_maap_common_control_header>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_maap_common_control_header_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_maap_common_control_header_write( this, base, pos, len );
    }
};
struct mixer_source : wrap<jdksavdecc_mixer_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_mixer_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_mixer_source_write( this, base, pos, len );
    }
};
struct msrp_mappings_format : wrap<jdksavdecc_msrp_mappings_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_msrp_mappings_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_msrp_mappings_format_write( this, base, pos, len );
    }
};
struct multiplexer_source : wrap<jdksavdecc_multiplexer_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_multiplexer_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_multiplexer_source_write( this, base, pos, len );
    }
};
struct signal_selector_source : wrap<jdksavdecc_signal_selector_source>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_signal_selector_source_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_signal_selector_source_write( this, base, pos, len );
    }
};
struct splitter_map : wrap<jdksavdecc_splitter_map>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_splitter_map_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_splitter_map_write( this, base, pos, len );
    }
};
struct avdecc_string : wrap<jdksavdecc_string>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_string_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_string_write( this, base, pos, len );
    }
};
struct values_bode_plot : wrap<jdksavdecc_values_bode_plot>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_values_bode_plot_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_values_bode_plot_write( this, base, pos, len );
    }
};
struct values_gptp_time : wrap<jdksavdecc_values_gptp_time>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_values_gptp_time_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_values_gptp_time_write( this, base, pos, len );
    }
};
struct values_sample_rate : wrap<jdksavdecc_values_sample_rate>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_values_sample_rate_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_values_sample_rate_write( this, base, pos, len );
    }
};
struct values_smpte_time : wrap<jdksavdecc_values_smpte_time>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_values_smpte_time_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_values_smpte_time_write( this, base, pos, len );
    }
};
struct values_vendor : wrap<jdksavdecc_values_vendor>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_values_vendor_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_values_vendor_write( this, base, pos, len );
    }
};
struct video_mapping : wrap<jdksavdecc_video_mapping>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_video_mapping_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_video_mapping_write( this, base, pos, len );
    }
};
struct video_mappings_format : wrap<jdksavdecc_video_mappings_format>
{
    ssize_t read( const uint8_t *base, ssize_t pos, size_t len )
    {
        return jdksavdecc_video_mappings_format_read( this, base, pos, len );
    }
    ssize_t write( uint8_t *base, ssize_t pos, size_t len ) const
    {
        return jdksavdecc_video_mappings_format_write( this, base, pos, len );
    }
};

struct printer : wrap<jdksavdecc_printer>
{
    printer()
    {
    }

    printer( char *buf, size_t buflen )
    {
        jdksavdecc_printer_init( this, buf, buflen );
    }

    void init( char *buf, size_t buflen )
    {
        jdksavdecc_printer_init( this, buf, buflen );
    }

    printer &print( eui48 const &v )
    {
        jdksavdecc_printer_print_eui48( this, *v.get() );
        return *this;
    }

    printer &print( eui64 const &v )
    {
        jdksavdecc_printer_print_eui64( this, *v.get() );
        return *this;
    }

    printer &print_streamid( eui64 const &v )
    {
        jdksavdecc_printer_print_streamid( this, *v.get() );
        return *this;
    }

    printer &print_label( const char *v )
    {
        jdksavdecc_printer_print_label( this, v );
        return *this;
    }

    printer &print_label( std::string const &v )
    {
        jdksavdecc_printer_print_label( this, v.c_str() );
        return *this;
    }

    printer &print_block( const uint8_t *p, size_t sz, size_t start_pos, size_t end_pos )
    {
        jdksavdecc_printer_print_block( this, p, sz, start_pos, end_pos );
        return *this;
    }

    printer &print_hexdigits( uint8_t v )
    {
        jdksavdecc_printer_print_hexdigits( this, v );
        return *this;
    }

    printer &print( uint8_t v )
    {
        jdksavdecc_printer_print_uint8( this, v );
        return *this;
    }

    printer &print( uint16_t v )
    {
        jdksavdecc_printer_print_uint16( this, v );
        return *this;
    }

    printer &print( uint32_t v )
    {
        jdksavdecc_printer_print_uint32( this, v );
        return *this;
    }

    printer &print( uint64_t v )
    {
        jdksavdecc_printer_print_uint64( this, v );
        return *this;
    }

    printer &print( avdecc_string const &v )
    {
        jdksavdecc_printer_print_string( this, v.get() );
        return *this;
    }

    printer &print( jdksavdecc_16bit_name const names[], uint16_t v )
    {
        jdksavdecc_printer_print_16bit_names( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_32bit_name const names[], uint32_t v )
    {
        jdksavdecc_printer_print_32bit_names( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_uint16_name const names[], uint16_t v )
    {
        jdksavdecc_printer_print_uint16_name( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_uint32_name const names[], uint32_t v )
    {
        jdksavdecc_printer_print_uint32_name( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_uint64_name const names[], uint64_t v )
    {
        jdksavdecc_printer_print_uint64_name( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_eui48_name const names[], eui48 v )
    {
        jdksavdecc_printer_print_eui48_name( this, names, v );
        return *this;
    }

    printer &print( jdksavdecc_eui64_name const names[], eui64 v )
    {
        jdksavdecc_printer_print_eui64_name( this, names, v );
        return *this;
    }

    printer &print( gptp_seconds const &v )
    {
        jdksavdecc_printer_print_gptp_seconds( this, v );
        return *this;
    }

#if !defined( JDKSAVDECC_CPP_NO_STDIO )
    bool output( FILE *f )
    {
        return fwrite( buf, pos, 1, f ) == 1;
    }
#endif
};

template <typename T>
printer &operator<<( printer &p, T &v )
{
    p.print( v );
    return p;
}

struct printer_with_buf : printer
{
    char *allocated_buf;

    printer_with_buf( size_t bufsz ) : allocated_buf( (char *)malloc( bufsz ) )
    {
        init( allocated_buf, bufsz );
    }

    ~printer_with_buf()
    {
        free( allocated_buf );
    }
};

#if !defined( JDKSAVDECC_CPP_NO_IOSTREAM )

inline std::ostream &operator<<( std::ostream &ostr, printer const &v )
{
    ostr << v.buf;
    return ostr;
}

inline std::ostream &operator<<( std::ostream &ostr, eui48 &v )
{
    printer p;
    char buf[128];
    p.init( buf, sizeof( buf ) );
    p.print( v );
    ostr << buf;
    return ostr;
}

inline std::ostream &operator<<( std::ostream &ostr, eui64 &v )
{
    jdksavdecc_printer p;
    char buf[128];
    jdksavdecc_printer_init( &p, buf, sizeof( buf ) );
    jdksavdecc_printer_print_eui64( &p, v );
    ostr << buf;
    return ostr;
}
#endif
}

#endif
