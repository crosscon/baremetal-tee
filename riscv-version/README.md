# RISC-V CROSSCON Baremetal TEE

The BareMetal-TEE for RISC-V is a solution for memory isolation and supervised execution aiming at increasing the security of embedded devices in a way that is mostly transparent to application developers. The architecture is fully compliant with the Global Platform TEE Client API specification and with a subset of the TEE Core API.

## Prerequisites

|	TOOL				  |	Version   |
|-------------------------|-----------|
| riscv32-unknown-elf-gcc |	13.3.0	  |
| riscv32-unknown-elf-gdb |	13.3	  |
| 	GNU Make			  |	4.3		  |
| 	Vivado				  | v2023.2   |
	
Download https://buildbot.embecosm.com/job/riscv32-gcc-ubuntu2404-release/lastSuccessfulBuild/artifact/riscv32-embecosm-ubuntu2404-gcc13.3.0.tar.gz for a pre-built gcc toolchain

## Setup

#### Setup Freedom SDK
- Clone repository https://github.com/sifive/freedom.git
		
- Edit file "src/main/scala/subsystem/Configs.scala" and in class "With1TinyCore" add "useUser = true," to the core parameters

```scala
class With1TinyCore extends Config((site, here, up) => {
	case XLen => 32
	case RocketTilesKey => List(RocketTileParams(
		core = RocketCoreParams(
	useVM = false,
==>	useUser = true,
	fpu = None,
	nBreakpoints = 10,
	mulDiv = Some(MulDivParams(mulUnroll = 8))),
```

- Edit file "/bootrom/xip/Makefile" and change C_FLAGS -march to rv32imac_zicsr
	
- Follow the repo readme to install the dependencies

- Run the following commands to make the bitstream:
```bash
$ make -f Makefile.e300artydevkit verilog
$ make -f Makefile.e300artydevkit mcs
```
			
- In vivado, after pluging in the arty and the olimex debugger, open hardware manager and connect to the board.
	
- On the left side of the default window, right click on xc7a35t nad select add configuration memory device

- Select part name mt25ql128-spi-x1_X2_X4 and press ok, press ok again when a prompt to program appears

- On the next prompt select the configuration file /builds/e300artydevkit/obj/E300ArtyDevKitFPGAChip.mcs and press ok

- Once programming finishes press the burron PROG in the arty board
				
						
#### Setup Freedom E SDK
- Clone repository https://github.com/sifive/freedom-e-sdk.git
			
- Edit RISCV_ARCH to rv32imac_zicsr in /bsp/freedom-e310-arty/setings.mk
		
		
#### Sanity Check
- With the board and debugger connected, open a uart terminal with BAUDRATE 57600

- In the Freedom E SDK dir run:
```bash
$ make PROGRAM=sifive-welcome TARGET=freedom-e310-arty upload
```
A Sifive HelloWorld message should be printed in the terminal
				

## Build & Compile

To build the worlds run:
``` bash
$ make worlds
```
To build the binaries run:
``` bash
$ make
```
	
## Uploading to the board	
		
- To upload to the arty, in the Freedom E SDK directory, run:

```bash
$ scripts/upload --elf (PATH_TO_REPO)/riscv-version/bin/arty_devkit/riscv-version.elf --openocd openocd --gdb riscv32-unknown-elf-gdb --openocd-config bsp/freedom-e310-arty/openocd.cfg
```
	
## Building your own TA/CA

An example of a CA can be seen inside worlds/world1/src/main.c, where a keylogger application uses the GP API to call up a TA to provide sensitive data depending on a specific password.

The complementary TA can be found in world2/src/ta/keylogger_ta.c, where the GP Compliant entry_points can be seen.

Therefore, any applications that follow the same structure as the one in the example will work (provided the necessary entrypoints are implemented in the new application).
