# -*- coding: utf-8 -*-

"""
seuif97

The package is the Python API of the high-speed IAPWS-IF97 shared library 

The Functions for Properties :the input pairs are implemented: 

   (p,t),(p,h),(p,s),(p,v)  (t,h),(t,s),(t,v)  (h,s)  (p,x),(t,x)

Two types of functions : ??2?(in1,in2) and ??(in1,in2,outid)

The Functions for the Thermodynamic Process of Steam Turbine

  Isentropic Enthalpy Drop :  ishd(pi,ti,po)
  Isentropic Efficiency(0~100)： ef(pi,ti,po,to)

Author: Cheng Maohua
Email: cmh@seu.edu.cn

"""
from ctypes import *
from platform import *

cdll_names = {'Linux': 'libseuif97.so',
              'Windows': 'libseuif97.dll'}
seuif97path = os.path.abspath(os.path.dirname(__file__))

osplat = system()
if (osplat == 'Linux'):
    flib = cdll.LoadLibrary(seuif97path+'/'+cdll_names[osplat])
    prototype = CFUNCTYPE(c_double, c_double, c_double, c_int)
elif (osplat == 'Windows'):
    flib = windll.LoadLibrary(seuif97path+'\\'+cdll_names[osplat])
    prototype = WINFUNCTYPE(c_double, c_double, c_double, c_int)

# ---(p,t) ----------------


def pt(p, t, pid):
    f = prototype(("seupt", flib),)
    result = f(p, t, pid)
    return result


def pt2h(p, t):
    f = prototype(("seupt", flib),)
    result = f(p, t, 4)
    return result


def pt2s(p, t):
    f = prototype(("seupt", flib),)
    result = f(p, t, 5)
    return result


def pt2v(p, t):
    f = prototype(("seupt", flib),)
    result = f(p, t, 3)
    return result


def pt2x(p, t):
    f = prototype(("seupt", flib),)
    result = f(p, t, 15)
    return result

# --- (p,h) -------------------


def ph(p, h, pid):
    f = prototype(("seuph", flib),)
    result = f(p, h, pid)
    return result


def ph2s(p, h):
    f = prototype(("seuph", flib),)
    result = f(p, h, 5)
    return result


def ph2v(p, h):
    f = prototype(("seuph", flib),)
    result = f(p, h, 3)
    return result


def ph2t(p, h):
    f = prototype(("seuph", flib),)
    result = f(p, h, 1)
    return result


def ph2x(p, h):
    f = prototype(("seuph", flib),)
    result = f(p, h, 15)
    return result

# ---- (p,s) --------------------


def ps(p, s, pid):
    f = prototype(("seups", flib),)
    result = f(p, s, pid)
    return result


def ps2t(p, s):
    f = prototype(("seups", flib),)
    result = f(p, s, 1)
    return result


def ps2h(p, s):
    f = prototype(("seups", flib),)
    result = f(p, s, 4)
    return result


def ps2v(p, s):
    f = prototype(("seups", flib),)
    result = f(p, s, 3)
    return result


def ps2x(p, s):
    f = prototype(("seups", flib),)
    result = f(p, s, 15)
    return result

# ---- (h,s)--------------


def hs(h, s, pid):
    f = prototype(("seuhs", flib),)
    result = f(h, s, pid)
    return result


def hs2t(h, s):
    f = prototype(("seuhs", flib),)
    result = f(h, s, 1)
    return result


def hs2p(h, s):
    f = prototype(("seuhs", flib),)
    result = f(h, s, 0)
    return result


def hs2v(h, s):
    f = prototype(("seuhs", flib),)
    result = f(h, s, 3)
    return result


def hs2x(h, s):
    f = prototype(("seuhs", flib),)
    result = f(h, s, 15)
    return result

# --- (t,s) -----


def ts(t, s, pid):
    f = prototype(("seuts", flib),)
    result = f(t, s, pid)
    return result


def ts2p(t, s):
    f = prototype(("seuts", flib),)
    result = f(t, s, 0)
    return result


def ts2v(t, s):
    f = prototype(("seuts", flib),)
    result = f(t, s, 3)
    return result


def ts2h(t, s):
    f = prototype(("seuts", flib),)
    result = f(t, s, 4)
    return result


def ts2x(t, s):
    f = prototype(("seuts", flib),)
    result = f(t, s, 15)
    return result


# --- (t,v) -----


def tv(t, v, pid):
    f = prototype(("seutv", flib),)
    result = f(t, v, pid)
    return result


def tv2p(t, v):
    f = prototype(("seutv", flib),)
    result = f(t, v, 0)
    return result


def tv2s(t, v):
    f = prototype(("seutv", flib),)
    result = f(t, v, 5)
    return result


def tv2h(t, v):
    f = prototype(("seutv", flib),)
    result = f(t, v, 4)
    return result


def tv2x(t, v):
    f = prototype(("seutv", flib),)
    result = f(t, v, 15)
    return result

# --- (p,x) -------------------


def px(p, x, pid):
    f = prototype(("seupx", flib),)
    result = f(p, x, pid)
    return result


def px2t(p, x):
    f = prototype(("seupx", flib),)
    result = f(p, x, 1)
    return result


def px2h(p, x):
    f = prototype(("seupx", flib),)
    result = f(p, x, 4)
    return result


def px2s(p, x):
    f = prototype(("seupx", flib),)
    result = f(p, x, 5)
    return result


def px2v(p, x):
    f = prototype(("seupx", flib),)
    result = f(p, x, 3)
    return result

# --- (t,x) ------------


def tx(t, x, pid):
    f = prototype(("seutx", flib),)
    result = f(t, x, pid)
    return result


def tx2p(t, x):
    f = prototype(("seutx", flib),)
    result = f(t, x, 0)
    return result


def tx2v(t, x):
    f = prototype(("seutx", flib),)
    result = f(t, x, 3)
    return result


def tx2h(t, x):
    f = prototype(("seutx", flib),)
    result = f(t, x, 4)
    return result


def tx2s(t, x):
    f = prototype(("seutx", flib),)
    result = f(t, x, 5)
    return result

# ---------- steam turbine processing ------------


def ishd(p1, t1, p2):
    f = flib.seuishd
    f.argtypes = [c_double, c_double, c_double]
    f.restype = c_double
    result = f(p1, t1, p2)
    return result


def ief(p1, t1, p2, t2):
    f = flib.seuief
    f.argtypes = [c_double, c_double, c_double, c_double]
    f.restype = c_double
    result = f(p1, t1, p2, t2)
    return result
