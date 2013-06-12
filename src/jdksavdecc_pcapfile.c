
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
#include "jdksavdecc_pcapfile.h"
#include "jdksavdecc_pdu_dispatch.h"

#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE (0xa1b2c3d4L)
#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_SWAPPED (0xd4c3b2a1L)

struct jdksavdecc_pcapfile_header {
        uint32_t magic_number;   /* magic number */
        uint16_t version_major;  /* major version number */
        uint16_t version_minor;  /* minor version number */
        int32_t  thiszone;       /* GMT to local correction */
        uint32_t sigfigs;        /* accuracy of timestamps */
        uint32_t snaplen;        /* max length of captured packets, in octets */
        uint32_t network;        /* data link type */
};

struct jdksavdecc_pcapfile_record_header {
        uint32_t ts_sec;         /* timestamp seconds */
        uint32_t ts_usec;        /* timestamp microseconds */
        uint32_t incl_len;       /* number of octets of packet saved in file */
        uint32_t orig_len;       /* actual length of packet */
};


void jdksavdecc_pcapfile_reader_init(struct jdksavdecc_pcapfile_reader *self)
{
    self->f=0;
    self->swapped = 0;
    self->open = jdksavdecc_pcapfile_reader_open;
    self->close = jdksavdecc_pcapfile_reader_close;
    self->read_frame = jdksavdecc_pcapfile_reader_read_frame;
    self->dispatch_frames = jdksavdecc_pcapfile_reader_dispatch_frames;
    self->tick = 0;
}

int jdksavdecc_pcapfile_reader_open( struct jdksavdecc_pcapfile_reader *self, char const *fname )
{
    int r=0;
    self->f = fopen(fname, "rb" );
    if( self->f )
    {
        struct jdksavdecc_pcapfile_header file_header;
        if( fread(&file_header, sizeof(file_header), 1, self->f)==1 )
        {
            if( file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_SWAPPED )
            {
                self->swapped = 1;
                r=1;
            }
            else if( file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE )
            {
                self->swapped = 0;
                r=1;
            }
            
            if( self->swapped )
            {
                file_header.magic_number = jdksavdecc_endian_reverse_uint32(&file_header.magic_number);
                file_header.version_major = jdksavdecc_endian_reverse_uint16(&file_header.version_major);
                file_header.version_minor = jdksavdecc_endian_reverse_uint16(&file_header.version_minor);
                file_header.thiszone = (int32_t)jdksavdecc_endian_reverse_uint32((uint32_t *)&file_header.thiszone);
                file_header.sigfigs = jdksavdecc_endian_reverse_uint32(&file_header.sigfigs);
                file_header.snaplen = jdksavdecc_endian_reverse_uint32(&file_header.snaplen);
                file_header.network = jdksavdecc_endian_reverse_uint32(&file_header.network);
            }
        }
        
        // Error in header, close file
        if( !r )
        {
            fclose(self->f);
            self->f=0;
        }
    }
    return r;
}

void jdksavdecc_pcapfile_reader_close( struct jdksavdecc_pcapfile_reader *self )
{
    if( self->f )
    {
        fclose( self->f );
        self->f=0;
    }
}

int jdksavdecc_pcapfile_reader_read_frame( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_frame *frame )
{
    int r=0;
    if( self->f )
    {
        struct jdksavdecc_pcapfile_record_header frame_record;
        if( fread(&frame_record, sizeof(frame_record), 1, self->f)==1 )
        {
            uint8_t buf[2048];
            if( self->swapped )
            {                
                frame_record.ts_sec = jdksavdecc_endian_reverse_uint32( &frame_record.ts_sec );
                frame_record.ts_usec = jdksavdecc_endian_reverse_uint32( &frame_record.ts_usec );
                frame_record.incl_len = jdksavdecc_endian_reverse_uint32( &frame_record.incl_len );
                frame_record.orig_len = jdksavdecc_endian_reverse_uint32( &frame_record.orig_len );
            }
            
            if( frame_record.incl_len <= sizeof(buf) )
            {
                if( fread(buf,frame_record.incl_len,1, self->f )==1 )
                {
                    if( jdksavdecc_frame_read(frame,buf, 0, frame_record.incl_len ) == frame_record.incl_len )
                    {
                        frame->time = ((uint64_t)frame_record.ts_sec * 1000) + (frame_record.ts_usec / 1000 );
                        r=1;
                    }
                }
            }
            else
            {
                fprintf( stderr, "pcap file parse error\n");
                self->close(self);
            }
        }
    }
    return r;
}

int jdksavdecc_pcapfile_reader_dispatch_frames( struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_pdu_dispatch *dispatcher )
{
    int r=-1;
    jdksavdecc_time cur_time=0;
    
    while( self->f && r==-1 )
    {
        struct jdksavdecc_frame frame;
        if( self->read_frame(self,&frame) )
        {
            if (cur_time==0)
            {
                cur_time=frame.time;
            }
            if( self->tick || dispatcher->tick )
            {
                // simulate ticks every 100ms to get to this point
                while( r==-1 && cur_time >= frame.time + 100 )
                {
                    if( dispatcher->tick )
                    {
                        dispatcher->tick( dispatcher, cur_time );
                    }
                    if( self->tick )
                    {
                        if( self->tick( self, cur_time )==0 )
                        {
                            // tick wanted us to halt
                            r=0;
                            break;
                        }
                    }
                    cur_time+=100;
                }
            }
            // give the 'received' frame to the dispatcher
            if( r==-1 )
            {
                dispatcher->rx_frame( dispatcher, &frame, 0 );
            }
        }
    }
    return r;
}



void jdksavdecc_pcapfile_writer_init( struct jdksavdecc_pcapfile_writer *self )
{
    self->f = 0;
    self->close = jdksavdecc_pcapfile_writer_close;
    self->swapped = 0;
    self->inherited.send = jdksavdecc_pcapfile_writer_send;
}

int jdksavdecc_pcapfile_writer_open( struct jdksavdecc_pcapfile_writer *self, char const *fname )
{
    int r=0;
    self->f = fopen(fname, "wb" );
    if( self->f )
    {
        struct jdksavdecc_pcapfile_header file_header;
        file_header.magic_number = JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE;
        file_header.version_major = 2;
        file_header.version_major = 4;
        file_header.sigfigs = 0;
        file_header.snaplen = 2048;
        file_header.network = 1;
        
        if( fwrite(&file_header, sizeof(file_header), 1, self->f)==1 )
        {
            r=1;
        }

        // Error writing header, close file
        if( !r )
        {
            fprintf( stderr, "pcap file write error\n" );
            self->close( self );
        }
    }
    return r;
}

void jdksavdecc_pcapfile_writer_close( struct jdksavdecc_pcapfile_writer *self )
{
    if( self->f )
    {
        fclose(self->f);
        self->f=0;
    }
}


void jdksavdecc_pcapfile_writer_send( struct jdksavdecc_frame_sender *self_, struct jdksavdecc_frame const *frame )
{
    struct jdksavdecc_pcapfile_writer *self = (struct jdksavdecc_pcapfile_writer *)self_;
    uint8_t buf[2048];
    ssize_t len;
    struct jdksavdecc_pcapfile_record_header frame_record;
    len = jdksavdecc_frame_write(frame, buf, 0, sizeof(buf) );
    if( len>0 )
    {
        int r=0;
        frame_record.incl_len = (uint32_t)len;
        frame_record.orig_len = (uint32_t)len;
        frame_record.ts_sec = (uint32_t)(frame->time / 1000);
        frame_record.ts_usec = (uint32_t)((frame->time % 1000) * 1000);
        
        if( fwrite(&frame_record, sizeof(frame_record), 1, self->f )==1 )
        {
            if( fwrite(buf,len,1,self->f )==1 )
            {
                r=1;
            }            
        }
        
        if( r==0 )
        {
            fprintf( stderr, "pcap file write error\n" );
            self->close( self );
        }
    }
}





