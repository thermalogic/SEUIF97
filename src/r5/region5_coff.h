
#pragma once
#include "../common/common.h"

static const double r5Pstar = 1.0;	  // MPa
static const double r5Tstar = 1000.0; // K

static const int Jo[6] = {0, 1, -3, -2, -1, 2};

static const double no[6] = {
	-0.13179983674201e+2,
	0.68540841634434e+1,
	-0.24805148933466e-1,
	0.36901534980333,
	-0.31161318213925e+1,
	-0.32961626538917};

// Table 38. coefficients and exponents of the residual part r of the dimensionless Gibbs free energy for region 5, Eq.(34)
static IJnData IJn[] = {
	{1, 1, 0.15736404855259e-2},
	{1, 2, 0.90153761673944e-3},
	{1, 3, -0.50270077677648e-2},
	{2, 3, 0.22440037409485e-5},
	{2, 9, -0.41163275453471e-5},
	{3, 7, 0.37919454822955e-7}};