"""
H-S(Mollier) Diagram

1 Calculating Isotherm lines isot(0.0,800.0)°C
2 Calculating Isobar lines  isop(611.657e-6, 100.0)Mpa
3 Calculating saturation lines x=0,x=1
4 Calculating isoquality lines x(0.1,0.9)

Author: Cheng Maohua. 2017.02.10
Email: cmh@seu.edu.cn

"""
from seuif97 import pt2h, pt2s, tx2h, tx2s

import matplotlib.pyplot as plt
import numpy as np

xAxis = "s"
yAxis = "h"
title = {"h": "h, kJ/kg", "s": "s, kJ/kgK"}

plt.title("%s-%s Diagram" % (yAxis, xAxis))
plt.xlabel(title[xAxis])
plt.ylabel(title[yAxis])
plt.xlim(0, 12.5)
plt.ylim(0, 4300)
plt.grid()

Pt = 611.657e-6

isot = np.array([0, 50, 100, 200, 300, 400, 500, 600, 700, 800])
isop = np.array([Pt, 0.001, 0.01, 0.1, 1, 10, 20, 50, 100])
# Isotherm lines to plot, values in ºC
for t in isot:
    h = np.array([pt2h(p, t) for p in isop])
    s = np.array([pt2s(p, t) for p in isop])
    plt.plot(s, h, 'g', lw=0.5)

# Isobar lines to plot
for p in isop:
    h = np.array([pt2h(p, t) for t in isot])
    s = np.array([pt2s(p, t) for t in isot])
    plt.plot(s, h, 'b', lw=0.5)

tc = 647.096-273.15
T = np.linspace(0.1, tc, 100)
# Calculate saturation line
for x in np.array([0, 1.0]):
    h = np.array([tx2h(t, x) for t in T])
    s = np.array([tx2s(t, x) for t in T])
    plt.plot(s, h, 'r', lw=1.0)

# Isoquality lines to plot
isox = np.linspace(0.1, 0.9, 11)
for x in isox:
    h = np.array([tx2h(t, x) for t in T])
    s = np.array([tx2s(t, x) for t in T])
    plt.plot(s, h, 'r--', lw=0.5)

plt.show()
