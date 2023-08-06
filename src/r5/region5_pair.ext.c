/*
 The extended pairs
   (p,v)->T
   (T,v)->p  (T,h)->p  (T,s)->p
*/
#include <math.h>
#include <stdint.h>
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region5.h"
#include "region5_coff.h"

// Region 5  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg5(double p, double v)
{
    double T1, T2, f1, f, v1, v2, T;
    T1 = TMIN5;
    v1 = pT2v_reg5(p, T1);
    T2 = TMAX5;
    v2 = pT2v_reg5(p, T2);
    f = v - pT2v_reg5(p, T2);
    if ((v2 - v1) != 0.0)
    {
        T1 = T1 + (T2 - T1) * (v - v1) / (v2 - v1);
    }
    f1 = v - pT2v_reg5(p, T1);
    T = rtsec2(pT2v_reg5, p, v, T1, T2, f1, f, xacc, iMAX);
    if (T < TMIN5)
    {
        T = TMIN5;
    }
    else
    {
        if (T > TMAX5)
        {
            T = TMAX5;
        };
    };
    return (T);
}

// Region 5 (T,v)->p using the secant method
//  T: temperature  K
//  v: specific volume m^3/kg
//  p: pressure  MPa
double Tv2p_reg5(double T, double v)
{
    double p, p1, p2, v1, v2, f1, f2;
    int vbounded = 0;
    p1 = PMIN5; //
    v1 = pT2v_reg5(p1, T);
    if (v == v1)
        return (p1);
    p2 = 10 * p1;
    v2 = pT2v_reg5(p2, T);
    if (v == v2)
        return (p2);
    if ((v > v2) && (v < v1))
        vbounded = 1;
    while (vbounded == 0)
    {
        p1 = p2;
        v1 = v2;
        p2 = 5 * p1;
        if (p2 >= PMAX5)
        {
            p2 = PMAX5;
            vbounded = 1;
        }
        v2 = pT2v_reg5(p2, T);
        if (v == v2)
            return (p2);
        if ((v > v2) && (v < v1))
            vbounded = 1;
    }
    f2 = v - v2;
    p1 = p2 - (p2 - p1) * (v - v2) / (v1 - v2);
    if (p1 < PMIN5)
        p1 = PMIN5;
    f1 = v - pT2v_reg5(p1, T);
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2v_reg5, T, v, p1, p2, f1, f2, xacc, iMAX);
    if (p > PMAX5)
        p = PMAX5;
    if (p < PMIN5)
        p = PMIN5;
    return (p);
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg5(double T, double s)
{
    double p, p1, p2, s1, s2, f1, f2;
    p1 = PMIN5; //
    s1 == pT2s_reg5(p1, T);
    f1 = s - s1;
    p2 = PMAX5;
    s2 = pT2s_reg5(p2, T);
    f2 = s - s2;
    p1 = p2 - (p2 - p1) * (s - s2) / (s1 - s2);
    if (p1 < PMIN5)
        p1 = PMIN5;
    s1 = pT2s_reg5(p1, T);
    f1 = s - s1;
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2s_reg5, T, s, p1, p2, f1, f2, xacc, iMAX);
    if (p > PMAX5)
        p = PMAX5;
    if (p < PMIN5)
        p = PMIN5;
    return (p);
}

// Region 5 (T,h)->p using the secant method
//  *  T: temperature  K
//  *  h: specific enthalpy kJ/kg
//  *  p: pressure  MPa
double Th2p_reg5(double T, double h)
{
    double p, p1, p2, h1, h2, f1, f2;
    p1 = PMIN5;
    h1 = pT2h_reg5(p1, T);
    p2 = PMAX5; //
    h2 = pT2h_reg5(p2, T);
    f2 = h - h2;
    p1 = p2 - (p2 - p1) * fabs(h - h2) / (h1 - h2);
    f1 = h - pT2h_reg5(p1, T);
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2h_reg5, T, h, p1, p2, f1, f2, xacc, iMAX);
    if (p > PMAX5)
        p = PMAX5;
    if (p < PMIN5)
        p = PMIN5;
    return (p);
}
