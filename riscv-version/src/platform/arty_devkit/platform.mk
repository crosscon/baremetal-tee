##
 # SPDX-License-Identifier: Apache-2.0
 # Copyright (c) uTango Project and Contributors. All rights reserved.
##

############################################################
# Architecture Definition
ARCH	:=	rv32imc_zicsr

############################################################
# CPU Definition
ABI		:=	ilp32

############################################################
# Exporting Flags
plat-flags = -march=$(ARCH) -mabi=$(ABI) 