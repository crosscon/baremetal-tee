#    Author: Michele Grisafi
#    Email: michele.grisafi@unitn.it
#    License: MIT 
TOOLCHAIN_DIR = ../toolchain
GCC_TOOL_ORIGINAL_ROOT := $(TOOLCHAIN_DIR)/compiler/msp430gcc-9.3.1.11-original
GCC_TOOL_INSTRUMENTED_ROOT := $(TOOLCHAIN_DIR)/compiler/msp430gcc-9.3.1.11-instrumented

COMPILER_ORIGINAL := $(GCC_TOOL_ORIGINAL_ROOT)/bin/msp430-elf-gcc-9.3.1
COMPILER_INSTRUMENTED := $(GCC_TOOL_INSTRUMENTED_ROOT)/bin/msp430-elf-gcc-9.3.1

OBJ_COPY := $(GCC_TOOL_ORIGINAL_ROOT)/bin/msp430-elf-objcopy
COMPILER_INCLUDE_ORIGINAL := $(GCC_TOOL_ORIGINAL_ROOT)/msp430-elf/include
COMPILER_INCLUDE_INSTRUMENTED := $(GCC_TOOL_INSTRUMENTED_ROOT)/msp430-elf/include

INCLUDE_GCC := $(TOOLCHAIN_DIR)/compiler/include_gcc

#Python 3 executable
PYTHON := python3

#Override paths
#include paths.mk

#Add to the PATH the various binaries
export PATH := $(PATH):$(GCC_TOOL_ROOT)/bin/:$(GCC_TOOL_ROOT)/libexec/gcc/msp430-elf/9.2.0:$(GCC_TOOL_ROOT)/msp430-elf/bin/


ROOT_DIR := .


VERIFIER := $(TOOLCHAIN_DIR)/postprocessor.py
MODIFIER := $(TOOLCHAIN_DIR)/modifier.py
METADATA := $(TOOLCHAIN_DIR)/metadata.py

RM := rm -rf

#GCC optimisation level for user application
OPTIMISATION := 0

#Additional flags to be used in compilation
EXTRA_FLAGS := #-fno-peel-loops #-fpeel-loops #-fgcse-after-reload -fipa-cp-clone -floop-interchange -floop-unroll-and-jam -fpredictive-commoning -fsplit-loops -fsplit-paths -ftree-loop-distribution -ftree-loop-vectorize -ftree-partial-pre -ftree-slp-vectorize -funswitch-loops -fvect-cost-model -fvect-cost-model=dynamic -fversion-loops-for-strides -fpeel-loops 

#Registers blocked by the compiler
FIXED_REGS = -ffixed-R4 -ffixed-R5 -ffixed-R6 -ffixed-R8

# variable used for the verification process
VERIFY:=1

# whether to use variables rather than absolute addresses for the virtual functions
VIRTUAL_LABELS = 0

# use modified gcc libraries
USE_NEW_LIB := 1

# replace reta and calla with ret and reta
SMALL_MEMORY=1

#Enable debug info for the post processor script
DEBUG_POST_PROCESSOR=0

#The base name of the final files
FILE_NAME := deployable

#This will be the file that can be deployed
OUTPUT_FILE := $(FILE_NAME).out

#This will be the file without initial metadata
OUTPUT_FILE_NO_METADATA := appWithNoMetadata.out

#Output map file
OUTPUT_MAP := $(FILE_NAME).map



#Formatting:
GREEN=\033[32m
BLUE=\033[34m
ORANGE=\033[33m
DEFAULT=\033[0m

# Linker script
LD_SRCS += $(TOOLCHAIN_DIR)/linkerScript.ld
LD_ORIG := $(TOOLCHAIN_DIR)/linkerScriptNoMod.ld


############# THE FOLLOWING FILES DETERMINE THE SOURCE FILES TO BE COMPILED

# These will be the folders created by the compiler
APPASM_DIR = ./asm
APPOBJ_DIR = ./obj
APPSRC_DIR = ./src

#The hook for the various PISTIS functions
PISTIS_HOOK = ../TCM/core/src/TCMhook.h



####### Load the files to be compiled
APPSRC_FILES := $(wildcard $(APPSRC_DIR)/*.c)
APP_OR_ASM_FILES := $(wildcard $(APPSRC_DIR)/*.s)
APPASM_FILES := $(patsubst $(APPSRC_DIR)/%.c,$(APPASM_DIR)/%.s,$(APPSRC_FILES))
APPASM_FILES += $(wildcard $(APPASM_DIR)/*.s)
APPASM_FILES += $(patsubst $(APPSRC_DIR)%,$(APPASM_DIR)%,$(APP_OR_ASM_FILES))

##### Compiler arguments
LIBS := -lgcc -lc -lm 

ifeq ($(USE_NEW_LIB),1)
	COMPILER_INCLUDE=$(COMPILER_INCLUDE_INSTRUMENTED)
else
	COMPILER_INCLUDE=$(COMPILER_INCLUDE_ORIGINAL)
	FIXED_REGS=
endif

# '-mhwmult' and '-mmcu' model dependent
# '-Wall' most warnings
# '-mcode-region=none' both the compiler and the linker do not make any changes to section names
# '-mlarge' use large 20 bit address mode
# '-Wl,-Map,"$(OUTPUT_MAP)" -Wl' pass the address map to the linker
# '--gc-sections' garbage collection on unused sections
# '--no-relax' disable linker relaxation
# '--disable-sec-transformation' Prevent the transformation of sections as specified by the --code-region and --data-region options
# '--allow-multiple-definition' Allow multiple definition of functions, so that the custom ones replace the default ones.
LINKER_ARGS := -mhwmult=none -mmcu=msp430f5529 -O$(OPTIMISATION) -w -mlarge -T"$(LD_SRCS)" \
-Wl,-Map,"$(OUTPUT_MAP)" -L"$(INCLUDE_GCC)" -Wl,--no-relax -Wl,--disable-sec-transformation -Wl,--allow-multiple-definition \


# '-c' Compile and assemble, but do not link.
# '-mdata-region=lower' the compiler assumes data is in the lower region of memory
# '-ffixed-R4 -ffixed-R5 -ffixed-R6' prevent the use of R4, R5 and R6 registers
# '-fno-function-cse' Reduce number of dynamic calls
ASSEMBLER_ARGS_APP := -c -mmcu=msp430f5529 -mhwmult=none -I"$(INCLUDE_GCC)" -I"$(ROOT_DIR)" -I"$(APPSRC_DIR)" \
-I"$(COMPILER_INCLUDE)" -O$(OPTIMISATION) -w -mlarge $(FIXED_REGS) -fno-function-cse -finline-functions -finline-limit=2000 $(EXTRA_FLAGS)



# All Target
all: verification

#Original application without any modification
original:
	$(COMPILER_ORIGINAL) -mhwmult=none -mmcu=msp430f5529 -O$(OPTIMISATION) -w -mlarge -T"$(LD_ORIG)" -Wl,-Map,"$(OUTPUT_MAP)" -I"$(INCLUDE_GCC)" -Wl,--no-relax -Wl,--disable-sec-transformation -Wl,--allow-multiple-definition $(APPSRC_FILES) $(LIBS) -o"$(OUTPUT_FILE_NO_METADATA)"
	$(MAKE) addMeta 

#$(eval FILE_LENGTH := $(shell stat -c "%s" $(OUTPUT_FILE_NO_METADATA)))
#Add metadata to output file
addMeta: $(OUTPUT_FILE_NO_METADATA)
	@echo -e '${BLUE}Adding metadata${DEFAULT}'
	$(PYTHON) $(METADATA) $^ $(OUTPUT_FILE) $(BSS_SIZE)
	@echo -e '${GREEN}Metadata added --> created file $(OUTPUT_FILE)${DEFAULT}'
	@chmod +x $(OUTPUT_FILE)


# Tool invocations
$(OUTPUT_FILE_NO_METADATA): $(LD_SRCS) $(OBJ_FILES)
	@echo -e '${GREEN}The application is safe${DEFAULT}'
	@echo -e '${BLUE}Building target: "$@"${DEFAULT}'
	@echo -e 'Invoking: GNU Linker'
ifeq ($(USE_NEW_LIB),1)
	$(COMPILER_INSTRUMENTED) $(LINKER_ARGS) -o"$@" $(OBJ_FILES) $(LIBS)
else
	$(COMPILER_ORIGINAL) $(LINKER_ARGS) -o"$@" $(OBJ_FILES) $(LIBS)
endif
	@echo -e '${GREEN}Finished building target: "$@"${DEFAULT}'
	@echo ' '

REJECT := 0

build_folders:  
	#Copying the asm files from srcdir or app
	@echo "Creating ASM directories and copying .s files"
	-mkdir $(APPASM_DIR)
	-mkdir $(APPOBJ_DIR) 
	-cp $(APPSRC_DIR)/*.s $(APPASM_DIR)/
	-cp $(PISTIS_HOOK) $(APPSRC_DIR)/
	#Replace them with new safe ones
ifeq ($(USE_NEW_LIB),1)
	@echo -e "${ORANGE}########## Using new Libs ###########${DEFAULT}"
else
	@echo -e "${ORANGE}########## Using original Libs ###########${DEFAULT}"
endif

# Perform the first verification by running the Rejecter module. Call the make file again with the result
verification: build_folders $(APPASM_FILES)
	$(eval OBJ_FILES += $(patsubst $(APPASM_DIR)/%.s,$(APPOBJ_DIR)/%.o,$(APPASM_FILES)))
ifeq ($(VERIFY),1) 
	@echo -e '${BLUE}Checking for the presence of unsafe instructions in $(APPASM_FILES)${DEFAULT}'
	$(eval REJECT = $(shell $(PYTHON) $(VERIFIER) $(DEBUG_POST_PROCESSOR) $(APPASM_FILES)))
	@echo Reject is "$(REJECT)"
ifeq ($(REJECT),1)
	@echo -e '${RED}REJECTED${DEFAULT}'
	$(error The application contains some unsafe instructions. It has been REJECTED)
else
	@echo -e '${GREEN}First verification passed${DEFAULT}'
endif
endif
	$(MAKE) addMeta REJECT=$(REJECT) OBJ_FILES="$(OBJ_FILES)"



# Create objects files without invoking the linker
$(APPOBJ_DIR)/%.o: $(APPASM_DIR)/%.s
ifeq ($(REJECT),1)
	@echo -e '${RED}REJECTED${DEFAULT}'
	$(error The compiled application has some unsafe code segments)
else
ifeq ($(VERIFY),1) 
	@echo -e '${BLUE}Replacing unsafe instructions${DEFAULT}'
	#@cp main.s old_main.s
	#backup the old asm file
	@cp $< $<.old
	@$(PYTHON) $(MODIFIER) $< $<.modified $(VIRTUAL_LABELS)
	@mv $<.modified $<
	@echo -e '${GREEN}Instructions replaced${DEFAULT}'
endif
endif
	@echo -e '${BLUE}Creating "$@" by building file: "$<"${DEFAULT}'
	@echo 'Invoking: GNU Compiler'
ifeq ($(USE_NEW_LIB),1)
	$(COMPILER_INSTRUMENTED) $(ASSEMBLER_ARGS_APP) -o"$@" "$<"
else
	$(COMPILER_ORIGINAL) $(ASSEMBLER_ARGS_APP) -o"$@" "$<"
endif
	@echo -e '${GREEN}Finished building: "$<" --> "$@" created${DEFAULT}'
	@echo ' '

#Create assembly files
$(APPASM_DIR)/%.s : $(APPSRC_DIR)/%.c
	@echo -e '${BLUE}Creating ASM file: "$@"${DEFAULT}'
ifeq ($(USE_NEW_LIB),1)
	$(COMPILER_INSTRUMENTED) $(ASSEMBLER_ARGS_APP) -S -o"$@" "$<"
else
	$(COMPILER_ORIGINAL) $(ASSEMBLER_ARGS_APP) -S -o"$@" "$<"
endif
	@echo -e '${GREEN}Finished creating: "$@"${DEAFULT}'
	@echo ' '

LIBRARY_COUNT=1
HELPER=0
# Instrument libraries
libraries:
	@python3 ../toolchain/helperScripts/auxGccParser.py src/helper${LIBRARY_COUNT}.s $(LIBRARY_COUNT)
	
	@[ -s src/helper${LIBRARY_COUNT}.s ] && echo -e "${ORANGE} just created helper${LIBRARY_COUNT}.s${DEFAULT}" || echo -e "${ORANGE} just created EMPTY helper${LIBRARY_COUNT}.s${DEFAULT}"
	@[ -s src/helper${LIBRARY_COUNT}.s ] && $(MAKE) clean || echo skipping make clean
	@[ -s src/helper${LIBRARY_COUNT}.s ] && $(MAKE) || echo skipping make
	@echo -e "${ORANGE} just finished invoking main to create helper${LIBRARY_COUNT}.s ${DEFAULT}"
	@[ -s src/helper${LIBRARY_COUNT}.s ] && $(MAKE) libraries LIBRARY_COUNT=${LIBRARY_COUNT}1 || echo skipping make libraries
	@[ ! -s src/helper${LIBRARY_COUNT}.s ] && rm src/helper${LIBRARY_COUNT}.s || echo ""
	@[ ! -f src/helper${LIBRARY_COUNT}.s ] && echo -e "${GREEN} Finished instrumenting libraries. ${DEFAULT}" || echo ""
	


# Other Targets
clean:
	-$(RM) $(APPOBJ_DIR) 
	-$(RM) $(APPASM_DIR)
	-$(RM) $(OUTPUT_FILE) $(OUTPUT_FILE_NO_METADATA)
	-$(RM) $(OUTPUT_MAP)
	-$(RM) $(APPSRC_DIR)/TCMhook.h
	-$(RM) *.s *.tmp
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean addMeta verification build_folders libraries
.SECONDARY: 
