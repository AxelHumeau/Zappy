class Queue:
    def __init__(self):
        self.queue = []

    def __len__(self):
        return len(self.queue)

    def __repr__(self):
        return str(self.queue)

    def push(self, elem):
        self.queue.append(elem)

    def pop(self):
        try:
            self.queue.pop(0)
        except IndexError:
            raise IndexError("List out of range")

    def empty(self):
        if len(self.queue == 0):
            return True
        else:
            return False

    def front(self):
        try:
            return self.queue[0]
        except IndexError:
            raise IndexError("List out of range")