
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
#include "jdksavdecc_test.h"

#if defined(FOPEN_MAX)

int jdksavdecc_test_run(char const *in_file_name,
                        char const *out_file_name,
                        struct jdksavdecc_pdu_dispatch *pdu_dispatch,
                        int (*tick)(struct jdksavdecc_pcapfile_reader *self, jdksavdecc_timestamp_in_microseconds time),
                        jdksavdecc_timestamp_in_microseconds minimum_time_to_synthesize,
                        jdksavdecc_timestamp_in_microseconds time_step_in_microseconds) {
    struct jdksavdecc_pcapfile_reader reader;
    struct jdksavdecc_pcapfile_writer writer;

    jdksavdecc_pcapfile_reader_init(&reader, minimum_time_to_synthesize, time_step_in_microseconds);
    if (!jdksavdecc_pcapfile_reader_open(&reader, in_file_name)) {
#ifdef _MSC_VER
        char buf[1024];
        strerror_s(buf, sizeof(buf), errno);
        fprintf(stderr, "Error %s reading file: %s\n", buf, in_file_name);
#else
        fprintf(stderr, "Error %s reading file: %s\n", strerror(errno), in_file_name);
#endif
        return 0;
    }
    reader.tick = tick;

    jdksavdecc_pcapfile_writer_init(&writer);
    if (!jdksavdecc_pcapfile_writer_open(&writer, out_file_name)) {
#ifdef _MSC_VER
        char buf[1024];
        strerror_s(buf, sizeof(buf), errno);
        fprintf(stderr, "Error %s writing file: %s\n", buf, in_file_name);
#else
        fprintf(stderr, "Error %s writing file: %s\n", strerror(errno), in_file_name);
#endif
        reader.close(&reader);
        return 0;
    }

    reader.tick = tick;

    pdu_dispatch->base.frame_sender = &writer.inherited;

    reader.dispatch_frames(&reader, pdu_dispatch);

    reader.close(&reader);
    writer.close(&writer);
    return 1;
}

#else
const char *jdksavdecc_test_file = __FILE__;
#endif
