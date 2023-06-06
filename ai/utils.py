import socket


def help():
    print('''USAGE: ./zappy_ai -p port -n name -h machine
        port is the port number
        name is the name of the team
        machine is the name of the machine; localhost by default''')


def split_information(message):
    """ split information

    Args:
        message (str): message that need to be split

    Returns:
        list: a list of element in message
    """
    pos = message.find('\n')
    result = []
    while (pos != -1):
        result.append(message[:pos])
        message = message[pos + 1:]
        pos = message.find('\n')
    return result


def connexion_team(socket, dict_args):
    """Connexion to the team

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


def connexion_server(port, machine):
    """ Connexion to the server

    Args:
        port (int): port value for the connexion
        machine (str): name of the machine

    Raises:
        Exception: Error connexion on server

    Returns:
        socket.socket: creation of a new socket (server)
    """

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((machine, port))
        return s
    except socket.error:
        raise Exception("Error connexion server")
