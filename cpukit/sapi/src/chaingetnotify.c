/**
 * @file
 *
 * @ingroup RTEMSAPIClassicChains
 *
 * @brief This source file contains the implementation of
 *   rtems_chain_get_with_notification().
 */

/*
 * Copyright (c) 2010 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/chain.h>

rtems_status_code rtems_chain_get_with_notification(
  rtems_chain_control *chain,
  rtems_id task,
  rtems_event_set events,
  rtems_chain_node **node
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  bool is_empty = rtems_chain_get_with_empty_check( chain, node );

  if ( is_empty ) {
    sc = rtems_event_send( task, events );
  }

  return sc;
}
