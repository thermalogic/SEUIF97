import NodeIF97


class Condenser:
    """
    The condenser class
    """

    def __init__(self, inletNode):
        """
        Initializes the condenser with the previous conditions

        inletNode: The Node of the steam on the Condenser's inlet.
            Must be an NodeIF97.Node object
        """

        if not isinstance(inletNode, NodeIF97.Node):
            raise TypeError("inletNode should be of type NodeIF97.Node")

        self.inletNode = inletNode
        self.exitNode=None

    def simulate(self, desiredOutletTemp):
        """
        Simulates the Condenser and tries to get the exit temperature down
        to the desiredOutletTemp. This is done by continuously extracting h
        while keeping the P constant.
        """

        self.exitNode = NodeIF97.Node(p=self.inletNode.p,
                                      t=desiredOutletTemp)

        self.heatExtracted = self.inletNode.h - self.exitNode.h
