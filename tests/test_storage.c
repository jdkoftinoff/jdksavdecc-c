
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
#include "test/jdksavdecc_test_descriptor_storage.h"

int main()
{
    bool r = false;
#ifdef TODO
    struct jdksavdecc_descriptor_storage storage;
    if ( jdksavdecc_test_descriptor_storage_create( &storage ) )
    {
        uint8_t descriptor_buffer[JDKSAVDECC_AEM_DESCRIPTOR_SIZE];
        uint16_t descriptor_len;

        descriptor_len = storage.base.read_descriptor(
            &storage.base, 0, JDKSAVDECC_DESCRIPTOR_ENTITY, 0, descriptor_buffer, sizeof( descriptor_buffer ) );
        if ( descriptor_len == 0 )
        {
            fprintf( stderr, "Unable to read entity descriptor\n" );
        }
        else
        {
            fprintf( stdout, "Read entity descriptor, length %d\n", descriptor_len );
            r = true;
        }
    }
#endif
    return r ? 0 : 255;
}
