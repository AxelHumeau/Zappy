import socket
import error_handling
import select
import sys
import socket

import socket

class ai:
    lifeUnite = 10
    TimeUnite = 1260
    def __init__(self, reciprocal, socket):
        if reciprocal:
            self.reciprocal = reciprocal;
        else:
            self.reciprocal = 100;
        self.socket = socket;
        def Forward(self):
            self.socket.send("Forward\n")
        def Right(self):
            self.socket.send("Right\n")
        def Left(self):
            self.socket.send("Left\n")
        def Look(self):
            self.socket.send("Look\n")
        def Inventory(self):
            self.socket.send("Inventory\n")
        def Broadcast(self, message):
            self.socket.send("Broadcast\n")
        def Connect_nbr(self):
            self.socket.send("Connect_nbr\n")
        def Fork(self):
            self.socket.send("Fork\n")
        def Eject(self):
            self.socket.send("Eject\n")
        def Death(self):
            self.socket.send("Death\n")
        def Take(self):
            self.socket.send("Take\n")
        def Set(self):
            self.socket.send("Set\n")
        def Incantation(self):
            self.socket.send("Incantation\n")

def loop_client(port, adress):
    s = connexion_server(port)
    while True:
        read, write, error = select.select([sys.stdin, s], [], [])
        if not read:
            continue
        if read[0] is sys.stdin:
            cmd = input("=> ")
            if cmd == "quit":
                s.close()
                break
            cmd += '\n'
            s.send(cmd.encode())
        else:
            print("recv: ", s.recv(1024).decode());

def connexion_server(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect(('127.0.0.1', port))
        return s
    except socket.error:
        raise Exception("Error connexion server")

if __name__ == "__main__":
    dict_argument = {}
    if len(sys.argv) == 1:
        sys.exit(84)
    error_handling.error_handler(sys.argv[1:], dict_argument)
    try:
        loop_client(dict_argument["port"], "kofeko")
    except Exception as error:
        print(error, file=sys.stderr)
        sys.exit(84)
    sys.exit(0)
