/**
 * @file
 *
 * @ingroup LibIOFSOps File System Operations 
 *
 * @brief RTEMS Default File System evaluates relative pathname to absolute
 */

/*
 * Copyright (c) 2012 embedded brains GmbH.  All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/libio_.h>

void rtems_filesystem_default_eval_path(
  rtems_filesystem_eval_path_context_t *ctx
)
{
  ctx->pathlen = 0;
  rtems_filesystem_location_detach(&ctx->currentloc);
}
