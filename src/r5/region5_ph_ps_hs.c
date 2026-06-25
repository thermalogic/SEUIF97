/**
 * @file region5_ph_ps_hs.c
 * @brief Property pair calculations for (p,h), (p,s), and (h,s) in Region 5
 *
 * This file implements property pair calculations for (p,h), (p,s), and (h,s)
 * in Region 5.
 *
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */
#include <math.h>
#include "region5.h"
#include "../algo/algorithm.h"
#include "../common/constant.h"

double ph2T_reg5(double p, double h)
{
   double T, T1, T2, f;
   // Method to find initial value for iteration using interpolation
   double hmin = pT2h_reg5(p, TMIN5);
   double hmax = pT2h_reg5(p, TMAX5);
   T1 = 1073.15 + (2273.15 - 1073.15) * (h - hmin) / (hmax - hmin);
   f = h - pT2h_reg5(p, T1);
   if (fabs(f) > xacc)
   {
      if (f > 0)
         T2 = TMAX5;
      else
         T2 = TMIN5;
      T = rtsec(pT2h_reg5, p, h, T1, T2, 1, xacc, iMAX);
   }
   else
      T = T1;
   if (T < TMIN5)
      T = TMIN5;
   else if (T > TMAX5)
      T = TMAX5;
   return (T);
}

double ps2T_reg5(double p, double s)
{
   double T, T1, T2, f;
   // Method to find initial value for iteration using interpolation
   double smin = pT2s_reg5(p, TMIN5);
   double smax = pT2s_reg5(p, TMAX5);
   T1 = 1073.15 + (2273.15 - 1073.15) * (s - smin) / (smax - smin);
   f = s - pT2s_reg5(p, T1);
   if (fabs(f) > xacc)
   {
      if (f > 0)
         T2 = TMAX5;
      else
         T2 = TMIN5;
      T = rtsec(pT2s_reg5, p, s, T1, T2, 1, xacc, iMAX);
   }
   else
      T = T1;
   if (T < TMIN5)
      T = TMIN5;
   else if (T > TMAX5)
      T = TMAX5;
   return T;
}

// helper for hs2preg5
double ph2s_reg5(double p, double h)
{
   double T = ph2T_reg5(p, h);
   double s = pT2s_reg5(p, T);
   return s;
}

double hs2p_reg5(double h, double s)
{
   double p, p1, p2, f;
   // Initial value for iteration
   double hmin = pT2h_reg5(PMIN5, TMIN5);
   double hmax = pT2h_reg5(PMAX5, TMAX5);
   p1 = PMIN5 + (PMAX5 - PMIN5) * (h - hmin) / (hmax - hmin);
   f = s - ph2s_reg5(p1, h);
   if (fabs(f) > xacc)
   {
      if (f > 0)
         p2 = PMAX5;
      else
         p2 = PMIN5;
      p = rtsec(ph2s_reg5, h, s, p1, p2, 2, xacc, iMAX);
   }
   else
      p = p1;
   return (p);
}