/*
   The API of region 4

*/
#include <math.h>
#include "../common/common.h"
#include "../common/constand.h"
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r3/region3.h"
#include "region4.h"

// TODO(cmh@seu.edu.cn): testing
double p2SatWater(double p, int o_id)
{
   // include region 3
   double T, v, r;

   if (o_id == OP)
      return p;

   T = TSat(p);
   if (o_id == OT)
      return T;

   if (p >= Pmin && p <= Ps_623)
   {
      r = pT_reg1(p, T, o_id);
   }
   else
   {
      if (p == pc_water)
         v = 1.0 / 322.0;
      else
         v = pT2vSat_reg3(p, T, 0);

      if (o_id == OV)
         return v;
      if (o_id == OD)
         return (1.0 / v);

      r = Td_reg3(T, 1 / v, o_id);
   }
   return r;
};

double p2SatSteam(double p, int o_id)
{
   double T, v, r;
   if (o_id == OP)
      return p;

   T = TSat(p);
   if (o_id == OT)
      return T;

   if (p >= Pmin && p <= Ps_623)
   {
      r = pT_reg2(p, T, o_id);
   }
   else
   { // reg3d =ss
      if (p == pc_water)
         v = 1.0 / 322.0;
      else
         v = pT2vSat_reg3(p, T, 1);

      if (o_id == OV)
         return v;

      if (o_id == OD)
         return (1.0 / v);

      r = Td_reg3(T, 1.0 / v, o_id);
   }

   return r;
}

double px_reg4(double p, double x, int o_id)
/*        * T: Saturated temperature [K]
 * P: Saturated pressure [MPa]
 * x: Vapor quality [-]
 * v: Specific volume [m³/kg]
 * h: Specific enthalpy [kJ/kg]
 * s: Specific entropy [kJ/kgK]
 */
{
   // TODO: testing
   double r1, r2, r;
   switch (o_id)
   {
   case OP:
      r = p;
      break;
   case OX:
      r = x;
      break;
   case OT:
      r = TSat(p);
      break;
   case OV:
   case OD:
   case OH:
   case OS:
   case OU:
      if (x == 0)
      {
         r1 = p2SatWater(p, o_id);
         r = r1;
      }
      else if (x == 1)
      {
         r2 = p2SatSteam(p, o_id);
         r = r2;
      }
      else if (x > 0 && x < 1)
      {
         r1 = p2SatWater(p, o_id);
         r2 = p2SatSteam(p, o_id);
         r = r1 + x * (r2 - r1);
      }
      break;
   default:
      r = -1000;
      break;
   };
   return r;
}
//--------------------------------------------------
double T2SatWater(double T, int o_id)
{
   double p, v, r;
   if (o_id == OT)
      return T;

   if (T == tc_water)
      p = pc_water;
   else
      p = pSat(T);
   if (o_id == OP)
      return p;

   if (T <= 623.15)
      r = pT_reg1(p, T, o_id);
   else
   { // region3
      if (T == tc_water)
      {
         if (o_id == OS)
            return sc_water;
         if (o_id == OH)
            return hc_water;
         v = 1.0 / 322.0;
      }
      else
         v = pT2vSat_reg3(p, T, 0);

      if (o_id == OV)
         return v;
      if (o_id == OD)
         return (1.0 / v);

      r = Td_reg3(T, 1 / v, o_id);
   }
   return (r);
}

double T2SatSteam(double T, int o_id)
{
   double p, v, r;
   if (o_id == OT)
      return T;

   if (T == tc_water)
      p = pc_water;
   else
      p = pSat(T);
   if (o_id == OP)
      return p;

   if (T <= 623.15)
      r = pT_reg2(p, T, o_id);
   else
   { // region3
      if (T == tc_water)
      {
         if (o_id == OS)
            return sc_water;
         if (o_id == OH)
            return hc_water;
         v = 1.0 / 322.0;
         if (o_id == OV)
            return v;
      }
      else
         v = pT2vSat_reg3(p, T, 1);

      r = Td_reg3(T, 1 / v, o_id);
   }
   return (r);
}

double Tx_reg4(double T, double x, int o_id)
{

   if (o_id == OT)
      return T;
   if (o_id == OX)
      return x;

   if (x == 0.0)
      return T2SatWater(T, o_id);
   if (x == 1.0)
      return T2SatSteam(T, o_id);

   if (x > 0.0 && x < 1.0)
   {
      double p = pSat(T);
      if (o_id == OP)
         return p;

      double sw = T2SatWater(T, o_id);
      double ss = T2SatSteam(T, o_id);
      return (sw + x * (ss - sw));
   }
   return INVALID_VALUE;
}

double ph_reg4(double p, double h, int o_id)
{
   double h1, h2, x;
   h1 = p2SatWater(p, OH);
   h2 = p2SatSteam(p, OH);
   x = (h - h1) / (h2 - h1);
   if (o_id == OX)
      return x;
   return px_reg4(p, x, o_id);
}

double ps_reg4(double p, double s, int o_id)
{
   double s1, s2, x;
   s1 = p2SatWater(p, OS);
   s2 = p2SatSteam(p, OS);
   x = (s - s1) / (s2 - s1);
   if (o_id == OX)
      return x;
   return px_reg4(p, x, o_id);
}

double hs_reg4(double h, double s, int o_id)
{
   double T, p;

   T = hs2T_reg4(h, s);
   if (o_id == OT)
      return T;
   p = pSat(T);
   if (o_id == OP)
      return p;

   double h1 = p2SatWater(p, OH);
   double h2 = p2SatSteam(p, OH);

   double x = (h - h1) / (h2 - h1);
   if (o_id == OX)
      return x;

   return px_reg4(p, x, o_id);
}

double pT_reg4(double p, double T, int o_id)
{
   double value;
   if (T == tc_water && p == pc_water)
      value = Td_reg3(T, dc_water, o_id);
   else
      value = INVALID_VALUE;
}

// the extend input pairs
//  (p,v) (T,v)p (T,s) (T,h)
double pv_reg4(double p, double v, int o_id)
{
   double x = pv2x_reg4(p, v);
   if (o_id == OX)
   {
      return x;
   }
   return px_reg4(p, x, o_id);
};
double Tv_reg4(double T, double v, int o_id)
{
   double x = Tv2x_reg4(T, v);
   if (o_id == OX)
   {
      return x;
   }
   return Tx_reg4(T, x, o_id);
};
double Ts_reg4(double T, double s, int o_id)
{
   double x = Ts2x_reg4(T, s);
   if (o_id == OX)
   {
      return x;
   }
   return Tx_reg4(T, x, o_id);
};
double Th_reg4(double T, double h, int o_id)
{

   double x = Th2x_reg4(T, h);
   if (o_id == OX)
   {
      return x;
   }
   return Tx_reg4(T, x, o_id);
};
