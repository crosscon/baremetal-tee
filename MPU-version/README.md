# Bare metal TEE with MPU

## Introduction

The BareMetal-TEE with MPU is a solution for memory isolation and supervised execution aiming at increasing the security of embedded devices in a way that is mostly transparent to application developers. The architecture is fully compliant with the Global Platform TEE Client API specification and with a subset of the TEE Core API. The BareMetal TEE with MPU support the deployment of up to two custom Trusted Applications (TAs) compliant with the Global Platform TEE Core API.  

MCU-Fortifier is designed to work on Cortex M4 devices (ARMv7-M Architecture) equipped with a Memory Protection Unit (MPU). In particular, the Baremetal TEE was developed using a B-L475E-IOT01A1 board (STM32L475VG MCU) and tested on that specific environment. Compatibility with other M4 boards is theoretically possible, but hardware-dependent configurations (e.g. memory map and MPU configurations) should be changed. 

The software package can be decomposed in the following macrocomponents:
* **Fortified Application**: an embedded application specifically compiled in order to be compatible with the Baremetal TEE. The fortified application can also be referred as *user application*, *client application* or *CA*.
* **BareMetal TEE with MPU**: the first piece of software executed on boot of the embedded device, acts as an OS, bootstraps the execution of the Fortified Application and constantly monitors it. The TEE also offer core security functionalities like secure storage, key generation and cryptographic primites compliant with the Global Platform Core API. It is sometimes referred to simply as *microvisor* or *TEE* and it is the main component of the software solution.
* **Trusted Applications**: embedded security services that run in an isolated environment (separate memory and storage). It is an interface between unstrused applications and the TEE. The trusted applications are usually referred as *TA*.
* **Instrumenter**: tool that during compilation instruments source files at assembly level allowing the creation of fortified applications.


## Repository Organization

The repository include the following major folder:
* **apps**: directory that include some sample fortified application.
* **TAs**: directory that include some sample trusted application (e.g. bitcoin wallet)
* **OS**: main folder which include almost all the component of the fortifier, the instrumenter and some sample trusted application compliant with Global Platform TEE APIs. 
* **reflasher**: directory that include the component used to update firmware of the Fortifier.
* **Update Server**: a server application running on a more powerful machine. The Microvisor contacts the Update Server on boot in order to report error and check for updates for both the fortified application and the Microvisor itself.

**NOTE**: The update process is temporarily unavailable due to ongoing improvements to their mechanisms.

The OS folder, which include the core code of the system, is organized as follow. 
* **Drivers**: directory containing BSP, CMSIS and STM32L475 drivers.
* **Microvisor**: directory containing all the TEE source code.
  * **Inc** contains all header files. 
  * **Private-Src** contains private source files not shared with TEE users. 
  * **Src** contains publicly available source files (that allows some customization of the TEE configuration).
* **Middlewares**: directory containing third party libraries such as *mbedtls*, *cJSON* and the *Wi-Fi library* used by the board.
* **TAs**: directory containing the trusted applications designed for the TEE. Multiple TAs can be inserted in the code, but only two of them can run at the same time on the system. 
* **UpdateServer**: directory containing all server side files used by the Update Server.
* **Utils**: directory containing multiple utility scripts, including the toolchain required for the instrumentation of fortified applications (in particular *instrumenter.py*).
* **BOOTLOADER.ld**: linker script including the directives used to build the microvisor.
* **Makefile**: Makefile automating the build process.
* **memory_map.ld**: linker script containing the memory map.
* **startup_bootloader.s**: assembly file including the entry point of the TEE, the vector table used by the microvisor and the vector table used for the interrupt deprioritization mechanisms.

**NOTE**: The update process is temporarily unavailable due to ongoing improvements to their mechanisms.

## Licensing

See the LICENSE file in the top-level directory of the repository.

## Configuration, Usage and Development for the Baremetal TEE with MPU

Clone the repository:

```bash=
git clone https://github.com/crosscon/baremetal-tee/tree/main/MPU-version
```

### Configuration of MCU Fortifier

The source files **microvisor_config.h** and **microvisor_config.c**, contained respectively in the folders *OS/Microvisor/Inc* and *OS/Microvisor/Src*, are designed to be modified to customize the microvisor configuration. These files contain the following:
* Network parameters, such as Wi-Fi SSID and password necessary for connecting the device to the Internet;
* Connection parameters, such as the IP and port of the remote Update Server queried to check and download updates during boot;
* Symmetric encryption key, used to encrypt and authenticate the communication with the Update Server (the same value must be set for both the Microvisor and the Update Server).

**NOTE**: The update process is temporarily unavailable due to ongoing improvements to their mechanisms.

### Compilation of MCU Fortifier

#### Prerequisites 

In order to compile both mbedtls library and the Baremetal TEE, the **GNU Arm Embedded Toolchain** should be installed on the system. It is normally included in the STM32CubeIDE (which will be used later on) with a path similar to this one (depending on the installation folder):

```bash=
/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.100.202403111256/tools/bin
```

Otherwise, the toolchain can be installed on the system as a standalone package. 

#### Compilation of MBEDTLS

After cloning the repository, and before compiling the Baremetal TEE for the first time, it is **required** to follow this additional step due to the usage of parts of the **mbedtls** cryptography library inside the TEE codebase. 

The required code of the library is stored in the *OS/Middlewares/mbedtls* folder, alongside a custom **Makefile** to obtain the library files (libmbedcrypto.a, libmbedtls.a and libmbedtls.a) needed. Only some parts of the library are used (see the mbedtls/include/mbedtls/mbedtls_config.h configuration file) and specific parameters are needed for the compilation to fit on and work with the target board.

To start the compilation process, use the following command while located in the **library** folder of mbedTLS (e.g. *emanuele@emanuele-HP:~/Desktop/Code/MCU-fortifier/OS/Middlewares/mbedtls/library$* ):
```bash=
make CC=arm-none-eabi-gcc AR=arm-none-eabi-ar LD=arm-none-eabi-ld CFLAGS="-mcpu=cortex-m3 -mthumb -DUSE_HAL_DRIVER -DSTM32L475xx -Og -Wall -fdata-sections -ffunction-sections -g -gdwarf-2" LDFLAGS="--specs=nosys.specs --specs=nano.spec"
```

Note: make sure to use the path of GNU Arm Embedded Toolchain installed on your system to point to the CC and AR executables, as explained above. 

#### Compilation of Baremetal TEE

Once the library is compiled, the process of obtaining the MCU-Fortifier Microvisor executable is straightforward.

* Move into the *OS folder* of source code (e.g. *emanuele@emanuele-HP:~/Desktop/Code/MCU-fortifier/OS* ).
* Edit the *GCC_PATH* and *PREFIX* variables inside the **Makefile** in order to point to the installation folder of the GNU Arm Embedded Toolchain on your system. A possible example is the following:

```bash=
GCC_PATH=/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.100.202403111256/tools/bin
PREFIX=arm-none-eabi
```

* Open a terminal and type:

```bash=
make
```

If the compilation process was successful, the complete executable can be found in the **Build** folder under the name **MCU-Fortifier.elf**.

Note: The whole compilation process is intended for (and was tested on) Linux environments. In case any other OS is used (e.g. Windows) additional steps and small modifications are required (e.g. installation of MakeTools and Python, definition of environment variables, path changes, etc.).     

### Customization of included Trusted Applications (TAs)

As mentioned before, multiple Global Platform-compliant trusted applications (that offer different services) can be developed for the Baremetal TEE with MPU but only **TWO** of them can be compiled and run alongside the microvisor at the same time. 

#### Global Platform Client API for Trusted Applications (TAs)

In order to be compliant with the GlobalPlatform standard, each TA deployed on the Baremetal TEE **MUST** implement this following Client API in order to allow the communication with the client (in a standardize way):
* TEE_Result TA_CreateEntryPoint(void);
* TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, TEE_Param params[4], void **sessionContext);
* TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext, uint32_t commandID, uint32_t paramTypes, TEE_Param params[4]);
* void TA_CloseSessionEntryPoint(void* sessionContext);
* void TA_DestroyEntryPoint(void);

These functions should be inserted in a file that will act as the entry point to the TA. 

#### Compilation and Deployment  

Deploying a Trusted Applications requires different steps and modification to the TEE compilation process. A TA can be inserted in one of the two slots (TA1 and TA2) pre-defined inside the TEE. Depending on which TA slot you want to deploy our TA, it is important to use the variables defined in the Makefile and Linker Script (TA1 vs TA2, TA1_INCLUDE vs TA2_INCLUDE, etc.) accordingly. 

In the following illustrative steps, the first TA slot (TA1) will be used to deploy the Bitcoin Wallet demo TA. 

**NOTE**: in the case of a single TA deployed, it is necessary to fill the TA1 slot first. Also, for the sake of simplicity, it is possible to leave the empty TA2 included in the repository in the second slot if nothing else is used. This will require less modification to the TEE Makefile (otherwise everything related to TA2 should be commented out).

**NOTE**: in the client application, the first call to TEEC_InitializeContext set the context identifier to the first trusted application, namely TA1, so that every subsequent call to a GP Client API with the same context (and session) with call the TA in the first slot (TA1). To execute the functions of TA2, another call to TEEC_InitializeContext must be executed. Using this approach it is not possibile to interact with TA2 without having a context set for TA1 (not need to Open a Session), but a more advanced solution with UUID is under consideration. 

The required modifications for deploying the TA are the following. 
* Create a subfolder with the name of the TA inside the "OS/TAs" folder.
* Modify the Makefile of the TEE (available in the path *OS/Makefile*) in according to the following points.
  * Specify the entry point file of the TA (the one that is implementing the Client API functions, e.g. *TA_CreateEntryPoint(void)*, *TEE_Result TA_OpenSessionEntryPoint(...)*) in the TA1 variable: 

    ```bash=
    TA1 = TAs/bitcoin-wallet-ta/bitcoin_wallet_ta.c
    ```
  * Specify the paths of the *.h* files/folder used by the TA in the TA1_INCLUDE variable and prepend "-I" to each path: 

    ```bash=
    TA1_INCLUDE = \
    -ITAs/bitcoin-wallet-ta \
    -ITAs/bitcoin-wallet-ta/include \
    -ITAs/bitcoin-wallet-ta/crypto \
    ```

  * Specify the other source files used by the TA in the TA1_C_SOURCES:

    ```bash=
    TA1_C_SOURCES = \
    TAs/bitcoin-wallet-ta/bip39.c \
    TAs/bitcoin-wallet-ta/bip32.c \
    TAs/bitcoin-wallet-ta/crypto/sha2.c \
    TAs/bitcoin-wallet-ta/crypto/ecdsa.c \
    TAs/bitcoin-wallet-ta/crypto/hmac.c \
    TAs/bitcoin-wallet-ta/crypto/secp256k1.c \
    TAs/bitcoin-wallet-ta/crypto/ta_ripemd160.c \
    TAs/bitcoin-wallet-ta/crypto/memzero.c \
    TAs/bitcoin-wallet-ta/crypto/bignum.c \
    TAs/bitcoin-wallet-ta/crypto/pbkdf2.c \
    ```

    * Comment/uncomment the following lines of the Makefile based on the number of TAs used and that needs to be compiled. In this case, only the TA one is used, while the compilation for the TA two is not performed:

    ```bash=
    # list of TA1 C objects
    MICROVISOR_OBJECTS += $(addprefix $(TA1_BUILD_DIR)/,$(notdir $(TA1_C_SOURCES:.c=.o)))
    vpath %.c $(sort $(dir $(TA1_C_SOURCES)))
    # list of TA2 C objects
    #MICROVISOR_OBJECTS += $(addprefix $(TA2_BUILD_DIR)/,$(notdir $(TA2_C_SOURCES:.c=.o)))
    #vpath %.c $(sort $(dir $(TA2_C_SOURCES)))

    ....

    $(TA1_BUILD_DIR)/%.o: %.c Makefile | $(TA1_BUILD_DIR)
      $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(TA1_BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

    #$(TA2_BUILD_DIR)/%.o: %.c Makefile | $(TA2_BUILD_DIR)
    #	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(TA2_BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

    ```

* Modify the linkerscript of the TEE (path *OS/BOOTLOADER.ld*) as follwing. 
  * Specify the name of entry point for the TA followed by .o (in the example *bitcoin_wallet_ta*) in the definition of the ta1 segment of FLASH_TA1 area. The other TA files, if correctly specified in the TA1_C_SOURCE variable of the Makefile, should be automaticcaly inserted and compiled in the Build/TA/TA1 folder.

    ```bash=
    .code_TA1 :
    { 
      . = ALIGN(4);
      Build/bitcoin_wallet_ta.o(.text .text* .rodata .rodata* .constdata .constdata*)  /* Entry point object for TA1 which include GP Client API*/ 
      Build/TA/TA1/*.o(.text .text* .rodata .rodata* .constdata .constdata*) /* Other objects of TA1 */ 
      . = ALIGN(4); 
    } >FLASH_TA1
    ```
  * Specify in the same way the name of the entry point file of the TA in the BSS segment for TA1:

    ```bash=
    .bss_TA1 :
    {
      . = ALIGN(4);
      *(.bss_TA1)
      Build/bitcoin_wallet_ta.o(.bss .bss*) /* Entry point object for TA1 which include GP Client API*/ 
      Build/TA/TA1/*.o(.bss .bss*) /* Other objects of TA1 */ 
      . = ALIGN(4);
    } > RAM_TA1

    ```

* Add the right include directives for the header files that define the entry points for the Global Platform API. This should be done both for Client API and Core API and in all the files that use them. 

  ```c
  ...
  #include "tee_client_api.h"
  #include "tee_core_api.h"
  ...  
    ```

After completing these steps it should be possible to compile the Baremetal TEE with a custom TA integrated. 

**NOTE**: due to the use of an older C version for the compilation, some constructs added recently, like *maybe_unused*, are not supported. 

**NOTE**: as the hardware has limited availability of FLASH and RAM storage, each TA has predefined limits for the resources. In particular: 
* Each TA can use up to 240KB of FLASH memory for its code and libraries; 
* Each TA can use up to 16KB of FLASH memory for secure storage; 
* Each TA can use up to 48KB of RAM, of which 10KB are reserved for dynamic memory allocation using the GP Core API (e.g., TEE_Malloc).

**NOTE**: "printing" information into a serial console from a trusted application is possible using the dedicated USART1 interface of the microcontroller. Using other interfaces requires their initialization and customization inside the bootloader code. In order to simplify the process of displaying information, the following procedures were implemented:
* EMSG("..."): should be used to print error messages;
* IMSG("..."): should be used to display information to the user;
* DMSG("..."): should be used to print debug messages.

#### Global Platform Core API available to Trusted Applications (TAs)

The Global Platform Core API offered by the TEE that can be used by TA to build secure services are the following (divided by categories).

Operation Management functions:
* TEE_Result TEE_AllocateOperation(TEE_OperationHandle* operation, uint32_t algorithm, uint32_t mode, uint32_t maxKeySize);
* void TEE_FreeOperation(TEE_OperationHandle operation);                         
* TEE_Result TEE_SetOperationKey(TEE_OperationHandle operation, TEE_ObjectHandle key);

Object Management and Secure Storage functions:
* TEE_Result TEE_CreatePersistentObject(uint32_t storageID, void* objectID, size_t objectIDLen, uint32_t flags, TEE_ObjectHandle attributes, void* initialData, size_t initialDataLen, TEE_ObjectHandle* object);
* TEE_Result TEE_OpenPersistentObject(uint32_t storageID, void* objectID, size_t objectIDLen, uint32_t flags, TEE_ObjectHandle* object);
* TEE_Result TEE_CloseAndDeletePersistentObject1(TEE_ObjectHandle object);
* void TEE_CloseObject(TEE_ObjectHandle object);                          
* TEE_Result TEE_ReadObjectData(TEE_ObjectHandle object, void* buffer, size_t size, size_t* count);
* TEE_Result TEE_WriteObjectData(TEE_ObjectHandle object, void* buffer, size_t size );
* TEE_Result TEE_AllocateTransientObject(uint32_t objectType, uint32_t maxObjectSize, TEE_ObjectHandle* object);
* void TEE_FreeTransientObject(TEE_ObjectHandle object);                  
* TEE_Result TEE_PopulateTransientObject(TEE_ObjectHandle object, TEE_Attribute* attrs, uint32_t attrCount);
* void TEE_InitRefAttribute(TEE_Attribute* attr, uint32_t attributeID, void* buffer, size_t length);
* void TEE_InitValueAttribute(TEE_Attribute* attr, uint32_t attributeID, uint32_t a, uint32_t b);
* TEE_Result TEE_GetObjectBufferAttribute(TEE_ObjectHandle object, uint32_t attributeID, void* buffer, size_t* size);

Memory Management functions:
* void* TEE_Malloc(size_t size, uint32_t hint);
* void TEE_Free(void *buffer);
* void TEE_MemMove(void* dest, void* src, size_t size);
* void TEE_MemFill(void* buffer, uint8_t x, size_t size);

Random Value generation and Key Generation functions
* TEE_Result TEE_GenerateKey(TEE_ObjectHandle object, uint32_t keySize, TEE_Attribute* params, uint32_t paramCount);
* void TEE_GenerateRandom(void* randomBuffer, size_t randomBufferLen);   

BigInt Functions
* TEE_Result TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src);
* int32_t TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal);
* void TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);
* void TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2);
* TEE_Result TEE_BigIntConvertFromOctetString(TEE_BigInt *dest, uint8_t *buffer, size_t bufferLen, int32_t sign);
* void TEE_BigIntInit(TEE_BigInt *bigInt, size_t len);

Symmetric Cipher Functions:
* void TEE_CipherInit(TEE_OperationHandle operation, void* IV, size_t IVLen);
* TEE_Result TEE_CipherUpdate(TEE_OperationHandle operation, void* srcData, size_t srcLen, void* destData, size_t *destLen);
* TEE_Result TEE_CipherDoFinal(TEE_OperationHandle operation, void* srcData, size_t srcLen, void* destData, size_t *destLen);
The supported algorithms are: AES ECB, AES CBC, AES CTR, AES XTS, AES CBC MAC, AES CMAC, AES CCM, AES GCM.

MAC functions:
* void TEE_MACInit(TEE_OperationHandle operation, void* IV, size_t IVLen);
* void TEE_MACUpdate(TEE_OperationHandle operation, void* chunk, size_t chunkSize);                        
* TEE_Result TEE_MACComputeFinal(TEE_OperationHandle operation, void* message, size_t messageLen, void* mac, size_t *macLen);     
The supported algorithms are: HMAC SHA256, HMAC SHA384, HMAC SHA512. 

Message Digest Functions:
* void TEE_DigestUpdate(TEE_OperationHandle operation, void* chunk, size_t chunkSize);
* TEE_Result TEE_DigestDoFinal(TEE_OperationHandle operation, void* chunk, size_t chunkLen, void* hash, size_t *hashLen);
* TEE_Result TEE_DigestExtract(TEE_OperationHandle operation, void* hash, size_t *hashLen);
The supported hash functions are: Supported algorithms: SHA256, SHA384, SHA512, SHA3_256, SHA3_384, SHA3_512.

Asymmetric functions for Sign and Verify operations
* TEE_Result TEE_AsymmetricSignDigest(TEE_OperationHandle operation, TEE_Attribute* params, uint32_t paramCount, void* digest, size_t digestLen, void* signature, size_t *signatureLen);
* TEE_Result TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation, TEE_Attribute* params, uint32_t paramCount, void* digest, size_t digestLen, void* signature, size_t signatureLen);          

### Fortifying an Application

The steps presented here are required to turn an embedded project into a fortified application that can be executed under the supervision of the Baremetal TEE and be a client of one or both trusted applications. 

**Note**: this part uses STM32CubeIDE as the development environment and test environment. Other tools can be used to obtain the same results, but different steps can be required.

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

* Edit the **Makefile** following the template inside the *apps/sample_application* folder of the repository. The main sections of the Makefile that needed to be considered are the following. 
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

* Edit the **linker script** to instruct the compiler where the different functions and variables must be positioned, since part of the RAM and FLASH memory are reserved for exclusive use of the Microvisor. This is used to place the Fortified Application at a specific location where the Microvisor will search. STM32CubeIDE automatically generate two linker scripts, namely *STM32L475VGTX_FLASH.ld* and *STM32L475VGTX_RAM.ld*, but the automatic build process uses only the first one (the second can be deleted). The part of the script that needs to be edited in the one containing the memory map: the new one should be compatible with the one developed for MCU-Fortifier listed below. A complete example of the file can be found in the *apps/sample_application* directory. 

  ```c
  MEMORY
  {
    FLASH_BOOT (rx)        	   : ORIGIN = 0x08000000, LENGTH = 0x20000   /* Microvisor reserved flash memory */
    FLASH_TA1 (rx)             : ORIGIN = 0x08020000, LENGTH = 0x3C000   /* Flash memory for first TA */
    FLASH_SECURE_TA1(rw)       : ORIGIN = 0x0805C000, LENGTH = 0x4000    /* Secure Storage (flash memory) for first TA */
    FLASH_TA2 (rx)             : ORIGIN = 0x08060000, LENGTH = 0x3C000   /* Flash memory for second TA - w needed for trusted storage */
    FLASH_SECURE_TA2(rw)       : ORIGIN = 0x0809C000, LENGTH = 0x4000    /* Secure Storage (flash memory) for second TA */
    FLASH (rx)                 : ORIGIN = 0x080A0000, LENGTH = 0x58000   /* Flash memory for user application */
    FLASH_BOOT_NOPRI (rx)      : ORIGIN = 0x080F8000, LENGTH = 0x8000    /* Microvisor code running without privileges */
    RAM_BOOT (xrw)             : ORIGIN = 0x10000000, LENGTH = 0x20 	 /* Reserved RAM used by the microvisor during user application runtime */
    RAM (xrw)             	   : ORIGIN = 0x10004000, LENGTH = 0x4000    /* RAM for the user application */
    RAM_TA1 (xrw)       	   : ORIGIN = 0x20000000, LENGTH = 0xC000    /* RAM for the first TA */
    RAM_TA2 (xrw)              : ORIGIN = 0x2000C000, LENGTH = 0xC000    /* RAM for the second TA */
  }
  ```

* Remove the **directives related to the target processor** (e.g. *.cpu cortex-m4* in the startup file) inseted automatically by STM32CubeIDE during the build process. This can be done by using a single search-and-replace and should be done because MCU-Fortifier is designed to work with Cortex-M3 devices (which only support a subsection of Cortex-M4 instructions) and the correct architecture is already specified with command line options. 

* Edit the **debug configuration** to correctly flash and load all the necessary information from both the Micorvisor executable (MCU-Fortifier.elf) and the fortified application executable (blinky_l475.elf). To do this with STM32CubeIDE it is necessary to open the *Debug Configuration* window by right-clicking on the project, selecting *Debug As* and choosing *Debug Configurations*. On the *Startup* tab, it is required to:
    * Add the Microvisor executable by clicking on *Add* and browsing the file system to the location where the ".elf" for MCU Fortifier is stored;
    * *Move down* the imported executable and make it the last element of the list (a green play symbol should appear next to its name). This ensures that MCU Fortifier will be the first code executed on boot, otherwise, the fortified application would be executed directly without performing all the necessary configuration steps resulting in unpredictable behaviours;
    * Uncheck the *Halt on exception* option as they are often triggered by the Microvisor and leaving that on would interfere with the debugging process, resulting in constant halting of the code.

* Edit the **system clock configuration** of the client application to allign it with the one used for the MCU Fortifier. To do that, swap the content of the automatically generated *SystemClock_Config()* function inside the *main.c* file with the one provided below.

  ```c
  void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
      Error_Handler();
    }

    /** Configure LSE Drive Capability
    */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */

    /* MSI is enabled after System reset, activate PLL with MSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLP = 7;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }

    /** Enable MSI Auto calibration
    */
    HAL_RCCEx_EnableMSIPLLMode();
  }

  ```

* Execute the Fortified Application via a normal debug session. The steps performed ensure that both the Fortified Application and Microvisor executables will be flashed on the board. On boot, the board will start executing the Microvisor which will perform the basic configuration operation and bootstrap the execution of the application.

**NOTE**: as the hardware has limited availability of FLASH and RAM storage, the CA has predefined limits for the resources. In particular: 
* A CA can use up to 352KB of FLASH memory for its code and libraries; 
* A CA can use up to 16KB of RAM.

**NOTE**: The Trusted Execution Environment (TEE) heavily relies on the Supervisor Call (SVC) mechanism to change the context, privileges level and call the appropriate GP API. While the SVC mechanism remains available to developers working of Client Application (CA), it's important to note that parameter values passed to SVC within the range of 0–50 are reserved for internal Global Platform API operations and will not trigger the CA's SVC handler. Values outside this range will behave normally. 

#### Using Trusted Applications' functionalities from a Client (Fortified) Application

In order to be able to use the security services offered by the Trusted Applications (and the Core Security Services of the TEE) the Global Platform client API should be used. To do that, it is required to insert in the codebase of the Fortified Application the following files provided in the repository, under the *app/sample_files* folder:
* tee_client_api.c and tee_client_api.h: they provide the implementation of the calls to the entry points offered by the TA, using the SVC mechanism and shared memory/registers for parameter passing;
* tee_common.h: define a set of parameters and data structures to communicate with the trusted application. 

**NOTE**: these files should be compiled togheter with the fortified application by including the in the custom Makefile. 

It is important to recall that the flow of communication between client application/fortified application and trusted applications should follow a predefined order:
* Initialization of the context ( TEEC_Result TEEC_InitializeContext(const char* name, TEEC_Context* ctx) );
* Open of the session ( TEEC_Result TEEC_OpenSession(TEEC_Context* ctx, TEEC_Session* session, const TEE_UUID* destination, uint32_t connectionMethod, const void* connectionData, TEEC_Operation* operation, uint32_t* returnOrigin) );
* Invocation of one or multiple commands ( TEEC_Result TEEC_InvokeCommand(TEEC_Session* session, uint32_t command_id, TEEC_Operation* op, uint32_t* returnOrigin) ) or allocation/deallocation of shared memory between CA and TAs (TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context* context, TEEC_SharedMemory* sharedMem)  and void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *shm) );
* Closure of the session ( void TEEC_CloseSession(TEEC_Session* session) );
* Finalization of the context ( void TEEC_FinalizeContext(TEEC_Context* ctx) ).