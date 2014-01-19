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

#if defined(__AVR__)

#if !defined(__cplusplus)
#define inline __inline__
#endif

typedef int ssize_t;

#define JDKSAVDECC_TIMESTAMP_TYPE uint32_t

#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#ifndef PRIi8
#define PRIi8 "hd"
#endif

#ifndef PRIu8
#define PRIu8 "hu"
#endif

#ifndef PRIx8
#define PRIx8 "hx"
#endif

#ifndef PRIi16
#define PRIi16 "d"
#endif

#ifndef PRIu16
#define PRIu16 "u"
#endif

#ifndef PRIx16
#define PRIx16 "x"
#endif

#ifndef PRIi32
#define PRIi32 "ld"
#endif

#ifndef PRIu32
#define PRIu32 "lu"
#endif

#ifndef PRIx32
#define PRIx32 "lx"
#endif

#ifndef PRIi64
#define PRIi64 "ld"
#endif

#ifndef PRIu64
#define PRIu64 "lu"
#endif

#ifndef PRIx64
#define PRIx64 "lx"
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS (0)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE (1)
#endif

#endif
