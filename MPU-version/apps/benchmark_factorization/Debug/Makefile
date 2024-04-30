######################################
# target
######################################
PROJECT_NAME = benchmark_factorization

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
# output files
######################################
STANDARD = $(PROJECT_NAME)_standard
FORTIFIED =  $(PROJECT_NAME)_fortified

######################################
# paths
######################################
# Build path
BUILD_DIR = Build
DIR_STANDARD = $(BUILD_DIR)/Standard
DIR_FORTIFIED = $(BUILD_DIR)/Fortified

######################################
# Code sources
######################################
C_SOURCES = \
../Core/Src/main.c \
../Core/Src/prime_factorization.c \
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
LDSCRIPT_STD = ../STM32L475VGTX_FLASH.ld
LDSCRIPT_FORT = ../STM32L475VGTX_FLASH_FORT.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS_STD = $(MCU) -specs=nano.specs -T$(LDSCRIPT_STD) $(LIBDIR) $(LIBS) -Wl,-Map=$(STANDARD).map,--cref -Wl,--gc-sections -Wl,-z,max-page-size=2048
LDFLAGS_FORT = $(MCU) -specs=nano.specs -T$(LDSCRIPT_FORT) $(LIBDIR) $(LIBS) -Wl,-Map=$(FORTIFIED).map,--cref -Wl,--gc-sections -Wl,-z,max-page-size=2048

# default action: build all
all: both
standard: $(STANDARD).elf 
fortified: $(FORTIFIED).elf
both: $(STANDARD).elf $(FORTIFIED).elf

######################################
# build normal application
######################################
# list of C objects
OBJECTS_STD = $(addprefix $(DIR_STANDARD)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM objects
OBJECTS_STD += $(addprefix $(DIR_STANDARD)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# compile .c sources into .s files, compile into .o files
$(DIR_STANDARD)/%.o: %.c Makefile | $(DIR_STANDARD)
	$(CC) -S $(CFLAGS) $< -o $(@:.o=.s)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(DIR_STANDARD)/$(notdir $(<:.c=.lst)) $(@:.o=.s) -o $@

# copy original .s files, compile into .o files
$(DIR_STANDARD)/%.o: %.s Makefile | $(DIR_STANDARD)
	$(COPY) $< $(@:.o=.s)
	$(AS) -c $(ASFLAGS) $(@:.o=.s) -o $@

# build application
$(STANDARD).elf: $(OBJECTS_STD) Makefile
	$(CC) $(OBJECTS_STD) $(LDFLAGS_STD) -o $@
	$(SZ) $@
	$(BIN) $@ $(STANDARD).bin

######################################
# build normal application
######################################
# list of C objects
OBJECTS_FORT = $(addprefix $(DIR_FORTIFIED)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(DIR_FORTIFIED)))
# list of ASM objects
OBJECTS_FORT += $(addprefix $(DIR_FORTIFIED)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(DIR_FORTIFIED)))

# compile .c sources into .s files, add instrumentation, compile into .o files
$(DIR_FORTIFIED)/%.o: %.c Makefile | $(DIR_FORTIFIED)
	$(CC) -S $(CFLAGS) $< -o $(@:.o=.s)
	$(INSTRUMENTER_PATH) --virtualize=all $(@:.o=.s)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(DIR_FORTIFIED)/$(notdir $(<:.c=.lst)) $(@:.o=.s) -o $@

# copy original .s files, add instrumentatino, compile into .o files
$(DIR_FORTIFIED)/%.o: %.s Makefile | $(DIR_FORTIFIED)
	$(COPY) $< $(@:.o=.s)
	$(INSTRUMENTER_PATH) --virtualize=all $(@:.o=.s)
	$(AS) -c $(ASFLAGS) $(@:.o=.s) -o $@

# build application
$(FORTIFIED).elf: $(OBJECTS_FORT) Makefile
	$(CC) $(OBJECTS_FORT) $(LDFLAGS_FORT) -o $@
	$(SZ) $@
	$(BIN) $@ $(FORTIFIED).bin

######################################
# build common
######################################
# create build directories
$(BUILD_DIR):
	mkdir $@
$(DIR_STANDARD): | $(BUILD_DIR)
	mkdir $@
$(DIR_FORTIFIED): | $(BUILD_DIR)
	mkdir $@

######################################
# clean up
######################################
clean:
	-rm -fR $(BUILD_DIR)
	-rm -fR *.elf
	-rm -fR *.bin
	-rm -fR *.map
  
######################################
# dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***