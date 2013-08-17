#pragma once
#ifndef JDKSAVDECC_WORLD_H
#define JDKSAVDECC_WORLD_H

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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <ctype.h>

#ifdef _MSC_VER
# include <BaseTsd.h> 
# include "jdksavdecc_msstdint.h"
# include "jdksavdecc_msinttypes.h"
# ifndef ssize_t
#  define ssize_t SSIZE_T
# endif
# ifndef inline
#  define inline __inline
# endif
#else
# include <stdint.h>
# include <inttypes.h>
#endif

#define JDKSAVDECC_LOG_TYPE_NONE (0)
#define JDKSAVDECC_LOG_TYPE_STDERR (1)
#define JDKSAVDECC_LOG_TYPE_SYSLOG (2)

#ifndef JDKSAVDECC_LOG_TYPE
# define JDKSAVDECC_LOG_TYPE (JDKSAVDECC_LOG_TYPE_STDERR)
#endif

#ifndef JDKSAVDECC_ENABLE_LOG
# define JDKSAVDECC_ENABLE_LOG (1)
#endif

#ifndef JDKSAVDECC_LOG_PREFIX
# define JDKSAVDECC_LOG_PREFIX ""
#endif

#if JDKSAVDECC_ENABLE_LOG
# if JDKSAVDECC_LOG_TYPE == JDKSAVDECC_LOG_TYPE_NONE
#  ifndef jdksavdecc_do_log
#   define jdksavdecc_do_log(prefix,fmt,...)
#  endif
# elif JDKSAVDECC_LOG_TYPE == JDKSAVDECC_LOG_TYPE_STDERR
#  ifndef jdksavdecc_do_log
#   define jdksavdecc_do_log(prefix,fmt,...) fprintf(stderr,prefix # fmt "\n", ## __VA_ARGS__ )
#  endif
# elif JDKSAVDECC_LOG_TYPE == JDKSAVDECC_LOG_TYPE_SYSLOG
#  include <syslog.h>
#  ifndef jdksavdecc_do_log
#   define jdksavdecc_do_log(prefix,fmt,...) syslog( LOG_INFO, prefix # fmt, ## __VA_ARGS__ )
#  endif
# endif
#else
# define jdksavdecc_do_log(prefix,fmt,...)
#endif

#define jdksavdecc_log(fmt,...) jdksavdecc_do_log(JDKSAVDECC_LOG_PREFIX,fmt,JDKSAVDECC_LOG_SUFFIX, ## __VA_ARGS__ )

#endif


