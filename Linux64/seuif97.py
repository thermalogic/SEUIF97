# -*- coding: utf-8 -*- 

"""
This is a python api of shared linrary  for linux platform to

calculate the properties of water and steam

using the IAPWS-IF97 industry-standard steam properties correlations.

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2016.4.20

"""
from ctypes import c_int,c_double,cdll

# lib in locale path
# import os 
#flib= cdll.LoadLibrary(os.getcwd() + '/SEUIF97.so')

# lib in a default path of linux:    /usr/lib/
flib= cdll.LoadLibrary('seuif97.so')
    
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
