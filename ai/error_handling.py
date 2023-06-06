from utils import help
import sys


def error_handler(av, dict):
    """ error handling of arguments

    Args:
        av ([str]): list of arguments entered by the user
        dict (dict): dict that will stock every value by the corresponding key

    Raises:
        Exception: Error on argument
    """
    if len(av) == 0:
        raise Exception("Invalid number of argument")
    if (len(av) == 1 and av[0] == "-help"):
        help()
        sys.exit(0)
    if (len(av) != 4 and len(av) != 6):
        raise Exception("Invalid number of argument")
    dict["machine"] = "127.0.0.1"
    for i in range(0, len(av), 2):
        if (av[i] == "-p"):
            if (not av[i + 1].isdigit()):
                raise Exception("Invalid port value")
            dict["port"] = int(av[i + 1])
        if (av[i] == "-n"):
            dict["name"] = av[i + 1]
        if (av[i] == "-h"):
            if av[i + 1] == "localhost":
                dict["machine"] = "127.0.0.1"
            else:
                dict["machine"] = av[i + 1]
    if "port" not in dict or "name" not in dict:
        raise Exception("Wrong parameter value")
