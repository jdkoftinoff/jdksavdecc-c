#pragma once
#ifndef JDKSAVDECC_PCAPFILE_H
#define JDKSAVDECC_PCAPFILE_H

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
#include "jdksavdecc_util.h"
#include "jdksavdecc_pdu.h"

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup pcapfile pcap file */
/*@{*/

struct jdksavdecc_pdu_dispatch;

int jdksavdecc_pcapfile_open_for_reading( FILE *f );
int jdksavdecc_pcapfile_read( FILE *f, struct jdksavdecc_frame *frame );
int jdksavdecc_pcapfile_read_all( FILE *f, struct jdksavdecc_pdu_dispatch *dispatcher );

int jdksavdecc_pcapfile_open_for_writing( FILE *f );
int jdksavdecc_pcapfile_write( FILE *f, struct jdksavdecc_frame const *frame );

struct jdksavdecc_pcapfile_sender
{
    struct jdksavdecc_frame_sender base;
    FILE *f;
};

int jdksavdecc_pcapfile_frame_sender( struct jdksavdecc_pcapfile_sender *self, struct jdksavdecc_frame const *frame );


/*@}*/

#ifdef __cplusplus
}
#endif

#endif

