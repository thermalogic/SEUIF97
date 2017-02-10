"""
T-s Diagram

1 Calculating isoenthalpic lines isoh(200, 3600)kJ/kg
2 Calculating isobar lines  isop(0.01,100)MPa
3 Calculating saturation lines x=0,x=1
4 Calculating isoquality lines x(0.1,0.9)

License: this code is in the public domain

Author: Cheng Maohua
Email: cmh@seu.edu.cn

Last modified: 2017.02.10

"""
from seuif97 import ph2t, ph2s, tx2s
import numpy as np
import matplotlib.pyplot as plt

xAxis = "s"
yAxis = "T"
title = {"T": "T, C", "s": "s, kJ/kgK"}

plt.title("%s-%s Diagram" % (yAxis, xAxis))
plt.xlabel(title[xAxis])
plt.ylabel(title[yAxis])
plt.xlim(0, 10.2)
plt.grid()

isoh = np.linspace(200, 3600, 18)
for h in isoh:
    P = np.linspace(0.01, 100, 100)
    T = np.array([ph2t(p, h) for p in P])
    S = np.array([ph2s(p, h) for p in P])
    plt.plot(S, T, 'b', lw=0.5)

isop = np.array([0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0,
                 2.0, 5.0, 10.0, 20.0, 50.0, 100.0])
for p in isop:
    H = np.linspace(200, 3600, 15)
    T = np.array([ph2t(p, h) for h in H])
    S = np.array([ph2s(p, h) for h in H])
    plt.plot(S, T, 'b', lw=0.5)

tc = 647.096 - 273.15
T = np.linspace(0.11, tc, 100)
for x in np.array([0, 1.0]):
    S = np.array([tx2s(t, x) for t in T])
    plt.plot(S, T, 'r', lw=1.0)

for x in np.linspace(0.1, 0.9, 11):
    S = np.array([tx2s(t, x) for t in T])
    plt.plot(S, T, 'r--', lw=0.5)

plt.show()
