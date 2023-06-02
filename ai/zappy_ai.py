import socket
import error_handling
import select
import sys
import socket
import ai

def loop_client(port, message: str):
    s = connexion_server(port)
    bot = ai.AI(s)
    bot.get_target([{"sibur": 1, "food": 2}, {"linemate": 1}, {"linemate": 1}, {"phiras": 1}])
    print(bot.goto)
    # while True:
    #     read, write, error = select.select([sys.stdin, s], [], [])
    #     if not read:
    #         continue
    #     if read[0] is sys.stdin:
    #         cmd = input("=> ")
    #         if cmd == "quit":
    #             s.close()
    #             break
    #         cmd += '\n'
    #         s.send(cmd.encode())
    #     elif read[0] is s:
    #         message += s.recv(1024).decode()
    #     pos = message.find('\n')
    #     while (pos != -1):
    #         print(message[:pos])
    #         message = message[pos + 1:]
    #         pos = message.find('\n')

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
    loop_client(dict_argument["port"], "")
    # try:
    #     loop_client(dict_argument["port"], "")
    # except Exception as error:
    #     print(error, file=sys.stderr)
    #     sys.exit(84)
    sys.exit(0)
