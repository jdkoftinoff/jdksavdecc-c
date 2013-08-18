#pragma once
#ifndef JDKSAVDECC_STATE_MACHINES_H
#define JDKSAVDECC_STATE_MACHINES_H

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
#include "jdksavdecc_state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup state_machines jdksavdecc_state_machines - A collection of jdksavdecc_state_machine objects */
/*@{*/


#ifndef JDKSAVDECC_STATE_MACHINES_ENABLE_LOG
# define JDKSAVDECC_STATE_MACHINES_ENABLE_LOG (1)
#endif

#if JDKSAVDECC_STATE_MACHINES_ENABLE_LOG
# define jdksavdecc_state_machines_log(fmt, ...) jdksavdecc_do_log("jdksavdecc_state_machines:%p:%s:",fmt, self, __FUNCTION__, ## __VA_ARGS__ )
# ifndef jdksavdecc_state_machines_log_enter
#  define jdksavdecc_state_machines_log_enter() jdksavdecc_state_machines_log("Enter")
# endif
# ifndef jdksavdecc_state_machines_log_exit
#  define jdksavdecc_state_machines_log_exit() jdksavdecc_state_machines_log("Exit")
# endif
#else
# define jdksavdecc_state_machines_log(fmt, ...)
# define jdksavdecc_state_machines_log_enter()
# define jdksavdecc_state_machines_log_exit()
#endif


struct jdksavdecc_state_machines
{
    struct jdksavdecc_state_machine base;

    int num_state_machines;
    int max_state_machines;
    struct jdksavdecc_state_machine **state_machines;

    int (*add_state_machine)(
            struct jdksavdecc_state_machines *self,
            struct jdksavdecc_state_machine *sm
            );
};

int jdksavdecc_state_machines_init(
        struct jdksavdecc_state_machines *self,
        int max_state_machines,
        struct jdksavdecc_frame_sender *frame_sender,
        uint32_t tag,
        void *additional
        );

void jdksavdecc_state_machines_destroy(
        struct jdksavdecc_state_machine *self
        );

void jdksavdecc_state_machines_terminate(
        struct jdksavdecc_state_machine *self
        );

int jdksavdecc_state_machines_tick(
        struct jdksavdecc_state_machine *self,
        jdksavdecc_microsecond_time timestamp
        );

ssize_t jdksavdecc_state_machines_rx_frame(
        struct jdksavdecc_state_machine *self,
        struct jdksavdecc_frame *rx_frame,
        size_t pos
        );

int jdksavdecc_state_machines_add_state_machine(
        struct jdksavdecc_state_machines *self,
        struct jdksavdecc_state_machine *s
        );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif


