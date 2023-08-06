/*
 Speciphic Helmholtz free energy and derivatives

*/
#include <math.h>
#include "../algo/algorithm.h"
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region3.h"
#include "region3_coff.h"
#include "region3_solo_ij.h"

/*
	 * Speciphic Helmholtz free energy.
	 * tau :dimensionless temperature [K]
	 * delta: dimensionless density [kg/m3]

*/
double phi_reg3(double delta, double tau)
// Fundamental equation for region 3
{
	// double phi = n1 * log(delta);
	// for (int k = 0; k < 39; k++)
	//		phi += IJn[k].n * pow(delta, IJn[k].I) * pow(tau, IJn[k].J);
	// return phi;
	return n1 * log(delta) + poly_solo(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

double phi_delta_reg3(double delta, double tau)
// first derivative in delta of fundamental equation for region 3
{
	// double phi_delta = n1 / delta;
	// for (int k = 0; k < 39; k++)
	//		phi_delta += IJn[k].n * IJn[k].I * pow(delta, IJn[k].I - 1) * pow(tau, IJn[k].J);
	//	return phi_delta;
	return (n1 / delta) + poly_solo_i(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

double phi_deltadelta_reg3(double delta, double tau)
// Second derivative in delta of fundamental equation for region 3
{
	// double phi_deltadelta = -n1 / delta / delta;
	// for (int k = 0; k < 39; k++)
	//		phi_deltadelta += IJn[k].n * IJn[k].I * (IJn[k].I - 1) * pow(delta, IJn[k].I - 2) * pow(tau, IJn[k].J);
	//	return phi_deltadelta;

	return (-n1 / delta / delta) + poly_solo_ii(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

double phi_tau_reg3(double delta, double tau)
// phirst derivative in tau of fundamental equation for region 3
{
	// double phi_tau = 0.0;
	// for (int k = 0; k < 39; k++)
	//	phi_tau += IJn[k].n * pow(delta, IJn[k].I) * IJn[k].J * pow(tau, IJn[k].J - 1);
	// return phi_tau;

	return poly_solo_j(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

double phi_tautau_reg3(double delta, double tau)
// Second derivative in tau of fundamental equation for region 3
{
	// double phi_tautau = 0.0;
	// for (int k = 0; k < 39; k++)
	//	phi_tautau += IJn[k].n * pow(delta, IJn[k].I) * IJn[k].J * (IJn[k].J - 1) * pow(tau, IJn[k].J - 2);
	//	return phi_tautau;

	return poly_solo_jj(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

double phi_deltatau_reg3(double delta, double tau)
// Second derivative in delta and tau of fundamental equation for region 3
{
	// double phi_deltatau = 0.0;
	// for (int k = 0; k < 39; k++)
	//	phi_deltatau += IJn[k].n * IJn[k].I * pow(delta, IJn[k].I - 1) * IJn[k].J * pow(tau, IJn[k].J - 1);
	// return phi_deltatau;

	return poly_solo_ij(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3);
}

//------------------------------------------------------------------------------------
// mutiple polys
//-----------------------------------------------------------------------------------------
void polys_solo_0_j_reg3(double delta, double tau,
						 double *poly,
						 double *poly_tau)
{
	polys_solo_0_j(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3, poly, poly_tau);
	*poly += n1 * log(delta);
}

void polys_solo_i_j_reg3(double delta, double tau,
						 double *poly_delta,
						 double *poly_tau)
{
	polys_solo_i_j(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3, poly_delta, poly_tau);

	*poly_delta += n1 / delta;
}

void polys_solo_i_ii_ij_jj_reg3(double delta, double tau,
								double *poly_delta, double *poly_deltadelta, double *poly_deltatau,
								double *poly_tautau)
{
	polys_solo_i_ii_ij_jj(delta, tau, 39, IJn, i2soI, j2soJ, solo_i_j_power_reg3, poly_delta, poly_deltadelta,
						  poly_deltatau, poly_tautau);

	*poly_delta += n1 / delta;
	*poly_deltadelta += (-n1 / delta / delta);
}