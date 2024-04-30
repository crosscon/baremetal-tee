from cryptography.hazmat.primitives.ciphers.aead import ChaCha20Poly1305
import os
import struct

PACKET_LEN_BYTES = 4

class SecComm():
	def __init__(self, client_socket, key, nonce_len, auth_tag_len):
		self.client_socket = client_socket
		self.key = key
		self.nonce_len = nonce_len
		self.auth_tag_len = auth_tag_len
		self.ccp_ctx = ChaCha20Poly1305(self.key)
		self.plaintext_buff = b''

	def send(self, msg):
		# encrypt plaintext
		nonce = os.urandom(self.nonce_len)
		ciphertext_and_auth = self.ccp_ctx.encrypt(nonce, msg, nonce)
		ciphertext = ciphertext_and_auth[:-self.auth_tag_len]
		auth_tag = ciphertext_and_auth[-self.auth_tag_len:]

		# send encrypted packet
		self.client_socket.send(struct.pack('<I', len(msg)))	# send ciphertext len
		self.client_socket.send(ciphertext)	# send ciphertext
		self.client_socket.send(auth_tag)	# send auth tag
		self.client_socket.send(nonce)	# send nonce
	
	def recv(self, n_bytes):
		remaining = n_bytes
		result = b''
		while(remaining > 0):
			if(len(self.plaintext_buff) > 0):
				chunk = self.plaintext_buff[:remaining]	# get text from plaintext buffer
				result += chunk	# concat new plaintext to result
				self.plaintext_buff = self.plaintext_buff[remaining:]	# advance plaintext buffer
				remaining -= len(chunk)	# decrease remining plaintext in buffer
			else:
				# receive packet len
				packet_len = self.client_socket.recv(PACKET_LEN_BYTES)
				if(packet_len == b''):
					return b''
				packet_len = struct.unpack('<I', packet_len)[0]	# unpack packet size

				# receive ciphertext
				ciphertext = self.client_socket.recv(packet_len)
				if(ciphertext == b''):
					return b''
				# receive auth tag
				auth_tag = self.client_socket.recv(self.auth_tag_len)
				if(auth_tag == b''):
					return b''
				# receive nonce (aad)
				nonce = self.client_socket.recv(self.nonce_len)
				if(nonce == b''):
					return b''

				# decrypt content into plaintext_buffer
				self.plaintext_buff = self.ccp_ctx.decrypt(nonce, ciphertext + auth_tag, nonce)
		return result