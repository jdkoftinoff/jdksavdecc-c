  
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
#include <unistd.h>
#include "jdksavdecc_pcapfile.h"
#include "jdksavdecc_pdu_dispatch.h"
#include "jdksavdecc_test.h"
#include "jdksavdecc_acmp_conversation_tester.h"



int main( int argc, char **argv )
{
    int r=0;
    const char *in_file_name="test_jdksavdecc_acmp_conversations.pcap";
    const char *out_file_name="output.pcap";
    struct jdksavdecc_pdu_dispatch pdu_dispatch;
    jdksavdecc_timestamp_in_microseconds minimum_time_to_synthesize = 5000000;
    jdksavdecc_timestamp_in_microseconds time_step_in_microseconds = 10000;

    chdir(getenv("HOME"));

    if( argc>1 )
    {
        in_file_name=argv[1];
    }
    if( argc>2 )
    {
        out_file_name=argv[2];
    }

    jdksavdecc_log_info("%8s:%s","Starting",argv[0]);
    
    jdksavdecc_pdu_dispatch_init(&pdu_dispatch);
    {
        struct jdksavdecc_state_machine my_acmp_scanner;
        
        pdu_dispatch.acmp_controller_state_machines->add_state_machine(
            pdu_dispatch.acmp_controller_state_machines,
            &my_acmp_scanner
            );
        
        r = jdksavdecc_test_run(
                    in_file_name,
                    out_file_name,
                    &pdu_dispatch,
                    0,
                    minimum_time_to_synthesize,
                    time_step_in_microseconds
                    );
    }
    return (r!=0) ? EXIT_SUCCESS : EXIT_FAILURE;
}




