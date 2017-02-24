import Node


class Boiler:
    """
    The boiler class
    """

    def __init__(self,inletNode, exitNode):
        """
        Initializes the boiler with nodes
        """
        self.inletNode = inletNode
        self.exitNode = exitNode

    def simulate(self,nodes,mdot):
        """
        Simulates the Boiler and tries to get the exit temperature down
        to the desiredOutletTemp. This is done by continuously adding h
        while keeping the P constant.
        """
        self.heatAdded = nodes[self.exitNode].h - nodes[self.inletNode].h
        self.Qindot = mdot*self.heatAdded/(3600*1000)   