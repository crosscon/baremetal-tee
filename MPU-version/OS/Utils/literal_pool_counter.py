#!/usr/bin/python3

import re
import sys

#
#	Definition of raw strings that contain the pattern needed to match the corresponding instruction.
#	Convention: the name of these constant should have a leading underscore in order to make them private
#	and prevent their import when importing all names from this module.
#

# Raw string for ".word" directives (used to define a word in the literal pool)
_WORD_DIR = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<directive>[.]word)  # ".word" directive
\s+
(?P<after>.+)	# everything else after the condition
$
"""

# Raw string for ".align" directives (used to align the literal pool)
_ALIGN_DIR = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<directive>[.]align\s+[0-9]+)  # ".align" directive
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

# Raw string for ".cfi_endproc" directives (used to mark the end of a procedure)
_CFI_ENDPROC_DIR = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<directive>[.]cfi_endproc)  # ".cfi_endproc" directive
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

# Raw string for labels (used to mark the start of a procedure)
_LABEL = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<label>[a-zA-Z0-9_.]+:)  # label
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

# Raw string used to match lines in a report, extracting the filename and literal pool sizes from each line
# Format: "filename" [literal pool sizes] - e.g. "file.s" [4, 8, 12]
_REPORT_LINE = r"""
^
(?P<filename>'.*')  # filename
\s+
(?P<lps>\[.*\])	# literal pool sizes
$
"""

#
#  Compilation of raw strings into actual RE.
#  Convention: these constant have the same name as the raw string that they compile but with a leading "RE".
#
RE_WORD_DIR = re.compile(_WORD_DIR, flags=re.VERBOSE | re.IGNORECASE)
RE_ALIGN_DIR = re.compile(_ALIGN_DIR, flags=re.VERBOSE | re.IGNORECASE)
RE_CFI_ENDPROC_DIR = re.compile(_CFI_ENDPROC_DIR, flags=re.VERBOSE | re.IGNORECASE)
RE_LABEL = re.compile(_LABEL, flags=re.VERBOSE | re.IGNORECASE)
RE_REPORT_LINE = re.compile(_REPORT_LINE, flags=re.VERBOSE | re.IGNORECASE)

# List to store the sizes of the literal pools found in the input file
LITERAL_POOL_SIZES = []


def count_literal_pools(input_file):
	'''Count the sizes of the literal pools in the input file and store them in the LITERAL_POOL_SIZES list'''

	stack = []  # stack to store the lines of the input file
	with open(input_file, 'r') as f:
		for line in f:
			if RE_CFI_ENDPROC_DIR.match(line):
				# found end of procedure, start counting literal pool
				loop = True
				size = 0
				while (loop):
					entry = stack.pop()
					if RE_WORD_DIR.match(entry):
						size += 4
					elif RE_LABEL.match(entry):
						continue    # label found, skip
					elif RE_ALIGN_DIR.match(entry):
						# end of literal pool found
						loop = False
						stack.clear()
						if size > 0:
							LITERAL_POOL_SIZES.append(size)
					else:
						# no align directive found (not a literal pool)
						loop = False
						stack.clear()
						# print('Literal pool ends with entry: %s'%(entry))
						assert size == 0
			else:
				stack.append(line)

def save_report(input_file, output_file):
	'''Save the report of the literal pool sizes to the output file'''

	lps_file_map = {}

	try:
		# process past report (if exists)
		with open(output_file, 'r') as f:
			content = f.readlines()
			for line in content:
				result = RE_REPORT_LINE.match(line)
				if result:
					lps = result.group('lps')
					lps = lps[1:-1]	# remove '[' and ']'
					if lps != '':	# check for empty list
						l = lps.split(',')
						l = [int(elem) for elem in l]
						lps_file_map[result.group('filename')] = l
	except IOError:
		print('No previous report exists')

	# add current file to report
	filename = '\'' + input_file + '\''
	lps_file_map[filename] = LITERAL_POOL_SIZES

	# output new report
	with open(output_file, 'w') as f:
		pool_count = 0
		total_size = 0
		for key, item in lps_file_map.items():
			pool_count += len(item)
			for el in item:
				total_size += el
			f.write('%s %s\n'%(key, item))
		f.write('\n')
		f.write('TOTAL POOL COUNT: %s\n'%(pool_count))
		f.write('TOTAL POOL SIZE (BYTES): %s'%(total_size))



def printUsage():
	'Prints to output the usage of the script'
	print('Usage: literal_pool_counter.py inputfile.s [aggregatedOutput]')
	print('Counts literal pool and sizes')
	print('[aggregatedOutput] option allows to specify aggregated output file')

def main():
	'''Entry point of the script: parse command line arguments, 
	call the main function to count literal pools and save the report'''

	input_file = None
	output_file = None

	# parse command line arguments
	if(len(sys.argv) == 2):
		input_file = sys.argv[1]
		output_file = None
	elif(len(sys.argv) == 3):
		input_file = sys.argv[1]
		output_file = sys.argv[2]
	else:
		printUsage()
		sys.exit()

	# count literal pools and save report	
	count_literal_pools(input_file)
	
	if output_file:
		save_report(input_file, output_file)

	# print literal pool sizes to stdout
	print('%s \'%s\''%(str(LITERAL_POOL_SIZES), input_file))


if __name__== "__main__":
	main()