# -*- coding: utf-8 -*-
"""
This is a simple sample for seuif.py

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2016.4.20

"""
from seuif97 import *

import matplotlib.pyplot as plt
import numpy as np

p1,t1 = 16, 535
p2,t2 = 3.56,315
h1 = pt2h(p1, t1)
s1 = pt2s(p1, t1)

h2 = pt2h(p2, t2)
s2 = pt2s(p2, t2)

h2s = ps2h(p2, s1)
his = ishd(p1, t1, p2)

ef = ief(p1, t1, p2, t2)

# print('The isentropic efficiency is ',ef)

# 4条线：p1、p2 等压，等熵焓降线、膨胀线

samp = 0.01

smp1 = s1 - samp
hsmp1 = ps2h(p1, smp1)
sap1 = s1 + samp
hsap1 = ps2h(p1, sap1)

smt1 = s1 - samp
hsmt1 = ps2h(p1, smp1)
sat1 = s1 + samp
hsat1 = ts2h(t1, sap1)

point_p1_h = np.zeros(shape=3)
point_p1_h[0] = hsmp1
point_p1_h[1] = h1
point_p1_h[2] = hsap1
point_p1_s = np.zeros(shape=3)
point_p1_s[0] = smp1
point_p1_s[1] = s1
point_p1_s[2] = sap1

# p2
smp2 = s1 - samp  # 等熵焓降点延伸
hsmp2 = ps2h(p2, smp2)
sap2 = s2 + samp
hsap2 = ps2h(p2, sap2)

smt2 = s2 - samp
hsmt2 = ps2h(p1, smp1)
sat2 = s2 + samp
hsat2 = ts2h(t2, sap1)

point_p2_h = np.zeros(shape=3)
point_p2_h[0] = hsmp2
point_p2_h[1] = h2
point_p2_h[2] = hsap2

point_p2_s = np.zeros(shape=3)
point_p2_s[0] = smp2
point_p2_s[1] = s2
point_p2_s[2] = sap2

# 等熵焓降
point_is_h = np.zeros(shape=2)
point_is_h[0] = h1
point_is_h[1] = h2s
point_is_s = np.zeros(shape=2)
point_is_s[0] = s1
point_is_s[1] = s1

# HP Expansion Line
point_hp_h = np.zeros(shape=2)
point_hp_h[0] = h1
point_hp_h[1] = h2
point_hp_s = np.zeros(shape=2)
point_hp_s[0] = s1
point_hp_s[1] = s2

plt.plot(point_p1_s, point_p1_h, 'bs-')

plt.plot(point_p2_s, point_p2_h, 'bs-')
plt.plot(point_is_s, point_is_h, 'ys-')
plt.plot(point_hp_s, point_hp_h, 'rs-', label='Expansion Line')

_title = 'The isentropic efficiency = ' + \
    r'$\frac{h1-h2}{h1-h2s}$' + '=' + '{:.2f}'.format(ef) + '%'

plt.legend(loc="best", bbox_to_anchor=[0.5, 0.5],
           ncol=2, shadow=True, title=_title)

# annotate some interesting points
plt.annotate('(P1,T1)',
             xy=(s1, h1), xycoords='data',
             xytext=(+10, +30), textcoords='offset points', fontsize=12,
             arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))

plt.annotate('(P2,T2)',
             xy=(s2, h2), xycoords='data',
             xytext=(+10, +30), textcoords='offset points', fontsize=12,
             arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))

plt.xlabel('s(kJ/(kg.K))')
plt.ylabel('h(kJ/kg)')
plt.show()
