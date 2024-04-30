##########################################################################################################################
# Author: Giuliani Daniele
##########################################################################################################################

######################################
# target
######################################
PROJECT_NAME = MCU-Reflasher

######################################
# GNU Arm Embedded Toolchain Path
######################################
GCC_PATH = /home/beaglehot/gcc-arm-none-eabi-10-2020-q4-major/bin
PREFIX = arm-none-eabi-

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Os	# optimize for size

#######################################
# paths
#######################################
# Build path
BUILD_DIR = Build

######################################
# Code Sourcess
######################################
C_SOURCES = \
Core/Src/reflash.c \
Core/Src/system_stm32l4xx.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \

ASM_SOURCES = \
startup_stm32l475vgtx.s \

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
-DUSE_HAL_DRIVER \
-DSTM32L475xx

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32L4xx_HAL_Driver/Inc \
-IDrivers/STM32L4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32L4xx/Include \
-IDrivers/CMSIS/Include \

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
LDSCRIPT = STM32L475VGTX_RAM.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(PROJECT_NAME).map,--cref -Wl,--gc-sections -Wl,-z,max-page-size=2048

# default action: build elf
all: $(BUILD_DIR)/$(PROJECT_NAME).elf

######################################
# build the application
######################################
# list C objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list ASM objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# compile .c sources
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# assemble .s files (that were not .c previously e.g. startup code)
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# build elf
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
	$(BIN) $@ $(BUILD_DIR)/$(PROJECT_NAME).bin

# create build directories
$(BUILD_DIR):
	mkdir $@

######################################
# clean up
######################################
clean:
	-rm -fR $(BUILD_DIR)
  
######################################
# dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***