#pragma once
#ifndef JDKSAVDECC_PDU_DISPATCH_H
#define JDKSAVDECC_PDU_DISPATCH_H

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

#include "jdksavdecc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_pdu_dispatch;
struct jdksavdecc_command_dispatch;
struct jdksavdecc_state_machines;


typedef ssize_t (*jdksavdecc_pdu_dispatch_proc)(
        struct jdksavdecc_pdu_dispatch *self,
        struct jdksavdecc_frame *frame,
        size_t pos
        );

struct jdksavdecc_pdu_dispatch
{
    uint32_t tag;
    void *additional;

    struct jdksavdecc_frame_sender *frame_sender;
    void (*tick)( struct jdksavdecc_pdu_dispatch *self, jdksavdecc_millisecond_time timestamp );

    void (*set_frame_sender)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame_sender *sender );
    jdksavdecc_pdu_dispatch_proc rx_frame;
    jdksavdecc_pdu_dispatch_proc unknown;
    jdksavdecc_pdu_dispatch_proc avtpv0;
    jdksavdecc_pdu_dispatch_proc avtpv1;
    jdksavdecc_pdu_dispatch_proc acmpdu;
    jdksavdecc_pdu_dispatch_proc adpdu;
    jdksavdecc_pdu_dispatch_proc aecpdu;
    jdksavdecc_pdu_dispatch_proc aecpdu_aa_command;
    jdksavdecc_pdu_dispatch_proc aecpdu_aa_response;
    jdksavdecc_pdu_dispatch_proc aecpdu_aem_command;
    jdksavdecc_pdu_dispatch_proc aecpdu_aem_response;
    jdksavdecc_pdu_dispatch_proc aecpdu_vendor_command;
    jdksavdecc_pdu_dispatch_proc aecpdu_vendor_response;
    jdksavdecc_pdu_dispatch_proc aecpdu_avc_command;
    jdksavdecc_pdu_dispatch_proc aecpdu_avc_response;
    jdksavdecc_pdu_dispatch_proc aecpdu_hdcp_apm_command;
    jdksavdecc_pdu_dispatch_proc aecpdu_hdcp_apm_response;
    jdksavdecc_pdu_dispatch_proc maap;

    struct jdksavdecc_command_dispatch *aem_command_dispatch;
    struct jdksavdecc_command_dispatch *aem_response_dispatch;

    struct jdksavdecc_state_machines *state_machines;
};


void jdksavdecc_pdu_dispatch_init( struct jdksavdecc_pdu_dispatch *self );
void jdksavdecc_pdu_dispatch_tick( struct jdksavdecc_pdu_dispatch *self, jdksavdecc_millisecond_time timestamp );
void jdksavdecc_pdu_dispatch_set_frame_sender( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame_sender *sender );

ssize_t jdksavdecc_pdu_dispatch_rx_frame( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_unknown( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_avtpv0( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_acmpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_adpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem_command( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem_response( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );

#ifdef __cplusplus
}
#endif

#endif


