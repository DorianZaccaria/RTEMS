#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>


#include "but.h"
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

int but_fd;
int led_fd;

void got_signal (int sig)
{
  int but_status;
  int led_status;

  but_status = ioctl (but_fd, 0, NULL);

  if (but_status == BUT1)
  {
    printf ("BUT #%d IS PUSHED\n", but_status);
    led_status = ioctl (led_fd, LED_ON, (void*)BUT1);
  }
  else if (but_status == BUT2)
  {
    printf ("BUT #%d IS PUSHED\n", but_status);
    led_status = ioctl (led_fd, LED_ON, (void*)BUT2);
  }
  else if (but_status == BUT3)
  {
    printf ("BUT #%d IS PUSHED\n", but_status);
    led_status = ioctl (led_fd, LED_ON, (void*)BUT3);
  }
  else if (but_status == BUT4)
  {
    printf ("BUT #%d IS PUSHED\n", but_status);
    led_status = ioctl (led_fd, LED_ON, (void*)BUT4);
  }
  else if (but_status == BUT5 || but_status == BUT6)
    printf ("BUT #%d IS PUSHED\n", but_status);
  else
   printf ("PRESS A BUTTON\n");
/*
  if (led_status)
    fprintf (stderr, "status= %d errno= %d => %s\n", led_status, errno, strerror(errno));
*/
}


void *POSIX_Init()
{
  timer_t myTimer;
  struct sigaction sig;
  struct itimerspec ti, ti_old;
  struct sigevent event;
  sigset_t mask;
  int status, n = 100;

  puts( "\n\n*** BUTs driver test ***" );

  if ((but_fd = open ("/dev/buts", O_RDWR)) < 0) {
    fprintf (stderr, "open error => %d %s\n", errno, strerror(errno));
    exit (1);
  }
  if ((led_fd = open ("/dev/leds", O_RDWR)) < 0) {
    fprintf (stderr, "open error => %d %s\n", errno, strerror(errno));
    exit (1);
  }

  printf ("but_fd = %d\n", but_fd);
  printf ("led_fd = %d\n", led_fd);

  puts( "All BUTs and LEDs OFF" );
  status = ioctl (but_fd, 0, NULL);
  if (status)
    fprintf (stderr, "status= %d errno= %d => %s\n", status, errno, strerror(errno));

  status = ioctl (led_fd, ALL_LEDS_OFF, NULL);
  if (status)
    fprintf (stderr, "status= %d errno= %d => %s\n", status, errno, strerror(errno));

  // Set up signal
  sig.sa_flags = 0;
  sig.sa_handler = got_signal;
  sigemptyset (&sig.sa_mask);
  sigaction (SIGALRM, &sig, NULL);
  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_UNBLOCK, &mask, NULL);

  event.sigev_notify = SIGEV_SIGNAL;
  event.sigev_value.sival_int = 0;
  event.sigev_signo = SIGALRM;

  // Start timer
  timer_create (CLOCK_REALTIME, &event, &myTimer);

  ti.it_value.tv_sec = 0;
  ti.it_value.tv_nsec = 50000000;
  ti.it_interval.tv_sec = 0;
  ti.it_interval.tv_nsec = 200000000;

  timer_settime(myTimer, 0, &ti, &ti_old);

  printf ("t0 = %ld\n", time(0));

  while (n--)
    pause ();

  close (but_fd);

  printf ("t1 = %ld\n", time(0));

  puts( "\n\n*** End of BUTs and LEDs driver test ***" );
}


/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_NUMBER_OF_DRIVERS 2
#define CONFIGURE_APPLICATION_EXTRA_DRIVERS BUTS_DRIVER_TABLE_ENTRY, LEDS_DRIVER_TABLE_ENTRY

/* include an extra slot for registering the termios one dynamically */
#define CONFIGURE_MAXIMUM_DRIVERS 3

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5

#define CONFIGURE_MAXIMUM_POSIX_TIMERS          1
#define CONFIGURE_MAXIMUM_POSIX_THREADS		1

#define CONFIGURE_EXTRA_TASK_STACKS         (6 * RTEMS_MINIMUM_STACK_SIZE)

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
/* end of file */
