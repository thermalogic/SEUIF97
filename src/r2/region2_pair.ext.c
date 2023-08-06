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
#include "region2.h"
#include "region2_coff.h"
#include "region2_solo_ij.h"
#include "../r4/region4.h"

/// the helper for the extended input pair
double p2Tmin_reg2(double p)
{
    double Tmin = TMIN2;
    if (p > 0.0 && p < 0.000611213)
    {
        Tmin = TMIN2;
    }
    else
    {
        if (p >= 0.000611213 && p <= pSat(623.15))
        {
            Tmin = TSat(p);
        }
        else
        {
            Tmin = B23_p2T(p);
        }
    }
    return Tmin;
}

double T2pmax_reg2(double T)
{
    double pmax = PMAX2;
    if (T >= 273.15 && T <= 623.15)
    {
        pmax = pSat(T);
    }
    else
    {
        if (T > 623.15 && T <= 863.15)
        {
            pmax = B23_T2p(T);
        }
        else
        {
            if (T > 863.15 && T <= 1073.15)
            {
                pmax = 100.0;
            };
        };
    };
    return pmax;
}

// Region 2  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg2(double p, double v)
{
    double T1, T2, f1, f, v1, v2, T;
    double Tmin2 = p2Tmin_reg2(p);
    T1 = Tmin2;
    v1 = pT2v_reg2(p, T1);
    f1 = v - v1;
    T2 = TMAX2;
    T2 = 1.1 * T1; // fast
    v2 = pT2v_reg2(p, T2);
    f = v - v2;
    T1 = T1 + (T2 - T1) * fabs(v - v1) / (v2 - v1);
    v1 = pT2v_reg2(p, T1);
    f1 = v - v1;
    if (fabs(f1) < xacc)
        return (T1);
    T = rtsec2(pT2v_reg2, p, v, T1, T2, f1, f, xacc, iMAX);
    if (T < Tmin2)
        T = Tmin2;
    if (T > TMAX2)
        T = TMAX2;

    // zoom
    double v0 = pT2v_reg2(p, T);
    int i = 0;
    int success = 1;
    if (fabs(v0 - v) > xacc)
        success = 0;
    while (success == 0)
    {
        if (v0 > v)
        {
            i += 1;
            T = T - 0.001;
            if (T < Tmin2)
                v0 = pT2v_reg2(p, T);
        }
        else
        {
            i += 1;
            T = T + 0.001;
            if (T > TMAX2)
                v0 = pT2v_reg2(p, T);
        }
        if (i < 1000)
            success = 1;
    }
    return (T);
}

// Region 2(T,v)->p using the secant method
//  T: temperature  K
//  v: specific volume m^3/kg
//  p: pressure  MPa
double Tv2p_reg2(double T, double v)
{
    double pmax2, p, p1, p2, pmid, v1, v2, f1, f2, stepa, stepm;
    int bounded = 0;
    p1 = PMIN2;
    pmax2 = T2pmax_reg2(T);
    stepa = 1.0;
    stepm = 5.0;
    v1 = pT2v_reg2(p1, T);
    if (fabs(v - v1) < xacc)
        return (p1);
    p2 = p1 * stepm;
    v2 = pT2v_reg2(p2, T);
    if (fabs(v - v2) < xacc)
        return (p2);
    if ((v > v2) && (v < v1))
        bounded = 1;
    while (bounded == 0)
    {
        p1 = p2;
        v1 = v2;
        if (p1 > 1.0)
            p2 = p1 + stepa;
        if (p1 < 1.0)
            p2 = p1 * stepm;
        if (p2 >= pmax2)
        {
            p2 = pmax2;
            bounded = 1;
        }
        v2 = pT2v_reg2(p2, T);
        if (fabs(v - v2) < xacc)
            return (p2);
        if ((v > v2) && (v < v1))
            bounded = 1;
    }
    f2 = v - v2;
    pmid = p2 - (p2 - p1) * (v - v2) / (v1 - v2);
    if (v < pT2v_reg2(pmid, T))
        p1 = pmid;
    if (p1 < PMIN2)
        p1 = PMIN2;
    f1 = v - pT2v_reg2(p1, T);
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2v_reg2, T, v, p1, p2, f1, f2, xacc, iMAX);
    if (p < PMIN2)
        p = PMIN2;
    if (p > pmax2)
        p = pmax2;
    return (p);
}

//----------------------------------------------
//      (T,s)->p
//----------------------------------------------
double Ts2p_reg2(double T, double s)
{
    double p, p1, p2, pmax2, f1, f2, s1, s2;
    p1 = PMIN2;
    s1 = pT2s_reg2(p1, T);
    f1 = s - s1;
    pmax2 = T2pmax_reg2(T);
    p2 = pmax2;
    s2 = pT2s_reg2(p2, T);
    f2 = s - s2;
    p1 = p2 - (p2 - p1) * (s - s2) / (s1 - s2);
    if (p1 < PMIN2)
        p1 = PMIN2;
    s1 = pT2s_reg2(p1, T);
    f1 = s - s1;
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2s_reg2, T,s, p1, p2, f1, f2, xacc, iMAX);
    if (p < PMIN2)
        p = PMIN2;
    if (p > pmax2)
        p = pmax2;
    return (p);
}

// Region 2(T,h)->p using the secant method
//  *  T: temperature  K
//  *  h: specific enthalpy kJ/kg
//  *  p: pressure  MPa
double Th2p_reg2(double T, double h)
{
    double p, p1, p2, pmax2, pmid, stepa, stepm, f1, f2, h1, h2;
    int bounded = 0;

    p1 = PMIN2; // 0.0001;
    pmax2 = T2pmax_reg2(T);
    p2 = pmax2;
    stepa = 1;
    stepm = 5.0;
    h1 = pT2h_reg2(p1, T);
    if (fabs(h - h1) < xacc)
        return (p1);
    p2 = p1 * stepm;
    h2 = pT2h_reg2(p2, T);
    if (fabs(h - h2) < xacc)
        return (p2);
    if ((h > h2) && (h < h1))
        bounded = 1;
    while (bounded == 0)
    {
        p1 = p2;
        h1 = h2;
        if (p1 > 1)
            p2 = p1 + stepa;
        if (p1 < 1)
            p2 = p1 * stepm;
        if (p2 >= pmax2)
        {
            p2 = pmax2;
            bounded = 1;
        }
        h2 = pT2h_reg2(p2, T);
        if (fabs(h - h2) < xacc)
            return (p2);
        if ((h > h2) && (h < h1))
            bounded = 1;
    }
    f2 = h - h2;
    pmid = p2 - (p2 - p1) * (h - h2) / (h1 - h2);
    if (pmid < PMIN2)
    {
        pmid = PMIN2;
    };
    h1 = pT2h_reg2(pmid, T);
    if (h < pT2h_reg2(pmid, T))
        p1 = pmid;
    h1 = pT2h_reg2(p1, T);
    f1 = h - h1;
    if (fabs(f1) < xacc)
        return (p1);
    p = rtsec1(pT2h_reg2, T, h, p1, p2, f1, f2, xacc, iMAX);
    if (p < PMIN2)
        p = PMIN2;
    if (p > pmax2)
        p = pmax2;
    return (p);
}
