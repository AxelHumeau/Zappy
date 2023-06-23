from enum import Enum
from communication import action


import sys
import commands

class priority(Enum):
    FOOD = 1
    RESSOURCES = 2
    PLAYER = 3


class AI:
    prio = priority.RESSOURCES
    ask_help = 0
    mapsize = (1, 1)
    message = []
    path = []
    lookaround = 0
    player_answer = 0
    want_to_elevate = False
    need_player = False
    start_elevation = False
    food = 10
    target = -1
    nb_players_on_me_team = 0
    lvl = 1
    following = False
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
                "mendiane": 0,
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

    def __init__(self, communication, team):
        self.communication = communication
        self.team = team

    def get_target(self, vision):
        itemtoget = []
        pos = []
        if (self.prio == priority.RESSOURCES):
            for item, nbr in self.elevation[self.lvl].items():
                if (item != "nb_players" and self.inventory[item] < nbr):
                    itemtoget.append((item, nbr - self.inventory[item]))
        if (self.prio == priority.FOOD):
            itemtoget.append(("food", 1))
        for i in range(len(vision)):
            for obj, nbr in vision[i].items():
                for objects in itemtoget:
                    if (obj == objects[0]):
                        pos.append((objects[0], nbr, i))
        #print("item in vison needed:", pos)
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
        # print("all path:", paths)
        # print("obj:", objs)
        # print("select =", objs[indexbest])
        paths[indexbest][len(paths[indexbest]) - 1] += " " + objs[indexbest][0]
        paths[indexbest][len(paths[indexbest]) - 1] = paths[indexbest][len(paths[indexbest]) - 1].split(" ")
        for i in range(int(objs[indexbest][1] - 1)):
            paths[indexbest].append(paths[indexbest][len(paths[indexbest]) - 1])
        return paths[indexbest]

    # run the A
    def convert_list_to_string(self, lst):
        result = ''
        for inner_list in lst:
            result += ' '.join(inner_list) + '\n'
        return result

    def add_to_request_queue(self, commande):
        for cmd in commande:
            self.communication.request.push(cmd)
            self.communication.count += 1

    def act_look(self):
        if (self.need_player == True and self.following != True):
            print("send here")
            self.communication.writebuffer += "Broadcast " + str(self.team) + " here " + str(self.lvl) + "\n"
            self.communication.request.push(["Broadcast", str(self.team) + " here " + str(self.lvl) + "\n"])
            self.communication.writebuffer += "Inventory\n"
            self.communication.request.push(["Inventory"])
            self.communication.count += 2
            self.ask_help += 1
            if self.ask_help >= 5 and self.nb_players_on_me_team  + 1 < self.elevation[self.lvl]["nb_players"]:
                self.need_player = False
                self.ask_help = 0
                self.nb_players_on_me_team = 0
            if self.prio != priority.FOOD:
                return
            if self.prio == priority.FOOD:
                self.need_player = False
                self.ask_help = 0
        if self.following == True and self.prio != priority.FOOD:
            self.communication.writebuffer += "Inventory\n"
            self.communication.request.push(["Inventory"])
            self.communication.count += 1
            return
        print("search = ", self.prio)
        path = self.get_best_path(self.get_target(self.communication.look_info))
        print("path", path)
        # print("nb_players_on_me", self.nb_players_on_me)
        #if len(path) != 0:
        print(self.communication.look_info)
        if len(path) == 0 and self.lookaround == 3:
            self.lookaround = 0
            self.communication.writebuffer += "Right\nForward\n"
            self.add_to_request_queue([["Right"], ["Forward"]])
            self.communication.writebuffer += "Inventory\n"
            self.communication.request.push(["Inventory"])
            self.communication.count += 1
            return
        if len(path) == 0:
            self.lookaround += 1
            self.communication.writebuffer += "Right\n"
            self.add_to_request_queue([["Right"]])
            return
        self.add_to_request_queue(path)
        self.communication.writebuffer += self.convert_list_to_string(path)
        # self.communication.request.push(path)
        # self.communication.writebuffer += "Inventory\n"
        # self.communication.request.push(["Inventory"])
        # print(self.communication.request)

    def act_inventory(self):
        self.fill_inventory(self.communication.inventory)
        print(self.communication.inventory)
        commands.try_elevation(self, self.communication.request)
        #print(self.need_player)
        #print("food =", self.food)
        if self.food < 6:
            self.prio = priority.FOOD
        else: self.prio = priority.RESSOURCES
        print("prio = ", self.prio )

    def incantation(self):
        print("INCANTATION")
        if (self.lvl != self.communication.current_level):
            self.lvl = self.communication.current_level
            self.start_elevation = False
            self.need_player = False
            self.following = False
            self.nb_players_on_me_team = 0
            print("lvl:", self.lvl)
        else:
            self.start_elevation = True
        if self.want_to_elevate == True:
            self.want_to_elevate = False

    def broadcast(self):
        print("broadcast")

    def Forward(self):
        print("forward")

    def Right(self):
        print("Right")

    def Left(self):
        print("Left")

    def Set(self):
        self.communication.writebuffer += "Inventory\n"
        self.communication.request.push(["Inventory"])
        self.communication.count += 1
        print("set")

    def Take(self):
        print("Take")
        self.communication.writebuffer += "Inventory\n"
        self.communication.request.push(["Inventory"])
        self.communication.count += 1

    def failed(self):
        if (self.start_elevation == True):
            self.start_elevation = False
            self.nb_players_on_me_team = 0
        self.communication.elevation = False
        print("Failed")

    dic_function = {
        action.LOOK: act_look,
        action.INVENTORY: act_inventory,
        action.RIGHT: Right,
        action.LEFT: Left,
        action.FORWARD: Forward,
        action.TAKE: Take,
        action.INCANTATION: incantation,
        action.BROADCAST: broadcast,
        action.FAILED: failed,
        action.SET: Set
    }

    def send_here(self):
        print("here")
        print(self.communication.message.front())
        if self.following == True:
            command = self.communication.message.front()[0]
            message = self.communication.message.front()[1].split(" ")[-1].strip()
            if (int(message) != self.lvl):
                return
            if command in [1, 2, 8]:
                self.communication.writebuffer += "Forward\n"
                self.add_to_request_queue([["Forward"]])
            elif command in [3, 4]:
                self.communication.writebuffer += "Left\n"
                self.add_to_request_queue([["Left"]])
            elif command in [6, 7]:
                self.communication.writebuffer += "Right\n"
                self.add_to_request_queue([["Right"]])
            elif command == 5:
                self.communication.writebuffer += "Right\nRight\n"
                self.add_to_request_queue([["Right"], ["Right"]])

    def send_need(self):
        print("my lvl = ", self.lvl, " requested = ", self.communication.message.front()[1].split(' ')[2])
        if int(self.lvl) == int(self.communication.message.front()[1].split(' ')[2]):
            # self.communication.request.clear()
            # self.communication.writebuffer = ""
            self.communication.writebuffer += "Broadcast " + str(self.team) + " come\n"
            self.add_to_request_queue([["Broadcast", str(self.team) + " come"]])
            self.following = True

    def send_stop(self):
        print("stop")
        if self.following == True and self.communication.message.front()[0] != 0:
            self.following = False

    def send_comming(self):
        print("comming")
        if self.want_to_elevate == True:
            if self.communication.message.front()[0] == 0:
                self.nb_players_on_me_team += 1


    dic_message = {
        "here": send_here,
        "need": send_need,
        "stop": send_stop,
        "come": send_comming
    }

    def handling_message(self):
        if len(self.communication.message) != 0:
            for msg in range(len(self.communication.message)):
                if self.communication.message.front()[1].find(str(self.team)) != -1:
                    self.dic_message[self.communication.message.front()[1].split(' ')[1]](self)
            self.communication.message.pop()


    def run(self):
        while True:
            self.communication.network()
            handling = self.communication.clean_information()
            if handling == action.DEAD:
                print ("DEAD")
                return
            self.handling_message()
            if (handling == action.NOTHING or handling == action.BROADCAST):
                self.communication.writebuffer += "Look\n"
                self.communication.request.push(["Look"])
                self.communication.count += 1
            while (handling != action.NOTHING):
                if handling == action.WAITING:
                    break
                print("following =", self.following)
                if handling == action.DEAD:
                    print ("DEAD 2")
                    return
                #print(handling)
                self.dic_function[handling](self)
                handling = self.communication.clean_information()
                # method corresponding to the handling (LOOK, INVENTORY, FORWARD...)

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
                instructions.append(["Left"])
                instructions.append(["Forward"])
            else:
                instructions.append(["Right"])
                instructions.append(["Forward"])
        else:
            instructions.append(["Forward"])
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
