/*
  The extended pairs:
     (p,v) ->t
    (T,h) ->d  (T,s)->d
*/
#include <math.h>
#include <stdint.h>
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region3.h"
#include "region3_coff.h"

// Region 3  (p,v)->T using the secant method and refine adjust
// * p: pressure  MPa
// * v: specific volume m^3/kg
// * T: temperature  K
double pv2T_reg3(double p, double v)
{
  double T1, T2, d, f1, f2;
  T1 = TMIN3;
  T2 = B23_p2T(p);
  d = 1.0 / v;
  f1 = p - Td2p_reg3(T1, d);
  f2 = p - Td2p_reg3(T2, d);
  return rtsec1(Td2p_reg3, d, p, T1, T2, f1, f2, xacc, iMAX);
}

//     (t,h) ->d
double Th2d_reg3(double T, double h)
{
  double p1 = B23_T2p(T);
  double d1 = 1.0 / pT2v_reg3(p1, T);
  double p2 = PMAX3;
  double d2 = 1.0 / pT2v_reg3(p2, T);
  double f1 = h - Td2h_reg3(T, d1);
  double f2 = h - Td2h_reg3(T, d2);
  return rtsec2(Td2h_reg3, T, h, d1, d2, f1, f2, xacc, iMAX);
}

// Region 3  (T,s)->d using the secant method
//  * T: temperature  K
//  * s: specific entropy  kJ/(kg K)
//  * d: density    kg/m^3
double Ts2d_reg3(double T, double s)
{
  double d1 = 100.0;
  double d2 = 1.1 * d1;
  double ft = s - Td2s_reg3(T, d1);
  double f = s - Td2s_reg3(T, d2);
  return rtsec2(Td2s_reg3, T, s, d1, d2, ft, f, xacc, iMAX);
}
