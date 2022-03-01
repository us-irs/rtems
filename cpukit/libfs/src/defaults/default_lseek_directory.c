/**
 * @file
 *
 * @ingroup LibIOFSOps File System Operations 
 *
 * @brief RTEMS Default File System reposits read/write file offset directory
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

off_t rtems_filesystem_default_lseek_directory(
  rtems_libio_t *iop,
  off_t offset,
  int whence
)
{
  off_t rv = 0;

  if ( offset == 0 && whence == SEEK_SET ) {
    iop->offset = 0;
  } else {
    errno = EINVAL;
    rv = -1;
  }

  return rv;
}
