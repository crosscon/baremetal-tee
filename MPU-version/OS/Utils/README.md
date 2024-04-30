# Utils folder content

Contains the instrumentation toolchain, used during the compilation process of fortified applications. A brief description of the purpose of each file included follows.
* `helper.py`: helper functions that simplify dealing with ARM registers and conditions.
* `instructions_re.py`: regular expressions used to match system instructions, and in particular CPS (Change Processor State), MRS (Move to Register from Special register) and MSR (Move to Special register from Register). 
* `instrumenter.py`: entry point of the pipeline. Handles input files, calls functions that deal with the IT instructions (If-Then) and virtualization process used to instrument the code.
* `literal_pool_counter.py`: using regular expressions for directives (like .word, .align), labels and report lines, counts the literal pools in an input file and saves the results in a report file.  
* `printer.py`: helper class that prints texts with the provided indentation.
* `regex_tester.py`: helper function which tests the resulting match of a provided regular expression.
* `replacer.py`: detects IT instructions and blocks using regular expressions. Converts them into a series of branching instructions.
* `uuid_dumper.py`: extract the immutable UUID from the board, that will host the MCU Fortifier, for fingerprinting purposes. 
* `virtualizer.py`: virtualizes the system instructions, namely CPS, MRS and MSR, by adding an SVC call and executing them in privileged mode under the control of the microvisor.