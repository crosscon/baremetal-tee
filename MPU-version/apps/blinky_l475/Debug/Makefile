######################################
# target
######################################
PROJECT_NAME = blinky_l475

######################################
# MCU-Fortifier Toolchain
######################################
INSTRUMENTER_PATH = $(PYTHON_PATH) /home/beaglehot/Desktop/MCU-Fortifier/Utils/instrumenter.py

######################################
# GNU Arm Embedded Toolchain Path
######################################
GCC_PATH = /home/beaglehot/gcc-arm-none-eabi-10-2020-q4-major/bin
PREFIX = arm-none-eabi-

######################################
# instrument source files
######################################
INSTRUMENT_SOURCES = 1

######################################
# windows specific configuration
######################################
WINDOWS_HOST = 0

ifeq ($(WINDOWS_HOST), 1)
PYTHON_PATH = py
COPY = busybox cp
else 
PYTHON_PATH =
COPY = cp
endif

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

######################################
# paths
######################################
# Build path
BUILD_DIR = Build

######################################
# Code sources
######################################
C_SOURCES = \
../Core/Src/main.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \

ASM_SOURCES = \
../Core/Startup/startup_stm32l475vgtx.s \

######################################
# binaries
######################################
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S --gap-fill 0xff
 
######################################
# CFLAGS
######################################
# cpu
CPU = -mcpu=cortex-m3

# mcu
MCU = $(CPU) -mthumb

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DDEBUG \
-DSTM32L475xx \
-DUSE_HAL_DRIVER \

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I../Core/Inc \
-I../Drivers/STM32L4xx_HAL_Driver/Inc \
-I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy \
-I../Drivers/CMSIS/Device/ST/STM32L4xx/Include \
-I../Drivers/CMSIS/Include \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

######################################
# LDFLAGS
######################################
# link script
LDSCRIPT = ../STM32L475VGTX_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(PROJECT_NAME).map,--cref -Wl,--gc-sections -Wl,-z,max-page-size=2048

# default action: build all
all: $(PROJECT_NAME).elf $(PROJECT_NAME).bin

######################################
# build the application
######################################
# list of C objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# compile .c sources into .s files, add instrumentation, compile into .o files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -S $(CFLAGS) $< -o $(@:.o=.s)
ifeq ($(INSTRUMENT_SOURCES), 1)
	$(INSTRUMENTER_PATH) --virtualize=all $(@:.o=.s)
endif
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $(@:.o=.s) -o $@

# copy original .s files, add instrumentatino, compile into .o files
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(COPY) $< $(@:.o=.s)
ifeq ($(INSTRUMENT_SOURCES), 1)
	$(INSTRUMENTER_PATH) --virtualize=all $(@:.o=.s)
endif
	$(AS) -c $(ASFLAGS) $(@:.o=.s) -o $@

# build application
$(PROJECT_NAME).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

%.bin: %.elf | $(BUILD_DIR)
	$(BIN) $< $@

######################################
# build common
######################################

# create build directories
$(BUILD_DIR):
	mkdir $@

######################################
# clean up
######################################
clean:
	-rm -fR $(BUILD_DIR)
	-rm -fR $(PROJECT_NAME).elf
	-rm -fR $(PROJECT_NAME).bin
	-rm -fR $(PROJECT_NAME).map
  
######################################
# dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***