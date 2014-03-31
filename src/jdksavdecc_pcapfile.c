
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

#if defined(FOPEN_MAX)

#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE (0xa1b2c3d4UL)
#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_SWAPPED (0xd4c3b2a1UL)

#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NANO_NATIVE (0xa1b23c4dUL)
#define JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NANO_SWAPPED (0x4d3cb2a1UL)

struct jdksavdecc_pcapfile_header {
    uint32_t magic_number;  /* magic number */
    uint16_t version_major; /* major version number */
    uint16_t version_minor; /* minor version number */
    int32_t thiszone;       /* GMT to local correction */
    uint32_t sigfigs;       /* accuracy of timestamps */
    uint32_t snaplen;       /* max length of captured packets, in octets */
    uint32_t network;       /* data link type */
};

struct jdksavdecc_pcapfile_record_header {
    uint32_t ts_sec;  /* timestamp seconds */
    uint32_t ts_usec; /* timestamp microseconds or nanoseconds when format is
                         nano */
    uint32_t incl_len; /* number of octets of packet saved in file */
    uint32_t orig_len; /* actual length of packet */
};

int jdksavdecc_pcapfile_reader_dispatch_with_no_file(struct jdksavdecc_pcapfile_reader *self,
                                                     struct jdksavdecc_state_machine *dispatcher);

int jdksavdecc_pcapfile_reader_dispatch_frames_with_file(struct jdksavdecc_pcapfile_reader *self,
                                                         struct jdksavdecc_state_machine *dispatcher);

void jdksavdecc_pcapfile_reader_init(struct jdksavdecc_pcapfile_reader *self,
                                     jdksavdecc_timestamp_in_microseconds minimum_time_to_synthesize,
                                     jdksavdecc_timestamp_in_microseconds time_step_in_microseconds) {
    self->f = 0;
    self->swapped = 0;
    self->nano = 0;
    self->minimum_time_to_synthesize = minimum_time_to_synthesize;
    self->time_step_in_microseconds = time_step_in_microseconds;
    self->destroy = jdksavdecc_pcapfile_reader_destroy;
    self->open = jdksavdecc_pcapfile_reader_open;
    self->close = jdksavdecc_pcapfile_reader_close;
    self->read_frame = jdksavdecc_pcapfile_reader_read_frame;
    self->dispatch_frames = jdksavdecc_pcapfile_reader_dispatch_frames;
    self->tick = 0;
}

void jdksavdecc_pcapfile_reader_destroy(struct jdksavdecc_pcapfile_reader *self) { self->close(self); }

int jdksavdecc_pcapfile_reader_open(struct jdksavdecc_pcapfile_reader *self, char const *fname) {
    int r = 0;

    // if fname is set then open the file
    if (fname) {
#ifdef _MSC_VER
        {
            errno_t e;
            e = fopen_s(&self->f, fname, "rb");
            if (e != 0) {
                self->f = 0;
            }
        }
#else
        self->f = fopen(fname, "rb");
#endif

        if (self->f) {
            struct jdksavdecc_pcapfile_header file_header;
            if (fread(&file_header, sizeof(file_header), 1, self->f) == 1) {
                if (file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_SWAPPED) {
                    self->swapped = 1;
                    self->nano = 0;
                    r = 1;
                } else if (file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE) {
                    self->swapped = 0;
                    self->nano = 0;
                    r = 1;
                } else if (file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NANO_SWAPPED) {
                    self->swapped = 1;
                    self->nano = 1;
                    r = 1;
                } else if (file_header.magic_number == JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NANO_NATIVE) {
                    self->swapped = 0;
                    self->nano = 1;
                    r = 1;
                }

                if (self->swapped) {
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
            if (!r) {
                fclose(self->f);
                self->f = 0;
            }
        }
    } else {
        // If fname is null then we don't try to open anything, we exist only to
        // synthesize ticks
        r = 1;
        self->f = 0;
    }

    return r;
}

void jdksavdecc_pcapfile_reader_close(struct jdksavdecc_pcapfile_reader *self) {
    if (self->f) {
        fclose(self->f);
        self->f = 0;
    }
}

int jdksavdecc_pcapfile_reader_read_frame(struct jdksavdecc_pcapfile_reader *self, struct jdksavdecc_frame *frame) {
    int r = 0;
    if (self->f) {
        struct jdksavdecc_pcapfile_record_header frame_record;
        if (fread(&frame_record, sizeof(frame_record), 1, self->f) == 1) {
            uint8_t buf[2048];
            if (self->swapped) {
                frame_record.ts_sec = jdksavdecc_endian_reverse_uint32(&frame_record.ts_sec);
                frame_record.ts_usec = jdksavdecc_endian_reverse_uint32(&frame_record.ts_usec);
                frame_record.incl_len = jdksavdecc_endian_reverse_uint32(&frame_record.incl_len);
                frame_record.orig_len = jdksavdecc_endian_reverse_uint32(&frame_record.orig_len);
            }

            if (frame_record.incl_len <= sizeof(buf)) {
                if (fread(buf, frame_record.incl_len, 1, self->f) == 1) {
                    if (jdksavdecc_frame_read(frame, buf, 0, frame_record.incl_len) == frame_record.incl_len) {
                        if (self->nano) {
                            frame->time = ((uint64_t)frame_record.ts_sec * 1000000)
                                          + (frame_record.ts_usec / 1000); // convert nano to micro
                        } else {
                            frame->time = ((uint64_t)frame_record.ts_sec * 1000000) + (frame_record.ts_usec);
                        }
                        r = 1;
                    }
                }
            } else {
                fprintf(stderr, "pcap file parse error\n");
                self->close(self);
            }
        }
    }
    return r;
}

int jdksavdecc_pcapfile_reader_dispatch_frames(struct jdksavdecc_pcapfile_reader *self,
                                               struct jdksavdecc_state_machine *dispatcher) {
    if (self->f) {
        return jdksavdecc_pcapfile_reader_dispatch_frames_with_file(self, dispatcher);
    } else {
        return jdksavdecc_pcapfile_reader_dispatch_with_no_file(self, dispatcher);
    }
}

int jdksavdecc_pcapfile_reader_dispatch_with_no_file(struct jdksavdecc_pcapfile_reader *self,
                                                     struct jdksavdecc_state_machine *dispatcher) {
    int r = 0;
    jdksavdecc_timestamp_in_microseconds cur_time = 0;

    // until we are finished dispatching all frames
    while (r == 0 && !dispatcher->terminated && cur_time < self->minimum_time_to_synthesize) {

        // notify the dispatcher about the tick time
        dispatcher->tick(dispatcher, cur_time);

        // notify self about the tick time
        if (self->tick && self->tick(self, cur_time) == 0) {
            r = 1;
        }

        cur_time += self->time_step_in_microseconds;
    }

    return r;
}

int jdksavdecc_pcapfile_reader_dispatch_frames_with_file(struct jdksavdecc_pcapfile_reader *self,
                                                         struct jdksavdecc_state_machine *dispatcher) {
    int r = 0;
    jdksavdecc_timestamp_in_microseconds cur_time = 0;
    jdksavdecc_timestamp_in_microseconds next_time = self->minimum_time_to_synthesize;

    // until we are finished dispatching all frames
    while (r == 0) {
        struct jdksavdecc_frame frame;
        int did_read_frame = 0;

        // Try read a frame from the file
        did_read_frame = self->read_frame(self, &frame);

        if (did_read_frame) {
            if (cur_time == 0) {
                // Synchronize our time to the beginning file time
                cur_time = frame.time;
                next_time = cur_time;
            } else {
                // Otherwise use the next packet time from the file as our
                // next_time
                next_time = frame.time;
            }
        } else {
            r = 1;
        }

        // Do we have tick functions to call?
        if (self->tick || dispatcher->tick) {
            // yes, simulate ticks every time_step_in_microseconds to get to
            // this point
            while (r == 0 && cur_time >= next_time + self->time_step_in_microseconds) {
                if (dispatcher->tick) {
                    // notify the dispatcher about the tick time
                    dispatcher->tick(dispatcher, cur_time);
                }
                if (self->tick) {
                    // notify self about the tick time
                    if (self->tick(self, cur_time) == 0) {
                        // tick proc wanted us to halt
                        r = 1;
                        break;
                    }
                }
                // advance the time
                cur_time += self->time_step_in_microseconds;
            }
        }

        // Synchronize the current time to the packet time if we jumped over it
        if (did_read_frame && cur_time > frame.time) {
            cur_time = frame.time;
        }
        // give the 'received' frame to the dispatcher
        if (r == 0 && did_read_frame) {
            dispatcher->rx_frame(dispatcher, &frame, 0);
        }
    }
    return r;
}

void jdksavdecc_pcapfile_writer_init(struct jdksavdecc_pcapfile_writer *self) {
    self->f = 0;
    self->destroy = jdksavdecc_pcapfile_writer_destroy;
    self->open = jdksavdecc_pcapfile_writer_open;
    self->close = jdksavdecc_pcapfile_writer_close;
    self->swapped = 0;
    self->inherited.send = jdksavdecc_pcapfile_writer_send;
}

void jdksavdecc_pcapfile_writer_destroy(struct jdksavdecc_pcapfile_writer *self) { self->close(self); }

int jdksavdecc_pcapfile_writer_open(struct jdksavdecc_pcapfile_writer *self, char const *fname) {
    int r = 0;
#ifdef _MSC_VER
    errno_t e;
    e = fopen_s(&self->f, fname, "wb");
    if (e != 0) {
        self->f = 0;
    }
#else
    self->f = fopen(fname, "wb");
#endif

    if (self->f) {
        struct jdksavdecc_pcapfile_header file_header;
        file_header.magic_number = JDKSAVDECC_PCAPFILE_HEADER_MAGIC_NATIVE;
        file_header.version_major = 2;
        file_header.version_major = 4;
        file_header.sigfigs = 0;
        file_header.snaplen = 2048;
        file_header.network = 1;

        if (fwrite(&file_header, sizeof(file_header), 1, self->f) == 1) {
            r = 1;
        }

        // Error writing header, close file
        if (!r) {
            fprintf(stderr, "pcap file write error\n");
            self->close(self);
        }
    }
    return r;
}

void jdksavdecc_pcapfile_writer_close(struct jdksavdecc_pcapfile_writer *self) {
    if (self->f) {
        fclose(self->f);
        self->f = 0;
    }
}

void jdksavdecc_pcapfile_writer_send(struct jdksavdecc_frame_sender *self_, struct jdksavdecc_frame const *frame) {
    struct jdksavdecc_pcapfile_writer *self = (struct jdksavdecc_pcapfile_writer *)self_;
    uint8_t buf[2048];
    ssize_t len;
    struct jdksavdecc_pcapfile_record_header frame_record;
    len = jdksavdecc_frame_write(frame, buf, 0, sizeof(buf));
    if (len > 0) {
        int r = 0;
        frame_record.incl_len = (uint32_t)len;
        frame_record.orig_len = (uint32_t)len;
        frame_record.ts_sec = (uint32_t)(frame->time / 1000000);
        frame_record.ts_usec = (uint32_t)(frame->time % 1000000);

        if (fwrite(&frame_record, sizeof(frame_record), 1, self->f) == 1) {
            if (fwrite(buf, len, 1, self->f) == 1) {
                r = 1;
            }
        }

        if (r == 0) {
            fprintf(stderr, "pcap file write error\n");
            self->close(self);
        }
    }
}
#else
const char *jdksavdecc_pcapfile_file = __FILE__;
#endif
