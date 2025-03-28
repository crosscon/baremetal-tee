# Examples

**NOTE**: the *sample_files* folder contains the files needed to support Global Platform API and to correctly compile a Client Application to run on top of the Baremetal TEE with MPU, but it does not include a complete application example. 

The other folders include some examples of client applications and the tests that were run in order to verify support and compatibility with the Global Platform API (both Core and Client) and to demonstrate the memory isolation of the various components of the system. The included applications are the following.

## Bitcoin Wallet

Client Application used to verify the support of Global Platform API. It was built targeting another platform but, in combination with the Bitcoin Wallet TA, is able able to run without modification on top of the Baremetal TEE. 

## Crypto AES

Client Application to test the support of key generation, encryption and decryption with AES inside a Trusted Application. It also verifies the correct support for SHA256 digest calculation. Works in combination with the *aes-ta*.

## Secure Storage

Client Application to test the support of permanent storage inside the trusted application: it tests the creation, modification, reading and deleting of persistent objects. Works in combination with the *secure-storage* TA. 

## Double Trusted Application

A simple client application that demonstrates how the system can support and invoke commands of up to two TAs at the same time. 

## Memory Violation

Client Application that is used to verify different security properties of the system. Different tests are included (it is recommended to uncomment a single test at a time), namely:
* Access from a CA to the FLASH/RAM of both the TEE and TAs;
* Access from a TA to the flash/RAM of the TEE and other TA;
* Gain of privileges from a TA and from a CA;
* Execution of a privileged function from a CA.

Some of these tests require the deployment of the *TA1* TA on the TEE. 

**NOTE**: each client application example developed includes a folder *Tests* with logs of execution and with the Makefile and BOOTLOADER.ld file used to compile the TEE. This simplifies the execution of the tests as these files already include the correct TAs needed by the CA. 

# Performance evaluation 

- Microbenchmarks
    - Domain switch time
	    - CA to TA: 21.848 / 21.824 μs
	    - TA to CA: 11.192 / 11.16 μs
- TA-based APIs
    - Opening a session with the TA: 28.8 μs / 28.76 μs
	- Invoking TA functions by sending commands: 40.472 μs / 40.432 μs
	- Closing the session once the TA operation is completed: 24.576 μs / 24.536 μs

- Keylogger (debug CA, no TA): 
    - 2 domains: 7.182064 ms
    - 1 domain: 7.18008 ms

- Bitcoin wallet (debug CA, no TA): 
    - 2 domains: 1.152729592 s
    - 1 domain:  0.986071904 s





