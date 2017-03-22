# -*- coding: utf-8 -*-

import seuif97

p = 0.00353658941
t = 300 - 273.15
s1 = seuif97.px2s(p, 0)
s2 = seuif97.px2s(p, 1)
h1 = seuif97.px2h(p, 0)
h2 = seuif97.px2h(p, 1)
x = 0.20
s = s1 + x * (s2 - s1)
h = h1 + x * (h2 - h1)
v = seuif97.hs2t(h, s)

print(v)
p = 3
t = 300 - 273.15
s = seuif97.ph2s(p, t)

print(s)

t = 310 - 273.15
s = seuif97.ph2s(p, t)
print(s)

s = seuif97.pt2s(0.000611212677444, 273.15)
print(s)
h = seuif97.pt2h(0.000611212677444, 273.15)
print(h)
