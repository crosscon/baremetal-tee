# Microvisor folder

It defines the main functionalities of MCU-Fortifier firmware. The main purpose of each file inside the folder is described in the following list. 

* `bootloader`: primary code unit of microvisor, is immediately called after the board reboot. Performs all necessary tasks (error reporting, update checking, memory configuration) before transitioning to fortified application execution.
* `error`: contains different error codes and length of data associated with each error.
* `exception_manager`: includes the definition of the deprioritized exceptions handler an the functions to simulate and to return from them.
* `it`: definition of the SVCall, HardFault and MemManage Handlers.
* `mbedtls_rng_wrapper`: wrapper providing an interface between STM DRBG (Deterministic Random Bit Generator) peripheral and mbedtls library.
* `memory_map`: file providing variables for memory map symbols
defined in linker scripts.
* `microvisor_config`: contains different configuration settings for the microvisor. Can be customized by the user before the compilation of MCU-Fortifier.
* `ota`: implements OTA update capabilities for both microvisor and fortified applications.
* `permanent_storage`: implements permanent storage system. 
* `PPB_handlers`: definition of the wrappers to launch the simulation of every version of STR and LDR instructions.
* `PPB_recovery`: includes the functions for detecting the cause of a HardFault and for invoking the STR and LDR wrappers.
* `sec_comm`: implements secure communication layer used transparently by
the rest of the system.
* `simulator_common`: defines the supporting functions to set/get the value of registers, the ones to simulate faulty instructions (using an in-memory routine and the current context) and to check accesses to PPB. 
* `stm32l4xx_hal_conf`: defines the import and configuration of HAL (Hardware Abstraction Layer) libraries provided by STMicroelectronics.
* `stm32l4xx_hal_msp`: provides HAL MSP (MCU Support Package) callbacks. Used to configure clocks and other low-level properties of DRBG peripheral.
* `stm32l4xx_it`: implements default system interrupts (provided by STM) used by microvisor before transitioning to fortified application execution and enforcing interrupt deprioritization.
* `stm32l475vg_mpu`: MPU configuration for STM32L475 MCU.
* `system_instruction_recovery`: includes functions for detecting the cause of an SVCall, the definition of the wrappers for the simulation of the system instructions (CPS, MSR and MRS) and their invocation.
* `tee_client_api`: Global Platform Client API that each TA should implement.
* `tee_common`: constants, data structures and types used by the TEE to adhere to the Global Platform TEE stanrd. 
* `tee_core_api`: Global Platform Core API that can be used by TAs.
* `virtual_IPSR`: definition of the virtual IPSR (Interrupt Program Status Register), with its supporting functions.  
* `wifi_wrapper`: interface layer abstracting specific characteristics of the Wi-Fi peripheral equipped on B-L475EIOT01A1 board. Used by the secure communication layer, allows to easily port implementation to devices using different communication peripherals.

More information can be found in the complete documentation under the "Documentation/source_manual" folder. 

# Logical flows

The following three main flows implemented by the MCU Fortifier are the ones that allows a more secure and controlled execution of fortified applications. 

## Exception Catcher

* Define of a custom `Exception_Catcher()` in the `exception_manager.c` file: 
    * Simulate the catched exception using the `Exception_Simulator(int exception_number, int exception_priority)` function defined in the `exception_manager.c` file; 
    * Cause an on purpuse HardFault to return from the execution. The fault is catched by the `Microvisor_HardFault_Handler()` in the `it.c` file;
    * If the cause of the HardFault is identified as an exception return request, the `Exception_Return_Handler(unsigned int* auto_frame)` in the `exception_manager.c` file is executed.
* Load of the custom `Exception_Catcher` in `startup_stm32f207xx.s` file during the microvisor startup;

In this way, every exeption is catched and executed under the supervision of the MCU Fortifier. 

## Hard Fault Handler

* Define of a custom `Microvisor_HardFault_Handler()` in the `it.c` file: 
    * Check if the HardFault is caused by a unprioritized access to PPB (Private Peripheral Bus) and, in that case, call the `Recover_PPB_Access(unsigned int* auto_frame, unsigned int* manual_frame)` function in the `PPB_recovery.c` file;
    * Determine if the faulty instruction match one of the PPB istruction, namely one of the STD or LDR variant, and call the appropriate simulation wrapper (e.g. `simulate16_str_ldr_r1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame)`) defined in `PPB_handlers.c`;
    * The wrapper simulate the instructions by calling the `Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, unsigned int inst_len)` function, which in turn, calls `Run_With_Context(unsigned int* address, unsigned int* auto_frame, unsigned int* manual_frame)`;
    * Both the latter functions are defined in `simulator_common.c`.
* Load of the custom `Microvisor_HardFault_Handler` in `startup_stm32f207xx.s` file during the microvisor startup;

Using this flow, the MCU Fortifier is in charge of executing and handling the Hard Faults caused by LDR and STR instructions.

## SVC Handler

* Define of a custom `Microvisor_SVC_Handler()` in the `it.c` file: 
    * Check if the SVC was executed in order to simulate the usage of a system instruction (CPS, MRS, MSR) with privileges and, in that case, call the `Recover_System_Instruction(unsigned int* auto_frame, unsigned int* manual_frame)` function in the `system_instruction_recovery.c` file;
        * Determine which one of the system instruction match, and call the appropriate simulation wrapper (e.g. `Simulate_CPS(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame)`) defined in `system_instruction_recovery.c`;
        * The wrapper simulate the instructions by calling the `Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, unsigned int inst_len)` function, which in turn, calls `Run_With_Context(unsigned int* address, unsigned int* auto_frame, unsigned int* manual_frame)`;
        * Both the latter functions are defined in `simulator_common.c`.
    * If that is not the case, the SVC handler could have been called by either a client application to perform a Global Platform Client API call (SVC number is in the range 0-4, and in that case the TA API call is performed and the exception return is executed) or by a trusted application to perform a TEE Core API call (SVC number is in the range 5-50, and in that case the API call is performed and the execution is returned to the trusted application);
    * In all the other cases, the original SVC_Handler is performed.
* Load of the custom `Microvisor_SVC_Handler` in `startup_stm32f207xx.s` file during the microvisor startup;

Using this flow, the MCU Fortifier is in charge of executing and handling the SVC caused by the simulation of the CPS, MRS and MSR instructions. 