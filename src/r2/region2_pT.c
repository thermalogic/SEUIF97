/* --------------------------------------------------------------------------
 Basic Equation of  IAPWS -IF 97 Region2
  * (p,T)->v,h,s,v,cp,cv,w
  Properties(9):
     T in K           temperature
     p in MPa         pressure
     v  in m^3/kg     volume
     u  in kJ/kg      internal energy
     s in kJ/(kg K)   entropy
     h  in kJ/kg      enthalpy
    cp  in kJ/(kg K)  specific isobaric heat capacity
    cv  in kJ/(kg K)  specific isochoric heat capacity
     w  in m/s        speed of sound
--------------------------------------------------- */
#include <math.h>
#include "../algo/algorithm.h"
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "region2.h"
#include "region2_coff.h"
#include "region2_solo_ij.h"

double pT_thermal_reg2(double p, double T, int o_id)
// o_id: output propertry
{
    double value;
    switch (o_id)
    {
    case OT:
        value = T;
        break;
    case OP:
        value = p;
        break;
    case OV:
        value = pT2v_reg2(p, T);
        break;
    case OD:
        value = 1.0 / pT2v_reg2(p, T);
        break;
    case OH:
        value = pT2h_reg2(p, T);
        break;
    case OS:
        value = pT2s_reg2(p, T);
        break;
    case OU:
        value = pT2u_reg2(p, T);
        break;
    case OCV:
        value = pT2cv_reg2(p, T);
        break;
    case OCP:
        value = pT2cp_reg2(p, T);
        break;
    case OW:
        value = pT2w_reg2(p, T);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}

double pT2v_reg2(double p, double T)
//
// specific volume in region 2
// vreg2 in m^3/kg
// temperature in K
// pressure in MPa
//
{
    double tau = r2Tstar / T;
    double pi = p;
    return 0.001 * rgas_water * T * pi * (gamma0_pi_reg2(pi) + gammar_pi_reg2(pi, tau)) / p;
}

double pT2h_reg2(double p, double T)
// specific enthalpy in region 2
// hreg2 in kJ/kg
// temperature in K
// pressure in Map
//
{
    double tau = r2Tstar / T;
    double pi = p;
    return rgas_water * T * tau * (gamma0_tau_reg2(tau) + gammar_tau_reg2(pi, tau));
}

double pT2u_reg2(double p, double T)
//
// specific internal energy in region 2
// ureg2 in kJ/kg
// temperature in K
// pressure in Mpa
//
{
    double tau = r2Tstar / T;
    double pi = p;
    // return rgas_water * T * (tau * (gamma0_tau_reg2(tau) + gammartau_reg2(pi,tau)) - pi * (gamma0_pi_reg2(pi) + gammarpi_reg2(pi,tau)));
    double gammar_pi = 0;
    double gammar_tau = 0.0;
    polys_solo_i_j_reg2(pi, tau, &gammar_pi, &gammar_tau);
    return rgas_water * T * (tau * (gamma0_tau_reg2(tau) + gammar_tau) - pi * (gamma0_pi_reg2(pi) + gammar_pi));
}

double pT2s_reg2(double p, double T)
//
// specific entropy in region 2
// sreg2 in kJ/(kg K)
// temperature in K
// pressure in Mpa
//
{
    double tau = r2Tstar / T;
    double pi = p;
    // return rgas_water * (tau * (gamma0_tau_reg2(tau) + gammartau_reg2(pi,tau)) - (gamma0__reg2(pi,tau) + gammar_reg2(pi,tau)));

    // gamma0_
    double gamma0_ = log(pi);
    double gamma0_tau = 0.0;
    double gamma0_item;
    for (int i = 0; i < 9; i++)
    {
        gamma0_item = n0[i] * IPOW(tau, r2j0[i]);
        gamma0_ += gamma0_item;
        gamma0_tau += gamma0_item * r2j0[i];
    }
    gamma0_tau /= tau;

    // gammar
    double gammar = 0;
    double gammar_tau = 0.0;
    polys_solo_0_j_reg2(pi, tau, &gammar, &gammar_tau);
    return rgas_water * (tau * (gamma0_tau + gammar_tau) - (gamma0_ + gammar));
}

double pT2cp_reg2(double p, double T)
//
// specific isobaric heat capacity in region 2
// cpreg2 in kJ/(kg K)
// temperature in K
// pressure in Mpa
//
{
    double tau = r2Tstar / T;
    double pi = p;
    return -rgas_water * tau * tau * (gamma0_tautau_reg2(pi, tau) + gammar_tautau_reg2(pi, tau));
}

double pT2cv_reg2(double p, double T)
//
// specific isochoric heat capacity in region 2
// cvreg2 in kJ/(kg K)
// temperature in K
// pressure in bar
//
{
    double tau = r2Tstar / T;
    double pi = p;
    // double a = 1 + pi * gammarpi_reg2(pi,tau) - tau * pi * gammarpitau_reg2(pi,tau);
    // return rgas_water * (-tau * tau * (gamma0_tautau_reg2(pi,tau) + gammartautau_reg2(pi,tau)) - a * a / (1 - pi * pi * gammarpipi_reg2(pi,tau)));

    double poly_pi = 0;
    double poly_pitau = 0;
    double poly_pipi = 0;
    double poly_tautau = 0;
    polys_solo_i_ii_ij_jj_reg2(pi, tau, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);
    double a = 1 + pi * (poly_pi - tau * poly_pitau);
    return rgas_water * (-tau * tau * (gamma0_tautau_reg2(pi, tau) + poly_tautau) - a * a / (1 - pi * pi * poly_pipi));
}

double pT2w_reg2(double p, double T)
//
// speed of sound in region 2
// wreg2 in m/s
// temperature in K
// pressure in Mpa
//
{
    double tau = r2Tstar / T;
    double pi = p;

    // double a = pi * gammarpi_reg2(pi,tau);
    // a *= a;
    // double b = 1 + pi * gammarpi_reg2(pi,tau) - tau * pi * gammarpitau_reg2(pi,tau);
    //  b *= b;
    //  return sqrt(1000.0 * rgas_water * T * (1 + 2 * pi * gammarpi_reg2(pi,tau) + a) /
    //              ((1 - pi * pi * gammarpipi_reg2(pi,tau)) + b / (tau * tau * (gamma0_tautau_reg2(pi,tau) + gammartautau_reg2(pi,tau)))));

    double poly_pi = 0;
    double poly_pitau = 0;
    double poly_pipi = 0;
    double poly_tautau = 0;
    polys_solo_i_ii_ij_jj_reg2(pi, tau, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);

    double a = pi * poly_pi;
    a *= a;
    double b = 1 + pi * (poly_pi - tau * poly_pitau);
    b *= b;
    return sqrt(1000.0 * rgas_water * T * (1 + 2 * pi * poly_pi + a) /
                ((1 - pi * pi * poly_pipi) + b / (tau * tau * (gamma0_tautau_reg2(pi, tau) + poly_tautau))));
}
