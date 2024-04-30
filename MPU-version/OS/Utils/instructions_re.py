import re

# array containing all compiled RE
_RE_ARRAY = []

def multi_match(text):
	'''Returns True if 'text' maches more than one RE.'''
	count = 0
	for re in _RE_ARRAY:
		if(re.match(text)):
			count += 1
	return (count > 1)
		

#
#	Definition of raw strings that contain the pattern needed to match the corresponding instruction.
#	Convention: the name of these constant should have a leading underscore in order to make them private
#	and prevent their import when importing all names from this module.
#	Attention: regular expression should be written such that at any time only one of them can match with a single
#	line of code, otherwise the order in which they are evaluated would impact on the result.
#


#  Raw string for CPS (Change Processor State) instruction
#  Format of instruction (from ARM Architecture Reference Manual): CPSeffect iflags
_CPS = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<mnemonic>cps)	# CPS
(?P<effect>ie|id)	# effect (IE set bits to 0, ID set bits to 1)
(?P<q>[.]n|[.]w)?	# qualifier (narrow or wide encoding), optional
\s+
(?P<iflags>i?f?)	# which bit are affected: i=PRIMASK, f=FAULTMASK
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

#  Raw string for MRS (Move to Register from Special register) instruction
#  Format of instruction: MRS{cond} Rd, spec_reg
_MRS = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<mnemonic>mrs)	# MRS
(?P<c>eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?	# condition code
(?P<q>[.]n|[.]w)?	# qualifier (narrow or wide encoding), optional
\s+
(?P<rd>r[0-9]{1,2}|a[1-4]|v[1-8]|sb|sl|fp|ip|tr|sp|lr|pc)	# destination register
\s*
,
\s*
(?P<spec_reg>[^@]*)	# targetted special register
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

#  Raw string for MSR (Move to Special register from Register) instruction
#  Format of instruction: MSR{cond} spec_reg, Rn
_MSR = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<mnemonic>msr)	# MSR
(?P<c>eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?	# condition code
(?P<q>[.]n|[.]w)?	# qualifier (narrow or wide encoding), optional
\s+
(?P<spec_reg>[^,]*)	# targetted special register
\s*
,
\s*
(?P<rn>r[0-9]{1,2}|a[1-4]|v[1-8]|sb|sl|fp|ip|tr|sp|lr|pc)	# destination register
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""


#
#	Compilation of raw strings into actual RE.
#   RE are appended to the _RE_ARRAY list.
#	Convention: these constant have the same name as the raw string that they compile but with a leading "RE".
#

RE_CPS = re.compile(_CPS, flags=re.VERBOSE | re.IGNORECASE)
_RE_ARRAY.append(RE_CPS)

RE_MRS = re.compile(_MRS, flags=re.VERBOSE | re.IGNORECASE)
_RE_ARRAY.append(RE_MRS)

RE_MSR = re.compile(_MSR, flags=re.VERBOSE | re.IGNORECASE)
_RE_ARRAY.append(RE_MSR)