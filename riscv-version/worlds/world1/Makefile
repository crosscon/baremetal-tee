##
 # SPDX-License-Identifier: Apache-2.0
 # Copyright (c) uTango Project and Contributors. All rights reserved.
##

TARGET 	= world1.elf
BSP		= ../bsp
CFG		= ../../src/config

LINKER_SCRIPT := linker.lds

CROSS_COMPILE = riscv32-unknown-elf-


CC		:=	$(CROSS_COMPILE)gcc
LD		:=	$(CROSS_COMPILE)ld
OBJDUMP	:=	$(CROSS_COMPILE)objdump
OBJCOPY	:=	$(CROSS_COMPILE)objcopy
READELF	:=	$(CROSS_COMPILE)readelf
GDB		:=	$(CROSS_COMPILE)gdb
SIZE	:=	$(CROSS_COMPILE)size
SSTRIP	:=	$(CROSS_COMPILE)strip

.PHONY: all
all: $(TARGET)

INCLUDES	+= -I../inc
INCLUDES	+= -I./inc
INCLUDES	+= -I$(BSP)/inc
INCLUDES    += -I../../lib/libutee/include
INCLUDES    += -I../../lib/libteec/include
INCLUDES    += -I../../lib/libutils/ext/include
INCLUDES    += -I../../lib/libutils/isoc/include

ASM_SRCS 	+= ./src/crt0.S ./src/vectors.S
C_SRCS		+= ./src/main.c $(wildcard $(BSP)/*.c) $(wildcard $(LIB)/*.c)
C_SRCS		+= ../../lib/libteec/tee_client_api.c

MCUFLAGS	+= -march=rv32imc_zicsr
MCUFLAGS	+= -mabi=ilp32

LDFLAGS += -T $(CFG)/worlds_mem.lds
LDFLAGS	+= -T $(LINKER_SCRIPT)
LDFLAGS += -static $(MCUFLAGS)
LDFLAGS += -nostartfiles
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += --specs=nano.specs
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,-Map=$(subst .elf,.map,$(TARGET))

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := 	$(C_SRCS:.c=.o)

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)
LINK_DEPS += $(LINKER_SCRIPT)

CLEAN_OBJS += $(TARGET) $(LINK_OBJS)

CFLAGS += -g -gdwarf-4
CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS += $(MCUFLAGS)
CFLAGS += -O0

HEX = $(subst .elf,.hex,$(TARGET))
BIN = $(subst .elf,.bin,$(TARGET))
LST = $(subst .elf,.lst,$(TARGET))
MAP = $(subst .elf,.map,$(TARGET))
CLEAN_OBJS += $(HEX)
CLEAN_OBJS += $(BIN)
CLEAN_OBJS += $(LST)
CLEAN_OBJS += $(MAP)

$(TARGET): $(LINK_OBJS) $(LINK_DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) $(LDFLAGS) -o $@ 
	@$(OBJCOPY) -O ihex $(TARGET) $(HEX)
	@$(OBJCOPY) -O binary $(TARGET) $(BIN)
	@$(OBJDUMP) --all-headers --demangle --disassemble --file-headers --wide -D $(TARGET) > $(LST)
	@$(SIZE) $@

$(ASM_OBJS): %.o: %.S $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS) 

