import NodeIF97
from tabulate import tabulate

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
        turbineEntropy = NodeIF97.Node(p=condenserPressure, x=desiredQuality).s

        turbineInletTemperature = NodeIF97.Node(p=boilerPressure,
                                                s=turbineEntropy).t

        condenserExitNode = NodeIF97.Node(p=condenserPressure, x=0.0)
        condenserExitNode = NodeIF97.Node(h=condenserExitNode.h - condenserOverCool,
                                          p=condenserPressure)

        p = pump.Pump(condenserExitNode)
        p.simulate(boilerPressure)

        b = boiler.Boiler(p.exitNode)
        b.simulate(turbineInletTemperature)

        boilerSaturationTemp = NodeIF97.Node(p=boilerPressure, x=0.0).t
        degreeOfSuperheat = turbineInletTemperature - boilerSaturationTemp

        t = turbine.Turbine(b.exitNode)
        t.simulate(condenserPressure)

        c = condenser.Condenser(t.exitNode)
        c.simulate(condenserExitNode.t)

        efficiency = (t.workExtracted - p.workRequired) / (b.heatAdded)

        table.append([boilerPressure, degreeOfSuperheat, efficiency])

    print(tabulate(table, headers=["Boiler Pressure",
                                   "Degree of Superheat",
                                   "Efficiency"]))


if __name__ == '__main__':
    RankineCycle()
