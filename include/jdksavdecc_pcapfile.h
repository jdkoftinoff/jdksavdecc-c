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
struct jdksavdecc_pcapfile_reader
{
    FILE *f;
    int swapped;
    int nano;
    void (*destroy)( struct jdksavdecc_pcapfile_reader * );

    int (*open)( struct jdksavdecc_pcapfile_reader *self, char const *fname );
    void (*close)( struct jdksavdecc_pcapfile_reader *self );
    int (*read_frame)( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_frame *frame );
    int (*dispatch_frames)( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_pdu_dispatch *dispatcher );
    int (*tick)( struct jdksavdecc_pcapfile_reader *self, jdksavdecc_microsecond_time time );
};

void jdksavdecc_pcapfile_reader_init(struct jdksavdecc_pcapfile_reader *self);
void jdksavdecc_pcapfile_reader_destroy(struct jdksavdecc_pcapfile_reader *self);
int jdksavdecc_pcapfile_reader_open( struct jdksavdecc_pcapfile_reader *self, char const *fname );
void jdksavdecc_pcapfile_reader_close( struct jdksavdecc_pcapfile_reader *self );
int jdksavdecc_pcapfile_reader_read_frame( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_frame *frame );
int jdksavdecc_pcapfile_reader_dispatch_frames( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_pdu_dispatch *dispatcher );

struct jdksavdecc_pcapfile_writer
{
    struct jdksavdecc_frame_sender inherited;
    
    FILE *f;
    int swapped;

    void (*destroy)( struct jdksavdecc_pcapfile_writer * );
    int (*open)( struct jdksavdecc_pcapfile_writer *self, char const *fname );
    void (*close)( struct jdksavdecc_pcapfile_writer *self );
    
    
};

void jdksavdecc_pcapfile_writer_init( struct jdksavdecc_pcapfile_writer *self );
void jdksavdecc_pcapfile_writer_destroy( struct jdksavdecc_pcapfile_writer *self );
int jdksavdecc_pcapfile_writer_open( struct jdksavdecc_pcapfile_writer *self, char const *fname );
void jdksavdecc_pcapfile_writer_close( struct jdksavdecc_pcapfile_writer *self );

void jdksavdecc_pcapfile_writer_send( struct jdksavdecc_frame_sender *self, struct jdksavdecc_frame const *frame );


/*@}*/

#ifdef __cplusplus
}
#endif

#endif

