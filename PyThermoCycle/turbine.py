import NodeIF97

class Turbine():

    """
    Turbine class

    Represents a turbine in the Rankine cycle
    """

    def __init__(self, inletNode):
        """
        Initializes the turbine with the previous conditions

        inletNode: the Turbine's inlet node  Must be an NodeIF97.Node object
        """

        if not isinstance(inletNode, NodeIF97.Node):
            raise TypeError("inletNode should be of type NodeIF97.Node")

        self.inletNode = inletNode
        self.exitNode=None

    def simulate(self, desiredOutletPressure):
        """
        Simulates the turbine and tries to have the exit quality
        as desiredOutletQuality. It does so by progressively and
        isentropically extracting work from the turbine until
        the desired outlet quality is reached

        desiredOutletQuality: The quality of the turbine exit
        """

        self.exitNode = NodeIF97.Node(p=desiredOutletPressure,
                                      s=self.inletNode.s)

        self.workExtracted = - self.exitNode.h + self.inletNode.h
