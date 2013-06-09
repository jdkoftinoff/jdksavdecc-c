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

struct jdksavdecc_pdu_dispatch
{
    ssize_t (*avtp)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*avtpv0)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*avtpv1)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*acmpdu)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*adpdu)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_aa)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_aecp)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_aem)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_vendor)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_avc)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*aecpdu_hdcp_apm)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
    ssize_t (*maap)( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
};

ssize_t jdksavdecc_pdu_dispatch_avtp( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_avtpv0( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_avtpv1( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_acmpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_aa( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_aecp( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_aem( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_vendor( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_avc( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_aecpdu_hdcp_apm( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );
ssize_t jdksavdecc_pdu_dispatch_maap( struct jdksavdecc_pdu_dispatch *self, struct jdksavdecc_frame *frame, size_t pos );

#endif


