import sys

def help():
    print("USAGE: ./zappy_ai -p port -n name -h machine\n \
        \tport is the port number\n \
        \tname is the name of the team\n \
        \tmachine is the name of the machine; localhost by default")

def error_handler(av):
    if (av[0] == "-help" and len(av) == 1):
        help()
        sys.exit(0)
    if (len(av) != 6):
        help()
        sys.exit(84)
    if (av[1].isdigit() == False):
        help()
        sys.exit(84)
