from enum import Enum


class priority(Enum):
    FOOD = 1
    RESSOURCES = 2


class AI:
    prio = priority.FOOD
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
    lvl = 3
    vision = []
    q_command = []
    # init

    def __init__(self, socket):
        self.socket = socket

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
        return paths[indexbest]

    ## look for tiles with the item he need
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
