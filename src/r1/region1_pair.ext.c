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
#include "region1.h"
#include "region1_coff.h"
#include "region1_solo_ij.h"
#include "../r4/region4.h"

// Region 1  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg1(double p, double v)
{
    double T1, T2, f1, f, v1, v2, T;
    T1 = TMIN1;
    v1 = pT2v_reg1(p, T1);
    if ((p >= 16.5291643) && (p <= 100.0))
    {
        T2 = TMAX1;
    }
    else
    {
        T2 = TSat(p);
    };
    v2 = pT2v_reg1(p, T2);
    f = v - pT2v_reg1(p, T2);
    if ((v2 - v1) != 0.0)
    {
        T1 = T1 + (T2 - T1) * (v - v1) / (v2 - v1);
    }
    f1 = v - pT2v_reg1(p, T1);
    T = rtsec2(pT2v_reg1, p, v, T1, T2, f1, f, xacc, iMAX);
    if (T >= 300)
        if (fabs(f1) < xacc)
            return (T1);

    f = v - pT2v_reg1(p, T);
    if (fabs(f) > xacc)
    {
        int success = 0;
        int sum = 0;
        T1 = T;
        f1 = f;
        if (f < 0) // t大了
        {
            while (!success)
            {
                T1 -= 0.1;
                if (T1 < 273.15)
                {
                    T = 273.15;
                    break;
                };
                f1 = v - pT2v_reg1(p, T1);
                if (fabs(f1) < fabs(f))
                {
                    f = f1;
                    T = T1;
                }
                if (fabs(f1) < xacc)
                {
                    T = T1;
                    break;
                }
                sum += 1;
                if (sum > 10000)
                    success = 1;
            };
        }
        else
        {
            while (!success)
            {
                T1 += 0.1;
                if (T1 > 623.15)
                {
                    T = 623.15;
                    break;
                };
                f1 = v - pT2v_reg1(p, T1);
                if (fabs(f1) < fabs(f))
                {
                    f = f1;
                    T = T1;
                }
                if (100 * fabs(f1) < xacc)
                {
                    T = T1;
                    break;
                }
                sum += 1;
                if (sum > 10000)
                {
                    success = 1;
                }
            }
        }
    };
    // 1 在低温区，v变化很小，
    // 2 在低温，低压区，v变化很小，同时变化规律发生反方向变化， T加，v减
    if (T < 290)
    {
    };
    if (T < TMIN1)
    {
        T = TMIN1;
    }
    else
    {
        if (T > TMAX1)
        {
            T = TMAX1;
        };
    };
    return (T);
}

// Region 1  (T,v)->p using the secant method
//  T: temperature  K
//  v: specific volume m^3/kg
//  p: pressure  MPa
double Tv2p_reg1(double T, double v)
{
    double p1 = 0.3 * (pSat(T) + PMAX1);
    double p2 = 1.05 * p1;
    double f1 = v - pT2v_reg1(p1, T);
    double f = v - pT2v_reg1(p2, T);
    double p = rtsec1(pT2v_reg1, T, v, p1, p2, f1, f, xacc, iMAX);
    return p;
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg1(double T, double s)
{
    double tau, p, p1, p2, pmin1, s1, s2, f1, f2;
    pmin1 = pSat(T);
    p1 = pmin1;
    s1 = pT2s_reg1(p1, T);
    f1 = s - s1;
    p2 = PMAX1;
    s2 = pT2s_reg1(p2, T);
    f2 = s - s2;
    p1 = p2 - (p2 - p1) * (s - s2) / (s1 - s2);
    if (p1 < pmin1)
        p1 = pmin1;
    s1 = pT2s_reg1(p1, T);
    f1 = s - s1;
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2s_reg1, T, s, p1, p2, f1, f2, xacc, iMAX);
    if (p > PMAX1)
        p = PMAX1;
    if (p < pmin1)
        p = pmin1;
    return (p);
}

// Region 1  (T,h)->p using the secant method
//  *  T: temperature  K
//  *  h: specific enthalpy kJ/kg
//  *  p: pressure  MPa
double Th2p_reg1(double T, double h)
{
    double pmin1 = pSat(T);
    double p1 = pmin1;
    double p2 = PMAX1; // p1 + stepa
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

    double f1 = h - pT2h_reg1(p1, T);
    double f = h - pT2h_reg1(p2, T);
    double p = rtsec1(pT2h_reg1, T, h, p1, p2, f1, f, xacc, iMAX);

    if (p > PMAX1)
    {
        p = PMAX1;
    }
    if (p < pmin1)
    {
        p = pmin1;
    }
    return p;
}
