/*---------------------------------------------------------------------------
   IAPWS -IF 97 Backware Equation (H,S)->P for Region 1:
     IAPWS-IF97-S01: Supp-PHS12-2014.pdf  June 2014
            (h,s)->p
 -------------------------------------------------------------------- */

#include <math.h>
#include "region1.h"
#include "../algo/algorithm.h"

// helper for iter (h,s)->p
double ph2s_reg1(double p, double h)
{
  double T;
  T = ph2T_reg1(p, h);
  return pT2s_reg1(p, T);
}

//----------------------------------------------------------------
//  Backward equation p(h,s) for region 1
//----------------------------------------------------------------
double hs2p_reg1(double h, double s)
{
  // Page 5, Table 2 :
  // Initialize coefficients and exponents (H,S)->P for region 1
  IJnData IJn[] = {
      {0, 0, -.691997014660582},
      {0, 1, -.183612548787560e2},
      {0, 2, -.928332409297335e1},
      {0, 4, .659639569909906e2},
      {0, 5, -.162060388912024e2},

      {0, 6, .450620017338667e3},
      {0, 8, .854680678224170e3},
      {0, 14, .607523214001162e4},
      {1, 0, .326487682621856e2},
      {1, 1, -.269408844582931e2},

      {1, 4, -.319947848334300e3},
      {1, 6, -.928354307043320e3},
      {2, 0, .303634537455249e2},
      {2, 1, -.650540422444146e2},
      {2, 10, -.430991316516130e4},

      {3, 4, -.747512324096068e3},
      {4, 1, .730000345529245e3},
      {4, 4, .114284032569021e4},
      {5, 0, -.436407041874559e3}};
  double eta, sigma;
  double pi;
  eta = h / 3400.0 + 0.05;
  sigma = s / 7.6 + 0.05;
  pi= poly(eta,sigma , 19,IJn);
  return (100.0*pi);

  /*// iteration: refine
  double p1, p2, p, f1, f2;
  p1 = (100.0 * pi);
  f1 = s - ph2s_reg1(p1, h);
  if (fabs(f1) > xacc)
  {
    if (f1 > 0) // pT2s_reg1(p,h)< s ,the p1< expt p，so， p2=1.05*p1 p（p1,p2)
      p2 = (1.0 + f1 / s) * p1;
    else
      p2 = (1.0 - f1 / s) * p1;

    f2 = s - ph2s_reg1(p2, h);
    p = rtsec1(ph2s_reg1, h, s, p1, p2, f1, f2, xacc, iMAX);
  }
  else
    p = p1;

  return p;*/
}
