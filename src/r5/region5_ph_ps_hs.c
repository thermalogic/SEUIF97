/*---------------------------------------------------------------------------

 Region 5: (p,h) (p,s) (h,s)
---------------------------------------------------------------------------*/
#include <math.h>
#include "region5.h"
#include "../r2/region2.h"
#include "../algo/algorithm.h"

static double TMAX5 = 2273.15;
static double TMIN5 = 1073.15;

static double PMAX5 = 50;
static double PMIN5 = 0.000611212677444;

double ph2T_reg5(double p, double h)
{
   double T, T1, T2;
   double f1, f2;

   // TODO:  插值求迭代初值方法
   //double  hmin =pT2hreg2(p,1073.15);
   //double  hmax = pT2h_reg5(p,2273.15);
   //T1=1073.15+(2273.15-1073.15)*(h-hmin)/(hmax-hmin);
   //  求迭代初值方法2： 以三相点为起点,采用与理想气体的对比关系求迭代初值

   T = -1000;

   T1 = 0.5 * (2273.15 + 1073.15);

   f1 = h - pT2h_reg5(p, T1);
   if (fabs(f1) > xacc)
   {
      if (f1 > 0)
         T2 = (1.0 + f1 / h) * T1;
      else
         T2 = (1.0 - f1 / h) * T1;

      f2 = h - pT2h_reg5(p, T2);

      T = rtsec2(pT2h_reg5, p, h, T1, T2, f1, f2, xacc, iMAX);
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
   double T, T1, T2, f1, f;
   //RODO: 插值求迭代初值方法1
   //double  smin =pT2sreg2(p,1073.15);
   //double  smax = pT2s_reg5(p,2273.15);
   //T1=1073.15+(2273.15-1073.15)*(s-smin)/(smax-smin);

   T = -1000;

   T1 = 0.5 * (2273.15 + 1073.15); // ,Get initial value

   f1 = s - pT2s_reg5(p, T1);

   if (fabs(f1) > xacc)
   {
      if (f1 > 0)
         T2 = (1.0 + f1 / s) * T1;
      else
         T2 = (1.0 - f1 / s) * T1;

      f = s - pT2s_reg5(p, T2);
      T = rtsec2(pT2s_reg5, p, s, T1, T2, f1, f, xacc, iMAX);
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
   double p, p1, p2, f1, f2;

   // TODO:  迭代初始值，可测试那个更好?
   // 也可以计算smin,smax,2元插值得到更接近的p1

   // 测试表明：更复杂的方法计算迭代初始数值并不更好
   //double  hmin =pT2h_reg5(PMIN5,1073.15);
   //double  hmax =pT2h_reg5(PMAX5,2273.15);
   //p1=PMIN5+(PMAX5-PMIN5)*(h-hmin)/(hmax-hmin);

   p1 = 0.5 * (PMIN5 + PMAX5);

   f1 = s - ph2s_reg5(p1, h);

   if (fabs(f1) > xacc)
   {
      if (f1 > 0)
         p2 = (1.0 + f1 / s) * p1;
      else
         p2 = (1.0 - f1 / s) * p1;

      f2 = s - ph2s_reg5(p2, h);

      p = rtsec1(ph2s_reg5, h, s, p1, p2, f1, f2, xacc, iMAX);
   }
   else
      p = p1;

   return (p);
}
