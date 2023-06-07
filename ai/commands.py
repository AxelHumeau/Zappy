from queue import Queue
from ai import AI


def try_elevation(ai: AI, request_queue: Queue):
    """Try to do an elevation, add the request in the queue

    Returns:
        boolean: True if the elevation requirement are fulfilled, false otherwise
    """
    if ai.nb_players_at_same_level < ai.elevation["nb_players"]:
        return False
    for el in ai.elevation[ai.level].items()[1:]:
        if el[1] < ai.inventory[el[0]]:
            return False
    request_queue.push("Incantation")
    return True
