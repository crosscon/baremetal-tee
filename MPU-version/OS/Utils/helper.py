# Helper file with utilities for speeding up the process 
# of working with registers and conditions 

# Mapping of register names to their numbered names
# Useful for converting special register (sp, lr, pc) to their numbered names
REGISTERS_NUMBERED_NAMES = {
	'r0' : 'r0',
	'r1' : 'r1',
	'r2' : 'r2',
	'r3' : 'r3',
	'r4' : 'r4',
	'r5' : 'r5',
	'r6' : 'r6',
	'r7' : 'r7',
	'r8' : 'r8',
	'r9' : 'r9',
	'r10' : 'r10',
	'r11' : 'r11',
	'r12' : 'r12',
	'r13' : 'r13',
	'r14' : 'r14',
	'r15' : 'r15',
	'sp' : 'r13',
	'lr' : 'r14',
	'pc' : 'r15',
	# Old APCS register names
	'a1' : 'r0',
	'a2' : 'r1',
	'a3' : 'r2',
	'a4' : 'r3',
	'v1' : 'r4',
	'v2' : 'r5',
	'v3' : 'r6',
	'v4' : 'r7',
	'v5' : 'r8',
	'v6' : 'r9',
	'v7' : 'r10',
	'sb' : 'r9',
	'sl' : 'r10',
	'fp' : 'r11',
	'ip' : 'r12',
	# AAPCS register names
	'v8' : 'r11',
	'tr' : 'r9'
}

# Map to invert condition codes
CONDITION_INVERSE_MAP = {
	'eq' : 'ne',
	'ne' : 'eq',
	'cs' : 'cc',
	'cc' : 'cs',
	'mi' : 'pl',
	'pl' : 'mi',
	'vs' : 'vc',
	'vc' : 'vs',
	'hi' : 'ls',
	'ls' : 'hi',
	'ge' : 'lt',
	'lt' : 'ge',
	'gt' : 'le',
	'le' : 'gt',
	'al' : 'nv',
	'nv' : 'al'
}

#
# Produce a unique Assembly labels with the format: .MCUFORTL + incremental number
# E.g: .MCUFORTL0, .MCUFORTL1, .MCUFORTL2, ...
# 

LABEL_PREFIX = '.MCUFORTL'
label_num = 0

def get_unique_label():
	'Return a unique string to be used as assembly label'
	global label_num
	temp = LABEL_PREFIX + str(label_num)
	label_num += 1
	return temp

def _reg_key(r):
	'Return only the number of the register starting from the string of the name'
	return int(numbered_name(r)[1:])

def numbered_name(r):
	''' Convert register name to its numbered name using the mapping created
	If the register does not exist, an assertion error is raised '''

	assert r.strip().lower() in REGISTERS_NUMBERED_NAMES, 'Register specified does not exist'
	return REGISTERS_NUMBERED_NAMES[r.lower().strip()]

def is_SP(r):
	'Check if a register is the SP (stack pointer) register '
	return numbered_name(r) == numbered_name('sp')

def is_LR(r):
	'Check if a register is the LR (link register) register'
	return numbered_name(r) == numbered_name('lr')

def is_PC(r):
	'Check if a register is the PC (program counter) register'
	return numbered_name(r) == numbered_name('pc')

def are_equal(rx, ry):
	'Check if two registers name correspond to the same register'
	return numbered_name(rx) == numbered_name(ry)

def is_reg_in_array(r, arr):
	'Check if a register is in an array of registers'
	arr = [numbered_name(el) for el in arr]
	return numbered_name(r) in arr

def sort_reg_array(arr):
	'Sort an array of registers by their number'
	return sorted(arr, key=_reg_key)

def string_to_reg_array(reg_s):
	''' Convert a string of registers to an array of registers
	The string can contain register ranges and single registers
    E.g: "r0-r3, r5, r7" will be converted to ["r0", "r1", "r2", "r3", "r5", "r7"]'''
	
	r_set = set()
	r_list = reg_s.split(',')
	for r in r_list:
		if '-' in r:	# register range conversion
			r_range = r.split('-')
			assert len(r_range) == 2, 'Invalid register range specified'
			low = numbered_name(r_range[0])
			high = numbered_name(r_range[1])
			low = int(low[1:])	# convert low register to integer boundry
			high = int(high[1:])	# convert high register to integer boundry
			assert low <= high, 'Invalid register range specified'
			for num in range(low, high+1):
				r_set.add('r%s'%(num))
		else:	# single register conversion
			r_set.add(numbered_name(r))
	numbered_list = []
	for r in r_set:
		numbered_list.append(numbered_name(r))
	return sort_reg_array(numbered_list)	

def is_array_unique(arr):
	'Check if an array of registers contains only unique registers (no duplicates)'
	arr = [numbered_name(el) for el in arr]
	s = set(arr)
	return len(s) == len(arr)

def immToInt(imm):
	'Converts an immediate value (string) to an int regardless if it is base 16 (0xIMM) or base 10 (IMM)'
	if imm[0] == '#':
		imm = imm[1:]
	return int(imm, 0)	

def get_inverted_condition(cond):
	'Return the inverted condition code using the mapping created before'
	return CONDITION_INVERSE_MAP[cond.lower().strip()]