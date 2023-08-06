/*
  polynominal with solo power
*/
#include <math.h>
#include "algorithm.h"

double poly_solo(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{ // 1 计算独立幂次数值soI_pow， soJ_pow
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly = 0.0;
  for (int k = 0; k < size; k++)
  {
    // 2 使用已经计算好的重复使用幂值
    poly += IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
  }
  return poly;
}

double poly_solo_i(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{ (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly_i = 0.0;
  for (int k = 0; k < size; k++)
  {
    poly_i += IJn[k].n * IJn[k].I * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
  }
  return (poly_i / vi);
}

double poly_solo_ii(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{ (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly_ii = 0.0;
  for (int k = 0; k < size; k++)
  {
    poly_ii += IJn[k].n * IJn[k].I *( IJn[k].I -1) *soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
  }
  return (poly_ii / vi/vi);
}


double poly_solo_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly_ij = 0.0;
  for (int k = 0; k < size; k++)
  {
    poly_ij += IJn[k].n * IJn[k].I * soI_pow[i2soI[k]] * IJn[k].J * soJ_pow[j2soJ[k]];
  }
  return (poly_ij / vi / vj);
}

double poly_solo_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{ (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly_j = 0.0;
  for (int k = 0; k < size; k++)
  {
    poly_j += IJn[k].n * soI_pow[i2soI[k]] * IJn[k].J * soJ_pow[j2soJ[k]];
  }
  return (poly_j / vj);
}

double poly_solo_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power)
{ (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double poly_jj = 0.0;
  for (int k = 0; k < size; k++)
  {
    poly_jj += IJn[k].n * soI_pow[i2soI[k]] * IJn[k].J * (IJn[k].J - 1) * soJ_pow[j2soJ[k]];
  }
  return (poly_jj / vj / vj);
}

//-------------------------------------------------------------------------
//                           multiple polynomials
//----------------------------------------------------------------------------
void polys_solo_0_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_j)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    *poly_0 += item;
    *poly_j += item * IJn[k].J;
  }
  *poly_j /= vj;
}

void polys_solo_0_i(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_i)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    *poly_0 += item;
    *poly_i += item * IJn[k].I;
  }
  *poly_i /= vi;
}

void polys_solo_i_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_j)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    *poly_i += item * IJn[k].I;
    *poly_j += item * IJn[k].J;
  }
  *poly_i /= vi;
  *poly_j /= vj;
}

void polys_solo_i_ii_ij_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                           double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  double i_item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    i_item = item * IJn[k].I;
    *poly_i += i_item;
    *poly_ii += i_item * (IJn[k].I - 1);
    *poly_ij += i_item * IJn[k].J;

    *poly_jj += item * IJn[k].J * (IJn[k].J - 1);
  }
  *poly_i /= vi;
  *poly_ii /= (vi * vi);
  *poly_ij /= (vi * vj);
  *poly_jj /= (vj * vj);
}

void polys_solo_i_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                     double *poly_i, double *poly_ij)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  double i_item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    i_item = item * IJn[k].I;
    *poly_i += i_item;
    *poly_ij += i_item * IJn[k].J;
  }
  *poly_i /= vi;
  *poly_ij /= (vi * vj);
}

void polys_solo_i_ii(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                     double *poly_i, double *poly_ii)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  double i_item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    i_item = item * IJn[k].I;
    *poly_i += i_item;
    *poly_ii += i_item * (IJn[k].I - 1);
  }
  *poly_i /= vi;
  *poly_ii /= (vi * vi);
}

void polys_solo_i_ij_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                        double *poly_i, double *poly_ij, double *poly_jj)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  double i_item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    i_item = item * IJn[k].I;
    *poly_i += i_item;
    *poly_ij += i_item * IJn[k].J;
    *poly_jj += item * IJn[k].J * (IJn[k].J - 1);
  }
  *poly_i /= vi;
  *poly_ij /= (vi * vj);
  *poly_jj /= (vj * vj);
}

void polys_solo_i_ii_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                           double *poly_i, double *poly_ii, double *poly_ij)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  double i_item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    i_item = item * IJn[k].I;
    *poly_i += i_item;
    *poly_ii += i_item * (IJn[k].I - 1);
    *poly_ij += i_item * IJn[k].J;(IJn[k].J - 1);
  }
  *poly_i /= vi;
  *poly_ii /= (vi * vi);
  *poly_ij /= (vi * vj);
}