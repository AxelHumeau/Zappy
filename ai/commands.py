from queue import Queue
from ai import AI


def try_elevation(ai: AI, request_queue: Queue):
    """Try to do an elevation, add the request in the queue

    Returns:
        boolean: True if the elevation requirement are fulfilled, false otherwise
    """
    for el in ai.elevation[ai.level].items():
        if el[1] < ai.inventory[el[0]]:
            return False
    request_queue.push("Incantation")
    return True
