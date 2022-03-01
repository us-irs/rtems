/**
 * @file
 *
 * @ingroup LibIO
 */

/*
 * Copyright (c) 2013 embedded brains GmbH.  All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>

#include <rtems/libio.h>

void rtems_libio_exit(void)
{
  (void)close(0);
  (void)close(1);
  (void)close(2);
}
