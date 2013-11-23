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

#ifndef JDKSAVDECC_WORLD_H
#include "jdksavdecc_world.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup log logging
*/
/*@{*/

enum {
    JDKSAVDECC_SUBSYSTEM_GENERIC = 0,
    JDKSAVDECC_SUBSYSTEM_PDU,
    JDKSAVDECC_SUBSYSTEM_AEM,
    JDKSAVDECC_SUBSYSTEM_PROXY_APC,
    JDKSAVDECC_SUBSYSTEM_PROXY_APS,
    JDKSAVDECC_SUBSYSTEM_CONTROLLER,
    JDKSAVDECC_SUBSYSTEM_ADVERTISER,
    JDKSAVDECC_SUBSYSTEM_DISCOVER,
    JDKSAVDECC_SUBSYSTEM_LISTENER,
    JDKSAVDECC_SUBSYSTEM_TALKER,
    JDKSAVDECC_SUBSYSTEM_RESPONDER,
    JDKSAVDECC_SUBSYSTEM_MAAP,
    JDKSAVDECC_SUBSYSTEM_ENTITY
};

extern void (*jdksavdecc_log_debug)(const char *fmt, ...);
extern void (*jdksavdecc_log_info)(const char *fmt, ...);
extern void (*jdksavdecc_log_warning)(const char *fmt, ...);
extern void (*jdksavdecc_log_error)(const char *fmt, ...);
extern bool jdksavdecc_log_subsystem_enable[32];

#ifndef log_debug
#ifdef JDKSAVDECC_DISABLE_LOG_DEBUG
#define log_debug(subsystem, ...)
#else
#define log_debug(subsystem, ...)                                              \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_debug) {                                            \
            jdksavdecc_log_debug(__VA_ARGS__);                                 \
        }                                                                      \
    } while (false)
#endif
#endif

#ifndef log_info
#ifdef JDKSAVDECC_DISABLE_LOG_INFO
#define log_info(subsystem, ...)
#else
#define log_info(subsystem, ...)                                               \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_info) {                                             \
            jdksavdecc_log_info(__VA_ARGS__);                                  \
        }                                                                      \
    } while (false)
#endif
#endif

#ifndef log_warning
#ifdef JDKSAVDECC_DISABLE_LOG_WARNING
#define log_warning(subsystem, ...)
#else
#define log_warning(subsystem, ...)                                            \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_warning) {                                          \
            jdksavdecc_log_warning(__VA_ARGS__);                               \
        }                                                                      \
    } while (false)
#endif
#endif

#ifndef log_error
#ifdef JDKSAVDECC_DISABLE_LOG_ERROR
#define log_error(subsystem, ...)
#else
#define log_error(subsystem, ...)                                              \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_error) {                                            \
            jdksavdecc_log_error(__VA_ARGS__);                                 \
        }                                                                      \
    } while (false)
#endif
#endif

#ifndef log_enter
#ifdef JDKSAVDECC_DISABLE_LOG_ENTER
#define log_enter(subsystem)
#else
#define log_enter(subsystem)                                                   \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_debug) {                                            \
            jdksavdecc_log_debug("ENTER:%s", __FUNCTION__);                    \
        }                                                                      \
    } while (false)
#endif
#endif

#ifndef log_exit
#ifdef JDKSAVDECC_DISABLE_LOG_EXIT
#define log_exit(subsystem)
#else
#define log_exit(subsystem)                                                    \
    do {                                                                       \
        if (jdksavdecc_log_subsystem_enable[(subsystem)] &&                    \
            jdksavdecc_log_debug) {                                            \
            jdksavdecc_log_debug("EXIT :%s", __FUNCTION__);                    \
        }                                                                      \
    } while (false)
#endif
#endif

/*@}*/

#ifdef __cplusplus
}
#endif
