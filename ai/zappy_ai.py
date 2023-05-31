import socket
import error_handling
import select
import sys
import socket

def connect_to_server(port, adresse):
    s = socket.socket()
    s.connect(('127.0.0.1', port))
    while True:
        read, write, error = select.select([sys.stdin, s], [], [])
        if not read:
            continue
        if read[0] is sys.stdin:
            cmd = input("=> ")
            if cmd == "quit":
                s.close()
                break
            s.send(cmd)
        else:
            print("recv: ", s.recv(1024));

if len(sys.argv) == 1:
    sys.exit(84)
error_handling.error_handler(sys.argv[1:])
connect_to_server(int(sys.argv[2]), sys.argv[5])
sys.exit(0)

