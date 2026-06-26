/**
 * @file region1_T_phps.c
 * @brief Backward equations for Region 1: (p,h)->T and (p,s)->T
 * 
 * This file implements the backward equations for calculating temperature
 * from (p,h) and (p,s) input pairs in Region 1.
 * Reference: IAPWS-IF97, August 2007 IF97-Rev.pdf, Page 6-9
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "region1.h"
#include "../algo/algorithm.h"

//-------------------------------------------------------------
// Backward equation T(p,h) for region 1
//--------------------------------------------------------------
double ph2T_reg1(double p, double h)
{
  // Page 11, Table6 :Initialize coefficients and exponents (P,H)->T for region 1
 static const IJnData IJn[] = {
      {0, 0, -238.72489924521},
      {0, 1, 404.21188637945},
      {0, 2, 113.49746881718},
      {0, 6, -5.8457616048039},
      {0, 22, -1.528548241314E-04},
      {0, 32, -1.0866707695377E-06},
      {1, 0, -13.391744872602},
      {1, 1, 43.211039183559},
      {1, 2, -54.010067170506},
      {1, 3, 30.535892203916},
      {1, 4, -6.5964749423638},
      {1, 10, 9.3965400878363E-03},
      {1, 32, 1.157364750534E-07},
      {2, 10, -2.5858641282073E-05},
      {2, 32, -4.0644363084799E-09},
      {3, 10, 6.6456186191635E-08},
      {3, 32, 8.0670734103027E-11},
      {4, 32, -9.3477771213947E-13},
      {5, 32, 5.8265442020601E-15},
      {6, 32, -1.5020185953503E-17}};

  static const int soI[7]= {0, 1, 2, 3, 4, 5, 6};
  static const int i2soI[20] = 
                       {0, 0, 0, 0, 0, 0,
                        1, 1, 1, 1, 1, 1, 1, 
                        2, 2, 3, 3, 4, 5, 6};
  static const int soJ[9]= {0, 1, 2, 6, 22, 32, 3, 4, 10};
  static const int j2soJ[20] =
                      {0, 1, 2, 3, 4, 5, 
                      0, 1, 2, 6, 7, 8, 5, 8, 
                      5, 8, 5, 5, 5, 5};
                          
  double pi, eta;
  double theta;
  pi = p / 1.0;
  eta = h / 2500.0 + 1.0;
  //theta = poly(pi, eta, 20, IJn);
  //return (1.0 *theta);
  
  //0, 1, 2, 3, 4, 5, 6
  double soI_pow[7];
  soI_pow[0]=1.0;
  soI_pow[1]=pi;
  soI_pow[2]=pi*pi;
  soI_pow[3]=soI_pow[2]*pi;
  soI_pow[4]=soI_pow[3]*pi;
  soI_pow[5]=soI_pow[4]*pi;
  soI_pow[6]=soI_pow[5]*pi;
  
  //0, 1, 2, 6, 22, 32, 3, 4, 10
  double soJ_pow[9];
  soJ_pow[0]=1.0;
  soJ_pow[1]=eta;
  soJ_pow[2]=eta*eta;
  
  soJ_pow[6]=soJ_pow[2]*eta; //3
  soJ_pow[7]=soJ_pow[6]*eta; //4
  
  soJ_pow[3]=soJ_pow[6]*soJ_pow[6]; //6
 
  soJ_pow[8]=soJ_pow[3]*soJ_pow[7]; //10

  soJ_pow[4]=soJ_pow[8]*soJ_pow[8]*soJ_pow[2]; //22
  soJ_pow[5]=soJ_pow[4]*soJ_pow[8]; //32
  
  theta= poly_solo_backward_eq(20,IJn,soI_pow,soJ_pow,i2soI, j2soJ);
  return 1.0*theta;
}

//----------------------------------------------------------------
//  Backward equation T(p,s) for region 1
//----------------------------------------------------------------
double ps2T_reg1(double p, double s)
// Page 12, Table 8 : Initialize coefficients and exponents (P,S)->T for region 1
{
 static const  IJnData IJn[] = {
      {0, 0, 0.17478268058307e3},
      {0, 1, 0.34806930892873e2},
      {0, 2, 0.65292584978455e1},
      {0, 3, 0.33039981775489},
      {0, 11, -0.19281382923196e-6},

      {0, 31, -0.24909197244573e-22},
      {1, 0, -0.26107636489332},
      {1, 1, 0.22592965981586},
      {1, 2, -0.64256463395226e-1},
      {1, 3, 0.78876289270526e-2},

      {1, 12, 0.35672110607366e-9},
      {1, 31, 0.17332496994895e-23},
      {2, 0, 0.56608900654837e-3},
      {2, 1, -0.32635483139717e-3},
      {2, 2, 0.44778286690632e-4},

      {2, 9, -0.51322156908507e-9},
      {2, 31, -0.42522657042207e-25},
      {3, 10, 0.26400441360689e-12},
      {3, 32, 0.78124600459723e-28},
      {4, 32, -0.30732199903668e-30}};

  double pi, sigma;
  double theta=0.0;
  pi = p / 1.0;
  sigma = s / 1.0 + 2.0;
 // theta = poly(pi, sigma, 20, IJn);
 
  static const int soI[5] = {0,1,2,3,4};
  static const int i2soI[20] = {0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,3,3,4};
  static const int soJ[10] = {0,1,2,3,11,31,12,9,10,32};
  static const int j2soJ[20] = {0,1,2,3,4,5,0,1,2,3,6,5,0,1,2,7,5,8,9,9};
  
  //0, 1, 2, 3, 4
  double soI_pow[5];
  soI_pow[0]=1.0;
  soI_pow[1]=pi;
  soI_pow[2]=pi*pi;
  soI_pow[3]=soI_pow[2]*pi;
  soI_pow[4]=soI_pow[3]*pi;
  
  // 0,1,2,3,11,31,12,9,10,32  
  double soJ_pow[9];
  soJ_pow[0]=1.0;
  soJ_pow[1]=sigma;
  soJ_pow[2]=sigma*sigma;
  soJ_pow[3]=soJ_pow[2]*sigma;

  soJ_pow[7]=soJ_pow[3]*soJ_pow[3]*soJ_pow[3]; //9
  soJ_pow[8]=soJ_pow[7]*sigma; //10
  
  soJ_pow[4]=soJ_pow[8]*sigma; //11
  soJ_pow[6]=soJ_pow[4]*sigma; //12

  soJ_pow[5]=soJ_pow[8]*soJ_pow[8]*soJ_pow[4]; //31
  soJ_pow[9]=soJ_pow[5]*sigma; //32

  theta= poly_solo_backward_eq(20,IJn,soI_pow,soJ_pow,i2soI, j2soJ);
  return (1.0*theta);
}