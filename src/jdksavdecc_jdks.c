
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
#include "jdksavdecc_jdks.h"

struct jdksavdecc_eui48 jdksavdecc_jdks_multicast_log = JDKSAVDECC_JDKS_MULTICAST_LOG;
struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_log_text = JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT;
struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_ipv4_parameters = JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS;


ssize_t jdksavdecc_jdks_log_control_read(
    struct jdksavdecc_jdks_log_control *p,
    void const *buf,
    ssize_t pos,
    size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos,len,JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN);
    if( r>=0 ) {
        jdksavdecc_eui64_read(&p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64+pos, len);
        if( jdksavdecc_eui64_compare(&jdksavdecc_jdks_aem_control_log_text,&p->vendor_eui64)==0 ) {
            jdksavdecc_uint16_read(&p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE+pos);
            if( p->blob_size > (JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT-JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN) &&
                p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE ) {
                uint16_t text_len =p->blob_size - (JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT-JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN);
                jdksavdecc_uint16_read(
                    &p->source_descriptor_type,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_TYPE+pos);

                jdksavdecc_uint16_read(
                    &p->source_descriptor_index,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_INDEX +pos);

                jdksavdecc_uint16_read(
                    &p->log_sequence_id,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_SEQUENCE_ID +pos);

                jdksavdecc_uint8_read(
                    &p->log_detail,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL,
                    len );

                if( text_len < JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN ) {
                    r=pos+JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT;
                    memcpy( p->text, (uint8_t const *)buf+r, text_len);
                    p->text[text_len+1]='\0';
                    r+=text_len;
                } else {
                    r=-1;
                }
            } else {
                r=-1;
            }
        } else {
        r=-1;
        }
    }
    return r;
}

