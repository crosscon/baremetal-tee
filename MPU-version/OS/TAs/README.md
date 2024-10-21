# Trusted Applications

This folder includes some Trusted Applications used by the Client Application examples. In particular, the trusted applications included are the following.

## Bitcoin Wallet TA

Trsuted Application used to verify the support of Global Platform API. It was built targeting another platform but, in combination with the Bitcoin Wallet CA, is able able to run without modification on top of the Baremetal TEE. 

## AES TA

Trusted Application to test the support of key generation, encryption and decryption with AES using the Core API. It also verifies the correct support for SHA256 digest calculation. 

## Secure Storage TA

TA to test the support of permanent storage of TAs offered using Core API.

## TA1 and T2 

Sample (almost empty) Trusted Application used to test various functionality of the system (support of multiple TA) and security properties. 