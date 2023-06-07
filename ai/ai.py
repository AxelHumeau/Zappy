from enum import Enum


class priority(Enum):
    FOOD = 1
    RESSOURCES = 2


class AI:
    prio = priority.RESSOURCES
    slot = 0
    goto = 0
    mapsize = (1, 1)
    food = 10
    target = -1
    nb_players_at_same_level = 0
    elevation = {
        1: {
                "nb_players": 1,
                "linemate": 1,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
        2: {
                "nb_players": 2,
                "linemate": 1,
                "deraumere": 1,
                "sibur": 1,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
        3: {
                "nb_players": 2,
                "linemate": 2,
                "phiras": 2,
                "sibur": 1,
                "mendiane": 0,
                "deraumere": 0,
                "thystame": 0
            },
        4: {
                "nb_players": 4,
                "linemate": 1,
                "deraumere": 1,
                "sibur": 2,
                "phiras": 1,
                "mandiane": 0,
                "thystame": 0
            },
        5: {
                "nb_players": 4,
                "linemate": 1,
                "deraumere": 2,
                "sibur": 1,
                "mendiane": 3,
                "phiras": 0,
                "thystame": 0
            },
        6: {
                "nb_players": 6,
                "linemate": 1,
                "deraumere": 2,
                "sibur": 3,
                "phiras": 1,
                "mendiane": 0,
                "thystame": 0
            },
        7: {
                "nb_players": 6,
                "linemate": 2,
                "deraumere": 2,
                "sibur": 2,
                "mendiane": 2,
                "phiras": 2,
                "thystame": 1
            }
    }
    inventory = {
        "linemate": 0,
        "deraumere": 0,
        "sibur": 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    }
    lvl = 1
    vision = []
    q_command = []
    # init

    def __init__(self, socket):
        self.socket = socket
    # communication
    # def Forward(self):
    #     self.socket.send("Forward\n").encode()
    # def Right(self):
    #     self.socket.send("Right\n").encode()
    # def Left(self):
    #     self.socket.send("Left\n").encode()
    # def Look(self):
    #     self.socket.send("Look\n").encode()
    # def Inventory(self):
    #     self.socket.send("Inventory\n").encode()
    # def Broadcast(self, message):
    #     self.socket.send("Broadcast" + message + '\n').encode()
    # def Connect_nbr(self):
    #     self.socket.send("Connect_nbr\n").encode()
    # def Fork(self):
    #     self.socket.send("Fork\n").encode()
    # def Eject(self):
    #     self.socket.send("Eject\n").encode()
    # def Take(self):
    #     self.socket.send("Take\n").encode()
    # def Set(self):
    #     self.socket.send("Set\n").encode()
    # def Incantation(self):
    #     self.socket.send("Incantation\n").encode()
    # with the vision provide by look and his own inventory get the tile to go

    def get_target(self, vision):
        itemtoget = []
        pos = []
        if (self.prio == priority.RESSOURCES):
            for item, nbr in self.elevation[self.lvl].items():
                if (item != "nb_players" and self.inventory[item] < nbr):
                    itemtoget.append((item, nbr - self.inventory[item]))
        if (self.prio == priority.FOOD):
            itemtoget.append(("food", 1))
        if (itemtoget):
            self.target = len(itemtoget)
        else:
            self.target = -1
        for i in range(len(vision)):
            print("case", i)
            for obj, nbr in vision[i].items():
                print("in", obj, "nbr", nbr)
                for objects in itemtoget:
                    print("my object :", objects[0])
                    if (obj == objects[0]):
                        pos.append((objects[0], nbr, i))
        print(pos)
    # look for tiles with the item he need

    # def look_aroud(self):
    #     rotation = 0
    #     while (self.target != -1):
    #         look()
    #         get_target(self.vision)
    #         Right()
    #         if (rotation == 4):
    #             Forward()
    #             rotation = 0
    #         rotation += 1
    # run the AI
    # def run(self):
    #     if (self.prio == priority.RESSOURCES and self.food < 5):
    #         prio = priority.FOOD
    #     else :
    #         priority = priority.RESSOURCES
        # look around to find a target (eat or ressources)
        # if the elevation is possible elevation
        # if there is target go to it
        # printf("running")
