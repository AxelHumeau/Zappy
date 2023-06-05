
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

    def parse_information_look(self):
        """_summary_

        Returns:
            _type_: true
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
        self.inventory.clear()
        info = self.response.front().translate({ord(i): None for i in '[]'})
        for square in info.split(","):
            dict_info = {}
            elem = square.strip().split(" ")
            dict_info[elem[0]] = int(elem[1])
            self.inventory.append(dict_info)
        return self.pop_information()

    def pop_response(self):
        response = self.response.front()
        if (response in Communication.communication[self.request.front()[0]]):
            return self.pop_information()
        return False

    def interaction_object(self):
        if (self.response.front()[0] == "ko"):
            # Algo to retake a object
            print("Failed take object")
        return self.pop_information()

    def pop_information(self):
        self.request.pop()
        self.response.pop()
        return True

    def get_message(self):
        info = self.response.front()[0].split(",")
        message_info = {int(info[0].split()(" ")[1]): info[1].strip()}
        self.message.append(message_info)
        self.response.pop()

    dict_function = {
        "Take": interaction_object,
        "Set": interaction_object,
        "Broadcast": pop_information,
        "ko": pop_information,
        "Look": parse_information_look,
        "Inventory": parse_information_inventory
    }

    def clean_information(self):
        # print("CLEAN INFORMATION")
        # print("\n\n-----------RESPONSE POKIMMMOON------------")
        # print(self.request)
        # print(self.response)
        # print("-----------RESPONSE POKIMMMOON------------\n")
        if (len(self.response) != 0):
            if (self.response.front().find("message") != -1):
                self.get_message()
        if (len(self.request) == 0 or len(self.response) == 0):
            return False
        if (self.request.front()[0] in Communication.communication):
            return self.pop_response()
        else:
            if (self.response.front() == "ko"):
                return self.pop_information()
            return self.dict_function[self.request.front()[0]](self)
