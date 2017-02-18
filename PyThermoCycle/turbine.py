import Node

class Turbine():

    """
    Turbine class

    Represents a turbine in the Rankine cycle
    """

    def __init__(self, inletNode,exitNode):
        """
        Initializes the turbine with the  conditions
        """
        self.inletNode = inletNode
        self.exitNode=exitNode
    
    def simulate(self):
        """
        Simulates the turbine and tries to have the exit quality
        as desiredOutletQuality. It does so by progressively and
        isentropically extracting work from the turbine until
        the desired outlet quality is reached
        desiredOutletQuality: The quality of the turbine exit
        """
        self.inletNode.s=self.exitNode.s
        self.inletNode.ps()
        
        self.workExtracted = - self.exitNode.h + self.inletNode.h
