import NodeIF97


class Pump():

    """
    Pump class

    Represents a pump in the Rankine cycle
    """

    def __init__(self, inletNode):
        """
        Initializes the pump with the previous conditions

        inletNode: the Pump's inlet node Must be an  NodeIF97.Node object
        """

        if not isinstance(inletNode,  NodeIF97.Node):
            raise TypeError("inletNode should be of type NodeIF97.Node")

        self.inletNode = inletNode
        self.exitNode = None

    def simulate(self, desiredFinalPressure):
        """
        Simulates the pump and tries to have the exit quality
        as desiredOutletQuality. It does so by progressively and
        isentropically extracting work from the pump until
        the desired outlet quality is reached

        desiredOutletQuality: The quality of the pump exit
        """

        self.exitNode = NodeIF97.Node(p=desiredFinalPressure,
                                      s=self.inletNode.s)

        self.workRequired = self.exitNode.h - self.inletNode.h
