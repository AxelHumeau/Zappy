class Queue:
    """ Class that represent a Queue (FIFO) """
    def __init__(self):
        """ Initialization of a queue """
        self.queue = []
        list

    def __len__(self):
        """ length of the queue

        Returns:
            int: size of the queue
        """
        return len(self.queue)

    def __getitem__(self, i):
        return self.queue[i]

    def __iter__(self):
        for i in self.queue:
            yield i

    def __repr__(self):
        return str(self.queue)

    def clear(self):
        self.queue.clear()

    def push(self, elem):
        """ push element

        Args:
            elem (any): elem that need to be push in last position in the queue
        """
        self.queue.append(elem)

    def pop(self):
        """ pop the first element in the queue

        Raises:
            IndexError: list empty
        """
        try:
            self.queue.pop(0)
        except IndexError:
            raise IndexError("List out of range")

    def empty(self):
        """ check if queue is empty

        Returns:
            boolean: if queue is empty or not
        """
        if len(self.queue == 0):
            return True
        else:
            return False

    def front(self):
        """ return the first element in the queue

        Raises:
            IndexError: empty queue

        Returns:
            any: first element in the queue
        """
        try:
            return self.queue[0]
        except IndexError:
            raise IndexError("List out of range")
