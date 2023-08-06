/*

*/
#include <math.h>
#include "algorithm.h"

double poly(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IPOW(vi, IJn[k].I) * IPOW(vj, IJn[k].J);
  return v;
}

double poly_i(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IJn[k].I * IPOW(vi, IJn[k].I - 1) * IPOW(vj, IJn[k].J);
  return v;
}

double poly_ii(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IJn[k].I * (IJn[k].I - 1) * IPOW(vi, IJn[k].I - 2) * IPOW(vj, IJn[k].J);
  return v;
}

double poly_j(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IPOW(vi, IJn[k].I) * IJn[k].J * IPOW(vj, IJn[k].J - 1);
  return v;
}

double poly_jj(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IPOW(vi, IJn[k].I) * IJn[k].J * (IJn[k].J - 1) * IPOW(vj, IJn[k].J - 2);
  return v;
}

double poly_ij(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IJn[k].I * IPOW(vi, IJn[k].I - 1) * IJn[k].J * IPOW(vj, IJn[k].J - 1);
  return v;
}
//--------------multiple values ------------------------------------------------------

// /df/dvj
void polys_0_j(double vi, double vj, int size, IJnData *IJn, double *poly_0, double *poly_j)
{
  double item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * IPOW(vi, IJn[k].I) * IPOW(vj, IJn[k].J);
    *poly_0 += item;
    *poly_j += item * IJn[k].J;
  }
  *poly_j /= vj;
}

void polys_i_ii_ij_jj(double vi, double vj, int size, IJnData *IJn,
     double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj)
{
  double item = 0.0;
  double di_item = 0.0;
 
  for (int k = 0; k < size; k++)
  {
     item = IJn[k].n * IPOW(vi, IJn[k].I) * IPOW(vj, IJn[k].J);
     di_item=IJn[k].I *item; 
    *poly_i += di_item;
    *poly_ii += di_item*(IJn[k].I-1);
    *poly_ij += di_item * IJn[k].J;

    *poly_jj += item * IJn[k].J*(IJn[k].J-1);
    
  }
  *poly_i /= vi;
  *poly_ii /= (vi*vi);
  *poly_ij /= (vi*vj);
  *poly_jj /= (vj*vj);
}  
  
  

