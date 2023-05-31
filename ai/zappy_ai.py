import socket
import error_handling
import sys
import socket

def connect_to_server(port, adresse):
    s = socket.socket()
    s.connect((adresse, port))
    print (s.recv(1024).decode())
    s.close()

if len(sys.argv) == 1:
    sys.exit(84)
error_handling.error_handler(sys.argv[1:])
sys.exit(0)

