
//---------------------------------------------------------------------------
// IAPWS -IF 97 Basic Equation for Region 2:  Release : IF97-rev  August 2007
// The dimensionless Gibbs free energy gamma and its derivatives
//     REGION 2 G(p,T) EQUATIONS ：  Eq. (15), P13
//     the ideal-gas part ： Eq. (16)
// Cheng  Maohua
//-------------------------------

//  Initialize coefficients and exponents for region 2
#include <math.h>
#include "../algo/algorithm.h"
#include "region2.h"
#include "region2_coff.h"
#include "region2_solo_ij.h"

// Ideal-gas part of fundamental equation for region 2
// Eq16 P13
double gamma0_reg2(double pi, double tau)

{
    double gamma0 = log(pi);
    for (int i = 0; i < 9; i++)
        gamma0 += n0[i] * IPOW(tau, r2j0[i]);
    return gamma0;
}

double gamma0_pi_reg2(double pi)
// First derivative in pi of ideal-gas part of fundamental equation for region 2
{
    return 1.0 / pi;
}

double gamma0_pipi_reg2(double pi)
// Second derivative in pi of ideal-gas part of fundamental equation for region 2
{
    return -1.0 / pi / pi;
}

double gamma0_tau_reg2(double tau)
// First derivative in tau of ideal-gas part of fundamental equation for region 2
{
    double gamma0tau = 0.0;
    for (int i = 0; i < 9; i++)
        gamma0tau += n0[i] * r2j0[i] * IPOW(tau, r2j0[i] - 1);
    return gamma0tau;
}

double gamma0_tautau_reg2(double pi, double tau)
// Second derivative in tau of ideal-gas part of fundamental equation for region 2
{
    double gamma0tautau = 0.0;
    for (int i = 0; i < 9; i++)
        gamma0tautau += n0[i] * r2j0[i] * (r2j0[i] - 1) * IPOW(tau, r2j0[i] - 2);
    return gamma0tautau;
}

double gamma0_pitau_reg2()
// Second derivative in pi and tau of ideal-gas part of fundamental equation for region 2
{
    return 0.0;
}

//-----------------------------------------------------------------
//  polynominal with solo i,j
//--------------------------------------------------------------------------------

double gammar_reg2(double pi, double tau)
{
    return poly_solo(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

double gammar_pi_reg2(double pi, double tau)
{
    return poly_solo_i(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

double gammar_pipi_reg2(double pi, double tau)
{
    return poly_solo_ii(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

double gammar_pitau_reg2(double pi, double tau)
{
    return poly_solo_ij(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

double gammar_tau_reg2(double pi, double tau)
{
    return poly_solo_j(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

double gammar_tautau_reg2(double pi, double tau)
{
    return poly_solo_jj(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2);
}

//-----------------------------------------------------------------
//  multiple polynominal with solo i,j
//--------------------------------------------------------------------------------

void polys_solo_0_i_reg2(double pi, double tau, double *poly, double *poly_pi)
{
    polys_solo_0_i(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly, poly_pi);
}

void polys_solo_i_j_reg2(double pi, double tau, double *poly_pi, double *poly_tau)
{
    polys_solo_i_j(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_tau);
}

void polys_solo_0_j_reg2(double pi, double tau, double *poly, double *poly_tau)
{
    polys_solo_0_j(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly, poly_tau);
}

void polys_solo_i_ij_reg2(double pi, double tau, double *poly_pi, double *poly_pitau)
{
    polys_solo_i_ij(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_pitau);
}

void polys_solo_i_ii_reg2(double pi, double tau, double *poly_pi, double *poly_pipi)
{
    polys_solo_i_ii(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_pipi);
}

void polys_solo_i_ij_jj_reg2(double pi, double tau, double *poly_pi, double *poly_pitau, double *poly_tautau)
{
    polys_solo_i_ij_jj(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_pitau, poly_tautau);
}

void polys_solo_i_ii_ij_reg2(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau)
{
    polys_solo_i_ii_ij(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_pipi, poly_pitau);
}

void polys_solo_i_ii_ij_jj_reg2(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau, double *poly_tautau)
{
    polys_solo_i_ii_ij_jj(pi, tau - 0.5, 43, IJn, i2soI, j2soJ, solo_i_j_power_reg2, poly_pi, poly_pipi, poly_pitau, poly_tautau);
}