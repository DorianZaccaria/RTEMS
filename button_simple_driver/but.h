/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#ifndef __TEST_DRIVER_h
#define __TEST_DRIVER_h

#include <rtems/libio.h>
/* Driver cmds */
#define ALL_BUTS_OFF    0
#define BUT_ON          1

#ifdef __cplusplus
extern "C" {
#endif

#define BUTS_DRIVER_TABLE_ENTRY \
  { buts_initialize, buts_open, buts_close, NULL, \
    NULL, buts_control }



rtems_device_driver buts_initialize(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver buts_open(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver buts_close(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver buts_control(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
