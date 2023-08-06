//  Initialize coefficients and exponents for region 1
#include <math.h>
#include "region1.h"
#include "region1_coff.h"
#include "../algo/algorithm.h"
#include "region1_solo_ij.h"

double gamma_reg1(double pi, double tau)
{
    return poly_solo(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

double gamma_pi_reg1(double pi, double tau)
{
    return -poly_solo_i(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

double gamma_tau_reg1(double pi, double tau)
{
    return poly_solo_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

double gamma_tautau_reg1(double pi, double tau)
{
    return poly_solo_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

double gamma_pitau_reg1(double pi, double tau)
{
    return -poly_solo_ij(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

double gamma_pipi_reg1(double pi, double tau)
{
    return -poly_solo_ii(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
}

//------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

void polys_solo_0_i_reg1(double pi, double tau, double *poly, double *poly_pi)
{
    polys_solo_0_i(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly, poly_pi);
    *poly_pi = -(*poly_pi);
}

void polys_solo_0_j_reg1(double pi, double tau, double *poly, double *poly_tau)
{
    polys_solo_0_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly, poly_tau);
}

void polys_solo_i_j_reg1(double pi, double tau, double *poly_pi, double *poly_tau)
{
    polys_solo_i_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi, poly_tau);
    *poly_pi = -(*poly_pi);
}

void polys_solo_i_ii_reg1(double pi, double tau, double *poly_pi, double *poly_pipi)
{
    polys_solo_i_ii(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi, poly_pipi);
    *poly_pi = -(*poly_pi);
}

void polys_solo_i_ij_reg1(double pi, double tau, double *poly_pi, double *poly_pitau)
{
    polys_solo_i_ij(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi, poly_pitau);
    *poly_pi = -(*poly_pi);
    *poly_pitau = -(*poly_pitau);
}

void polys_solo_i_ii_ij_reg1(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau)
{
    polys_solo_i_ii_ij(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi,poly_pipi, poly_pitau);
    *poly_pi = -(*poly_pi);
    *poly_pitau = -(*poly_pitau);
}

void polys_solo_i_ij_jj_reg1(double pi, double tau, double *poly_pi, double *poly_pitau, double *poly_tautau)
{
    polys_solo_i_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi,poly_pitau, poly_tautau);
    *poly_pi = -(*poly_pi);
    *poly_pitau = -(*poly_pitau);
}

void polys_solo_i_ii_ij_jj_reg1(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau, double *poly_tautau)
{
    polys_solo_i_ii_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi, poly_pipi, poly_pitau, poly_tautau);
    *poly_pi = -(*poly_pi);
    *poly_pitau = -(*poly_pitau);
}