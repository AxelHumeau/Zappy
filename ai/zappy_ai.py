import socket
import error_handling
import select
import sys
from communication import Communication


def split_information(message):
    """_summary_

    Args:
        message (str): message that need to be split

    Returns:
        _type_: a list of element in message
    """
    pos = message.find('\n')
    result = []
    while (pos != -1):
        result.append(message[:pos])
        message = message[pos + 1:]
        pos = message.find('\n')
    return result


def connexion_team(socket, dict_args):
    """_summary_

    Args:
        socket (socket.socket): initiliaze socket server
        dict_args (dict): dictionnary of informations entered by users

    Raises:
        Exception: Error on connexion team
    """

    print(socket.recv(1024).decode(), end="")
    socket.send((dict_args["name"] + "\n").encode())
    result = socket.recv(1024).decode()
    if (result == "ko\n"):
        raise Exception("Error connexion to team")
    # team_info = print(split_information(result))
    # ai = Ai(socket, communication, int(team_info[0]), int(team_info[1]))
    # ai


def loop_client(dict_args):
    """_summary_

    Args:
        dict_args (dict): dictionnary of informations entered by users
    """
    message = ""
    communication = Communication()
    s = connexion_server(dict_args["port"], dict_args["machine"])
    connexion_team(s, dict_args)
    while True:
        read, write, error = select.select([sys.stdin, s], [], [])
        if not read:
            continue
        if read[0] is sys.stdin:
            cmd = input()
            if cmd == "quit":
                s.close()
                break
            cmd += '\n'
            cmd = cmd.replace("\\n", "\n")
            pos = cmd.find('\n')
            # s.send(cmd.encode())
            while (pos != -1):
                s.send(cmd[:pos + 1].encode())
                if (cmd != "\n"):
                    communication.request.push(cmd[:pos].split(" "))
                cmd = cmd[pos + 1:]
                pos = cmd.find('\n')
        elif read[0] is s:
            message += s.recv(1024).decode()
        pos = message.find('\n')
        tmp = []
        # print("MEsagge : " + message)
        while (pos != -1):
            tmp.append(message[:pos])
            message = message[pos + 1:]
            pos = message.find('\n')
        # print("----------TMP----------")
        # print(tmp)
        # print("----------TMP----------")
        if (len(tmp) != 0):
            for elem in tmp:
                communication.response.push(elem)
        while (communication.clean_information()):
            continue
        print("\n----------")
        print(communication.request)
        print(communication.response)
        print("Look info : ")
        print(communication.look_info)
        print("Inventory info : ")
        print(communication.inventory)
        print("-----------\n")


def connexion_server(port, machine):
    """_summary_

    Args:
        port (int): port value for the connexion
        machine (str): name of the machine

    Raises:
        Exception: Error connexion on server

    Returns:
        _type_: creation of a new socket (server)
    """

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((machine, port))
        return s
    except socket.error:
        raise Exception("Error connexion server")


if __name__ == "__main__":
    dict_argument = {}
    try:
        error_handling.error_handler(sys.argv[1:], dict_argument)
        loop_client(dict_argument)
    except Exception as error:
        print(error, file=sys.stderr)
        sys.exit(84)
    sys.exit(0)
