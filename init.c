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

#include <main.h>

#ifdef FATAL_ERROR_HANDLER
#include <hal-fatal-error-handler.h>
#endif


typedef enum
{
#ifdef USE_HEARTBEAT_LED
  TASK_LED,
#endif

#ifdef USE_UART_TX
  TASK_UART_TX,
#endif

#ifdef USE_CAN
  TASK_CAN,
#endif

#ifdef USE_WEB_SERVER
  TASK_WEB_SERVER,
#endif

#ifdef USE_LIDAR
  TASK_LIDAR,
#endif

#ifdef USE_ECHO
  TASK_ECHO,
#endif

#ifdef USE_SPI
  TASK_SPI,
#endif

  NUM_TASKS_FOR_THIS_EXAMPLE
} PlatformTasks;

typedef enum
{
LED1 = 0,
LED_GREEN = LED1,
}Led_TypeDef;

typedef enum {
  TaskPriority_High = 10,
  TaskPriority_Medium = 100,
  TaskPriority_Low
} TaskPriorities;

#define TEST_LED LED1

rtems_id   Task_id[ NUM_TASKS_FOR_THIS_EXAMPLE ];         /* array of task ids */
rtems_name Task_name[ NUM_TASKS_FOR_THIS_EXAMPLE ];       /* array of task names */

//==================== POSIX_Init ====================================
void* POSIX_Init()
{
  // This function is necessary in able to call CONFIGURE_POSIX_INIT_THREAD_TABLE
  return NULL;
}

//==================== Init ====================================

rtems_task Init(
  rtems_task_argument argument
)
{
  //BSP_LED_Init(TEST_LED);

#ifdef FATAL_ERROR_HANDLER
  stm32f_initialize_user_extensions();
#endif

  printf( "\n\n*** Vecna NextGen Controller Project ***\n\n" );

  printf("-------- HAL Clock Values --------\n");
  printf("SYSCLK = %lu Hz\n",  HAL_RCC_GetSysClockFreq());
  printf("HCLK   = %lu Hz\n",  HAL_RCC_GetHCLKFreq());
  printf("PCLK1  = %lu Hz\n",  HAL_RCC_GetPCLK1Freq());
  printf("PCLK2  = %lu Hz\n",  HAL_RCC_GetPCLK2Freq());

#ifdef USE_UART_TX
  Task_name[ TASK_UART_TX ] = rtems_build_name( 'T', '_', 'T', 'X' );

  (void) rtems_task_create(
    Task_name[ TASK_UART_TX ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES , &Task_id[ TASK_UART_TX ]
  );

  (void) rtems_task_start( Task_id[ TASK_UART_TX ], Test_uart_task, 3 );
#endif

#ifdef USE_CAN
  Task_name[ TASK_CAN ]     = rtems_build_name( 'C', 'A', 'N', 'T' );

  (void) rtems_task_create(
    Task_name[ TASK_CAN ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ TASK_CAN ]
  );

  (void) rtems_task_start( Task_id[ TASK_CAN ], Test_can_tx_task,  7 );
#endif

#ifdef USE_WEB_SERVER

  Task_name[ TASK_WEB_SERVER ]     = rtems_build_name( 'W', 'E', 'B', 'S' );

   (void) rtems_task_create(
     Task_name[ TASK_WEB_SERVER ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
     RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ TASK_WEB_SERVER ]
   );

   (void) rtems_task_start( Task_id[ TASK_WEB_SERVER ], Test_web_server_task,  8 );
#endif

#ifdef USE_LIDAR

  Task_name[ TASK_LIDAR ]     = rtems_build_name( 'L', 'I', 'D', 'R' );

   (void) rtems_task_create(
     Task_name[ TASK_LIDAR ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
     RTEMS_DEFAULT_ATTRIBUTES , &Task_id[ TASK_LIDAR ]
   );

   (void) rtems_task_start( Task_id[ TASK_LIDAR ], Test_lidar_task,  9 );
#endif

#ifdef USE_ECHO

  Task_name[ TASK_ECHO ]     = rtems_build_name( 'E', 'C', 'H', 'O' );

   (void) rtems_task_create(
     Task_name[ TASK_ECHO ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
     RTEMS_DEFAULT_ATTRIBUTES , &Task_id[ TASK_ECHO ]
   );

   (void) rtems_task_start( Task_id[ TASK_ECHO ], Test_echo_task,  9 );
#endif

#ifdef USE_HEARTBEAT_LED

   Task_name[ TASK_LED ]     = rtems_build_name( 'T', 'L', 'E', 'D' );

  (void) rtems_task_create(
    Task_name[ TASK_LED ], 250, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES , &Task_id[ TASK_LED ]
  );

  (void) rtems_task_start( Task_id[ TASK_LED ], Test_led_task,  2 );
#endif

#ifdef USE_SPI

  Task_name[ TASK_SPI ]     = rtems_build_name( 'T', 'S', 'P', 'I' );

  (void) rtems_task_create(
    Task_name[ TASK_SPI ], 240, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES , &Task_id[ TASK_SPI ]
  );

  (void) rtems_task_start( Task_id[ TASK_SPI ], Test_spi_master_task,  2 );
#endif

  printf("Starting shell...\r\n");
  start_shell();

  (void) rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
//#define CONFIGURE_APPLICATION_NEEDS_RT

#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS   64
#define CONFIGURE_IMFS_MEMFILE_BYTES_PER_BLOCK    512
#define CONFIGURE_MAXIMUM_DRIVERS                  20

#define CONFIGURE_APPLICATION_NEEDS_LIBBLOCK
#define CONFIGURE_SWAPOUT_TASK_PRIORITY            2

#define CONFIGURE_INIT_TASK_STACK_SIZE           RTEMS_MINIMUM_STACK_SIZE
#define CONFIGURE_EXTRA_TASK_STACKS              RTEMS_MINIMUM_STACK_SIZE
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_MAXIMUM_TASKS                  rtems_resource_unlimited (20)
#define CONFIGURE_MAXIMUM_BARRIERS               rtems_resource_unlimited (10)
#define CONFIGURE_MAXIMUM_SEMAPHORES             rtems_resource_unlimited (20)
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES         rtems_resource_unlimited (4)
#define CONFIGURE_MAXIMUM_PARTITIONS             rtems_resource_unlimited (2)
#define CONFIGURE_MAXIMUM_USER_EXTENSIONS            8
#define CONFIGURE_UNIFIED_WORK_AREAS

#define CONFIGURE_MAXIMUM_POSIX_KEYS                 16
#define CONFIGURE_MAXIMUM_POSIX_KEY_VALUE_PAIRS      16
#define CONFIGURE_MAXIMUM_POSIX_THREADS              10
#define CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES  20
#define CONFIGURE_MAXIMUM_POSIX_MUTEXES              40

#define CONFIGURE_MICROSECONDS_PER_TICK          1000

#define CONFIGURE_SHELL_COMMANDS_INIT
#define CONFIGURE_SHELL_COMMANDS_ALL
#define CONFIGURE_POSIX_INIT_THREAD_TABLE
#include <rtems/shellconfig.h>

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/

