
# -*- coding: utf-8 -*-

from ctypes import *
import os
# 参数为生成的.so文件所在的绝对路径
flib = cdll.LoadLibrary(os.getcwd() + '/seuif.so')


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
