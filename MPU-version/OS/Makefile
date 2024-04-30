##########################################################################################################################
# Author: Giuliani Daniele
##########################################################################################################################

######################################
# target
######################################
PROJECT_NAME = MCU-Fortifier
MICROVISOR_LIB = lib$(PROJECT_NAME).a
MICROVISOR_ELF = $(PROJECT_NAME).elf

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
OPT = -Og

#######################################
# paths
#######################################
# Build path
LIB_DIR = Lib
BUILD_DIR = Build
TEMP_DIR = Build-Lib

######################################
# Microvisor code
######################################
MICROVISOR_C_SOURCES = \
Microvisor/Src/microvisor_config.c \
Microvisor/Src/stm32l475vg_mpu.c \
Microvisor/Src/bootloader.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
Middlewares/Wifi/Src/es_wifi_io.c \
Middlewares/Wifi/Src/es_wifi.c \
Middlewares/Wifi/Src/wifi.c \

MICROVISOR_ASM_SOURCES = \
startup_bootloader.s \

######################################
# Library code
######################################
MICROVISOR_LIB_C_SOURCES = \
Microvisor/Private-Src/exception_manager.c \
Microvisor/Private-Src/it.c \
Microvisor/Private-Src/stm32l4xx_it.c \
Microvisor/Private-Src/stm32l4xx_hal_msp.c \
Microvisor/Private-Src/PPB_handlers.c \
Microvisor/Private-Src/PPB_recovery.c \
Microvisor/Private-Src/simulator_common.c \
Microvisor/Private-Src/system_instruction_recovery.c \
Microvisor/Private-Src/virtual_IPSR.c \
Microvisor/Private-Src/activator.c \
Microvisor/Private-Src/system_stm32l4xx.c \
Microvisor/Private-Src/mbedtls_rng_wrapper.c \
Microvisor/Private-Src/ota.c \
Microvisor/Private-Src/permanent_storage.c \
Microvisor/Private-Src/error.c \
Microvisor/Private-Src/sec_comm.c \
Microvisor/Private-Src/wifi_wrapper.c \

MICROVISOR_LIB_ASM_SOURCES = \

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
-IMicrovisor/Inc \
-IDrivers/STM32L4xx_HAL_Driver/Inc \
-IDrivers/STM32L4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32L4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/BSP/B-L475E-IOT01 \
-IMiddlewares/mbedtls/include \
-IMiddlewares/Wifi/Inc \
-IMiddlewares/ST/STM32_Cryptographic/include \

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
MICROVISOR_LDSCRIPT = BOOTLOADER.ld

# libraries
LIBS = -Wl,--whole-archive -l$(PROJECT_NAME) -Wl,--no-whole-archive -lc -lm -lnosys -lmbedtls -lmbedx509 -lmbedcrypto
LIBDIR = -LMiddlewares/mbedtls/library -L$(LIB_DIR)
MICROVISOR_LDFLAGS = $(MCU) -specs=nano.specs -T$(MICROVISOR_LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(PROJECT_NAME).map,--cref -Wl,--gc-sections -Wl,-z,max-page-size=2048

# default action: build elf
all: $(LIB_DIR)/$(MICROVISOR_LIB) $(BUILD_DIR)/$(MICROVISOR_ELF)
lib: $(LIB_DIR)/$(MICROVISOR_LIB)

######################################
# build the bootloader
######################################
# list of Microvisor C objects
MICROVISOR_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(MICROVISOR_C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(MICROVISOR_C_SOURCES)))
# list of Microvisor ASM objects
MICROVISOR_OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(MICROVISOR_ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(MICROVISOR_ASM_SOURCES)))

# compile microvisor .c sources
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# assemble microvisor .s files (that were not .c previously e.g. startup code)
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# build bootloader
$(BUILD_DIR)/$(MICROVISOR_ELF): $(MICROVISOR_OBJECTS) Makefile $(LIB_DIR)/$(MICROVISOR_LIB) 
	$(CC) $(MICROVISOR_OBJECTS) $(MICROVISOR_LDFLAGS) -o $@
	$(SZ) $@

######################################
# build microvisor library
######################################
# list of library C objects
MICROVISOR_LIB_OBJECTS = $(addprefix $(TEMP_DIR)/,$(notdir $(MICROVISOR_LIB_C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(MICROVISOR_LIB_C_SOURCES)))
# list of library ASM objects
MICROVISOR_LIB_OBJECTS += $(addprefix $(TEMP_DIR)/,$(notdir $(MICROVISOR_LIB_ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(MICROVISOR_LIB_ASM_SOURCES)))

# compile MCU-Fortifier library .c sources
$(TEMP_DIR)/%.o: %.c Makefile | $(TEMP_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(TEMP_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# assemble microvisor .s files (that were not .c previously e.g. startup code)
$(TEMP_DIR)/%.o: %.s Makefile | $(TEMP_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# archive object files in library
$(LIB_DIR)/$(MICROVISOR_LIB): $(MICROVISOR_LIB_OBJECTS) Makefile | $(LIB_DIR)
	ar rcs $@ $(MICROVISOR_LIB_OBJECTS)

######################################
# build common
######################################

# create build directories
$(BUILD_DIR):
	mkdir $@
$(LIB_DIR):
	mkdir $@
$(TEMP_DIR):
	mkdir $@

######################################
# clean up
######################################
clean:
	-rm -fR $(BUILD_DIR)
clean-lib:
	-rm -fR $(LIB_DIR)
	-rm -fR $(TEMP_DIR)
clean-temp:
	-rm -fR $(TEMP_DIR)
  
######################################
# dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***