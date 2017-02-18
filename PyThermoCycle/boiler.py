import Node


class Boiler:
    """
    The boiler class
    """

    def __init__(self, inletNode, exitNode):
        """
        Initializes the boiler with the previous conditions
        """
        self.inletNode = inletNode
        self.exitNode = exitNode

    def simulate(self):
        """
        Simulates the Boiler and tries to get the exit temperature down
        to the desiredOutletTemp. This is done by continuously adding h
        while keeping the P constant.
        """
        self.exitNode.p = self.inletNode.p
        self.exitNode.pt()

        self.heatAdded = self.exitNode.h - self.inletNode.h
