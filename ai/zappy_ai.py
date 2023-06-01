import socket
import error_handling
import select
import sys
import socket

class ai:
    lifeUnite = 10
    inventory = {
        "linemate" : 0,
        "deraumere" : 0,
        "sibur" : 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame" : 0
    }
    lvl = 1
    vision = []
    q_command = []
    def __init__(self, socket):
        self.socket = socket;
        def Forward(self):
            self.socket.send("Forward\n").encode()
        def Right(self):
            self.socket.send("Right\n").encode()
        def Left(self):
            self.socket.send("Left\n").encode()
        def Look(self):
            self.socket.send("Look\n").encode()
        def Inventory(self):
            self.socket.send("Inventory\n").encode()
        def Broadcast(self, message):
            self.socket.send("Broadcast" + message + '\n').encode()
        def Connect_nbr(self):
            self.socket.send("Connect_nbr\n").encode()
        def Fork(self):
            self.socket.send("Fork\n").encode()
        def Eject(self):
            self.socket.send("Eject\n").encode()
        def Take(self):
            self.socket.send("Take\n").encode()
        def Set(self):
            self.socket.send("Set\n").encode()
        def Incantation(self):
            self.socket.send("Incantation\n").encode()
        def run(self):
            self.socket.send("Run\n").encode()

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
