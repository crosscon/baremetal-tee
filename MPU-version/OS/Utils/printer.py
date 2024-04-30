class Printer:
	"""Printer class used to print text with preceding indentation."""

	def __init__(self, tabs):
		if tabs:
				self.tabs = tabs
		else:
			self.tabs = ''
			
	def pprint(self, text):
		print('%s%s'%(self.tabs, text))