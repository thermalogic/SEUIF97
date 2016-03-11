# -*- coding: utf-8 -*- 

from ctypes import *
import os 
# 参数为生成的.so文件所在的绝对路径
flib= cdll.LoadLibrary(os.getcwd() + '/SEUIF97.so')
    
def pt2h(p,t): 
    f=flib.seupt
    f.argtypes = [c_double,c_double,c_int]
    f.restype = c_double 
    result=f(p,t,4)
    return result

def pt2s(p,t): 
    f=flib.seupt
    f.argtypes = [c_double,c_double,c_int]
    f.restype = c_double 
    result=f(p,t,5)
    return result

def ph2s(p,h): 
    f=flib.seuph
    f.argtypes = [c_double,c_double,c_int]
    f.restype = c_double 
    result=f(p,h,4)
    return result

def ps2h(p,s): 
    f=flib.seups
    f.argtypes = [c_double,c_double,c_int]
    f.restype = c_double 
    result=f(p,s,4)
    return result


def ts2h(t,s): 
    f=flib.seuts
    f.argtypes = [c_double,c_double,c_int]
    f.restype = c_double 
    result=f(t,s,4)
    return result

def ishd(p1,t1,p2): 
    f=flib.seuishd
    f.argtypes = [c_double,c_double,c_double]
    f.restype = c_double 
    result=f(p1,t1,p2)
    return result

def ief(p1,t1,p2,t2): 
    f=flib.seuief
    f.argtypes = [c_double,c_double,c_double,c_double]
    f.restype = c_double 
    result=f(p1,t1,p2,t2)
    return result

h=pt2h(16.1,535.2)
print(h)
