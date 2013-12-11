#pragma once

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

#ifdef __cplusplus
extern "C" {
#endif

struct jdksavdecc_16bit_name {
    uint16_t bit_value;
    char const *name;
};

struct jdksavdecc_32bit_name {
    uint32_t bit_value;
    char const *name;
};

struct jdksavdecc_uint16_name {
    uint16_t value;
    char const *name;
};

struct jdksavdecc_uint32_name {
    uint32_t value;
    char const *name;
};

struct jdksavdecc_uint64_name {
    uint64_t value;
    char const *name;
};

struct jdksavdecc_eui48_name {
    struct jdksavdecc_eui48 value;
    char const *name;
};

struct jdksavdecc_eui64_name {
    struct jdksavdecc_eui64 value;
    char const *name;
};

char const *jdksavdecc_get_name_for_16bit_value(struct jdksavdecc_16bit_name const names[], uint16_t v);
uint16_t jdksavdecc_get_16bit_value_for_name(struct jdksavdecc_16bit_name const names[], char const *name);
char const *jdksavdecc_get_name_for_32bit_value(struct jdksavdecc_32bit_name const names[], uint32_t v);
uint16_t jdksavdecc_get_32bit_value_for_name(struct jdksavdecc_32bit_name const names[], char const *name);

char const *jdksavdecc_get_name_for_uint16_value(struct jdksavdecc_uint16_name const names[], uint16_t v);
uint16_t jdksavdecc_get_uint16_value_for_name(struct jdksavdecc_uint16_name const names[], char const *name);

char const *jdksavdecc_get_name_for_uint32_value(struct jdksavdecc_uint32_name const names[], uint32_t v);
uint32_t jdksavdecc_get_uint32_value_for_name(struct jdksavdecc_uint32_name const names[], char const *name);

char const *jdksavdecc_get_name_for_uint64_value(struct jdksavdecc_uint64_name const names[], uint64_t v);
uint64_t jdksavdecc_get_uint64_value_for_name(struct jdksavdecc_uint64_name const names[], char const *name);

char const *jdksavdecc_get_name_for_eui48_value(struct jdksavdecc_eui48_name const names[], struct jdksavdecc_eui48 v);
struct jdksjdksavdecc_eui48 const *avdecc_get_eui48_value_for_name(struct jdksavdecc_eui48_name const names[],
                                                                   char const *name);

char const *jdksavdecc_get_name_for_eui64_value(struct jdksavdecc_eui64_name const names[], struct jdksavdecc_eui64 v);
struct jdksavdecc_eui64 const *avdecc_get_eui64_value_for_name(struct jdksavdecc_eui64_name const names[], char const *name);

struct jdksavdecc_printer {
    char *buf;
    size_t max_len;
    size_t pos;
};

static inline void jdksavdecc_printer_init(struct jdksavdecc_printer *self, char *buf, size_t max_len) {
    self->buf = buf;
    self->max_len = max_len;
    self->pos = 0;
}

static inline void jdksavdecc_printer_printc(struct jdksavdecc_printer *self, char v) {
    if (self->max_len - self->pos > 2) {
        self->buf[self->pos++] = v;
        self->buf[self->pos] = '\0';
    }
}

void jdksavdecc_printer_print(struct jdksavdecc_printer *self, const char *fmt);

static inline void jdksavdecc_printer_print_eol(struct jdksavdecc_printer *self) { jdksavdecc_printer_printc(self, '\n'); }

void jdksavdecc_printer_print_label(struct jdksavdecc_printer *self, const char *v);

void jdksavdecc_printer_print_hexdigits(struct jdksavdecc_printer *self, uint8_t v);

void jdksavdecc_printer_print_block(
    struct jdksavdecc_printer *self, const uint8_t *p, size_t sz, size_t start_pos, size_t end_pos);

void jdksavdecc_printer_print_uint8(struct jdksavdecc_printer *self, uint8_t v);
void jdksavdecc_printer_print_uint16(struct jdksavdecc_printer *self, uint16_t v);
void jdksavdecc_printer_print_uint32(struct jdksavdecc_printer *self, uint32_t v);
void jdksavdecc_printer_print_uint64(struct jdksavdecc_printer *self, uint64_t v);
void jdksavdecc_printer_print_eui48(struct jdksavdecc_printer *self, struct jdksavdecc_eui48 v);
void jdksavdecc_printer_print_eui64(struct jdksavdecc_printer *self, struct jdksavdecc_eui64 v);
void jdksavdecc_printer_print_streamid(struct jdksavdecc_printer *self, struct jdksavdecc_eui64 v);
void jdksavdecc_printer_print_string(struct jdksavdecc_printer *self, struct jdksavdecc_string const *v);
void jdksavdecc_printer_print_gptp_seconds(struct jdksavdecc_printer *self, struct jdksavdecc_gptp_seconds v);

void jdksavdecc_printer_print_16bit_names(struct jdksavdecc_printer *self,
                                          struct jdksavdecc_16bit_name const names[],
                                          uint16_t v);
void jdksavdecc_printer_print_32bit_names(struct jdksavdecc_printer *self,
                                          struct jdksavdecc_32bit_name const names[],
                                          uint32_t v);
void jdksavdecc_printer_print_uint16_name(struct jdksavdecc_printer *self,
                                          struct jdksavdecc_uint16_name const names[],
                                          uint16_t v);
void jdksavdecc_printer_print_uint32_name(struct jdksavdecc_printer *self,
                                          struct jdksavdecc_uint32_name const names[],
                                          uint32_t v);
void jdksavdecc_printer_print_uint64_name(struct jdksavdecc_printer *self,
                                          struct jdksavdecc_uint64_name const names[],
                                          uint64_t v);
void jdksavdecc_printer_print_eui48_name(struct jdksavdecc_printer *self,
                                         struct jdksavdecc_eui48_name const names[],
                                         struct jdksavdecc_eui48 v);
void jdksavdecc_printer_print_eui64_name(struct jdksavdecc_printer *self,
                                         struct jdksavdecc_eui64_name const names[],
                                         struct jdksavdecc_eui64 v);

extern char jdksavdecc_hexdig[16];

#ifdef __cplusplus
}
#endif
