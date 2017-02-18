import Node


class Pump():

    """
    Pump class

    Represents a pump in the Rankine cycle
    """

    def __init__(self, inletNode, exitNode):
        """
        Initializes the pump with the conditions
        """
        self.inletNode = inletNode
        self.exitNode = exitNode

    def simulate(self):
        """
        Simulates the pump and tries to have the exit quality
        as desiredOutletQuality. It does so by progressively and
        isentropically extracting work from the pump until
        the desired outlet quality is reached 
        desiredOutletQuality: The quality of the pump exit
        """
        self.exitNode.s = self.inletNode.s
        self.exitNode.ps()

        self.workRequired = self.exitNode.h - self.inletNode.h
