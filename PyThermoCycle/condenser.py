import Node


class Condenser:
    """
    The condenser class
    """

    def __init__(self, inletNode, exitNode):
        """
        Initializes the condenser with the conditions
        """
        self.inletNode = inletNode
        self.exitNode = exitNode

    def simulate(self, condenserOverCool):
        """
        Simulates the Condenser and tries to get the exit temperature down
        to the desiredOutletTemp. This is done by continuously extracting h
        while keeping the P constant.
        """

        self.heatExtracted = self.inletNode.h - self.exitNode.h

        self.exitNode.h = self.exitNode.h - condenserOverCool
        self.exitNode.ph()
