import NodeIF97


class Boiler:
    """
    The boiler class
    """

    def __init__(self, inletNode):
        """
        Initializes the boiler with the previous conditions

        inletNode:  the Boiler's inlet node Must be an NodeIF97.Node object
        """

        if not isinstance(inletNode, NodeIF97.Node):
            raise TypeError("inletNode should be of type NodeIF97.Node")

        self.inletNode = inletNode
        self.exitNode = None

    def simulate(self, desiredOutletTemp):
        """
        Simulates the Boiler and tries to get the exit temperature down
        to the desiredOutletTemp. This is done by continuously adding h
        while keeping the P constant.
        """

        self.exitNode = NodeIF97.Node(t=desiredOutletTemp,
                                      p=self.inletNode.p)

        self.heatAdded = self.exitNode.h - self.inletNode.h
