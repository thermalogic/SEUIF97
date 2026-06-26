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

#define FIRST_FIXED              1        /* f(fvar, x)：第一个参数固定，搜索第二个 */
#define SECOND_FIXED             2        /* f(x, fvar)：第二个参数固定，搜索第一个 */
#define CONVERGENCE_PRECISION    1.0E-08   /* rtsec 的 xacc：搜索变量收敛阈值 */
#define FN_TOLERANCE             1.0E-08   /* bisection 的 tol：函数值阈值 */
#define INTERVAL_TOLERANCE       1.0E-08   /* bisection 的 x_tol：区间长度阈值 */
#define MAX_ITER                 20000     /* 最大迭代次数 */
typedef double (*calfn)(double, double);
double rtsec(calfn fn, double var, double target, double x1, double x2, int var_position, int max_iter,double xacc);
double bisection(calfn fn, double var, double target, double t1, double t2, int var_position, int max_iter, double tol, double x_tol);
