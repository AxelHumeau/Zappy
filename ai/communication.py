
from queue import Queue
from enum import Enum
import select

class action(Enum):
    NOTHING = 0
    FORWARD = 1
    RIGHT = 2
    LEFT = 3
    LOOK = 4
    INVENTORY = 5
    BROADCAST = 6
    CONNECTNBR = 7
    FORK = 8
    EJECT = 9
    TAKE = 10
    SET = 11
    INCANTATION = 12
    FAILED = 13
    WAITING = 14


class Communication:
    """ Class representing Communication information between ai and server """

    communication = {
        "": ["WELCOME"],
        "Forward": [["ok"], action.FORWARD],
        "Right": [["ok"], action.RIGHT],
        "Left": [["ok"], action.LEFT],
        "Broadcast text": [["ok"], action.BROADCAST],
        "Fork": [["ok"], action.FORK],
        "Eject": [["ok", "ko"], action.EJECT],
    }

    def __init__(self, socket):
        self.request = Queue()
        self.response = Queue()
        self.look_info = []
        self.inventory = []
        self.message = []
        self.current_level = 1
        self.nbr_conect = 1
        self.readbuffer = ""
        self.writebuffer = ""
        self.s = socket

    # def connect_number(self):
    #     info = self.response.front()
    #     self.nbr_conect = int(info)
    #     return self.pop_information()

    def parse_information_look(self):
        """ parse all information of the command 'Look'

        Returns:
            boolean: True
        """
        self.look_info.clear()
        info = self.response.front().translate({ord(i): None for i in '[]'})
        for square in info.split(","):
            dict_info = {}
            for elem in square.strip().split(" "):
                if elem.isnumeric():
                    self.request.pop()
                    self.response.pop()
                    return False
                if elem != "":
                    try:
                        dict_info[elem] += 1
                    except KeyError:
                        dict_info[elem] = 1
                else:
                    dict_info[None] = 0
            self.look_info.append(dict_info)
        self.request.pop()
        self.response.pop()
        return True

    def parse_information_inventory(self):
        """ parse all information of the command 'Inventory'

        Returns:
            boolean: True
        """
        self.inventory.clear()
        info = self.response.front().translate({ord(i): None for i in '[]'})
        for square in info.split(","):
            dict_info = {}
            elem = square.strip().split(" ")
            if len(elem) != 2 or elem[1].isnumeric() == False:
                break
            dict_info[elem[0]] = int(elem[1])
            self.inventory.append(dict_info)
        return self.pop_information()

    def pop_response(self):
        """ Pop response with its corresponding request

        Returns:
            boolean: False
        """
        response = self.response.front()
        if (response in Communication.communication[self.request.front()[0]]):
            return self.pop_information()
        return False

    def interaction_object(self):
        """ Interaction with object on the map (Take, Set)

        Returns:
            boolean: pop_information()
        """
        if (self.response.front()[0] == "ko"):
            # Algo to retake a object
            print("Failed take object")
        return self.pop_information()

    def pop_information(self):
        """ Pop response and request

        Returns:
            boolean: True
        """
        self.request.pop()
        self.response.pop()
        return True

    def get_message(self):
        """ Get a message (from the command Broadcast 'Message') """
        info = self.response.front().split(",")
        message_info = {int(info[0].split(" ")[1]): info[1].strip()}
        self.message.append(message_info)
        self.response.pop()

    def get_elevation_response(self):
        """Get the elevation response from the command Incantation

        Returns:
            boolean: True if the elevation is successful, False otherwise
        """
        resp = self.response.pop()
        if resp[0] == "ko":
            self.current_level = -1
            return False
        try:
            self.current_level = int(resp[4])
            return True
        except Exception:
            self.current_level = -1
            return False

    dict_function = {
        "Take": [interaction_object, action.TAKE],
        "Set": [interaction_object, action.SET],
        "Broadcast": [pop_information, action.BROADCAST],
        "ko": [pop_information, action.NOTHING],
        "Look": [parse_information_look, action.LOOK],
        "Inventory": [parse_information_inventory, action.INVENTORY],
        # "Connect_nbr" : connect_number
    }

    def clean_information(self):
        """ Pop queue of response/request

        Returns:
            boolean: True/False
        """
        if (len(self.response) == 0 and len(self.request) != 0):
            return action.WAITING
        if (len(self.request) == 0 and len(self.response) == 0):
            return action.NOTHING
        if (len(self.response) != 0 and
                self.response.front().find("message") != -1):
            self.get_message()
        if (self.request.front()[0] in Communication.communication):
            oldrq = self.request.front()[0]
            self.pop_information()
            return self.communication[oldrq][1]
        elif (len(self.response) != 0 and self.response.front() == "ko"):
            self.pop_information()
            return action.FAILED
        if len(self.request) != 0:
            oldrq = self.request.front()[0]
            self.dict_function[self.request.front()[0]][0](self)
        return self.dict_function[oldrq][1]

    def network(self):
        read, write, error = select.select([self.s], [self.s], [])
        if write and len(self.writebuffer) != 0:
            self.s.send((self.writebuffer).encode())
            self.writebuffer = ""
        if read:
            self.readbuffer += self.s.recv(1024).decode()
        tmp = []
        pos = self.readbuffer.find('\n')
        while (pos != -1):
            tmp.append(self.readbuffer[:pos])
            self.readbuffer = self.readbuffer[pos + 1:]
            pos = self.readbuffer.find('\n')
        for elem in tmp:
            self.response.push(elem)
