#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/nextgen.exe

# optional managers required
MANAGERS=all

# C source names
CSRCS = init.c          \
        heartbeat_led.c \
        web_server.c    \
        rtems_shell.c   
 #       can_blaster.c   \
 #       uart_blaster.c  \
 #       uart_echo.c     \
 #       lidar_scanner.c \
 #       spi_master.c 

COBJS = $(CSRCS:%.c=${ARCH}/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

BSP_PATH=$(PROJECT_ROOT)/arm-rtems4.11/stm32f7x/lib/include/bsp
LWIP_PATH=$(PROJECT_ROOT)/arm-rtems4.11/stm32f7x/lwip/include
STM32F_LWIP_PATH=$(PROJECT_ROOT)/arm-rtems4.11/stm32f7x/stm32f_lwip/include

CFLAGS += -I. -I$(BSP_PATH) -I$(LWIP_PATH) -I$(LWIP_PATH)/ipv4 -I$(STM32F_LWIP_PATH) 
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LINK_LIBS += -v -Wl,-Map=${ARCH}/next_gen.map -lstm32-lwip -llwip -lstdc++ -L /other/rtems/bsps/arm-rtems4.11/stm32f7x/lwip/lib -L /other/rtems/bsps/arm-rtems4.11/stm32f7x/stm32f_lwip/lib -L /other/rtems/bsps/  

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
