
"""
The Simple example of seuif97.py

  The input pairs implemented in  seuif97.py

    (p,t) (p,h) (p,s) (p,v)

    (t,h) (t,s) (t,v) 

    (h,s) 

    (p,x) (t,x) 

The types of functions: 
    
    1 ??2?(in1,in2) , e.g: h=pt2h(p,t)
    2 ??(in1,in2,propertyID),  , e.g: h=pt(p,t,4),  the propertyID h is 4
     
License: this code is in the public domain

Author: Cheng Maohua(cmh@seu.edu.cn)

Last modified: 2018.11.28

"""
import seuif97

p, t = 16.10, 535.10

# ??2?(in1,in2)
h = seuif97.pt2h(p, t)
s = seuif97.pt2s(p, t)
v = seuif97.pt2v(p, t)

print("(p,t),h,s,v:",
      "{:>.2f}\t {:>.2f}\t {:>.2f}\t {:>.3f}\t {:>.4f}".format(p, t, h, s, v))

# ??(in1,in2,propertyid)
t = seuif97.ph(p, h, 1)
s = seuif97.ph(p, h, 5)
v = seuif97.ph(p, h, 3)

print("(p,h),t,s,v:",
      "{:>.2f}\t {:>.2f}\t {:>.2f}\t {:>.3f}\t {:>.4f}".format(p, h, t, s, v))
