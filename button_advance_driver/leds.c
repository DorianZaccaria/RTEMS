/*
 * RTEMS leds driver for Mini2440
 */
#include <rtems.h>
#include "leds.h"

#define	GPBCON		(*(volatile unsigned long *)0x56000010)
#define	GPBDAT		(*(volatile unsigned long *)0x56000014)

#define LEDS   (1<<5|1<<6|1<<7|1<<8) // LED on if bit == 0

void led_on (int n)
{     
  GPBCON = 0x00015400;
  GPBDAT = (GPBDAT & ~(LEDS)) | (LEDS & ~(1<<(n+4)));
}

void all_leds_off()
{
  GPBCON = 0x00015400;
  GPBDAT = (GPBDAT | LEDS);
}

/* 
 * The test driver routines are mostly derived from the null driver routines.
 */

rtems_device_driver leds_initialize(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  rtems_device_driver status;

  status = rtems_io_register_name("/dev/leds", major, (rtems_device_minor_number) 0);

  if (status != RTEMS_SUCCESSFUL)
    rtems_fatal_error_occurred(status);

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver leds_open(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  printk ("leds_open\n");
  all_leds_off ();

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver leds_close(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  printk ("leds_close\n");
  all_leds_off ();

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver leds_control(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  int n, cmd;
  rtems_libio_ioctl_args_t *args = pargp;

  n = (int)(args->buffer);
  cmd = (int)(args->command);

  switch (cmd) {
  case ALL_LEDS_OFF: 
    all_leds_off(); 
    break;
    
  case LED_ON : 
    led_on (n); 
    break;

  default: 
    printk ("leds_control: unknown cmd %x\n", cmd); 

    args->ioctl_return = -1;
    return RTEMS_UNSATISFIED;
  }
    

  args->ioctl_return = 0;

  return RTEMS_SUCCESSFUL;
}
