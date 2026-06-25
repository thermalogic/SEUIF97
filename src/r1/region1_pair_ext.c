/**
 * @file region1_pair_ext.c
 * @brief Extended pairs for Region 1
 * 
 * The extended pairs
 *   (p,v)->T
 *   (T,v)->p  (T,h)->p  (T,s)->p
 *
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */
#include <math.h>
#include <stdint.h>
#include "../common/constant.h"
#include "../algo/algorithm.h"
#include "region1.h"
#include "../r4/region4.h"

#include "../algo/algorithm.h"
#include "region1.h"
#include "../r4/region4.h"

// Region 1  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg1(double p, double v)
{
    double T1 = TMIN1;
    double T2 = ((p >= 16.5291643) && (p <= 100.0)) ? TMAX1 : TSat(p);
    return bisection(T1, T2, pT2v_reg1, p, v, 1,iMAX, 1.0e-10, 1.0e-6);   
}

// Region 1  (T,v)->p using the secant method
//  T: temperature  K
//  v: specific volume m^3/kg
//  p: pressure  MPa
double Tv2p_reg1(double T, double v)
{
    double p1 = 0.3 * (pSat(T) + PMAX1);
    double p2 = 1.05 * p1;
    return rtsec(pT2v_reg1, T, v, p1, p2, 2, xacc, iMAX);
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg1(double T, double s)
{
    double p1 = pSat(T);
    double p2 = PMAX1;
    return bisection(p1, p2, pT2s_reg1, T, s, 2,iMAX, 1.0e-10, 1.0e-6); 
 }

// Region 1  (T,h)->p using the secant method
//  *  T: temperature  K
//  *  h: specific enthalpy kJ/kg
//  *  p: pressure  MPa
double Th2p_reg1(double T, double h)
{
    double pmin1 = pSat(T);
    double p1 = pmin1;
    double p2 = PMAX1; 
    double h1 = pT2h_reg1(p1, T);
    if (fabs(h - h1) < xacc)
    {
        return p1;
    };
    double h2 = pT2h_reg1(p2, T);
    if (fabs(h - h2) < xacc)
    {
        return p2;
    }
    double p = rtsec(pT2h_reg1, T, h, p1, p2, 2, xacc, iMAX);
   if (p > PMAX1)
    {
        p = PMAX1;
    }
    else if (p < pmin1)
    {
        p = pmin1;
    }
    return p;
}