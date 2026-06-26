/**
 * @file region1_p_hs.c
 * @brief Backward equations for Region 1 (h,s)->p
 * 
 * This file implements the backward equation (h,s)->p
 * Reference: IAPWS-IF97-S01, Supp-PHS12-2014
 *       (h,s)->p
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

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
 static const  IJnData IJn[] = {
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
// pi= poly(eta,sigma , 19,IJn);
 
  static const int soI[6] = {0,1,2,3,4,5};
  static const int i2soI[19] = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,3,4,4,5};
  static const int soJ[9] = {0,1,2,4,5,6,8,14,10};
  static const int j2soJ[19] = {0,1,2,3,4,5,6,7,0,1,3,5,0,1,8,3,1,3,0};

  //0, 1, 2, 3, 4, 5
  double soI_pow[6];
  soI_pow[0]=1.0;
  soI_pow[1]=eta;
  soI_pow[2]=eta*eta;
  soI_pow[3]=soI_pow[2]*eta;
  soI_pow[4]=soI_pow[3]*eta;
  soI_pow[5]=soI_pow[4]*eta;
  
  //0,1,2,4,5,6,8,14,10
  double soJ_pow[9];
  soJ_pow[0]=1.0;
  soJ_pow[1]=sigma;
  soJ_pow[2]=sigma*sigma;
  soJ_pow[3]=soJ_pow[2]*soJ_pow[2]; //4
  soJ_pow[4]=soJ_pow[3]*sigma; // 5
  soJ_pow[5]=soJ_pow[4]*sigma; // 6
  soJ_pow[6]=soJ_pow[5]*soJ_pow[2]; //8
  soJ_pow[7]=soJ_pow[5]*soJ_pow[6]; //14
  soJ_pow[8]=soJ_pow[6]*soJ_pow[2]; //10  
  
  pi= poly_solo_backward_eq(19,IJn,soI_pow,soJ_pow,i2soI, j2soJ);
  return (100.0*pi);
}