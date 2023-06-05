
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
        "Take": ["ok", "ko"]
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

    def parse_information_look(self, list):
        print("~~~~~~~~~~~~~~~~~~")
        print(self.response.front()[0])
        info = self.response.front()[0].translate({ord(i): None for i in '[]'})
        print(info)
        print("~~~~~~~~~~~~~~~~~~")
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
            list.append(dict_info)
        self.request.pop()
        self.response.pop()
        return True

    def parse_information_inventory(self, list):
        print(self.response.front()[0])
        info = self.response.front()[0].translate({ord(i): None for i in '[]'})
        for square in info:
            dict_info = {}
            elem = square.strip().split(" ")
            dict_info[elem[0]] = int(elem[1])
            list.append(dict_info)
        self.request.pop()
        self.response.pop()
        return True

    def pop_response(self):
        response = self.response.front()[0]
        if (response in Communication.communication[self.request.front()]):
            self.request.pop()
            self.response.pop()
            return True
        return False

    def clean_information(self):
        if (len(self.request) == 0):
            return False
        if (self.request.front() in Communication.communication):
            return self.pop_response()
        else:
            if (self.response.front()[0] == "ko"):
                self.request.pop()
                self.response.pop()
                return True
            if (self.request.front() == "Look"):
                if (len(self.look_info) != 0):
                    self.look_info.clear()
                return self.parse_information_look(self.look_info)
            if (self.request.front() == "Inventory"):
                if (len(self.inventory) != 0):
                    self.inventory.clear()
                return self.parse_information_inventory(self.inventory)
        return False
