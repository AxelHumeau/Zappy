
from queue import Queue


class Communication:
    """ Class representing Communication information between ai and server """

    communication = {
        "": ["WELCOME"],
        "Forward": ["ok"],
        "Right": ["ok"],
        "Left": ["ok"],
        "Broadcast text": ["ok"],
        "Fork": ["ok"],
        "Eject": ["ok", "ko"],
    }

    def __init__(self):
        self.request = Queue()
        self.response = Queue()
        self.look_info = []
        self.inventory = []
        self.message = []
        self.current_level = 1

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
        info = self.response.front()[0].split(",")
        message_info = {int(info[0].split()(" ")[1]): info[1].strip()}
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
        "Take": interaction_object,
        "Set": interaction_object,
        "Broadcast": pop_information,
        "ko": pop_information,
        "Look": parse_information_look,
        "Inventory": parse_information_inventory
    }

    def clean_information(self):
        """ Pop queue of response/request

        Returns:
            boolean: True/False
        """
        if (len(self.request) == 0 or len(self.response) == 0):
            return False
        if (len(self.response) != 0 and
                self.response.front().find("message") != -1):
            self.get_message()
        if (self.request.front()[0] in Communication.communication):
            return self.pop_response()
        elif (self.response.front() == "ko"):
            return self.pop_information()
        return self.dict_function[self.request.front()[0]](self)
