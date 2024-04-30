import helper
from printer import Printer

#
# Functions used to replace the original instructions with virtualized ones:
# the virtualization consists in adding a SVC call before the original instruction
# to execute the system instruction in privileged mode under the control of the microvisor
#
# SVC calls are used to trigger exceptions and make the microvisor handle the system instructions
#

def cps(match):
	""" Adds SVC call before CPS instruction.
	This allows the system instruction to be executed in privileged mode
	under the control of the microvisor.

	match represent the regular expression matching object.
	"""
	tabs = match.group('tabs')
	mnemonic = match.group('mnemonic')
	effect = match.group('effect')
	q = match.group('q')
	iflags = match.group('iflags')
	comment = match.group('comment')

	prt = Printer(tabs)

	if not comment:
		comment = ''

	# print leading SVC instruction
	prt.pprint('svc 0')
	# print original CPS instruction
	prt.pprint('%s%s %s %s'%(mnemonic, effect, iflags, comment))


def mrs(match):
	""" Adds SVC call before MRS instruction.
	This allows the system instruction to be executed in privileged mode
	under the control of the microvisor.

	match represent the regular expression matching object.
	"""
	tabs = match.group('tabs')
	mnemonic = match.group('mnemonic')
	c = match.group('c')
	q = match.group('q')
	rd = match.group('rd')
	spec_reg = match.group('spec_reg')
	comment = match.group('comment')

	prt = Printer(tabs)

	if not c:
		c = ''
	if not comment:
		comment = ''

	# print leading SVC instruction
	prt.pprint('svc 0')
	# print original MRS instruction
	prt.pprint('%s%s %s, %s %s'%(mnemonic, c, rd, spec_reg, comment))

def msr(match):
	""" Adds SVC call before MSR instruction.
	This allows the system instruction to be executed in privileged mode
	under the control of the microvisor.

	match represent the regular expression matching object.
	"""
	tabs = match.group('tabs')
	mnemonic = match.group('mnemonic')
	c = match.group('c')
	q = match.group('q')
	spec_reg = match.group('spec_reg')
	rn = match.group('rn')
	comment = match.group('comment')

	prt = Printer(tabs)

	if not c:
		c = ''
	if not comment:
		comment = ''

	# print leading SVC instruction
	prt.pprint('svc 0')
	# print original MSR instruction
	prt.pprint('%s%s %s, %s %s'%(mnemonic, c, spec_reg, rn, comment))