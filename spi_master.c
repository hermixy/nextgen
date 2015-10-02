/*
 *  spi_master.c
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
rtems_task Test_spi_master_task(
  rtems_task_argument task_index
)
{
  uint8_t test_msg[8] = {0,1,2,3,4,5,6,7};

  int filedesc = open("/dev/spi2", O_RDWR | O_APPEND);

  while (true)
  {
    write(filedesc, &test_msg, sizeof(test_msg));
    (void) rtems_task_wake_after( 1000 );
  }

  close(filedesc);
}


