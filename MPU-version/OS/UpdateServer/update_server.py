#!/usr/bin/python3

import socket
import struct
import hashlib
import os
import threading
from sec_comm import SecComm


SERVER_IP = ''	# leave empty for server reachable by any interface
SERVER_PORT = 4433
NONCE_LEN = 12
AUTH_TAG_LEN = 16

UPDATE_PACKET_SIZE = 256

uuid_key_map = {
	bytes.fromhex('2d003b000450564656313220'): b'this is the 32 bytes shared key!'
}

# Stores association between UUIDs and (path to) firmware (fortified applications)
uuid_firmware_map = {
	bytes.fromhex('2d003b000450564656313220') : 'UpdateServer/binaries/blink_l475_green.bin'
	#bytes.fromhex('2d003b000450564656313220') : 'UpdateServer/binaries/blink_l475_network.bin'
}

# Association between boards and reflasher utility + microvisor update to install
uuid_microvisor_map = {
	#bytes.fromhex('2d003b000450564656313220') : ['UpdateServer/binaries/MCU-Reflasher.bin', 'UpdateServer/binaries/buffer_overflow_l475_standard.bin']
}


message_string_to_id = {
	'OTA_FIRMWARE_REQUEST' : 0,
	'OTA_FIRMWARE_REPLY' : 1,
	'OTA_FIRMWARE_SIZE_REQUEST' : 2,
	'OTA_FIRMWARE_SIZE_REPLY' : 3,
	'OTA_UPDATE_PACKET' : 4,
	'OTA_UPDATE_NEXT' : 5,
	'OTA_ERROR_REPORT' : 6,
	'OTA_ERROR_REPLY' : 7,
	'OTA_MICROVISOR_REQUEST' : 8,
	'OTA_MICROVISOR_REPLY' : 9,
	'OTA_MICROVISOR_SIZE_REQUEST' : 10,
	'OTA_MICROVISOR_SIZE_REPLY' : 11,
	'OTA_REFLASHER_SIZE_REQUEST' : 12,
	'OTA_REFLASHER_SIZE_REPLY' : 13,
}

error_id_to_string = {
	0xffffffff : 'ERROR_NONE',
	1 : 'ERROR_INIT',
	2 : 'ERROR_EXCEPTION_SIM_PRIO',
	3 : 'ERROR_PPB_ACCESS',
	4 : 'ERROR_REGISTER_SIM',
	5 : 'ERROR_MPU_VIOLATION',
	6 : 'ERROR_INVALID_LICENSE',
	7 : 'ERROR_LICENSE_LIMIT_EXCEEDED',
}

message_id_to_string = {}	# Automatically filled

# Stores association between address and board UUIDs
# Filled at runtime, after connection with board established
addr_uuid_map = {}


def get_file_sha256sum(path):
	with open(path,"rb") as f:
		bytes = f.read() # read entire file as bytes
		hex_hash = hashlib.sha256(bytes).hexdigest()
	return bytes.fromhex(hex_hash)

def handle_unexpected_message(conn, addr, msg_id):
	print('[{}] In Unexpected message id received: {}'.format(addr, msg_id))
	return False

def handle_firmware_request(conn, addr, msg_id):
	print('[{}] In {}'.format(addr, message_id_to_string[msg_id]))
	uuid = addr_uuid_map[addr]

	# Read board current firmware SHA256
	hash = conn.recv(32)
	if(hash == b''):
		return False

	# Check firmware update availability
	update_available = False
	if(uuid in uuid_firmware_map):
		if(hash != get_file_sha256sum(uuid_firmware_map[uuid])):
			update_available = True

	if not update_available:
		conn.send(struct.pack('<I', message_string_to_id['OTA_FIRMWARE_REPLY']))
		conn.send(struct.pack('<I', 0))	# send False (no firmware update avaiable)
		print('[{}] Out {}: 0'.format(addr, 'OTA_FIRMWARE_REPLY'))
		return True
	
	# Update is available
	conn.send(struct.pack('<I', message_string_to_id['OTA_FIRMWARE_REPLY']))
	conn.send(struct.pack('<I', 1))	# send True (firmware update avaiable)
	print('[{}] Out {}: 1'.format(addr, 'OTA_FIRMWARE_REPLY'))

	# Read expected firmware size request
	req = conn.recv(4)
	if(req == b''):
		return False
	req = struct.unpack('<I', req)[0]
	if(req != message_string_to_id['OTA_FIRMWARE_SIZE_REQUEST']):
		return False
	print('[{}] In {}'.format(addr, message_id_to_string[req]))

	# Prepare and send firmware size reply
	firmware_path = uuid_firmware_map[uuid]
	firmware_size = os.path.getsize(firmware_path)
	conn.send(struct.pack('<I', message_string_to_id['OTA_FIRMWARE_SIZE_REPLY']))
	conn.send(struct.pack('<I', firmware_size))
	print('[{}] Out {}: {}'.format(addr, 'OTA_FIRMWARE_SIZE_REPLY', firmware_size))

	# Begin firmware transfer
	print('[{}] Begin firmware transfer'.format(addr))
	remaining = firmware_size
	with open(firmware_path,"rb") as f:
		while remaining > 0:
			# Read packet request
			req = conn.recv(4)
			if(req == b''):
				return False
			req = struct.unpack('<I', req)[0]
			if(req != message_string_to_id['OTA_UPDATE_NEXT']):
				return False
			print('[{}] In {}'.format(addr, message_id_to_string[req]))

			# Calculate data amount to read
			read_size = UPDATE_PACKET_SIZE
			if remaining < UPDATE_PACKET_SIZE:
				read_size = remaining
			data = f.read(read_size)

			# Send update packet with length of data and data
			conn.send(struct.pack('<I', message_string_to_id['OTA_UPDATE_PACKET']))
			conn.send(struct.pack('<I', len(data)))
			conn.send(data)
			remaining -= read_size
			print('[{}] Out {}: {} bytes'.format(addr, 'OTA_UPDATE_PACKET', read_size))
			print('[{}] Remaining {} bytes'.format(addr, remaining))

	print('[{}] Completed firmware transfer'.format(addr))

	# Read expected firmware update request
	req = conn.recv(4)
	if(req == b''):
		return False
	req = struct.unpack('<I', req)[0]
	if(req != message_string_to_id['OTA_FIRMWARE_REQUEST']):
		return False

	# Read new firmware SHA256
	hash = conn.recv(32)
	if(hash == b''):
		return False

	# Check firmware update availability
	update_available = False
	if(uuid in uuid_firmware_map):
		if(hash != get_file_sha256sum(uuid_firmware_map[uuid])):
			update_available = True

	if not update_available:
		conn.send(struct.pack('<I', message_string_to_id['OTA_FIRMWARE_REPLY']))
		conn.send(struct.pack('<I', 0))	# send False (no firmware update avaiable)
		print('[{}] Update completed succesfully!'.format(addr))
		return True
	else:
		conn.send(struct.pack('<I', message_string_to_id['OTA_FIRMWARE_REPLY']))
		conn.send(struct.pack('<I', 1))	# send True (firmware update avaiable)
		print('[{}] Update failed!'.format(addr))
	return True	

def handle_error_report(conn, addr, msg_id):
	# read error id
	error_id = conn.recv(4)
	if(error_id == b''):
			return False
	error_id = struct.unpack('<I', error_id)[0]
	# parse error and read error data
	if(error_id in error_id_to_string):
		print('[{}] In	OTA_ERROR_REPORT error={}'.format(addr, error_id_to_string.get(error_id)))
		if(error_id == 5):	# MPU violation error
			cfsr = conn.recv(4)
			if(cfsr == b''):
				return False
			mmfar = conn.recv(4)
			if(mmfar == b''):
				return False
			bfar = conn.recv(4)
			if(bfar == b''):
				return False
			sp = conn.recv(4)
			if(sp == b''):
				return False
			lr = conn.recv(4)
			if(lr == b''):
				return False
			pc = conn.recv(4)
			if(pc == b''):
				return False
			cfsr = struct.unpack('<I', cfsr)[0]
			mmfar = struct.unpack('<I', mmfar)[0]
			bfar = struct.unpack('<I', bfar)[0]
			sp = struct.unpack('<I', sp)[0]
			lr = struct.unpack('<I', lr)[0]
			pc = struct.unpack('<I', pc)[0]
			print(		'CFSR: {}'.format(hex(cfsr)))
			print(		'MMFAR: {}'.format(hex(mmfar)))
			print(		'BFAR: {}'.format(hex(bfar)))
			print(		'SP: {}'.format(hex(sp)))
			print(		'LR: {}'.format(hex(lr)))
			print(		'PC: {}'.format(hex(pc)))
	if(error_id == 6):	# Invalid License
		print('		License not valid')
	if(error_id == 7):	# License exceeded number of MCU activatable
		print('		Number of activated MCU exceeded')

	else:
		print('[{}] In	OTA_ERROR_REPORT unknown error id={}'.format(addr,error_id))

	# send acknoledgement
	conn.send(struct.pack('<I', message_string_to_id['OTA_ERROR_REPLY']))
	print('[{}] Out	OTA_ERROR_REPLY'.format(addr))
	return True

def handle_microvisor_request(conn, addr, msg_id):
	print('[{}] In {}'.format(addr, message_id_to_string[msg_id]))

	uuid = addr_uuid_map[addr]

	if uuid not in uuid_microvisor_map:
		conn.send(struct.pack('<I', message_string_to_id['OTA_MICROVISOR_REPLY']))
		conn.send(struct.pack('<I', 0))	# send False (no microvisor update avaiable)
		print('[{}] Out {}: 0'.format(addr, 'OTA_MICROVISOR_REPLY'))
		return True
	
	# Update is available
	conn.send(struct.pack('<I', message_string_to_id['OTA_MICROVISOR_REPLY']))
	conn.send(struct.pack('<I', 1))	# send True (microvisor update avaiable)
	print('[{}] Out {}: 1'.format(addr, 'OTA_MICROVISOR_REPLY'))

	# Read expected reflasher size request
	req = conn.recv(4)
	if(req == b''):
		return False
	req = struct.unpack('<I', req)[0]
	if(req != message_string_to_id['OTA_REFLASHER_SIZE_REQUEST']):
		return False
	print('[{}] In {}'.format(addr, message_id_to_string[req]))

	# Prepare and send reflasher size reply
	reflasher_path = uuid_microvisor_map[uuid][0]
	reflasher_size = os.path.getsize(reflasher_path)
	conn.send(struct.pack('<I', message_string_to_id['OTA_REFLASHER_SIZE_REPLY']))
	conn.send(struct.pack('<I', reflasher_size))
	print('[{}] Out {}: {}'.format(addr, 'OTA_REFLASHER_SIZE_REPLY', reflasher_size))

	# Begin reflasher transfer
	# The reflasher is not stored on the flash memory of the board
	# It is downloaded from the server every time to same memory space 
	print('[{}] Begin Reflasher transfer'.format(addr))
	remaining = reflasher_size
	with open(reflasher_path,"rb") as f:
		while remaining > 0:
			# Read packet request
			req = conn.recv(4)
			if(req == b''):
				return False
			req = struct.unpack('<I', req)[0]
			if(req != message_string_to_id['OTA_UPDATE_NEXT']):
				return False
			print('[{}] In {}'.format(addr, message_id_to_string[req]))

			# Calculate data amount to read
			read_size = UPDATE_PACKET_SIZE
			if remaining < UPDATE_PACKET_SIZE:
				read_size = remaining
			data = f.read(read_size)

			# Send update packet with length of data and data
			conn.send(struct.pack('<I', message_string_to_id['OTA_UPDATE_PACKET']))
			conn.send(struct.pack('<I', len(data)))
			conn.send(data)
			remaining -= read_size
			print('[{}] Out {}: {} bytes'.format(addr, 'OTA_UPDATE_PACKET', read_size))
			print('[{}] Remaining {} bytes'.format(addr, remaining))

	print('[{}] Completed Reflasher transfer'.format(addr))

	# Read expected microvisor size request
	req = conn.recv(4)
	if(req == b''):
		return False
	req = struct.unpack('<I', req)[0]
	if(req != message_string_to_id['OTA_MICROVISOR_SIZE_REQUEST']):
		return False
	print('[{}] In {}'.format(addr, message_id_to_string[req]))

	# Prepare and send microvisor size reply
	microvisor_path = uuid_microvisor_map[uuid][1]
	microvisor_size = os.path.getsize(microvisor_path)
	conn.send(struct.pack('<I', message_string_to_id['OTA_MICROVISOR_SIZE_REPLY']))
	conn.send(struct.pack('<I', microvisor_size))
	print('[{}] Out {}: {}'.format(addr, 'OTA_MICROVISOR_SIZE_REPLY', microvisor_size))

	# Begin Microviros transfer
	print('[{}] Begin Microvisor transfer'.format(addr))
	remaining = microvisor_size
	with open(microvisor_path,"rb") as f:
		while remaining > 0:
			# Read packet request
			req = conn.recv(4)
			if(req == b''):
				return False
			req = struct.unpack('<I', req)[0]
			if(req != message_string_to_id['OTA_UPDATE_NEXT']):
				return False
			print('[{}] In {}'.format(addr, message_id_to_string[req]))

			# Calculate data amount to read
			read_size = UPDATE_PACKET_SIZE
			if remaining < UPDATE_PACKET_SIZE:
				read_size = remaining
			data = f.read(read_size)

			# Send update packet with length of data and data
			conn.send(struct.pack('<I', message_string_to_id['OTA_UPDATE_PACKET']))
			conn.send(struct.pack('<I', len(data)))
			conn.send(data)
			remaining -= read_size
			print('[{}] Out {}: {} bytes'.format(addr, 'OTA_UPDATE_PACKET', read_size))
			print('[{}] Remaining {} bytes'.format(addr, remaining))

	print('[{}] Completed Microvisor transfer'.format(addr))

	uuid_microvisor_map.pop(uuid)	# update performed, remove entry

	return True

# all reply messages do not need a handler as they are never received by the server
# but only sent
message_handlers = {
	0: handle_firmware_request,
	1: handle_unexpected_message,
	2: handle_unexpected_message,
	3: handle_unexpected_message,
	4: handle_unexpected_message,
	5: handle_unexpected_message,
	6: handle_error_report,
	7: handle_unexpected_message,
	8: handle_microvisor_request,
	9: handle_unexpected_message,
	10: handle_unexpected_message,
	11: handle_unexpected_message,
	12: handle_unexpected_message,
	13: handle_unexpected_message,
}

class ClientThread(threading.Thread):
	def __init__(self, client_socket, address):
		threading.Thread.__init__(self)
		self.client_socket = client_socket
		self.address = address
		self.sc_ctx = None
		print('[{}] New connection'.format(self.address))
	
	def run(self):
		# perform client identification
		uuid = self.client_socket.recv(12)
		if(uuid == b''):
			return	# connection closed
		if(uuid not in uuid_key_map):
			self.client_socket.send(struct.pack('<I', 0))	# board unknown
			self.client_socket.close()
			return
		
		self.sc_ctx = SecComm(self.client_socket, uuid_key_map[uuid], NONCE_LEN, AUTH_TAG_LEN)
		self.client_socket.send(struct.pack('<I', 1))	# board identified
		addr_uuid_map[self.address] = uuid	# associate address with UUID
		
		# perform message parsing
		parse_message = True
		while parse_message:
			msg = self.sc_ctx.recv(4)	# read 4 bytes (message code)
			if(msg == b''):
				parse_message = False
			else:
				# process message
				msg_id = struct.unpack('<I', msg)[0]	# unpack message id
				print('[{}] New message:	{}'.format(self.address, message_id_to_string[msg_id]))
				handler = message_handlers.get(msg_id, handle_unexpected_message)	# get appropriate handler
				parse_message = handler(self.sc_ctx, self.address, msg_id)	# call handler				

		# connection closed
		self.client_socket.close()
		print('[{}] Connection closed'.format(self.address))

def main():
	for key,value in message_string_to_id.items():	# fill helper structure
		message_id_to_string[value] = key

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0) as server_socket:
		server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)	# avoid problem of socket already binded after restart
		server_socket.bind((SERVER_IP, SERVER_PORT))
		server_socket.listen()
		print('[Server]	Waiting for connections...')

		accept_connections = True
		while accept_connections:
			(client_socket, address) = server_socket.accept()
			ct = ClientThread(client_socket, address)
			ct.start()		

if __name__== '__main__':
	main()