
from queue import Queue


class Communication:
    communication = {
        "": ["WELCOME"],
        "Forward": ["ok"],
        "Right": ["ok"],
        "Left": ["ok"],
        # "Look": [...,],
        "Broadcast text": ["ok"],
        "Fork": ["ok"],
        "Eject": ["ok", "ko"],
        # "Take"
    }

    def __init__(self):
        self.request = Queue()
        self.response = Queue()
        self.look_info = []
        self.inventory = []

    def push_request(self, elem):
        self.request.push(elem)

    def push_response(self, elem):
        self.response.push(elem)

    def parse_information(self, list):
        list_information = self.response.front()[0].replace("[", "").replace("]", "").split(",")
        for square in list_information:
            dict_info = {}
            for elem in square.strip().split(" "):
                if elem != "":
                    try:
                        dict_info[elem] += 1
                    except KeyError:
                        dict_info[elem] = 1
                else:
                    dict_info[None] = 0
            list.append(dict_info)
        self.request.pop()
        self.response.pop()

    def clean_information(self):
        if (len(self.request) != 0 and self.request.front() in Communication.communication):
            print()
            if (self.response.front()[0] in Communication.communication[self.request.front()]):
                self.request.pop()
                self.response.pop()
                return True
            else:
                return False
        else:
            if (len(self.request) != 0 and self.response.front()[0] == "ko"):
                self.request.pop()
                self.response.pop()
                return True
            if (len(self.request) != 0 and self.request.front() == "Look"):
                if (len(self.look_info) != 0):
                    self.look_info.clear()
                self.parse_information(self.look_info)
                return True
            if (len(self.request) != 0 and self.request.front() == "Inventory"):
                if (len(self.inventory) != 0):
                    self.inventory.clear()
                look_info = self.response.front()[0].replace("[", "").replace("]", "").split(",")
                for square in look_info:
                    dict_info = {}
                    elem = square.strip().split(" ")
                    dict_info[elem[0]] = int(elem[1])
                    self.inventory.append(dict_info)
                self.request.pop()
                self.response.pop()
                return True
        return False
