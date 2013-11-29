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
#include "jdksavdecc_maap_print.h"

struct jdksavdecc_uint16_name jdksavdecc_maap_print_message_type[] = {
    {JDKSAVDECC_MAAP_PROBE, "PROBE"},       {JDKSAVDECC_MAAP_DEFEND, "DEFEND"},
    {JDKSAVDECC_MAAP_ANNOUNCE, "ANNOUNCE"}, {0, 0}};

void jdksavdecc_maap_print(struct jdksavdecc_printer *self,
                           struct jdksavdecc_maap const *p) {
    jdksavdecc_printer_print_label(self, "message_type");
    jdksavdecc_printer_print_uint16_name(
        self, jdksavdecc_maap_print_message_type, p->header.message_type);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "maap_version");
    jdksavdecc_printer_print_uint16(self, p->header.maap_version);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "maap_data_length");
    jdksavdecc_printer_print_uint16(self, p->header.maap_data_length);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "requested_start_address");
    jdksavdecc_printer_print_eui48(self, p->requested_start_address);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "requested_count");
    jdksavdecc_printer_print_uint16(self, p->requested_count);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "conflict_start_address");
    jdksavdecc_printer_print_eui48(self, p->conflict_start_address);
    jdksavdecc_printer_print_eol(self);

    jdksavdecc_printer_print_label(self, "conflict_count");
    jdksavdecc_printer_print_uint16(self, p->conflict_count);
    jdksavdecc_printer_print_eol(self);
}
