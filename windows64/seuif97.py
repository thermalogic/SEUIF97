# -*- coding: utf-8 -*- 

"""
This is a python api of SEUIF97  for windows platform

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2016.4.20

"""

from ctypes import c_int,c_double,WINFUNCTYPE,windll
prototype=WINFUNCTYPE(c_double,c_double,c_double,c_int)

def pt(p,t,w): 
    f=prototype(("seupt",windll.seuif97),)
    result=f(p,t,w)
    return result

def pt2h(p,t): 
    f=prototype(("seupt",windll.seuif97),)
    result=f(p,t,4)
    return result

def pt2s(p,t): 
    f=prototype(("seupt",windll.seuif97),)
    result=f(p,t,5)
    return result

def ph(p,h,w): 
    f=prototype(("seuph",windll.seuif97),)
    result=f(p,h,w)
    return result

def ph2t(p,h): 
    f=prototype(("seuph",windll.seuif97),)
    result=f(p,h,1)
    return result

def ph2s(p,h): 
    f=prototype(("seuph",windll.seuif97),)
    result=f(p,h,5)
    return result

def ps(p,s,w): 
    f=prototype(("seups",windll.seuif97),)
    result=f(p,s,w)
    return result

def ps2h(p,s): 
    f=prototype(("seups",windll.seuif97),)
    result=f(p,s,4)
    return result

def ps2t(p,s): 
    f=prototype(("seups",windll.seuif97),)
    result=f(p,s,1)
    return result

def hs(h,s,w): 
    f=prototype(("seuhs",windll.seuif97),)
    result=f(h,s,w)
    return result

def hs2t(h,s): 
    f=prototype(("seuhs",windll.seuif97),)
    result=f(h,s,0)
    return result

def pv(p,v,w): 
    f=prototype(("seupv",windll.seuif97),)
    result=f(p,v,w)
    return result

def px(p,x,w): 
    f=prototype(("seupx",windll.seuif97),)
    result=f(p,x,w)
    return result

def px2t(p,x): 
    result=px(p,x,1)
    return result

def px2v(p,x): 
    result=px(p,x,3)
    return result

def px2s(p,x): 
    result=px(p,x,5)
    return result

def px2h(p,x): 
    result=px(p,x,4)
    return result

def tx(t,x,w): 
    f=prototype(("seutx",windll.seuif97),)
    result=f(t,x,w)
    return result

def tx2p(t,x): 
    result=tx(t,x,0)
    return result

def tx2v(t,x): 
    result=tx(t,x,3)
    return result

def tx2s(t,x): 
    result=tx(t,x,5)
    return result

def tx2h(t,x): 
    result=tx(t,x,4)
    return result


def th(t,h,w): 
    f=prototype(("seuth",windll.seuif97),)
    result=f(t,h,w)
    return result


def th2p(t,h): 
    f=prototype(("seuth",windll.seuif97),)
    result=f(t,h,0)
    return result

def th2s(t,h,w): 
    f=prototype(("seuth",windll.seuif97),)
    result=f(t,h,5)
    return result

def ts(t,s,w): 
    f=prototype(("seuts",windll.seuif97),)
    result=f(t,s,w)
    return result

def ts2h(t,s): 
    f=prototype(("seuts",windll.seuif97),)
    result=f(t,s,4)
    return result

def ts2p(t,s): 
    f=prototype(("seuts",windll.seuif97),)
    result=f(t,s,0)
    return result

def tv(t,v,w): 
    f=prototype(("seutv",windll.seuif97),)
    result=f(t,v,w)
    return result

def ishd(p1,t1,p2):
    ishdprototype=WINFUNCTYPE(c_double,c_double,c_double,c_double)
    f=ishdprototype(("seuishd",windll.seuif97),)
    result=f(p1,t1,p2)
    return result

def ief(p1,t1,p2,t2):
    iefprototype=WINFUNCTYPE(c_double,c_double,c_double,c_double,c_double)
    f=iefprototype(("seuief",windll.seuif97),)
    result=f(p1,t1,p2,t2)
    return result

