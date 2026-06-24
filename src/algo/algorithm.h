/**
 * @file algorithm.h
 * @brief General algorithms for IAPWS-IF97
 * 
 * This header file defines general algorithms used in IAPWS-IF97 calculations.
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */
#pragma once

#include <math.h>

#include "../common/common.h"
#include "ipow.h"

#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

double poly(double vi, double vj, int size, const IJnData *IJn);
double poly_i(double vi, double vj, int size, const IJnData *IJn);
double poly_ii(double vi, double vj, int size, const IJnData *IJn);
double poly_j(double vi, double vj, int size, const IJnData *IJn);
double poly_jj(double vi, double vj, int size, const IJnData *IJn);
double poly_ij(double vi, double vj, int size, const IJnData *IJn);
// multiple
void polys_0_j(double vi, double vj, int size, const IJnData *IJn, double *poly_0, double *poly_j);
void polys_i_ii_ij_jj(double vi, double vj, int size, const IJnData *IJn,
                      double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj);

static double soI_pow[45] = {(double)(0.0)};
static double soJ_pow[45] = {(double)(0.0)};

typedef void (*solo_power_fn)(double, double, double *, double *);

double poly_solo(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_i(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_ii(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);

double poly_solo_j(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_ij(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);
double poly_solo_jj(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power);

// multiple
void polys_solo_0_i(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_i);
void polys_solo_0_j(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_0, double *poly_j);
void polys_solo_i_j(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_j);

void polys_solo_i_ij(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                     double *poly_i, double *poly_ij);

void polys_solo_i_ii(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_ii);

void polys_solo_i_ii_ij(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                        double *poly_i, double *poly_ii, double *poly_ij);

void polys_solo_i_ij_jj(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                        double *poly_i, double *poly_ij, double *poly_jj);

void polys_solo_i_ii_ij_jj(double vi, double vj, int size, const IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power,
                           double *poly_i, double *poly_ii, double *poly_ij, double *poly_jj);

static double xacc = 1.0E-08;
static int iMAX = 20000;
typedef double (*callfunc)(double, double);

double rtsec(callfunc func, double var, double target, double x1,
              double x2, int var_position, double xacc, int iMAX);
typedef double (*bisection_func)(double, double);
double bisection(double t1, double t2, double (*f)(double, double), double var, double r, int var_position, int max_iter, double tol, double x_tol);