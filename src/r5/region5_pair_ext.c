/**
 * @file region5_pair_ext.c
 * @brief Extended input pairs for Region 5
 * 
 * This file implements extended input pair calculations for Region 5:
 *    1. (p,v)->T
 *    2. (T,v)->p
 *    3. (T,h)->p
 *    4. (T,s)->p
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include <stdint.h>
#include "../common/constant.h"
#include "../algo/algorithm.h"
#include "region5.h"

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
    if ((v2 - v1) != 0.0)
    {
        T1 = T1 + (T2 - T1) * (v - v1) / (v2 - v1);
    }
    T = rtsec(pT2v_reg5, p, v, T1, T2, 1, xacc, iMAX);
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
   double p1 = PMIN5;
   double p2 = PMAX5;
   return bisection(p1, p2, pT2v_reg5, T, v,2, iMAX, 1.0e-15, 1.0e-9);  
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg5(double T, double s)
{
    double p, p1, p2, s1, s2, f1, f2;
    p1 = PMIN5; //
    s1 = pT2s_reg5(p1, T);
    p2 = PMAX5;
    s2 = pT2s_reg5(p2, T);
    p1 = p2 - (p2 - p1) * (s - s2) / (s1 - s2);
    if (p1 < PMIN5)
        p1 = PMIN5;
    s1 = pT2s_reg5(p1, T);
    p = rtsec(pT2s_reg5, T, s, p1, p2, 2, xacc, iMAX);
    if (p > PMAX5)
        p = PMAX5;
    else if (p < PMIN5)
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
    p1 = p2 - (p2 - p1) * fabs(h - h2) / (h1 - h2);
    p = rtsec(pT2h_reg5, T, h, p1, p2, 2, xacc, iMAX);
    if (p > PMAX5)
        p = PMAX5;
    else if (p < PMIN5)
        p = PMIN5;
    return (p);
}