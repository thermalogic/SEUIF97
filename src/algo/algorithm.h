/*
  The algorithms
*/
#pragma once

#include <math.h>

#include "../common/common.h"

#define IPOW ipowsac
// #define IPOW ipowrqm
// #define IPOW powf

#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

double ipowsac(double x, int n);
double ipowrqm(double x, int n);

double poly(double vi, double vj, int size, IJnData *IJn);
double poly_i(double vi, double vj, int size, IJnData *IJn);
double poly_ii(double vi, double vj, int size, IJnData *IJn);
double poly_j(double vi, double vj, int size, IJnData *IJn);
double poly_jj(double vi, double vj, int size, IJnData *IJn);
double poly_ij(double vi, double vj, int size, IJnData *IJn);
// multiple
void polys_0_j(double vi, double vj, int size, IJnData *IJn, double *poly_0, double *poly_j);
void polys_i_ii_ij_jj(double vi, double vj, int size, IJnData *IJn,
                      double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj);

static double soI_pow[45] = {(double)(0.0)};
static double soJ_pow[45] = {(double)(0.0)};

typedef void (*solo_power_fn)(double, double, double *, double *);

double poly_solo(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_i(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_ii(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);

double poly_solo_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);

// multiple
void polys_solo_0_i(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_i);
void polys_solo_0_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_j);
void polys_solo_i_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_j);

void polys_solo_i_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                     double *poly_i, double *poly_ij);

void polys_solo_i_ii(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_ii);

void polys_solo_i_ii_ij(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                        double *poly_i, double *poly_ii, double *poly_ij);

void polys_solo_i_ij_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                        double *poly_i, double *poly_ij, double *poly_jj);

void polys_solo_i_ii_ij_jj(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                           double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj);

static double xacc = 1.0E-08;
static int iMAX = 100;
typedef double (*callfunc)(double, double);

double rtsec1(callfunc func, double cVar2, double fr, double x1,
              double x2, double ft, double f, double xacc, int iMAX);
double rtsec2(callfunc func, double cVar1, double fr, double x1,
              double x2, double fl, double f, double xacc, int iMAX);
