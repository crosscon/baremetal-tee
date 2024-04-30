# pyOCD is a Python package used for programming and debugging Arm Cortex-M microcontrollers 
# ConnectHelper class provides helper functions to connect to a target board.
from pyocd.core.helpers import ConnectHelper

# Definition of the padding length for the UUIDs
PAD_TO_LEN = 8

# Base addresses for the UUIDs of the different boards
STM32WB55RG_UUID_BASE_ADDRESS = 0x1FFF7590
STM32L475VG_UUID_BASE_ADDRESS = 0x1FFF7590

# Dictionary with the options for the connection to the board
options_dict = {"target_override": "cortex_m"}


def get_uuid():
    '''Connects to the board and reads the UUID from the memory'''

    print("Attempting connection to board...")
    with ConnectHelper.session_with_chosen_probe(options=options_dict) as session:
        print("Connection succesfull!")
        board = session.board
        target = board.target
        flash = target.memory_map.get_boot_memory()

        # Halt possibly running device
        target.halt()

        # Read UUID for STM32WB55RG
        part1 = target.read32(STM32WB55RG_UUID_BASE_ADDRESS)
        part2 = target.read32(STM32WB55RG_UUID_BASE_ADDRESS + 4)
        part3 = target.read32(STM32WB55RG_UUID_BASE_ADDRESS + 8)

        # Reset and halt
        target.reset_and_halt()

        # Combine the various parts into a single hex string
        uid_hex_string = "{0:0{1}X}".format(part1,PAD_TO_LEN)
        uid_hex_string += "{0:0{1}X}".format(part2,PAD_TO_LEN)
        uid_hex_string += "{0:0{1}X}".format(part3,PAD_TO_LEN)

        return uid_hex_string

def main():
    '''Entry point of the script to read the UUID from the currently used board''' 

    print("UUID reader for STM32WB55RG and STM32L475VG")
    uuid = get_uuid()
    print("Board UUID:")
    print(uuid)

if __name__== "__main__":
	main()