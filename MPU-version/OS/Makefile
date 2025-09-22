##########################################################################################################################
# Authors: Giuliani Daniele, Emanuele Beozzo
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
GCC_PATH = /opt/stm32cubeide/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.linux64_1.0.0.202410170706/tools/bin
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
TA1_BUILD_DIR = $(BUILD_DIR)/TA/TA1
TA2_BUILD_DIR = $(BUILD_DIR)/TA/TA2


# First TA main file path and include path
TA1 = TAs/aes-ta/aes-ta.c
TA1_INCLUDE = \
-ITAs/aes-ta \
-ITAs/aes-ta/include
#TA1 = TAs/bitcoin-wallet-ta/bitcoin_wallet_ta.c
#TA1_INCLUDE = \
#-ITAs/bitcoin-wallet-ta \
#-ITAs/bitcoin-wallet-ta/include \
#-ITAs/bitcoin-wallet-ta/crypto \

# Second TA main file path and include path
TA2 = TAs/ta2/ta2.c
TA2_INCLUDE = -ITAs/ta2/include

#TODO: move the includes of the tee_common.h to the TA folder
TA1_INCLUDE += -ITAs -IMicrovisor/Inc
#TA1_INCLUDE += -ITAs -IMicrovisor/Inc
TA2_INCLUDE += -ITAs -IMicrovisor/Inc


#######################################
## TA1 code (Bitcoin Wallet TA) and TA2 code
#######################################
#TA1_C_SOURCES = \
#TAs/bitcoin-wallet-ta/bip39.c \
#TAs/bitcoin-wallet-ta/bip32.c \
#TAs/bitcoin-wallet-ta/crypto/sha2.c \
#TAs/bitcoin-wallet-ta/crypto/ecdsa.c \
#TAs/bitcoin-wallet-ta/crypto/hmac.c \
#TAs/bitcoin-wallet-ta/crypto/secp256k1.c \
#TAs/bitcoin-wallet-ta/crypto/ta_ripemd160.c \
#TAs/bitcoin-wallet-ta/crypto/memzero.c \
#TAs/bitcoin-wallet-ta/crypto/bignum.c \
#TAs/bitcoin-wallet-ta/crypto/pbkdf2.c \

######################################
# TA1 code (AES TA) and TA2 code
######################################
TA1_C_SOURCES = \

TA2_C_SOURCES = \

#This code will be used by both TAs
TA1_C_SOURCES += TAs/tee_core_api.c
TA2_C_SOURCES += TAs/tee_core_api.c

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
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
Middlewares/Wifi/Src/es_wifi_io.c \
Middlewares/Wifi/Src/es_wifi.c \
Middlewares/Wifi/Src/wifi.c \
Middlewares/cJSON/src/cJSON.c \
Middlewares/cJSON/src/cJSON_Utils.c \
$(TA1) \
$(TA2) \

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
Microvisor/Private-Src/access_handlers.c \
Microvisor/Private-Src/PPB_recovery.c \
Microvisor/Private-Src/simulator_common.c \
Microvisor/Private-Src/system_instruction_recovery.c \
Microvisor/Private-Src/virtual_IPSR.c \
Microvisor/Private-Src/system_stm32l4xx.c \
Microvisor/Private-Src/mbedtls_rng_wrapper.c \
Microvisor/Private-Src/ota.c \
Microvisor/Private-Src/permanent_storage.c \
Microvisor/Private-Src/error.c \
Microvisor/Private-Src/sec_comm.c \
Microvisor/Private-Src/wifi_wrapper.c \
Microvisor/Private-Src/internal_core_api.c \
Microvisor/Private-Src/flash.c


MICROVISOR_LIB_ASM_SOURCES = \

######################################
# binaries
#############################q#########
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
CPU = -mcpu=cortex-m4

# mcu
MCU = $(CPU) -mthumb

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32L476xx\

# Enable peripherals. This list includes all the STM32L47x/L48x peripherals.
# Not every peripheral is supported by the specific platform.
C_DEFS += -DACCESS_PPB
## Aggregates
#C_DEFS += -DACCESS_TIM			# Also allows the access to LPTIMs.
#C_DEFS += -DACCESS_SPI
C_DEFS += -DACCESS_UART		# Also allows the access to USARTs/LPUARTs.
#C_DEFS += -DACCESS_I2C
#C_DEFS += -DACCESS_CAN
#C_DEFS += -DACCESS_DAC
#C_DEFS += -DACCESS_SWPMI
#C_DEFS += -DACCESS_SDMMC
#C_DEFS += -DACCESS_SAI
#C_DEFS += -DACCESS_DFSDM
#C_DEFS += -DACCESS_DMA
#C_DEFS += -DACCESS_GPIO
## APB1
#C_DEFS += -DACCESS_TIM2
#C_DEFS += -DACCESS_TIM3
#C_DEFS += -DACCESS_TIM4
#C_DEFS += -DACCESS_TIM5
#C_DEFS += -DACCESS_TIM6
#C_DEFS += -DACCESS_TIM7
#C_DEFS += -DACCESS_LCD
#C_DEFS += -DACCESS_RTC
#C_DEFS += -DACCESS_WWDC
#C_DEFS += -DACCESS_IWDC
#C_DEFS += -DACCESS_SPI2
#C_DEFS += -DACCESS_SPI3
#C_DEFS += -DACCESS_USART2
#C_DEFS += -DACCESS_USART3
#C_DEFS += -DACCESS_UART4
#C_DEFS += -DACCESS_UART5
#C_DEFS += -DACCESS_I2C1
#C_DEFS += -DACCESS_I2C2
#C_DEFS += -DACCESS_I2C3
#C_DEFS += -DACCESS_CAN1
C_DEFS += -DACCESS_PWR
#C_DEFS += -DACCESS_DAC1
#C_DEFS += -DACCESS_OPAMP
#C_DEFS += -DACCESS_LPTIM1
#C_DEFS += -DACCESS_LPUART1
#C_DEFS += -DACCESS_SWPMI1
#C_DEFS += -DACCESS_LPTIM2
## APB2
#C_DEFS += -DACCESS_SYSCFG
#C_DEFS += -DACCESS_VREFBUF
#C_DEFS += -DACCESS_COMP
#C_DEFS += -DACCESS_EXTI
#C_DEFS += -DACCESS_FIREWALL
#C_DEFS += -DACCESS_SDMMC1
#C_DEFS += -DACCESS_TIM1
#C_DEFS += -DACCESS_SPI1
#C_DEFS += -DACCESS_TIM8
#C_DEFS += -DACCESS_USART1
#C_DEFS += -DACCESS_TIM15
#C_DEFS += -DACCESS_TIM16
#C_DEFS += -DACCESS_TIM17
#C_DEFS += -DACCESS_SAI1
#C_DEFS += -DACCESS_SAI2
#C_DEFS += -DACCESS_DFSDM1
## AHB1
#C_DEFS += -DACCESS_DMA1
#C_DEFS += -DACCESS_DMA2
C_DEFS += -DACCESS_RCC
C_DEFS += -DACCESS_FLASH
#C_DEFS += -DACCESS_CRC
#C_DEFS += -DACCESS_TSC
## AHB2
#C_DEFS += -DACCESS_GPIOA
C_DEFS += -DACCESS_GPIOB
#C_DEFS += -DACCESS_GPIOC
#C_DEFS += -DACCESS_GPIOD
#C_DEFS += -DACCESS_GPIOE
#C_DEFS += -DACCESS_GPIOF
#C_DEFS += -DACCESS_GPIOG
#C_DEFS += -DACCESS_GPIOH
#C_DEFS += -DACCESS_OTG_FS
#C_DEFS += -DACCESS_ADC
#C_DEFS += -DACCESS_AES
#C_DEFS += -DACCESS_RNG

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
-IMiddlewares/cJSON/inc \
$(TA1_INCLUDE) \
$(TA2_INCLUDE) \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -Wextra -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -Wextra -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Specific flags for ta.c and ta2.c
# As both ta.c and ta2.c contain the same functions with the same name, as part of GlobalPlatform TEE Client APIs, and are compiled in the same executable
# We need to rename these functions using the -D directive to avoid conflicts
TA1_CFLAGS = $(CFLAGS) -DTA_CreateEntryPoint=TA_CreateEntryPoint1 -DTA_DestroyEntryPoint=TA_DestroyEntryPoint1 -DTA_InvokeCommandEntryPoint=TA_InvokeCommandEntryPoint1 -DTA_CloseSessionEntryPoint=TA_CloseSessionEntryPoint1 -DTA_OpenSessionEntryPoint=TA_OpenSessionEntryPoint1 \
-DTEE_Malloc=TEE_Malloc1 \
-DTEE_Free=TEE_Free1 \
-DTEE_MemMove=TEE_MemMove1 \
-DTEE_MemFill=TEE_MemFill1 \
-DTEE_BigIntConvertToS32=TEE_BigIntConvertToS321 \
-DTEE_BigIntCmpS32=TEE_BigIntCmpS321 \
-DTEE_BigIntMod=TEE_BigIntMod1 \
-DTEE_BigIntDiv=TEE_BigIntDiv1 \
-DTEE_BigIntConvertFromOctetString=TEE_BigIntConvertFromOctetString1 \
-DTEE_BigIntInit=TEE_BigIntInit1 \
-DTEE_AllocateTransientObject=TEE_AllocateTransientObject1 \
-DTEE_PopulateTransientObject=TEE_PopulateTransientObject1 \
-DTEE_InitRefAttribute=TEE_InitRefAttribute1 \
-DTEE_InitValueAttribute=TEE_InitValueAttribute1 \
-DTEE_GetObjectBufferAttribute=TEE_GetObjectBufferAttribute1 \
-DTEE_GetObjectValueAttribute=TEE_GetObjectValueAttribute1 \
-DTEE_FreeTransientObject=TEE_FreeTransientObject1 \
-DTEE_CloseObject=TEE_CloseObject1 \
-DTEE_ReadObjectData=TEE_ReadObjectData1 \
-DTEE_WriteObjectData=TEE_WriteObjectData1 \
-DTEE_CreatePersistentObject=TEE_CreatePersistentObject1 \
-DTEE_OpenPersistentObject=TEE_OpenPersistentObject1 \
-DTEE_CloseAndDeletePersistentObject1=TEE_CloseAndDeletePersistentObject11 \
-DTEE_AllocateOperation=TEE_AllocateOperation1 \
-DTEE_FreeOperation=TEE_FreeOperation1 \
-DTEE_SetOperationKey=TEE_SetOperationKey1 \
-DTEE_GenerateKey=TEE_GenerateKey1 \
-DTEE_GenerateRandom=TEE_GenerateRandom1 \
-DTEE_DeriveKey=TEE_DeriveKey1 \
-DTEE_CipherInit=TEE_CipherInit1 \
-DTEE_CipherUpdate=TEE_CipherUpdate1 \
-DTEE_CipherDoFinal=TEE_CipherDoFinal1 \
-DTEE_MACInit=TEE_MACInit1 \
-DTEE_MACUpdate=TEE_MACUpdate1 \
-DTEE_MACComputeFinal=TEE_MACComputeFinal1 \
-DTEE_AsymmetricSignDigest=TEE_AsymmetricSignDigest1 \
-DTEE_AsymmetricVerifyDigest=TEE_AsymmetricVerifyDigest1 \
-DTEE_DigestUpdate=TEE_DigestUpdate1 \
-DTEE_DigestDoFinal=TEE_DigestDoFinal1 \
-DTEE_DigestExtract=TEE_DigestExtract1

TA2_CFLAGS = $(CFLAGS) -DTA_CreateEntryPoint=TA_CreateEntryPoint2 -DTA_DestroyEntryPoint=TA_DestroyEntryPoint2 -DTA_InvokeCommandEntryPoint=TA_InvokeCommandEntryPoint2 -DTA_CloseSessionEntryPoint=TA_CloseSessionEntryPoint2 -DTA_OpenSessionEntryPoint=TA_OpenSessionEntryPoint2 \
-DTEE_Malloc=TEE_Malloc2 \
-DTEE_Free=TEE_Free2 \
-DTEE_MemMove=TEE_MemMove2 \
-DTEE_MemFill=TEE_MemFill2 \
-DTEE_BigIntConvertToS32=TEE_BigIntConvertToS322 \
-DTEE_BigIntCmpS32=TEE_BigIntCmpS322 \
-DTEE_BigIntMod=TEE_BigIntMod2 \
-DTEE_BigIntDiv=TEE_BigIntDiv2 \
-DTEE_BigIntConvertFromOctetString=TEE_BigIntConvertFromOctetString2 \
-DTEE_BigIntInit=TEE_BigIntInit2 \
-DTEE_AllocateTransientObject=TEE_AllocateTransientObject2 \
-DTEE_PopulateTransientObject=TEE_PopulateTransientObject2 \
-DTEE_InitRefAttribute=TEE_InitRefAttribute2 \
-DTEE_InitValueAttribute=TEE_InitValueAttribute2 \
-DTEE_GetObjectBufferAttribute=TEE_GetObjectBufferAttribute2 \
-DTEE_GetObjectValueAttribute=TEE_GetObjectValueAttribute2 \
-DTEE_FreeTransientObject=TEE_FreeTransientObject2 \
-DTEE_CloseObject=TEE_CloseObject2 \
-DTEE_ReadObjectData=TEE_ReadObjectData2 \
-DTEE_WriteObjectData=TEE_WriteObjectData2 \
-DTEE_CreatePersistentObject=TEE_CreatePersistentObject2 \
-DTEE_OpenPersistentObject=TEE_OpenPersistentObject2 \
-DTEE_CloseAndDeletePersistentObject1=TEE_CloseAndDeletePersistentObject12 \
-DTEE_AllocateOperation=TEE_AllocateOperation2 \
-DTEE_FreeOperation=TEE_FreeOperation2 \
-DTEE_SetOperationKey=TEE_SetOperationKey2 \
-DTEE_GenerateKey=TEE_GenerateKey2 \
-DTEE_GenerateRandom=TEE_GenerateRandom2 \
-DTEE_DeriveKey=TEE_DeriveKey2 \
-DTEE_CipherInit=TEE_CipherInit2 \
-DTEE_CipherUpdate=TEE_CipherUpdate2 \
-DTEE_CipherDoFinal=TEE_CipherDoFinal2 \
-DTEE_MACInit=TEE_MACInit2 \
-DTEE_MACUpdate=TEE_MACUpdate2 \
-DTEE_MACComputeFinal=TEE_MACComputeFinal2 \
-DTEE_AsymmetricSignDigest=TEE_AsymmetricSignDigest2 \
-DTEE_AsymmetricVerifyDigest=TEE_AsymmetricVerifyDigest2 \
-DTEE_DigestUpdate=TEE_DigestUpdate2 \
-DTEE_DigestDoFinal=TEE_DigestDoFinal2 \
-DTEE_DigestExtract=TEE_DigestExtract2
TA1_CFLAGS += -DTA
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
# list of TA1 C objects
MICROVISOR_OBJECTS += $(addprefix $(TA1_BUILD_DIR)/,$(notdir $(TA1_C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(TA1_C_SOURCES)))
# list of TA2 C objects
#MICROVISOR_OBJECTS += $(addprefix $(TA2_BUILD_DIR)/,$(notdir $(TA2_C_SOURCES:.c=.o)))
#vpath %.c $(sort $(dir $(TA2_C_SOURCES)))

# compile microvisor .c sources
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# compile ta1 main source for library with specific flags
$(BUILD_DIR)/$(patsubst %.c,%.o,$(notdir $(TA1))): $(TA1) Makefile | $(BUILD_DIR)
	@echo "Compiling TA1: $(TA1)"
	$(CC) -c $(TA1_CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(TA1:.c=.lst)) $< -o $@

# compile ta2 main source for library with specific flags
$(BUILD_DIR)/$(patsubst %.c,%.o,$(notdir $(TA2))): $(TA2) Makefile | $(BUILD_DIR)
	$(CC) -c $(TA2_CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(TA1_BUILD_DIR)/%.o: %.c Makefile | $(TA1_BUILD_DIR)
	$(CC) -c $(TA1_CFLAGS) -Wa,-a,-ad,-alms=$(TA1_BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

#$(TA2_BUILD_DIR)/%.o: %.c Makefile | $(TA2_BUILD_DIR)
#	$(CC) -c $(TA2_CFLAGS) -Wa,-a,-ad,-alms=$(TA2_BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

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
$(TA1_BUILD_DIR):
	mkdir -p $@
$(TA2_BUILD_DIR):
	mkdir -p $@

######################################
# clean up
######################################
clean:
	-rm -fR $(BUILD_DIR)
	-rm -fR $(LIB_DIR)
	-rm -fR $(TEMP_DIR)
clean-lib:
	-rm -fR $(LIB_DIR)
	-rm -fR $(TEMP_DIR)
clean-temp:
	-rm -fR $(TEMP_DIR)

######################################
# dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)
-include $(wildcard $(TEMP_DIR)/*.d)
-include $(wildcard $(TA1_BUILD_DIR)/*.d)
-include $(wildcard $(TA2_BUILD_DIR)/*.d)

# *** EOF ***
