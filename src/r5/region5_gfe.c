/*
  Region 5
  * http://www.iapws.org/relguide/IF97-Rev.html,
	 P39  Eq 32-34:
	   (p,T)->v,h,s,cp,cv,w
*/
#include <math.h>
#include "region5.h"
#include "region5_coff.h"
#include "../algo/algorithm.h"

//	P37 Table 37
//  Ideal properties for Region 5
// Table 37. Numerical values of the coefficients and exponents of ideal-gas part  of the
// dimensionless Gibbs free energy for region 5, Eq. (33)

// P36 The equation for the ideal-gas part of the dimensionless Gibbs free energy reads eq33
double gamma0_reg5(double pi, double tau)
{
	double value = log(pi);
	for (unsigned i = 0; i < 6; i++)
		value += no[i] * IPOW(tau, Jo[i]);
	return value;
}

// 38p
double gamma0_pi_reg5(double pi)
{
	return 1.0 / pi;
}

// 38p
double gamma0_pipi_reg5(double pi)
{
	return -1.0 / pi / pi;
}

double gamma0_tau_reg5(double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += no[i] * Jo[i] * IPOW(tau, Jo[i] - 1);
	return value;
}

double gamma0_tautau_reg5(double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += no[i] * Jo[i] * (Jo[i] - 1) * IPOW(tau, Jo[i] - 2);
	return value;
}

double gamma0_pitau_reg5()
{
	return 0.0;
}

double gammar_reg5(double pi, double tau)
{
	double value = 0.0;
	for (int i = 0; i < 6; i++)
		value += IJn[i].n * IPOW(pi, IJn[i].I) * IPOW(tau, IJn[i].J);
	return value;
}

// Table 41. The residual part  r of the dimensionless Gibbs free energy and its
// derivatives  valueaccording to Eq. (34)
double gammar_pi_reg5(double pi, double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += IJn[i].n * IJn[i].I * IPOW(pi, IJn[i].I - 1) * IPOW(tau, IJn[i].J);
	return value;
}

double gammar_pipi_reg5(double pi, double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += IJn[i].n * IJn[i].I * (IJn[i].I - 1) * IPOW(pi, IJn[i].I - 2) * IPOW(tau, IJn[i].J);
	return value;
}

double gammar_tau_reg5(double pi, double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += IJn[i].n * IPOW(pi, IJn[i].I) * IJn[i].J * IPOW(tau, IJn[i].J - 1);
	return value;
}

// 39p
double gammar_tautau_reg5(double pi, double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += IJn[i].n * IPOW(pi, IJn[i].I) * IJn[i].J * (IJn[i].J - 1) * IPOW(tau, IJn[i].J - 2);
	return value;
}

double gammar_pitau_reg5(double pi, double tau)
{
	double value = 0.0;
	for (unsigned i = 0; i < 6; i++)
		value += IJn[i].n * IJn[i].I * IPOW(pi, IJn[i].I - 1) * IJn[i].J * IPOW(tau, IJn[i].J - 1);
	return value;
}
