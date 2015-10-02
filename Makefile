#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/nextgen.exe

# optional managers required
MANAGERS=all

# C source names
CSRCS = init.c          \
        heartbeat_led.c \
        rtems_shell.c   \
        can_blaster.c   \
        uart_blaster.c  \
        uart_echo.c     \
        web_server.c    \
        lidar_scanner.c \
        spi_master.c 

COBJS = $(CSRCS:%.c=${ARCH}/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CFLAGS += -I$(RTEMS_BSP_INCLUDE_PATH)
CFLAGS += -I. -I /other/rtems/bsps/arm-rtems4.11/stm32f7x/lwip/include
CFLAGS += -D$(RTEMS_TARGET_PROCESSOR) -DTARGET_STM_PROCESSOR_PREFIX=$(TARGET_STM_PROCESSOR_PREFIX) -DTARGET_STM_PROCESSOR=$(TARGET_STM_PROCESSOR)
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LINK_LIBS += -v -Wl,-Map=${ARCH}/next_gen.map -lstdc++  -L /other/rtems/bsps/arm-rtems4.11/stm32f7x/lwip/lib  -L /other/rtems/bsps/  

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
