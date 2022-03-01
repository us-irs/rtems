/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup RTEMSScoreThread
 *
 * @brief This source file contains the implementation of
 *   _Thread_Iterate().
 */

/*
 * Copyright (c) 2016 embedded brains GmbH.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/score/threadimpl.h>

void _Thread_Iterate(
  Thread_Visitor  visitor,
  void           *arg
)
{
  int api_index;

  for ( api_index = 1 ; api_index <= OBJECTS_APIS_LAST ; ++api_index ) {
    const Objects_Information *information;
    Objects_Maximum            maximum;
    Objects_Maximum            index;

    _Assert( _Objects_Information_table[ api_index ] != NULL );
    information = _Objects_Information_table[ api_index ][ 1 ];

    if ( information == NULL ) {
      continue;
    }

    maximum = _Objects_Get_maximum_index( information );

    for ( index = 0 ; index < maximum ; ++index ) {
      Thread_Control *the_thread;

      the_thread = (Thread_Control *) information->local_table[ index ];

      if ( the_thread != NULL ) {
        bool done;

        done = (* visitor )( the_thread, arg );

        if ( done ) {
          return;
        }
      }
    }
  }
}
