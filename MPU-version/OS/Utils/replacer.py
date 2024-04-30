import helper
import re
import sys
from printer import Printer

#
#	Definition of raw strings that contain the pattern needed to match the corresponding instruction.
#	Convention: the name of these constant should have a leading underscore in order to make them private
#	and prevent their import when importing all names from this module.
#

#  Raw string that contains the pattern to detect an IT (If-Then) instruction
#  Format of instruction (from ARM docs): IT{x{y{z}}} cond
_IT = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<mnemonic>it)	# IT
(?P<x>t|e)?	# then-else for 2nd instruction
(?P<y>t|e)?	# then-else for 3d instruction
(?P<z>t|e)?	# then-else for 4th instruction
(?P<q>[.]n|[.]w)?	# qualifier (narrow or wide encoding), optional
\s+
(?P<firstcond>
eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al
)	# condition for first instruction
\s*
(?P<comment>@.*)?	# optional assembly comment
$
"""

#  Raw string for IT blocks (instructions that can be executed as part of an IT block)
_IT_BLOCK_INST = r"""
^
(?P<tabs>\s*)	# tabulation
(?P<mnemonic>	# mnemonic codes for instructions
adc|add|addw|adr|and|asr|b|bfc|bfi|bic|bl|blx|bx|cbnz|cbz|cdp|cdp2|clrex|clz|cmn|cmp|
cpy|csdb|dbg|dmb|dsb|eor|isb|ldc|ldc2|ldcl|ldc2l|ldm|ldmia|ldmfd|ldmdb|ldmea|ldr|
ldrb|ldrbt|ldrd|ldrex|ldrexb|ldrexh|ldrh|ldrht|ldrsb|ldrsbt|ldrsh|ldrsht|ldrt|lsl|
lsr|mcr|mcr2|mcrr|mcrr2|mla|mls|mov|movw|movt|mrc|mrc2|mrrc|mrrc2|mrs|msr|mul|mvn|
neg|nop|orn|orr|pkhbt|pkhtb|pld|pli|pop|push|qadd|qadd16|qadd8|qasx|qdadd|qdsub|
qsax|qsub|qsub16|qsub8|rbit|rev|rev16|revsh|ror|rrx|rsb|sadd16|sadd8|sasx|sbc|sbfx|
sdiv|sel|sev|shadd16|shadd8|shasx|shsax|shsub16|shsub8|smlabb|smlabt|smlatb|smlatt|
smlad|smladx|smlal|smlalbb|smlalbt|smlaltb|smlaltt|smlald|smlaldx|smlawb|smlawt|
smlsd|smlsdx|smlsld|smlsldx|smmla|smmlar|smmls|smmlsr|smmul|smmulr|smuad|smuadx|
smulbb|smulbt|smultb|smultt|smull|smulwb|smulwt|smusd|smusdx|ssat|ssat16|ssax|
ssub16|ssub8|stc|stc2|stc2l|stcl|stm|stmia|stmea|stmdb|stmfd|str|strb|strbt|strd|
strex|strexb|strexh|strh|strht|strt|sub|subw|svc|sxtab|sxtab16|sxtah|sxtb|sxtb16|
sxth|tbb|tbh|teq|teq|tst|tst|uadd16|uadd8|uasx|ubfx|udf|udiv|uhadd16|uhadd8|uhasx|
uhsax|uhsub16|uhsub8|umaal|umlal|umull|uqadd16|uqadd8|uqasx|uqsax|uqsub16|uqsub8|
usad8|usada8|usat|usat16|usax|usub16|usub8|uxtab|uxtab16|uxtah|uxtb|uxtb16|uxth|
vabs|add|avmp|vcmp|vcmpe|vcvt|vcvtr|vcvtb|vcvtt|vdiv|vfma|vfms|vfnma|vfnms|vldmia|
vldmdb|vldr|vmla|vmls|vmov|vmrs|vmsr|vneg|vnmla|vnmls|vnmul|vpop|vpush|vrintx|
vrintz|vrintr|vsel|vsqrt|vstmia|vstmdb|vstr|vsub|wfe|wfi|yield
)
(?P<s>
s
)?
(?P<c>
eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al
)
(?P<after>.*)	# everything else after the condition
$
"""

#
#	Compilation of raw strings into actual RE.
#	Convention: these constant have the same name as the raw string that they compile but with a leading "RE".
#
RE_IT = re.compile(_IT, flags=re.VERBOSE | re.IGNORECASE)
RE_IT_BLOCK_INST = re.compile(_IT_BLOCK_INST, flags=re.VERBOSE | re.IGNORECASE)


def it(lines):
	""" Replaces the IT instruction with branch instructions.

	The single 'IT cond' instruction is converted into a series of 'B not(cond)' instructions that branch
	to the end of the replacement.  This is done for the instructions targeted by virtualization.

	E.g.: ['IT EQ', 'MOV r0, r1', 'ADD r2, r3'] >>> ['BNE end_of_it_block', 'MOV r0, r1', 'ADD r2, r3', 'end_of_it_block:']
    """

	match = RE_IT.match(lines[0])	# match original IT instruction
	it_block = lines[1:]	# extract IT block instructions

	# store matching groups of the RE
	tabs = match.group('tabs')
	mnemonic = match.group('mnemonic')
	x = match.group('x')
	y = match.group('y')
	z = match.group('z')
	firstcond = match.group('firstcond')
	comment = match.group('comment')

	# create a vector of conditions based on the structure of the IT instruction
	it_cond = firstcond.lower().strip()
	skip_cond_vector = []
	skip_cond_vector.append(helper.get_inverted_condition(it_cond))
	if x:
		if x.lower().strip() == 't': # in case of 'then' condition, invert the condition
			skip_cond_vector.append(helper.get_inverted_condition(it_cond))
		else: # in case of 'else' condition, use the original condition
			skip_cond_vector.append(it_cond)
	if y:
		if y.lower().strip() == 't':
			skip_cond_vector.append(helper.get_inverted_condition(it_cond))
		else:
			skip_cond_vector.append(it_cond)
	if z:
		if z.lower().strip() == 't':
			skip_cond_vector.append(helper.get_inverted_condition(it_cond))
		else:
			skip_cond_vector.append(it_cond)
	
	# use the Printer class to print the instructions with the correct tabulation
	prt = Printer(tabs)

	if comment:
		prt.pprint(comment)
	
	# raises an asertionError if 'NV' (never) condition code is used in the IT block.
	for s in skip_cond_vector:
		assert s != 'al', 'NV (never) condition code used in IT block'
	
	# iterate through the IT block and modify the instructions
	c_index = 0
	for inst in it_block:
		i = RE_IT_BLOCK_INST.match(inst)
		if i:
			label_skip = helper.get_unique_label()
			if s != 'nv':	# if instruction is never skipped branching is not necessary
				prt.pprint('b%s %s'%(skip_cond_vector[c_index], label_skip))
			prt.pprint('%s%s'%(i.group('mnemonic'), i.group('after')))	# print original instruction but without flag update and condition code
			prt.pprint('%s:'%(label_skip))	# label to skip instruction execution
			c_index += 1	# move condition index to next condition
		else:
			sys.stdout.write(inst)	# print directive as-is