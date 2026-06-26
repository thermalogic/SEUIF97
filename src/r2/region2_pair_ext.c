/**
 * @file region2_pair_ext.c
 * @brief Extended input pairs for Region 2
 * 
 * This file implements extended input pair calculations for Region 2:
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
#include "region2.h"
#include "../r4/region4.h"

/// the helper for the extended input pair
double p2Tmin_reg2(double p)
{
    double pSat623 = pSat(623.15);
    if (p >= 0.000611213 && p <= pSat623)
    {  return TSat(p);  }
    else if (p>pSat623 && p<=PMAX2) { return B23_p2T(p);  }
    return TMIN2; 
}

double T2pmax_reg2(double T)
{
    if (T >= 273.15 && T <= 623.15)
    {   return pSat(T); }
    else if (T > 623.15 && T <= 863.15)
    {  return B23_T2p(T);  }
    return PMAX2; 
}

// Region 2  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg2(double p, double v)
{
   double T1 = p2Tmin_reg2(p);
   double T2 = TMAX2;
   return bisection(pT2v_reg2, p, v,T1, T2, FIRST_FIXED, MAX_ITER, 1.0e-10, 1.0e-6);   
}

// Region 2(T,v)->p using the secant method
//  T: temperature  K
//  v: specific volume m^3/kg
//  p: pressure  MPa
double Tv2p_reg2(double T, double v)
{
   double p1 = PMIN2;
   double p2 = T2pmax_reg2(T);
   return bisection(pT2v_reg2, T, v,p1, p2, SECOND_FIXED, MAX_ITER, 1.0e-15, 1.0e-9);  
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg2(double T, double s)
{
    double p1 = PMIN2;
    double p2 = T2pmax_reg2(T);
    return bisection(pT2s_reg2, T, s,p1, p2,  SECOND_FIXED, MAX_ITER, 1.0e-10, 1.0e-9); 
}

// Region 2(T,h)->p using the secant method
//  *  T: temperature  K
//  *  h: specific enthalpy kJ/kg
//  *  p: pressure  MPa
double Th2p_reg2(double T, double h)
{
    double p1 = PMIN2;
    double p2 = T2pmax_reg2(T);
    return bisection(pT2h_reg2, T, h,p1, p2, SECOND_FIXED, MAX_ITER, 1.0e-10, 1.0e-9); 
}