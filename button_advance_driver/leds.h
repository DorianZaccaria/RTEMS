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
#define ALL_LEDS_OFF    0
#define LED_ON          1

#ifdef __cplusplus
extern "C" {
#endif

#define LEDS_DRIVER_TABLE_ENTRY \
  { leds_initialize, leds_open, leds_close, NULL, \
    NULL, leds_control }



rtems_device_driver leds_initialize(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver leds_open(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver leds_close(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

rtems_device_driver leds_control(
  rtems_device_major_number,
  rtems_device_minor_number,
  void *
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
