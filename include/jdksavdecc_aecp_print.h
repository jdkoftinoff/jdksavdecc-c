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
#include "jdksavdecc_aecp.h"
#include "jdksavdecc_aecp_aa.h"
#include "jdksavdecc_aecp_aem.h"
#include "jdksavdecc_aecp_avc.h"
#include "jdksavdecc_aecp_hdcp_apm.h"
#include "jdksavdecc_aecp_vendor.h"
#include "jdksavdecc_print.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup aecp AECP - Clause 9 */
/*@{*/

/** \addtogroup aecp_print AECP Print
 *  @todo aecp_print
*/
/*@{*/

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_print_message_type[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_print_status[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_aem_print_status[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_aa_print_status[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_aa_print_mode[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_avc_print_status[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_hdcp_apm_print_status[];

extern struct jdksavdecc_uint16_name jdksavdecc_aecp_vendor_print_status[];


void jdksavdecc_aecp_common_control_header_print(struct jdksavdecc_printer *self,
                                                 struct jdksavdecc_aecpdu_common_control_header const *p);

void jdksavdecc_aecp_common_print(struct jdksavdecc_printer *self,
                                  struct jdksavdecc_aecpdu_common const *p);


void jdksavdecc_aecp_print(struct jdksavdecc_printer *self,
                           struct jdksavdecc_aecpdu_common const *msg,
                           void const *p,
                           ssize_t pos,
                           size_t len);

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif
