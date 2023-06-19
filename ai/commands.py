from queue import Queue

def try_elevation(ai, request_queue: Queue):
    """Try to do an elevation, add the request in the queue

    Returns:
        boolean: True if the elevation requirement are fulfilled, false otherwise
    """
    if ai.nb_players_at_same_level < ai.elevation[ai.lvl]["nb_players"]:
        return False
    if ai.start_elevation == True:
        return False
    else:
        ai.start_elevation = True
    for el in ai.elevation[ai.lvl].items():
        if (el[0] == "nb_players"):
            continue
        elif ai.inventory[el[0]] < el[1]:
            return False
    for item in ai.elevation[ai.lvl].items():
        if (item[0] == "nb_players"):
            continue
        for i in range(item[1]):
            request_queue.push(["Set", item[0]])
            ai.communication.writebuffer += "Set " + item[0] + "\n"
    request_queue.push(["Incantation"])
    ai.communication.writebuffer += "Incantation\n"
    # request_queue.push(["Inventory"])
    # ai.communication.writebuffer += "Inventory\n"
    return True
