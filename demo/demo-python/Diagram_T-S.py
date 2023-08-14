"""
T-s Diagram

1 Calculating isoenthalpic lines isoh(200, 3600)kJ/kg
2 Calculating isobar lines  isop(611.657e-6,100)MPa
3 Calculating saturation lines x=0,x=1
4 Calculating isoquality lines x(0.1,0.9)

Author: Cheng Maohua. 2017.02.10
Email: cmh@seu.edu.cn

"""
from seuif97 import ph2s, ph2t, tx2s, px2t, px2s

import matplotlib.pyplot as plt
import numpy as np

xAxis = "s"
yAxis = "T"
title = {"T": "T, °C", "s": "s, kJ/kgK"}

plt.title("%s-%s Diagram" % (yAxis, xAxis))
plt.xlabel(title[xAxis])
plt.ylabel(title[yAxis])
plt.grid()

Pt = 611.657e-6
isoh = np.linspace(200, 3600, 20)
isop = np.array([Pt, 0.0015, 0.004, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5,
                 1.0, 2.0, 5.0, 10.0, 20.0, 35.0, 60,100.0])
# Calculating isoenthalpic lines isoh(200, 3600)kJ/kg
for h in isoh:
    T = np.array([ph2t(p, h) for p in isop])
    S = np.array([ph2s(p, h) for p in isop])
    plt.plot(S, T, 'g', lw=0.5)
# Calculating isobar lines  isop(611.657e-6,100)MPa
for p in isop:
    T = np.array([ph2t(p, h) for h in isoh])
    S = np.array([ph2s(p, h) for h in isoh])
    plt.plot(S, T, 'b', lw=0.5)

# saturate water to wet steam
for p in [Pt,  0.0015, 0.004]:
    s = ph2s(p, 200)
    t = ph2t(p, 200)
    s_sat_water = px2s(p, 0.0)
    t_sat_water = px2t(p, 0.0)
    plt.plot([s_sat_water, s], [t_sat_water, t], 'b', lw=0.5)


tc = 647.096 - 273.15
T = np.linspace(0.11, tc, 100)
for x in np.array([0, 1.0]):
    S = np.array([tx2s(t, x) for t in T])
    plt.plot(S, T, 'r', lw=1.0)

for x in np.linspace(0.1, 0.9, 11):
    S = np.array([tx2s(t, x) for t in T])
    plt.plot(S, T, 'r--', lw=0.5)

plt.show()
