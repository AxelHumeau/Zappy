from enum import Enum
from communication import action
import uuid
import os
import sys
import commands

class priority(Enum):
    """
    A class representing a priority as enum
    ...

    Attributes
    ----------

    FOOD: int
        targeting food
    RESSOURCES: int
        targeting resources
    PLAYER: int
        targeting player
    """
    FOOD = 1
    RESSOURCES = 2
    PLAYER = 3

class AI:
    """
        A Class representing a AI
        ...

        Attributes
        ----------

        id: uuid
            ai unique id
        prio: priority(Enum)
            priority of the ai
        ask_help: int
            number of times the ai asked for help
        mapsize: tuple
            size of the map (x,y)
        path: list
            path to the target
        lookaround: int
            number of times the ai has rotated on it self
        want_to_elevate: bool
            true if the ai want to elevate
        need_player: bool
            true if the ai need player to elevate
        start_elevation: bool
            true if the elevation started
        food: int
            nuber of food of the ai
        target: int
            number of possible target or -1 if no target is found
        nb_players_on_me_team: int
            team's player on me
        notmove: bool
            true if as to stop moving until the elevation start
        answerer: list
            list of players that have answer to the help resquest
        requester: str
            player that request the ai help
        lvl: int
            current lv of the player
        following: bool
            true if trying to follow a ai
        elevation: dictionary
            elevation dictionary with the level and the item needed for elevate at this level
        inventory: dictionary
            dictionary with the inventory
        communication: Communication
            class representing the communication with the server
        team: string
            name of the team
        dic_function: dictionary
            dictionary with the function associate to the 
        dic_message: dictionary
            dictionary with the fonction associate

    Methods
    -------
    get_target(vision):
        select the item to target in the vision given

    get_best_path(objs):
        selct the best path bettewen all objects

    add_to_request_queue(commande):
        add several commands to the request queue

    act_look():
        logic when a look is received

    act_inventory():
        logic when a inventory is received

    incantation():
        logic when a incantation is received

    broadcast():
        logic when a broadcast is received

    Forward():
        logic when a Forward is received

    Right()
        logic when a Right is received

    Left()
        logic when a Left is received

    Set()
        logic when a Set is received

    Take()
        logic when a Take is received

    failed()
        logic when a Fail is reiceived

    send_here()
        logic when a message with here is received

    send_need()
        logic when a message with need is received

    send_stop()
        logic when a message with stop is received

    send_comming()
        logic when a message with come is received

    handling_message()
        handling when a message is received and lunch the associated function

    elevation_multiple()
        logic when mates are needed to elevation

    join_mate()
        logic when the bot try to join a mate for elevation

    run()
        loop with the communication ai/server and all the bot logic

    fill_inventory(inventory)
        fill the inventory with the given inventory

    convert_list_to_string(lst):
        convert a list into a simple string
    """
    id = uuid.uuid4()
    prio = priority.RESSOURCES
    ask_help = 0
    mapsize = (1, 1)
    path = []
    lookaround = 0
    want_to_elevate = False
    need_player = False
    start_elevation = False
    food = 10
    target = -1
    nb_players_on_me_team = 0
    notmove = False
    answerer = []
    requester = ""
    lvl = 1
    following = False
    number_of_time_without_mate = 0
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
        """
        Constructs the attributes for the ai
        Parameters
        ----------
            communication: Communication
                Communication class
            team: str
                team name
        """
        self.communication = communication
        self.team = team

    def get_target(self, vision):
        """ target in the vision
        Parameters
        --------
        vision: list
            List of vision content
        Returns
        --------
        list: contaning the targets position name and nbr of it
        """
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
        """ selct the best path bettewen all objects
        Parameters
        ----------
        objs : list
            objects to search for best path
        Returns
            list: contaning the best path
        """
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
        """ convert a list of strings to a single string
        Parameters:
        -----------
        lst : list
            the list of string to convert to a single string one
        Returns:
        str: contaning all the strings in lst
        """
        result = ''
        for inner_list in lst:
            result += ' '.join(inner_list) + '\n'
        return result

    def add_to_request_queue(self, commande):
        """ push in resquest queue the commande
        Parameters:
        ----------
        commande: lst
            commande to push in the request queue
        """
        for cmd in commande:
            self.communication.request.push(cmd)
            self.communication.count += 1

    def act_look(self):
        """ logic when a look is received
        """
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
        """ logic when a inventory is received
        """
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
        """ logic when a incantation is received
        """
        print("INCANTATION")
        print(self.communication.request)
        print(self.communication.response)
        print("---------------------------------------------------------------")
        if (self.lvl != self.communication.current_level):
            self.lvl = self.communication.current_level
            self.start_elevation = False
            self.need_player = False
            self.following = False
            self.nb_players_on_me_team = 0
            self.answerer = []
            self.notmove = False
            print("lvl:", self.lvl)
        else:
            self.start_elevation = True
        if self.want_to_elevate == True:
            self.want_to_elevate = False

    def broadcast(self):
        """ logic when a broadcast is received
        """
        print("broadcast")

    def Forward(self):
        """ logic when a Forward is received
        """
        print("forward")

    def Right(self):
        """ logic when a Right is received
        """
        print("Right")

    def Left(self):
        """ logic when a Left is received
        """
        print("Left")

    def Fork(self):
        print("fork")
        pid = os.fork()
        if pid == 0:
            return "forked"

    def Set(self):
        """ logic when a Set is received
        """
        self.communication.writebuffer += "Inventory\n"
        self.communication.request.push(["Inventory"])
        self.communication.count += 1
        print("set")

    def Take(self):
        """ logic when a Take is received
        """
        print("Take")
        self.communication.writebuffer += "Inventory\n"
        self.communication.request.push(["Inventory"])
        self.communication.count += 1

    def failed(self):
        """ logic when a Failed is received
        """
        if (self.start_elevation == True):
            self.start_elevation = False
            self.nb_players_on_me_team = 0
            self.answerer = []
            self.notmove = False
            self.communication.request.clear()
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
        action.SET: Set,
        action.FORK: Fork
    }

    def send_here(self):
        """ logic when a message with here is received
        """
        if self.following == True and self.prio != priority.FOOD and self.requester == self.communication.message.front()[1].split(' ')[-1]:
            print("here")
            command = self.communication.message.front()[0]
            message = self.communication.message.front()[1].split(" ")[-2].strip()
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
            self.communication.writebuffer += "Broadcast " + str(self.team) + " come " + str(self.id) + "\n"
            self.add_to_request_queue([["Broadcast", str(self.team) + " come " + str(self.id)]])

    def send_need(self):
        """ logic when a message with need is received
        """
        print("my lvl = ", self.lvl, " requested = ", self.communication.message.front()[1].split(' ')[2])
        if int(self.lvl) == int(self.communication.message.front()[1].split(' ')[2]) and self.start_elevation == False and self.need_player == False:
            # self.communication.request.clear()
            # self.communication.writebuffer = ""
            self.communication.writebuffer += "Broadcast " + str(self.team) + " come " + str(self.id) + "\n"
            self.add_to_request_queue([["Broadcast", str(self.team) + " come " + str(self.id)]])
            self.following = True
            self.requester = self.communication.message.front()[1].split(' ')[-1]

    def send_stop(self):
        """ logic when a message whith stop is received
        """
        if (self.communication.message.front()[1].find(self.team) != -1 and self.communication.message.front()[1].split(' ')[-1] == self.requester):
            print("stop")
            if self.following == True and self.communication.message.front()[0] != 0:
                self.communication.writebuffer = ""
                self.communication.request.clear()
                self.following = False
                self.requester = ""
            if self.following == True and self.communication.message.front()[0] == 0:
                self.notmove = True


    def send_comming(self):
        """logic when a message with come is received
        """
        if self.want_to_elevate == True:
            print("comming")
            if self.communication.message.front()[1].split(' ')[-1] not in self.answerer:
                self.answerer.append(self.communication.message.front()[1].split(' ')[-1])
            if self.communication.message.front()[0] == 0:
                self.nb_players_on_me_team += 1
                commands.try_elevation(self, self.communication.request)

    dic_message = {
        "here": send_here,
        "need": send_need,
        "stop": send_stop,
        "come": send_comming
    }

    def handling_message(self):
        """  logic when mates are needed to elevation
        """
        if len(self.communication.message) != 0:
            for msg in range(len(self.communication.message)):
                if self.communication.message.front()[1].find(str(self.team)) != -1:
                    self.dic_message[self.communication.message.front()[1].split(' ')[1]](self)
            self.communication.message.pop()

    def elevation_multiple(self):
        """  logic when mates are needed to elevation
        """
        print("answerer: ", self.answerer)
        if (self.following != True):
            print("send here")
            self.communication.writebuffer += "Broadcast " + str(self.team) + " here " + str(self.lvl) +  " " + str(self.id) + "\n"
            self.communication.request.push(["Broadcast", str(self.team) + " here " + str(self.lvl) + " " + str(self.id) + "\n"])
            self.communication.count += 1
            self.ask_help += 1
        if self.ask_help >= 2 and len(self.answerer) + 1 < self.elevation[self.lvl]["nb_players"]:
            self.number_of_time_without_mate += 1
            if self.number_of_time_without_mate >= 10:
                self.number_of_time_without_mate = 0
                self.communication.writebuffer += "Fork\n"
                self.communication.request.push(["Fork"])
        if self.ask_help >= 2 and self.nb_players_on_me_team + 1 < self.elevation[self.lvl]["nb_players"]:
            self.need_player = False
            self.ask_help = 0
            self.nb_players_on_me_team = 0
            self.answerer = []
            self.communication.writebuffer += "Inventory\n"
            self.communication.request.push(["Inventory"])
        if self.prio == priority.FOOD:
            self.communication.writebuffer += "Look\n"
            self.communication.request.push(["Look"])
            self.need_player = False
            self.ask_help = 0
            return

    def join_mate(self):
        """ logic when the bot try to join a mate for elevation
        """
        if self.notmove == True:
            return
        if self.following == True and self.prio == priority.FOOD:
            self.communication.writebuffer += "Look\n"
            self.communication.request.push(["Look"])
            self.communication.count += 1
        if self.following == True and self.prio != priority.FOOD:
            self.communication.writebuffer += "Inventory\n"
            self.communication.request.push(["Inventory"])
            self.communication.count += 1
            return

    def run(self):
        """ loop with the communication ai/server and all the bot logic
        """
        while True:
            if self.communication.network() == "closed":
                return
            handling = self.communication.clean_information()
            if handling == action.DEAD:
                print ("DEAD")
                return
            self.handling_message()
            if (handling == action.NOTHING and self.following == True):
                self.join_mate()
            if (handling == action.NOTHING and self.need_player == True):
                self.elevation_multiple()
            if (handling == action.NOTHING and self.following == False and self.need_player == False and self.notmove == False):
                self.communication.writebuffer += "Look\n"
                self.communication.request.push(["Look"])
                self.communication.count += 1
            while (handling != action.NOTHING and handling != None):
                if handling == action.WAITING:
                    break
                print("following =", self.following)
                if handling == action.DEAD:
                    print ("DEAD 2")
                    return
                #print(handling)
                if self.dic_function[handling](self) == "forked":
                    return "forked"
                handling = self.communication.clean_information()
                # method corresponding to the handling (LOOK, INVENTORY, FORWARD...)

    def fill_inventory(self, inventory):
        """ convert a list into a simple string
        """
        for item in inventory:
            key = list(item.keys())[0]
            value = item[key]
            if key in self.inventory:
                self.inventory[key] = value
            if key == "food":
                self.food = value

def generate_instructions(path):
    """ generate the instruction path for a item
    Parameters
    ----------
    path : list
    Returns
    -------
    list : list of instructions
    """
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
    """ checks if a given number is part of a sequence
    Parameters:
    ----------
    number : int
        The number to check.
    Returns:
    -------
    bool: True if the number is part of the sequence, False otherwise.
    """
    for n in range(1, number + 1):
        term = n**2 + n
        if term == number:
            return True
    return False

def get_path(posobj, lvl):
    """ generates a path to move from a given position to a target position based on a level
    Parameters:
    ----------
    posobj : int
        The starting position.
    lvl : int
        The level of the target.
    Returns:
    --------
    list: The path as a list of positions
    """
    line, sens = get_objline(posobj, lvl)
    path = []
    while posobj != line:
        path.append(posobj)
        posobj -= sens
    path += add_sequence_terms_to_list(posobj)
    return path[::-1]

def add_sequence_terms_to_list(number):
    """ generates a list of terms in the sequence up to a given number
    Parameters:
    -----------
    number : int
        The upper limit of the sequence
    Returns:
    --------
    list: The list of sequence terms
    """
    sequence_list = [0]
    for n in range(1, number + 1):
        term = n**2 + n
        sequence_list.append(term)
        if number == term:
            break
    return sequence_list[::-1]

def get_objline(posobj, lvl):
    """ determines the line in which a given position is located based on a level
    Parameters:
    ----------
    posobj : int
        The position to determine the line for
    lvl : int
        The level of the player
    Returns:
    tuple: The line position and the direction (-1, 0, or 1).
    """
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
