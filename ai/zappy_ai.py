import socket
import error_handling
import select
import sys
from communication import Communication


def split_information(message):
    pos = message.find('\n')
    result = []
    while (pos != -1):
        result.append(message[:pos])
        message = message[pos + 1:]
        pos = message.find('\n')
    return result


def connexion_team(socket, dict_args, communication):
    socket.recv(1024).decode()
    socket.send((dict_args["name"] + "\n").encode())
    result = socket.recv(1024).decode()
    if (result == "ko\n"):
        raise Exception("Error connexion to team")
    team_info = print(split_information(result))
    # ai = Ai(socket, communication, int(team_info[0]), int(team_info[1]))
    # ai


def loop_client(dict_args):
    message = ""
    communication = Communication()
    s = connexion_server(dict_args["port"])
    connexion_team(s, dict_args, communication)
    while True:
        read, write, error = select.select([sys.stdin, s], [], [])
        if not read:
            continue
        if read[0] is sys.stdin:
            cmd = input()
            if cmd == "quit":
                s.close()
                break
            cmd += "\n"
            cmd = cmd.replace("\\n", "\n")
            pos = cmd.find('\n')
            while (pos != -1):
                s.send(cmd[:pos + 1].encode())
                if (cmd != "\n"):
                    communication.request.push(cmd[:pos])
                cmd = cmd[pos + 1:]
                pos = cmd.find('\n')
        elif read[0] is s:
            message += s.recv(1024).decode()
        pos = message.find('\n')
        tmp = []
        i = 0
        while (pos != -1):
            tmp.append(message[:pos])
            message = message[pos + 1:]
            pos = message.find('\n')
        if (len(tmp) != 0):
            communication.response.push(tmp)
            if (len(communication.response) == len(communication.request)):
                while (communication.clean_information()):
                    continue
        print("----------")
        print(communication.request)
        print(communication.response)
        print("Look info : ")
        print(communication.look_info)
        print("Inventory info : ")
        print(communication.inventory)
        print("----------")


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
        print(len([]))
        loop_client(dict_argument)
    except Exception as error:
        print(error, file=sys.stderr)
        sys.exit(84)
    sys.exit(0)
