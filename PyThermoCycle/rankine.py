"""
PyThermoCycle is a simple simulator of the ideal rankine cycle as 
   
    ----Node 0---Turbine---Node 1---
    |                               |
  Boiler                          Condenser
    |                               |
    ----Node 3---Pump------Node 2---- 

Author:Cheng Maohua
Email: cmh@seu.edu.cn

"""
from tabulate import tabulate
import Node
import turbine
import pump
import condenser
import boiler


def RankineCycle():
    condenserOverCool = 0.1
    condenserPressure = 0.006
    desiredQuality = 0.9

    table = []

    for boilerPressure in [1, 1.5, 2]:
        nodes = []
        for i in range(4):
            nodes.append(Node.Node())

        nodes[0].p = boilerPressure

        nodes[1].p = condenserPressure
        nodes[1].x = desiredQuality

        nodes[2].p = condenserPressure
        nodes[2].x = 0

        nodes[3].p = boilerPressure

        #  simulate
        nodes[1].px()
        t = turbine.Turbine(nodes[0], nodes[1])
        t.simulate()
        nodes[0] = t.inletNode

        nodes[2].px()
        c = condenser.Condenser(nodes[1], nodes[2])
        c.simulate(condenserOverCool)
        nodes[2] = c.exitNode

        p = pump.Pump(nodes[2], nodes[3])
        p.simulate()
        nodes[3] = p.exitNode

        b = boiler.Boiler(nodes[3], nodes[0])
        b.simulate()

        efficiency = (t.workExtracted - p.workRequired) / (b.heatAdded)

        table.append([boilerPressure, efficiency])

    print(tabulate(table, headers=["Boiler Pressure", "Efficiency"]))


if __name__ == '__main__':
    RankineCycle()
