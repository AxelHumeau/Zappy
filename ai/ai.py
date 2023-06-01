class ai:
    lifeUnite = 10
    TimeUnite = 1260
    def __init__(self, reciprocal, socket):
        if reciprocal:
            self.reciprocal = reciprocal;
        else:
            self.reciprocal = 100;
        self.socket = socket;
        def Forward(self):
            self.socket.send("Forward\n")
        def Right(self):
            self.socket.send("Right\n")
        def Left(self):
            self.socket.send("Left\n")
        def Look(self):
            self.socket.send("Look\n")
        def Inventory(self):
            self.socket.send("Inventory\n")
        def Broadcast(self, message):
            self.socket.send("Broadcast\n")
        def Connect_nbr(self):
            self.socket.send("Connect_nbr\n")
        def Fork(self):
            self.socket.send("Fork\n")
        def Eject(self):
            self.socket.send("Eject\n")
        def Death(self):
            self.socket.send("Death\n")
        def Take(self):
            self.socket.send("Take\n")
        def Set(self):
            self.socket.send("Set\n")
        def Incantation(self):
            self.socket.send("Incantation\n")