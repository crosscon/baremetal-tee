# Bare-metal TEE MPU-version
This is the CROSSCON baremetal-TEE implementation for MPU-capable devices, taking as reference the ARMv7-m architecture. We call this version MCU-fortifier
## Introduction

MCU-Fortifier is a solution for memory isolation aiming at increasing the security of embedded devices in a way that is mostly transparent to application developers. MCU-Fortifier also provides additional services such as Over-The-Air (OTA) update capabilities and error reporting features, which allow developers to easily monitor the applications being executed on their devices.

MCU-Fortifier is designed to work on Cortex M3 devices (ARMv7-M Architecture) equipped with a Memory Protection Unit (MPU).

The software package can be decomposed in the following macrocomponents which will be explained throughout this document:
* **Fortified Application**: an embedded application specifically compiled in order to be compatible with MCU-Fortifier. A fortified application is sometimes called *user application* or *firmware*.
* **MCU-Fortifier Microvisor**: the first piece of software executed on boot of the embedded device, acts as an OS, bootstraps the execution of the Fortified Application and constantly monitors it. This is sometimes referred to simply as *microvisor*. This is the main component of the MCU-Fortifier software solution.
* **Instrumenter**: tool that during compilation instruments source files at assembly level allowing the creation of fortified applications.
* **Update Server**: a server application running on a more powerful machine. The Microvisor contacts the Update Server on boot in order to report error and check for updates for both the fortified application and the Microvisor itself.
* **Activation Server**: another server application running on a more powerful machine. The Microvisor contacts the Activation Server during its first boot in order to activate the board on which it was installed using a specific license.


## Repository Organization

The repository include the following major folder:
* **apps**: directory that include some sample fortified application.
* **OS**: main folder which include almost all the component of the fortifier, the instrumenter, the update and activation server.
* **reflasher**: directory that include the component used to update firmware of the Fortifier.
* **TAs**: link to the repository of a sample TAs.



The OS folder, which include the code code of the system, is organized as follow. 
* **ActivationServer**: directory containing all server side files regarding the Activation Server.
* **Documentation**: directory containing both the MCU-Fortifier User Manual and Source Manual.
* **Drivers**: directory containing BSP, CMSIS and STM32L475 drivers.
* **Microvisor**: directory containing Microvisor source code.
    * **Inc** folder contains all header files. 
    * **Private-Src** contains source files not shared with MCU-Fortifier users. 
    * **Src** contains publicly available source files.
* **Middlewares**: directory containing third party libraries such as *mbedtls* and the board Wi-Fi library.
* **UpdateServer**: directory containing all server side files regarding the Update Server.
* **Utils**: directory containing multiple utility scripts, including the instrumentation required to create fortified applications (\verb|instrumenter.py|).
* **BOOTLOADER.ld**: linker script used to build the MCU-Fortifier microvisor.
* **Makefile**: Makefile automating the build process.
* **memory_map.ld**: linker script containing the memory map.
* **startup_bootloader.s**: assembly file including the entry point of MCU-Fortifier, the vector table used by the microvisor and the vector table used for the interrupt deprioritization mechanisms.


## Licensing

See the LICENSE file in the top-level directory.

## Configuration, Usage and Development of applications for MCU Fortifier

Clone the repository of MCU fortifier:

```bash=
git clone https://github.com/CybersecurityUnitn/MCU-fortifier/tree/main
```

### Configuration of MCU Fortifier

The source files **microvisor_config.h** and **microvisor_config.c**, contained respectively in the folders *OS/Microvisor/Inc* and *OS/Microvisor/Src*, are designed to be modified by the user to customize the Microvisor configuration. These files contain the following:
* Network parameters, such as Wi-Fi SSID and password necessary for connecting the device to the Internet.
* Connection parameters, such as the IP and port of the remote Update Server queried for updates on boot.
* Symmetric encryption key, used to encrypt and authenticate the communication with the Update Server (the same value must be set for both the Microvisor and the Update Server).
* MCU-Fortifier License, used to activate the device during the first boot by communicating with the Activation Server.

### Compilation of MCU Fortifier

#### Prerequisites
After cloning the repository, before compiling MCU Fortifier for the first time, it is **required** to follow this additional step due to the usage of some parts of the **mbedtls** cryptography library inside the codebase. All the required code of the library is stored in the *OS/Middlewares/mbedtls* folder, alongside a custom **Makefile** to obtain the *\*.a* files needed. Only some parts of the library are used and specific parameters are needed for the compilation to fit on the dedicated space of the target board. 

Note: in order to compile both mbedtls library and MCU Fortifier, the **GNU Arm Embedded Toolchain** should be installed on the system. It is normally included in the STM32CubeIDE (which will be used later on) with a path similar to this one (depending on the installation folder):

```bash=
/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.100.202403111256/tools/bin
```

Otherwise, the toolchain can be installed on the system as a standalone package. 

To start the compilation process, use the following command (make sure to substitute the CC and AR paths with the correct ones on your system):
```bash=
make CC=arm-none-eabi-gcc AR=arm-none-eabi-ar LD=arm-none-eabi-ld CFLAGS="-Os -march=armv7-m -mthumb" LDFLAGS="--specs=nosys.specs --specs=nano.specs"
```

#### Compilation

Once the library is compiled, the process of obtaining the MCU-Fortifier Microvisor executable is straightforward.

* Open the *OS folder* of source code for MCU-Fortifier.
* Edit the *GCC_PATH* and *PREFIX* variables inside the **Makefile** in order to point to the installation folder of the GNU Arm Embedded Toolchain on your system. A possible example is the following (case of standalone toolchain):

```bash=
GCC_PATH=/home/beaglehot/gcc-arm-none-eabi-10-2020-q4-major/bin
PREFIX=arm-none-eabi
```

* Open a terminal and type:

```bash=
make
```

If the compilation process was successful, the executable can be found in the **Build** folder under the name **MCU-Fortifier.elf**.

Note: The whole compilation described is intended for (and was tested on) Linux environments. In case any other OS is used (e.g. Windows) additional steps and small modifications can be required (e.g. installation of Make Tools and Python, definition of environment variables, path changes, etc.).     

### Activation of MCU-Fortifier

In order to execute, MCU-Fortifier must be activated. The activation is a one-time process performed on the first boot of MCU-Fortifier.

To completely perform the activation the device must be capable of communicating with the Security Embedded Activation Server, for this reason a valid Internet connection is required on the first boot. Subsequent boots check that the activation has been performed without requiring any Internet access.

A board that has not been activated will continue rebooting and attempt to connect to Internet until the activation process has been carried out successfully. If your fortified application is not being executed, make sure that a valid license is specified in the \textit{microvisor\_config.c} file.


### Fortifying an Application

In order to turn an embedded project into a fortified application, executed under the supervision of the MCU-Fortifier Microvisor, the steps presented here are required. 

Note: this part uses STM32CubeIDE as the development environment and a B-L475E-IOT01A1 board (STM32L475VG MCU) as a test environment. Other tools and boards can be used to obtain the same results, but different steps can be required.

This first set of steps presents how to develop and build a sample application to make LEDs blink on the board.

* Create a new STM32 Project in STM32CubeIDE, selecting *STML475VG* as target board and name it, for example, *blinky l475*.
* In the Device Configuration screen, left-click on pin PB14 and PC9 and configure them as GPIO_Output. In the GPIO Configuration tab assign a label to each of the pins, respectively Green_Led to PB14 and Network_Led to PC9.
* Open the source file main.c and edit the main() function in order to make the leds blink. 

```c
int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();

    /* Led blink */
    while (1)
    {
        HAL_GPIO_TogglePin(Green_Led_GPIO_Port, Green_Led_Pin);
        HAL_GPIO_TogglePin(Network_Led_GPIO_Port, Network_Led_Pin);
        HAL_Delay(100);
    }
}
```

* Build the application, and launch a Debug session with the default configuration. 
* Verify that the application is working as intended (the green and orange led should be blinking).

To build a fortified application able to run on top of MCU Fortifier, the build process should be customized in order to run the **Instrumenter** on the source files. The second set of steps for doing this is presented below. 

* Disable the setting that automatically generates a standard Makefile in STM32CubeIDE. Go into the project properties and uncheck the option *Generate Makefiles automatically* under the *C/C++ Build* tab. 
* If the project was previously compiled, navigate to the *Debug* folder of and locate the file called *Makefile*. Otherwise, create a file structure for the project as the one illustrated below (*Debug* folder with a *Makefile* inside):

```bash=
.
├── blinky_l475.ioc
├── blinky_l475.launch
├── Core
├── Debug
|   └── Makefile
├── Drivers
└── STM32L475VGTX_FLASH.ld
```

* Edit the **Makefile** following one of examples, that act as a template, inside the *apps* folder of the repository. The main sections of the Makefile that needed to be considered are the following. 
    * Target: includes the variable *PROJECT_NAME* that can be edited according to the name of the project under development.
    * MCU-Fortifier Toolchain: includes the variable *INSTRUMENTER_PATH* that contains the path of the Python program used to instrument the application sources during the compilation process. This program is called *instrumenter.py* and can be found at the *MCU-fortifier/OS/Utils/instrumenter.py* path inside the repository.
    * GNU Arm Embedded Toolchain Path: contains the variables *GCC_PATH* and *PREFIX* already described for the Makefile of MCU Fortifier. They indicates the paths to the installation of GNU Arm Embedded Toolchain.
    * Instrument source files: boolean variable named *INSTRUMENT_SOURCES* that can be set to decide whether to use the toolchain to instrument the application source files or not. To enforce the fortification process this variable should be set to 1.
    * Windows specific configuration: set of variables specific for Windows users.
    * Code sources: contains two variables *C_SOURCES* and *ASM_SOURCES* that store respectively the list of C source files (files with .c extension) and assembly files (files with .s extension) that will be used in the compilation process. In basic projects, like the one of the example, the vast majority of files are C sources and part of the default Drivers folder, with the exception of the startup code. For more complex projects, the C sources that includes the application logic should be inserted as well. 
    * Binaries: specify the tools needed for compilation process. Uses the already set variables *GCC_PATH* and *PREFIX* to specify the path of GNU Arm Embedded Toolchain binaries.
    * CFLAGS: stores different flags and option used during the compilation process. For example, the flag *-mcpu=cortex-m3* that indicates to compile the code for an ARM M3 processor should be included. Aside from that, other variables that must be edited are *C_DEFS* and *C_INCLUDES* that contain respectively a list of preprocessor definitions and a set of folders that will be used by GCC to look for header files. All the header files of the application developed (or the folder containing them) should be inserted here.
    * LDFLAGS: contains the variable *LDSCRIPT* which indicates the path of the linker script needed to correctly link the project. STM32CubeIDE generates a linker script after the creation of the project, but the file should be edited as well in order to create a Fortified Application able to run on MCU Fortifier.
    * The remaining sections contain the rules used to compile and link together the application that normally do not require any editing.

* Edit the linker script to instruct the compiler where the different functions and variables must be positioned, since part of the RAM and FLASH memory are reserved for exclusive use of the Microvisor. This is used to place the Fortified Application at a specific location where the Microvisor will search. STM32CubeIDE automatically generate two linker scripts, namely *STM32L475VGTX_FLASH.ld* and *STM32L475VGTX_RAM.ld*, but the automatic build process uses only the first one (the second can be deleted). The part of the script that needs to be edited in the one containing the memory map: the new one should be compatible with the one developed for MCU-Fortifier listed below. 

```c
MEMORY
{
    FLASH_BOOT (rx)            : ORIGIN = 0x08000000, LENGTH = 0x20000  /* Microvisor reserved flash memory */
	FLASH_BOOT_NOPRI (rx)      : ORIGIN = 0x08020000, LENGTH = 0x1000   /* Microvisor code running without privileges */
	FLASH (rx)                 : ORIGIN = 0x08021000, LENGTH = 0xdf000  /* Flash memory for user application */
	RAM_BOOT (xrw)             : ORIGIN = 0x20000000, LENGTH = 0x20     /* Reserved RAM used by the microvisor during user application runtime */
	RAM (xrw)                  : ORIGIN = 0x20000020, LENGTH = 0x17FE0
	RAM2 (xrw)                 : ORIGIN = 0x10000000, LENGTH = 32K
}
```

* Remove the directive related to the target processor (e.g. *.cpu cortex-m4* in the startup file) inseted automatically by STM32CubeIDE during the build process. This can be done by using a single search-and-replace and should be done because MCU-Fortifier is designed to work with Cortex-M3 devices (which only support a subsection of Cortex-M4 instructions) and the correct architecture is already specified with command line options. 

* Edit the debug configuration to correctly flash and load all the necessary information from both the Micorvisor executable (MCU-Fortifier.elf) and the fortified application executable (blinky_l475.elf). To do this with STM32CubeIDE it is necessary to open the *Debug Configuration* window by right-clicking on the project, selecting *Debug As* and choosing *Debug Configurations*. On the *Startup* tab, it is required to:
    * Add the Microvisor executable by clicking on *Add* and browsing the file system to the location where the ".elf" for MCU Fortifier is stored;
    * *Move down* the imported executable and make it the last element of the list (a green play symbol should appear next to its name). This ensures that MCU Fortifier will be the first code executed on boot, otherwise, the fortified application would be executed directly without performing all the necessary configuration steps resulting in unpredictable behaviours;
    * Uncheck the *Halt on exception* option as they are often triggered by the Microvisor and leaving that on would interfere with the debugging process, resulting in constant halting of the code.

* Execute the Fortified Application via a normal debug session. The steps performed ensure that both the Fortified Application and Microvisor executables will be flashed on the board. On boot, the board will start executing the Microvisor which will perform the basic configuration operation and bootstrap the execution of the application.
