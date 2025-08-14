##
 # SPDX-License-Identifier: Apache-2.0
 # Copyright (c) uTango Project and Contributors. All rights reserved.
##

################################################################################
# Project Name
PROJECT_NAME := $(notdir $(shell pwd))

################################################################################
# Makefile Arguments
BOARD 		?= arty_devkit
DEBUG 		?= y
OPTIM 		?= O0
USERDEFINES ?= y

################################################################################


CROSS_COMPILE = riscv32-unknown-elf-

CC		:=	$(CROSS_COMPILE)gcc
LD		:=	$(CROSS_COMPILE)ld
OBJDUMP	:=	$(CROSS_COMPILE)objdump
OBJCOPY	:=	$(CROSS_COMPILE)objcopy
READELF	:=	$(CROSS_COMPILE)readelf
GDB		:=	$(CROSS_COMPILE)gdb
SIZE	:=	$(CROSS_COMPILE)size
SSTRIP	:=	$(CROSS_COMPILE)strip

################################################################################
# Include Directories
CUR_DIR   := $(abspath .)
SRC_DIR	  := $(CUR_DIR)/src
WDL_DIR	  := $(CUR_DIR)/worlds
ARCH_DIR   = $(SRC_DIR)/arch/rv32imc
CORE_DIR   = $(SRC_DIR)/core
LIB_DIR    = $(SRC_DIR)/lib
PLAT_DIR   = $(SRC_DIR)/platform
BSP_DIR   =  $(WDL_DIR)/bsp/$(BOARD)
CONFIG_DIR = $(SRC_DIR)/config

ifeq ($(BOARD),)
ifneq ($(MAKECMDGOALS), clean)
$(error Target board argument (BOARD) not specified)
endif
endif

BOARD_DIR = $(PLAT_DIR)/$(BOARD)

ifeq ($(wildcard $(BOARD_DIR)),)
$(error Unsupported $(BOARD))
endif

SRC_DIRS  := $(ARCH_DIR) $(CORE_DIR) $(BOARD_DIR) $(LIB_DIR) $(CONFIG_DIR)
INC_DIRS  := $(addsuffix /inc, $(SRC_DIRS))

BUILD_DIR := $(CUR_DIR)/build/$(BOARD)
BIN_DIR   := $(CUR_DIR)/bin/$(BOARD)
MKDIR	  := $(BUILD_DIR) $(BIN_DIR)

################################################################################
# Include Objects for Compilation
-include $(addsuffix /objects.mk, $(SRC_DIRS))

objs-y :=
objs-y += $(addprefix $(ARCH_DIR)/,  $(arch-objs-y))
objs-y += $(addprefix $(CORE_DIR)/,  $(core-objs-y))
objs-y += $(addprefix $(LIB_DIR)/, $(lib-objs-y))
objs-y += $(addprefix $(BOARD_DIR)/, $(board-objs-y))
objs-y += $(addprefix $(CONFIG_DIR)/, $(config-objs-y))

deps   += $(patsubst %.o,%.d,$(objs-y))
objs-y := $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(objs-y))

BUILD_DIRS := $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SRC_DIRS) $(INC_DIRS))
MKDIR      += $(BUILD_DIRS)

################################################################################
# Files for generation
ASM_DEFS_SRC:=$(CORE_DIR)/asm_defs.c
ASM_DEFS_HDR:=$(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, \
	$(CORE_DIR))/inc/asm_defs.h
INC_DIRS+=$(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(CORE_DIR))/inc
deps+=$(ASM_DEFS_HDR).d

gens:=
gens+=$(ASM_DEFS_HDR)

################################################################################
# Compilation Target
TARGET += $(BIN_DIR)/$(PROJECT_NAME).elf
TARGET += $(BIN_DIR)/$(PROJECT_NAME).hex

################################################################################
# Toolchain Flags
-include $(BOARD_DIR)/platform.mk

CFLAGS	 = -$(OPTIM) -Wall $(plat-flags) $(addprefix -I, $(INC_DIRS)) \
		   -D$(BOARD) -D$(USERDEFINES) -fcommon

ifeq ($(DEBUG), y)
CFLAGS 	 += -g
endif

ASFLAGS	 := $(CFLAGS)

LDSCRIPT := $(CONFIG_DIR)/linker.ld
LDFLAGS  += -Xlinker -Map=$(BIN_DIR)/$(PROJECT_NAME).map
LDFLAGS  += -T $(CONFIG_DIR)/worlds_mem.lds
LDFLAGS  += -T $(LDSCRIPT) -nostdlib
STDLIBS  = -lgcc
################################################################################
# Default Makefile Rules
EMPTYTARGETS := clean worlds load qemu erase help

.PHONY: all
all: $(TARGET)

$(BIN_DIR)/$(PROJECT_NAME).elf: $(gens) $(objs-y)
	@echo "\nGenerating elf		$(patsubst $(CUR_DIR)/%, %, $@)"
	@$(CC) $(CFLAGS) $(objs-y) $(LDFLAGS) -o $@ $(STDLIBS)
	@echo "Generating hex		$(patsubst $(CUR_DIR)/%, %, $(basename $@).hex)"
	@$(OBJCOPY) -O ihex $@ $(basename $@).hex
	@$(OBJCOPY) -O binary $@ $(basename $@).bin
	@echo "\nuTango size table"
	@$(SIZE) $@
	@$(OBJDUMP) -S --wide $@ > $(basename $@).asm
	@$(READELF) -a --wide $@ > $(basename $@).txt
	@$(OBJDUMP) --all-headers --demangle --disassemble --file-headers --wide \
				-D $@ > $(basename $@).lst

ifneq ($(DEBUG), y)
	@echo "Striping	$@"
	@$(SSTRIP) -s $@
endif

$(BUILD_DIR)/%.d : $(SRC_DIR)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(CUR_DIR)/%, %, $<)"
	@$(CC) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@" $(CFLAGS) $< > $@

#avoid including .d files during empty targets
ifeq (,$(filter $(EMPTYTARGETS),$(MAKECMDGOALS)))
-include $(deps)
endif

$(objs-y):
	@echo "Compiling source	$(patsubst $(CUR_DIR)/%, %, $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

################################################################################
# Rule to generate assembly macros

ifneq ($(wildcard $(ASM_DEFS_SRC)),)
$(ASM_DEFS_HDR): $(ASM_DEFS_SRC)
	@echo "Generating header	$(patsubst $(CUR_DIR)/%, %, $@)"
	@$(CC) -S $(CFLAGS) $< -o - \
		| awk '($$1 == "->") { print "#define " $$2 " " $$3 }' > $@

$(ASM_DEFS_HDR).d: $(ASM_DEFS_SRC)
	@echo "Creating dependency	$(patsubst $(CUR_DIR)/%, %,\
		 $(patsubst %.d,%, $@))"
	@$(CC) -MM -MT "$(patsubst %.d,%, $@)" $(addprefix -I, $(INC_DIRS)) $< > $@
endif

################################################################################
# Rule to create directories
.SECONDEXPANSION:

$(objs-y) $(deps) $(TARGET) $(gens): | $$(@D)

$(MKDIR):
	@echo "Creating directories	$(patsubst $(CUR_DIR)/%, %, $@)"
	@mkdir -p $@

################################################################################
# Rule to build worlds
WORLDS := $(wildcard $(WDL_DIR)/world*)
.PHONY: worlds $(WORLDS)

worlds: $(WORLDS)
	$(if $(strip $(WORLDS)),,$(error No worlds are present in the utango tree \
	(worlds/<EMPTY>)))

$(WORLDS):
	$(if $(wildcard $@/Makefile), \
		@echo "Cleaning $(patsubst $(WDL_DIR)/%, %, $@)..."; \
		$(MAKE) -s -C $@ clean; \
		echo "Building $(patsubst $(WDL_DIR)/%, %, $@) for $(BOARD) board..."; \
		$(MAKE) -s -C $@ BOARD=$(BOARD), \
		@echo "No Makefile found for $(@F)...")

################################################################################
# Rule to clean garbage files
.PHONY: clean
clean:
	@echo "Erasing directories..."
	-rm -rf $(BUILD_DIR)
	-rm -rf $(BIN_DIR)

################################################################################
# Rule to load  executable to the board or erase flash

ifeq ($(BOARD),$(filter $(BOARD),arty_devkit))

GDB_BOARD_RESET = -ex "monitor reset emulated"

else ifeq ($(BOARD),$(filter $(BOARD),LPC55S69))

GDB_BOARD_RESET = -ex "monitor reset"

   ifndef OPENOCD
      $(error OPENOCD (Free and Open On-Chip Debugging, In-System Programming and Boundary-Scan Testing) variable path \
      not set. [usage] export OPENOCD=<openocd_directory>/bin/openocd)
   else
      DEBUG_TOOL += $(OPENOCD)

      ifeq ($(BOARD),LPC55S69)
         DEBUG_TOOL_ARGS +=
      endif
   endif
endif

GDB_PORT ?= 3333
GDB_LOAD_ARGS ?= --batch --nx
GDB_LOAD_CMDS += -ex "set mem inaccessible-by-default off"
GDB_LOAD_CMDS += -ex "set remotetimeout 240"
GDB_LOAD_CMDS += -ex "target remote localhost:$(GDB_PORT)"
GDB_LOAD_CMDS += $(GDB_BOARD_RESET)
GDB_LOAD_CMDS += -ex "load"
GDB_LOAD_CMDS += -ex "monitor continue"
GDB_LOAD_CMDS += -ex "quit"

.PHONY: load qemu erase gdb
load:
	@echo "Start loading utango...\n"
	@$(DEBUG_TOOL) $(DEBUG_TOOL_ARGS) &
	@$(GDB) bin/$(BOARD)/$(PROJECT_NAME).elf $(GDB_LOAD_ARGS) $(GDB_LOAD_CMDS)
	@pkill $(notdir $(PYOCD))

erase:
	@echo "Start erasing board $(BOARD)..."
	@$(DEBUG_TOOL) $(ERASE)
	
gdb:
	$(CROSS_COMPILE)gdb -x script.gdb


################################################################################
# Rule to show a help
.PHONY: help

help:
	@echo
	@echo "Makefile targets:"
	@echo "  all		- Build uTango binary"
	@echo "  worlds 	- Compile each World"
	@echo "  load		- Load uTango to the target board"
	@echo "  qemu		- Load uTango in QEMU"
	@echo "  gdb		- Load uTango to GDB"
	@echo "  erase		- Call the erase command from the debugger tool"
	@echo "  help		- This help"
	@echo