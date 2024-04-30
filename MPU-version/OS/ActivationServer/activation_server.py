#!/usr/bin/python3

from os import read
import socket
import struct
import hashlib
import threading

from cryptography.hazmat.backends.interfaces import CipherBackend
from sec_comm import SecComm
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric import padding


SERVER_IP = ''	# leave empty for server reachable by any interface
SERVER_PORT = 25565
NONCE_LEN = 12
AUTH_TAG_LEN = 16
KEY_FILE = 'ActivationServer/server.pem'


valid_licenses = {
	b'thislicenseisvalid!!!!!!!!!!!!!!'.hex(): 10,
	b'thislicenselimithasbeenexceeded!'.hex(): 1,
}

recorded_activations = {
	b'thislicenselimithasbeenexceeded!'.hex(): {b'fakeboardid!'.hex()},
}


message_string_to_id = {
	'ACTIVATOR_ACTIVATION_REQUEST' : 0,
	'ACTIVATOR_ACTIVATION_REPLY' : 1
}

message_id_to_string = {}	# Automatically filled

private_key = None
public_key = None

def is_license_valid(license):
	if license in valid_licenses:
		return True
	else:
		return False

def is_limit_exceeded(license):
	if not is_license_valid(license):
		return False	# License not valid, no limit exceeded
	else:
		max_activations = valid_licenses[license]
		curr_activations = recorded_activations.get(license, {})
		if len(curr_activations) < max_activations:
			return False
		else:
			return True

def handle_unexpected_message(conn, addr, msg_id):
	print('Unexpected message received: {}'.format(msg_id))
	return False

def handle_activation_request(conn, addr, msg_id):
	license = conn.recv(32)	# read board license
	if(license == b''):
		return False
	uuid = conn.recv(12)	# read board UUID
	if(uuid == b''):
		return False
	
	# parse data as strings of hexadecimal characters
	license_hs = license.hex()
	uuid_hs = uuid.hex()

	# compose and send reply
	conn.send(struct.pack('<I', message_string_to_id['ACTIVATOR_ACTIVATION_REPLY']))
	if is_license_valid(license_hs):	# verify license
		if is_limit_exceeded(license_hs):	# check license limit
			conn.send(struct.pack('<I', 2))	# send ACTIVATOR_LICENSE_LIMIT_EXCEEDED
			print('Server --> {}	ACTIVATOR_ACTIVATION_REPLY	license limit exceeded'.format(addr))
		else:
			# store newly activated board
			if license_hs in recorded_activations:
				recorded_activations[license_hs].add(uuid_hs)
			else:
				recorded_activations[license_hs] = {uuid_hs}
			conn.send(struct.pack('<I', 0))	# send ACTIVATOR_ACTIVATION_OK
			# compute sha256 of uid (activation code)
			uuid_hash = hashlib.sha256(uuid)
			conn.send(uuid_hash.digest())	# send activation code
			print('Server --> {}	ACTIVATOR_ACTIVATION_REPLY	board activated'.format(addr))
	else:
		conn.send(struct.pack('<I', 1))	# send ACTIVATOR_INVALID_LICENSE
		print('Server --> {}	ACTIVATOR_ACTIVATION_REPLY	invalid license'.format(addr))
	
	return True

# all reply messages do not need a handler as they are never received by the server
# but only sent
message_handlers = {
	0: handle_activation_request,
	1: handle_unexpected_message,
}

class ClientThread(threading.Thread):
	def __init__(self, client_socket, address):
		threading.Thread.__init__(self)
		self.client_socket = client_socket
		self.address = address
		self.sc_ctx = None
		print('[{}] New connection'.format(self.address))
	
	def run(self):
		try:
			# read encrypted packet length
			n = self.client_socket.recv(4)
			n = struct.unpack('<I', n)[0] # unpack packet length
			if(n == b''):
				raise Exception	# connection closed
			# read packet encrypted with server public key
			pkt = self.client_socket.recv(n)
			if(pkt == b''):
				raise Exception	# connection closed
			# decrypt symmetric key contained in packet
			key = private_key.decrypt(pkt, padding.PKCS1v15())
			
			# create SecComm context
			self.sc_ctx = SecComm(self.client_socket, key, NONCE_LEN, AUTH_TAG_LEN)
			self.client_socket.send(struct.pack('<I', 1))
			
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
		finally:
			# connection closed
			self.client_socket.close()
			print('[{}] Connection closed'.format(self.address))


def main():
	for key,value in message_string_to_id.items():	# fill helper structure
		message_id_to_string[value] = key
	
	# read private-public keys
	global private_key, public_key
	with open(KEY_FILE, 'rb') as key_file:
		private_key = serialization.load_pem_private_key(key_file.read(), password=None)
		public_key = private_key.public_key()

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