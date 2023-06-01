import sys

def help():
    print('''USAGE: ./zappy_ai -p port -n name -h machine
        port is the port number
        name is the name of the team
        machine is the name of the machine; localhost by default''')

def error_handler(av, dict):
    if (av[0] == "-help" and len(av) == 1):
        help()
        sys.exit(0)
    if (len(av) != 6):
        print('Invalid number of argument', file=sys.stderr)
        sys.exit(84)
    for i in range(0, len(av), 2):
        if (av[i] == "-p"):
            if (not av[i + 1].isdigit()):
                print('Invalid port value', file=sys.stderr)
                sys.exit(84)
            dict["port"] = int(av[i + 1])
        if (av[i] == "-n"):
            dict["name"] =  av[i + 1]
        if (av[i] == "-h"):
            dict["machine"] = av[i + 1]
    if "port" not in dict or "name" not in dict or "machine" not in dict:
        print('Wrong parameter value', file=sys.stderr)
        sys.exit(84)