
# -*- coding: utf-8 -*-

from ctypes import *
import os
# 参数为生成的.so文件所在的绝对路径
flib = cdll.LoadLibrary(os.getcwd() + '/libseuif97.so')


def pt2h(p, t):
    f = flib.seupt
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, t, 4)
    return result


def pt2s(p, t):
    f = flib.seupt
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, t, 5)
    return result


def ph2s(p, h):
    f = flib.seuph
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, h, 5)
    return result


def ph2t(p, h):
    f = flib.seuph
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, h, 1)
    return result

def ps2t(p, s):
    f = flib.seups
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, s, 1)
    return result

def ps2h(p, s):
    f = flib.seups
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, s, 4)
    return result

def ps2v(p, s):
    f = flib.seups
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, s, 3)
    return result

def ps2x(p, s):
    f = flib.seups
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, s, 15)
    return result


def hs2t(h, s):
    f = flib.seuhs
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(h, s, 1)
    return result

def hs2p(h, s):
    f = flib.seuhs
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(h, s, 0)
    return result

def hs2v(h, s):
    f = flib.seuhs
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(h, s, 3)
    return result

def hs2x(h, s):
    f = flib.seuhs
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(h, s, 15)
    return result

def px2t(p, x):
    f = flib.seupx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, x, 1)
    return result

def px2h(p, x):
    f = flib.seupx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, x, 4)
    return result

def px2s(p, x):
    f = flib.seupx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, x, 5)
    return result

def px2v(p, x):
    f = flib.seupx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(p, x, 3)
    return result

def tx2p(t, x):
    f = flib.seutx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(t, x, 0)
    return result

def tx2v(t, x):
    f = flib.seutx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(t, x, 3)
    return result

def tx2h(t, x):
    f = flib.seutx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(t, x, 4)
    return result


def tx2s(t, x):
    f = flib.seutx
    f.argtypes = [c_double, c_double, c_int]
    f.restype = c_double
    result = f(t, x, 5)
    return result


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
