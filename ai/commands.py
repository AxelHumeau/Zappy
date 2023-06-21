from queue import Queue

def try_elevation(ai, request_queue: Queue):
    """Try to do an elevation, add the request in the queue

    Returns:
        boolean: True if the elevation requirement are fulfilled, 0 otherwise
    """
    for el in ai.elevation[ai.lvl].items():
        if (el[0] == "nb_players"):
            continue
        elif ai.inventory[el[0]] < el[1]:
            return 0
    if ai.start_elevation == True:
        return 0
    if ai.nb_players_on_me < ai.elevation[ai.lvl]["nb_players"]:
        if ai.need_player == False:
            ai.communication.writebuffer += "Broadcast " + str(ai.team) + " " + str(ai.lvl) + "\n"
            request_queue.push(["Broadcast", str(ai.team) + " " + str(ai.lvl)])
            ai.need_player = True
        return 0
    else:
        ai.start_elevation = True
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
    return 1
