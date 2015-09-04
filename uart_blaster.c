
/**
 * NOTICE: This software  source code and any of  its derivatives are the
 * confidential  and  proprietary   information  of  Vecna  Technologies,
 * Inc. (such source  and its derivatives are hereinafter  referred to as
 * "Confidential Information"). The  Confidential Information is intended
 * to be  used exclusively by  individuals or entities that  have entered
 * into either  a non-disclosure agreement or license  agreement (or both
 * of  these agreements,  if  applicable) with  Vecna Technologies,  Inc.
 * ("Vecna")   regarding  the  use   of  the   Confidential  Information.
 * Furthermore,  the  Confidential  Information  shall be  used  only  in
 * accordance  with   the  terms   of  such  license   or  non-disclosure
 * agreements.   All  parties using  the  Confidential Information  shall
 * verify that their  intended use of the Confidential  Information is in
 * compliance  with and  not in  violation of  any applicable  license or
 * non-disclosure  agreements.  Unless expressly  authorized by  Vecna in
 * writing, the Confidential Information  shall not be printed, retained,
 * copied, or  otherwise disseminated,  in part or  whole.  Additionally,
 * any party using the Confidential  Information shall be held liable for
 * any and  all damages incurred  by Vecna due  to any disclosure  of the
 * Confidential  Information (including  accidental disclosure).   In the
 * event that  the applicable  non-disclosure or license  agreements with
 * Vecna  have  expired, or  if  none  currently  exists, all  copies  of
 * Confidential Information in your  possession, whether in electronic or
 * printed  form, shall be  destroyed or  returned to  Vecna immediately.
 * Vecna  makes no  representations  or warranties  hereby regarding  the
 * suitability  of  the   Confidential  Information,  either  express  or
 * implied,  including  but not  limited  to  the  implied warranties  of
 * merchantability,    fitness    for    a   particular    purpose,    or
 * non-infringement. Vecna  shall not be liable for  any damages suffered
 * by  licensee as  a result  of  using, modifying  or distributing  this
 * Confidential Information.  Please email [info@vecnatech.com]  with any
 * questions regarding the use of the Confidential Information.
 */

#include <rtems.h>
#include <rtems/system.h>
#include <bsp.h>
#include <main.h>
#include <fcntl.h>
#include <rtems/shell.h>
#include <hal-utils.h>

//=====================UART==============================================

// -------------- UART DMA TX TASK -------------------------
rtems_task Test_uart_task(
  rtems_task_argument task_index
)
{
  rtems_interval    ticks;
  uint32_t counter = 0UL;
  uint8_t szTestTx[128];
  char UartName[32];
  const int TEST_UART = 3;
  int ret;

  ticks = rtems_clock_get_ticks_per_second() / 90;

  sprintf(UartName, "/dev/ttyS%d", TEST_UART);
  int filedesc = open(UartName, O_WRONLY | O_APPEND);

  snprintf((char*)szTestTx, COUNTOF(szTestTx), "Beginning UART Test\n\r");
  ret = write(filedesc, szTestTx, strlen((char*) szTestTx));

  close(filedesc);

  filedesc = open(UartName, O_WRONLY | O_APPEND);

  while (true)
  {
    counter++;

    snprintf((char*) szTestTx, COUNTOF(szTestTx), "ttyS%d %lu 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "\n\r", TEST_UART, counter);
    ret = write(filedesc, szTestTx, strlen((char*) szTestTx));

    while(ret != 0) {
        (void) rtems_task_wake_after( 1 );
        ret = write(filedesc, szTestTx, strlen((char*) szTestTx));
    }

    (void) rtems_task_wake_after( ticks );
  }
}

