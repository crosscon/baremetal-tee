## CROSSCON baremetal-TEE

Here you can find the initial version of the _CROSSCON baremetal-TEE_:  a software-based Trusted Execution Environment for bare-metal devices, developed as part of the [CROSSCON project](https://crosscon.eu/). The repository contains two different versions of TEE: an MPU version and a nonMPU version, designed to work with MPU-equipped devices and with those that lack such a hardware, respectively. For detailed description of the CROSSCON Baremetal-TEE, please refer to Section 3.5 on the deliverable [D3.1: CROSSCON Open Security Stack Documentation ‐ Draft.](https://crosscon.eu/library/deliverables) This repository is part of the deliverable D3.2: CROSSCON Open Security Stack - Initial Version.

### Overview
In order to meet the security requirements of CROSSCON, we propose two different bare-metal TEEs: the BareTEE-noMPU and the BareTEE-MPU. From a high perspective, both TEEs are a bridge between the CROSSCON Hypervisor and the bare-metal devices. Given the constrained resources of the latter, running the full CROSSCON stack is infeasible, reason for which the BareTEE strives to supply a reduced yet comprehensive set of security features to satisfy the bare-metal requirements: memory isolation, privilege separation and cross-domain intercommunication. 
Depending on the available resources on the target device, we can either deploy the BareTEE-MPU or the BareTEE-noMPU. Specifically, in the presence of an MPU we can use the former, in the absence of it the latter. As part of the CROSSCON project we provide two prototypes: we implement the MPU version for the ARMv7-M architecture and nonMPU version for the MSP430 architecture.
Although both solutions provide a similar set of security guarantees to the Applications, they do so using a slightly different isolation model.

More details on the two different versions can be found in the respective folders in this repository.

**NOTE**: This is work in progress! Don't expect things to be complete. Use at your own risk.


### Acknowledgments
The work presented in this repository is part of the [CROSSCON project](https://crosscon.eu/) that received funding from the European Union’s Horizon Europe research and innovation programme under grant agreement No 101070537.
