#!/usr/bin/python3

import re
import instructions_re as asm

# 
# Code used to test the regular expression defined in the instructions_re module (namely CPS, MRS, MSR)
#

# insert here regular expression to test (must be already compiled)
test_re = asm.RE_MSR

def main():
	'''Given an input string, test the regular expression,
	print the math and highlight groups and dictionary of the match'''
	
	while True:
		string = input('Insert string: ')

		temp = test_re.match(string)
		print('Match: ' + str(temp != None))
		if(temp):
			print('Grouping:')
			print(temp.groups())
			print('Dictionary:')
			print(temp.groupdict())

if __name__== "__main__":
	main()