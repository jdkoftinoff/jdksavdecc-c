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
#include "jdksavdecc_entity_manager.h"
#include "jdksavdecc_controller_manager.h"

#ifdef TODO
bool jdksavdecc_controller_manager_init(
        struct jdksavdecc_controller_manager *self,
        struct jdksavdecc_entity_model *entity_model,
        int symbol_dispatch_table_num_entries,
        struct jdksavdecc_symbol_dispatch *symbol_dispatch_table,
        void *context,
        void (*frame_send)(struct jdksavdecc_entity_manager *, void *, const uint8_t *, uint16_t) ) {
    bool r=false;
    r=jdksavdecc_entity_manager_init(
        &self->base,
        entity_model,
        symbol_dispatch_table_num_entries,
        symbol_dispatch_table,
        context,
        frame_send);
    if( r ) {
        self->base.destroy = jdksavdecc_controller_manager_destroy;
    }
    return r;
}
#else

const char *jdksavdecc_controller_manager_file = __FILE__;

#endif

