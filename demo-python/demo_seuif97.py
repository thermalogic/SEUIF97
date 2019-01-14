
"""
The Simple example of seuif97.py

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2018.11.28

"""
import seuif97

p = 16.10
t = 535.10
# type 1 : ??2?(in1,in2)
h = seuif97.pt2h(p, t)
s = seuif97.pt2s(p, t)
v = seuif97.pt2v(p, t)

print("(p,t),h,s,v:",
      "{:>.2f} \t {:>.2f} \t {:>.2f} \t {:>.3f} \t {:>.4f}".format(p, t, h, s, v))

# type 2: ??(in1,in2,outid)
t = seuif97.ph(p, h, 1)
s = seuif97.ph(p, h, 5)
v = seuif97.ph(p, h, 3)

print("(p,h),t,s,v:",
      "{:>.2f} \t {:>.2f} \t {:>.2f} \t {:>.3f} \t {:>.4f}".format(p, h, t, s, v))
