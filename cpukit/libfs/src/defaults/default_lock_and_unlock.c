/**
 * @file
 *
 * @ingroup LibIOFSOps File System Operations 
 *
 * @brief RTEMS Default File System locks and unlocks rtems filesystem
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

void rtems_filesystem_default_lock(
  const rtems_filesystem_mount_table_entry_t *mt_entry
)
{
  rtems_libio_lock();
}

void rtems_filesystem_default_unlock(
  const rtems_filesystem_mount_table_entry_t *mt_entry
)
{
  rtems_libio_unlock();
}
