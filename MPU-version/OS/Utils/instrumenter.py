#!/usr/bin/python3

import sys
import re
import fileinput
import instructions_re as asm
import virtualizer as v
import replacer as r
import logging

# 
# 	Instrumenter for ARM assembly code.
# 	Core script of the virtualization process that takes care of:
# 	- handling IT blocks (discover if IT block contains virtualization targets and replace it with branches)
# 	- virtualizing instructions
#   - ...
#


# set to True to enable debug mode
DEBUG = True

# map of instructions to virtualize, with their corresponding regular expression and virtualization function 
# The virtual functions are defined in the virtualizer module
virtualize_option_map = {
	'cps' : (asm.RE_CPS, v.cps),
	'mrs' : (asm.RE_MRS, v.mrs),
	'msr' : (asm.RE_MSR, v.msr)
}

def it_handler(input_file, virtualize_targets):
	'''
	When an IT block covers system instructions that must be virtualized,
	the whole IT block is replaced with a series of branches that execute conditionally.
	'''
	with fileinput.FileInput(input_file, inplace=True, backup='.bak') as file:  # open the file with a inplace edit
		it_mode = False
		contains_v_targets = False
		remaining_it = 0
		buffer = []
		for line in file:
			if not it_mode:	# single-line matching mode
				match = r.RE_IT.match(line)
				if match:
					it_mode = True
					remaining_it = 1
					x = match.group('x')
					y = match.group('y')
					z = match.group('z')
					if x:
						remaining_it += 1
					if y:
						remaining_it += 1
					if z:
						remaining_it += 1
					buffer.append(line)
				else:
					sys.stdout.write(line)	# print line as-is
			else:
				buffer.append(line)
				if r.RE_IT_BLOCK_INST.match(line):	# directives are not counted as instruction inside IT block
					remaining_it -= 1
				# check if appened line should be virtualized
				for option, (regex, v_func) in virtualize_option_map.items():
					if (option in virtualize_targets) or ('all' in virtualize_targets):
						match = regex.match(line)
						if (match):
							contains_v_targets = True
				if remaining_it == 0:	# end of IT block
					if contains_v_targets:
						r.it(buffer)
					else:
						for l in buffer:
							sys.stdout.write(l)	# print line as-is
					it_mode = False
					contains_v_targets = False					
					buffer = []

def virtualize(input_file, virtualize_targets):
	'''
	Match the instructions to virtualize and call the corresponding function
	(defined in the virtualizer) to replace them.
	'''
	with fileinput.FileInput(input_file, inplace=True, backup='.bak') as file:
		for line in file:
			if DEBUG:
				# when a single assmebly line maches more than one RE stop, RE are badly defined
				if asm.multi_match(line):
					sys.exit(1)
			
			match_found = False
			
			for option, (regex, v_func) in virtualize_option_map.items():
				if (option in virtualize_targets) or ('all' in virtualize_targets):
					match = regex.match(line)
					if (match):
						# log the line number where the match was found and the option that was matched
						logging.info('%s fount at: %s'%(option, file.lineno()))
						v_func(match)
						match_found = True
						break

			if not match_found:
				sys.stdout.write(line)	# print line as-is

def printUsage():
	''' 
	Prints to output how the script should be used
	'''
	print('Usage: instrumenter.py --virtualize=cps,mrs,msr inputfile.s')
	print('--virtualize={targets}:')
	print('\tall')
	for option in virtualize_option_map:
		print('\t%s'%option)

def main():
	'''
	Main function of the whole instrumenter pipeline.
	
	Handles the command line arguments, in particular the input files,
	and calls the IT handler and the virtualizer to instrument the code.
	'''
	logging.basicConfig(level=logging.INFO)

	if(len(sys.argv) < 2):
		printUsage()
		sys.exit()
	
	input_file = sys.argv[-1]

	options = sys.argv[1:-1]

	virtualize_targets = []

	# parse options
	for o in options:
		if o.strip().lower().startswith('--virtualize'):
			split = o.strip().lower().split('=')
			for v in split[1].split(','):
				if v.strip() not in virtualize_targets:
					virtualize_targets.append(v.strip())
			continue

		else:
			print('Unknown option: %s'%o)
			printUsage()
			sys.exit()

	# first pass, handle IT instructions that contain virtualization targets
	it_handler(input_file, virtualize_targets)
	# second pass, virtualize target instructions
	virtualize(input_file, virtualize_targets)

if __name__== "__main__":
	main()