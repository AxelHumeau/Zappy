from enum import Enum
from communication import action

import sys
import commands

class priority(Enum):
    FOOD = 1
    RESSOURCES = 2


class AI:
    prio = priority.RESSOURCES
    mapsize = (1, 1)
    path = []
    lookaround = 0
    food = 10
    target = -1
    nb_players_at_same_level = 0
    lvl = 1
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
    # init

    def __init__(self, communication):
        self.communication = communication

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
            for obj, nbr in vision[i].items():
                for objects in itemtoget:
                    if (obj == objects[0]):
                        pos.append((objects[0], nbr, i))
        return pos

    def get_best_path(self, objs):
        paths = []
        pathscores = []
        bestscore = 0
        indexbest = 0
        if len(objs) == 0:
            return []
        for obj in objs:
            paths.append(generate_instructions(get_path(obj[2], self.lvl)))
        if self.prio == priority.RESSOURCES:
            for i in range(len(paths)):
                pathscores.append((1 - self.inventory[objs[i][0]] / self.elevation[self.lvl][objs[i][0]]) * len(paths[i]))
        else:
            for i in range(len(paths)):
                pathscores.append(len(paths[i]))
        bestscore = pathscores[0]
        for i in range(len(pathscores) - 1):
            if pathscores[i] < bestscore:
                indexbest = i
                bestscore = pathscores[i]
        paths[indexbest][len(paths[indexbest]) - 1] += " " + obj[0]
        paths[indexbest][len(paths[indexbest]) - 1] = paths[indexbest][len(paths[indexbest]) - 1].split(" ")
        return paths[indexbest]

    #def bot_engine(self):
        # print("SENDING")
        # #  if self.lookaround != 3 or len(self.path) != 0:
        # self.s.send(("Inventory\n").encode())
        # self.communication.request.push(["Inventory"])
        # if (len(self.communication.inventory) != 0):
        #     self.fill_inventory(self.communication.inventory)
        # commands.try_elevation(self, self.communication)
        # if (len(self.path) == 0):
        #     self.s.send(("Look\n").encode())
        #     self.communication.request.push(["Look"])
        #     if (len(self.communication.look_info) != 0):
        #         self.path = self.get_best_path(self.get_target(self.communication.look_info))
        #         print("" self.communication.look_info)
        #         print(self.get_best_path(self.get_target(self.communication.look_info)))
        #         if len(self.path) == 0 self.lookaround != 3:
        #             self.s.send(("Right\n").encode())
        #             self.lookaround += 1
        #             self.communication.request.push(["Right"])
            #     if len(self.path) == 0 and self.lookaround == 3:
            #         self.s.send(("Right\n").encode())
            #         self.s.send(("Forward\n").encode())
            #         self.communication.request.push(["Rigth", "Forward"])
            #         self.lookaround = 0
            # else:
            #     for cmd in self.path:
            #         self.s.send((cmd + "\n").encode())
            #     self.communication.request.push(self.path)

    # run the AI

    def add_to_request_queue(self, commande):
        for cmd in commande:
            self.communication.request.push(cmd)

    def act_look(self):
        path = self.get_best_path(self.get_target(self.communication.look_info))
        print(path)
        if len(path) == 0 and self.lookaround == 3:
            self.lookaround += 0
            self.communication.writebuffer += "Right\nForward\n"
            self.add_to_request_queue([["Right"], ["Forward"]])
            return
        if len(path) == 0:
            self.lookaround += 1
            self.communication.writebuffer += "Right\n"
            self.add_to_request_queue([["Right"]])
            return
        # self.communication.request.push(path)
        # self.communication.writebuffer += "Inventory\n"
        # self.communication.request.push(["Inventory"])

        # print(self.communication.request)

    def act_inventory(self):
        self.fill_inventory(self.communication.inventory)
        print(self.inventory)

    def Forward(self):
        print("forward")

    def Right(self):
        print("Right")


    dic_function = {
        action.LOOK: act_look,
        action.INVENTORY: act_inventory,
        action.RIGHT: Right,
        action.FORWARD: Forward,
        # action.LEFT: left,
        # action.RIGHT: right,
    }

    def run(self):
        while True:
            self.communication.network()
            if (len(self.communication.response) != 0 and self.communication.response.front() == 'dead'):
                break
            handling = self.communication.clean_information()
            if (handling == action.NOTHING and len(self.communication.response) == 0):
                self.communication.writebuffer += "Look\n"
                self.communication.request.push(["Look"])
            while (handling != action.NOTHING):
                if handling == action.WAITING:
                    break
                print(handling)
                self.dic_function[handling](self)
                handling = self.communication.clean_information()
                # method corresponding to the handling (LOOK, INVENTORY, FORWARD...)
        self.s.close()

    def fill_inventory(self, inventory):
            for item in inventory:
                key = list(item.keys())[0]
                value = item[key]
                if key in self.inventory:
                    self.inventory[key] = value
                if key == "food":
                    self.food = value

def generate_instructions(path):
    instructions = []
    for i in range(1, len(path)):
        current = path[i - 1]
        next_num = path[i]
        if not is_part_of_sequence(next_num) and is_part_of_sequence(current):
            if next_num < current:
                instructions.append("Left")
                instructions.append("Forward")
            else:
                instructions.append("Right")
                instructions.append("Forward")
        else:
            instructions.append("Forward")
    instructions.append("Take")
    return instructions

def is_part_of_sequence(number):
    for n in range(1, number + 1):
        term = n**2 + n
        if term == number:
            return True
    return False

def get_path(posobj, lvl):
    line, sens = get_objline(posobj, lvl)
    path = []
    while posobj != line:
        path.append(posobj)
        posobj -= sens
    path += add_sequence_terms_to_list(posobj)
    return path[::-1]

def add_sequence_terms_to_list(number):
    sequence_list = [0]
    for n in range(1, number + 1):
        term = n**2 + n
        sequence_list.append(term)
        if number == term:
            break
    return sequence_list[::-1]

def get_objline(posobj, lvl):
    n = 0
    while n <= lvl:
        term = n**2 + n
        if term == posobj:
            return term, 0
        if (posobj <= term) and posobj >= term - n:
            return term, -1
        if (posobj >= term) and (posobj <= term + n):
            return term, 1
        n += 1
