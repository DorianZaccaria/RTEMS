/*
 * RTEMS leds driver for Mini2440
 */
#include <rtems.h>
#include "but.h"

#define rGPGDAT    (*(volatile unsigned *)0x56000064)

rtems_device_driver buts_initialize(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  rtems_device_driver status;

  status = rtems_io_register_name("/dev/buts", major, (rtems_device_minor_number) 0);

  if (status != RTEMS_SUCCESSFUL)
    rtems_fatal_error_occurred(status);

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver buts_open(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  printk ("buts_open\n");

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver buts_close(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  printk ("buts_close\n");

  return RTEMS_SUCCESSFUL;
}


rtems_device_driver buts_control(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp)
{
  rtems_libio_ioctl_args_t *args = pargp;

  if( (rGPGDAT&(1<< 0)) == 0 )  {args->ioctl_return = BUT1;}

  if( (rGPGDAT&(1<< 3)) == 0 )  {args->ioctl_return = BUT2;}

  if( (rGPGDAT&(1<< 5)) == 0 )  {args->ioctl_return = BUT3;}

  if( (rGPGDAT&(1<< 6)) == 0 )  {args->ioctl_return = BUT4;}

  if( (rGPGDAT&(1<< 7)) == 0 )  {args->ioctl_return = BUT5;}

  if( (rGPGDAT&(1<<11)) == 0 )  {args->ioctl_return = BUT6;}


  return RTEMS_SUCCESSFUL;
}
