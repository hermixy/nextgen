/*
 * can_blaster.c
 *
 *  Created on: Sep 4, 2015
 *      Author: jay.doyle
 */
#include <rtems.h>
#include <rtems/system.h>
#include <bsp.h>
#include <main.h>
#include <dev/can/can.h>
#include <fcntl.h>
#include <rtems/shell.h>

//=======================CAN TX TASK================================================
rtems_task Test_can_tx_task(
  rtems_task_argument task_index
)
{
  can_msg test_msg = {
    .id = 0xDEADBEEFUL,
    .len = 8,
    .data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}
  };

  int filedesc = open("/dev/can1", O_RDWR | O_APPEND);

  while (true)
  {
    write(filedesc, &test_msg, sizeof(test_msg));
    (void) rtems_task_wake_after( 1 );
  }

  close(filedesc);
}


