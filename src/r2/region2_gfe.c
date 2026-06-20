
/**
 * @file region2_gfe.c
 * @brief Gibbs free energy and derivatives for Region 2
 * 
 * This file implements the dimensionless Gibbs free energy (gamma) and
 * its derivatives for Region 2 (steam) using the IAPWS-IF97 formulation.
 * Includes both ideal gas part and residual part.
 * Reference: IAPWS-IF97, Section 4.2, Page 12-17
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "../algo/algorithm.h"
#include "region2.h"
#include "region2_coff.h"
#include "region2_solo_ij.h"

// Ideal-gas part of fundamental equation for region 2
// Eq16 P13
double gamma0_reg2(double pi, double tau)

{
    //r2j0  0  1  -5  -4  -3  -2  -1 2  3
    double tau_inv = 1.0 / tau;
    double tau_inv2 = tau_inv * tau_inv;
    double tau_inv3 = tau_inv2 * tau_inv;
    double tau2=tau*tau;
      
    double gamma0 = log(pi);
   
    gamma0 += n0[0];
    gamma0 += n0[1]*tau;
    gamma0 += n0[2]*tau_inv3*tau_inv2;
    gamma0 += n0[3]*tau_inv3*tau_inv;
    gamma0 += n0[4]*tau_inv3;
    gamma0 += n0[5]*tau_inv2;
    gamma0 += n0[6]*tau_inv;
    gamma0 += n0[7]*tau2;
    gamma0 += n0[8]*tau2*tau;

    //for (int i = 0; i < 9; i++)
    //   gamma0 += n0[i] * IPOW(tau, r2j0[i]);
    return gamma0;
}

double gamma0_pi_reg2(double pi)
// First derivative in pi of ideal-gas part of fundamental equation for region 2
{
    return 1.0 / pi;
}

double gamma0_pipi_reg2(double pi)
// Second derivative in pi of ideal-gas part of fundamental equation for region 2
{   double p_inv=1.0/pi;
    return p_inv* p_inv;
}

double gamma0_tau_reg2(double tau)
// First derivative in tau of ideal-gas part of fundamental equation for region 2
{
    double gamma0tau = 0.0;
    // r2j0    0  1  -5  -4   -3  -2  -1  2  3
    // r2j0-1 -1  0  -6  -5  -4  -3  -2  1  2
    double tau_inv = 1.0 / tau;
    double tau_inv2 = tau_inv * tau_inv;
    double tau_inv3 = tau_inv2 * tau_inv;
      
    // i=0,r2j0 = 0
    gamma0tau += n0[1];              
    gamma0tau += n0[2]*(-5.0)*tau_inv3*tau_inv3;  
    gamma0tau += n0[3]*(-4.0)*tau_inv3*tau_inv2;
    gamma0tau += n0[4]*(-3.0)*tau_inv2*tau_inv2;
    gamma0tau += n0[5]*(-2.0)*tau_inv3;
    gamma0tau += n0[6]*(-1.0)*tau_inv2;
    gamma0tau += n0[7]*2.0*tau;
    gamma0tau += n0[8]*3.0*tau*tau;

    //for (int i = 0; i < 9; i++)
    //   gamma0tau += n0[i] * r2j0[i] * IPOW(tau, r2j0[i] - 1);
    return gamma0tau;
}

double gamma0_tautau_reg2(double pi, double tau)
// Second derivative in tau of ideal-gas part of fundamental equation for region 2
{
    double gamma0tautau = 0.0;

    // r2j0    0  1  -5  -4   -3  -2  -1  2  3
    // r2j0-1 -1  0  -6  -5  -4  -3   -2  1  2
    // r2j0-2 -2 -1  -7  -6  -5  -4   -3  0  1

    double tau_inv = 1.0 / tau;
    double tau_inv2 = tau_inv * tau_inv;
    double tau_inv3 = tau_inv2 * tau_inv;
    double tau_inv6 = tau_inv3 * tau_inv3;
      
    // i=0,r2j0=0, r2j0*(r2j0-1) = 0
    // i=1,r2j0=1, r2j0-1=0r2j0*(r2j0-1) = 0
    gamma0tautau += n0[2]*30.0*tau_inv6*tau_inv;    // -5 -6
    gamma0tautau += n0[3]*20.0*tau_inv6;            // -4 -5
    gamma0tautau += n0[4]*12.0*tau_inv3*tau_inv2;   // -3 -4
    gamma0tautau += n0[5]*6.0*tau_inv3*tau_inv;     // -2 -3
    gamma0tautau += n0[6]*2.0*tau_inv3;             // -2 -1
    gamma0tautau += n0[7]*2.0;                      //  2  1 
    gamma0tautau += n0[8]*6.0*tau;                  //  2  3

    //for (int i = 0; i < 9; i++)
    //    gamma0tautau += n0[i] * r2j0[i] * (r2j0[i] - 1) * IPOW(tau, r2j0[i] - 2);
    return gamma0tautau;
}

double gamma0_pitau_reg2()
// Second derivative in pi and tau of ideal-gas part of fundamental equation for region 2
{
    return 0.0;
}

//-----------------------------------------------------------------
//  polynomial with solo i,j
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
//  multiple polynomial with solo i,j
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