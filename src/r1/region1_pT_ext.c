/*  Region1: The extended Properties:
  * pT_ext_reg1(p: f64, T: f64, o_id: i32) -> f64

  Properties(12 + 5):

   *  k: Isentropic exponent OKISE 11 -
   *  ipcec: Isobaric cubic expansion coefficient  OIPCEC 17 αv  1/K
   *  kt: Isothermal compressibility, OKT kT 1/MPa

   *  e: Specific exergy    kJ/kg
   *  f: Specific Helmholtz free energy OF 12  kJ/kg
   *  g: Specific Gibbs free energy  OG 13 kJ/kg

   *  joule : Joule-Thomson coefficient  OJTC  23   K/MPa
   *  ijoule: Isothermal Joule-Thomson coefficient OIJTC 22 kJ/(kg·MPa)
   *
   *  z: Compressibility factor   -

   *  dpdtcv:  Partial derivative (dP/dT)v  MPa/K
   *  dvdpct: Partial derivative (dV/dP)T  m³/(kg·MPa)
   *  dvdtcp: Partial derivative (dV/dT)p  m³/(kg·K)
  TODO:
   *  pc:  isochoric pressure coefficient  1/K
   *  batap ：Isothermal stress coefficient, kg/m³
   *  fi: Fugacity coefficient
   *  fu: Fugacity, MPa
   * alfap: relative pressure coefficient  1/K
*/

#include <math.h>
#include <stdint.h>
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region1.h"
#include "region1_coff.h"
#include "region1_solo_ij.h"

// Region1: the extended properties
double pT_ext_reg1(double p, double T, int o_id)
{
    double r = 0.0;
    switch (o_id)
    {
    case OKISE:
        r = pT2k_reg1(p, T);
        break;
    case OIPCEC:
        r = pT2ipcec_reg1(p, T);
        break;
    case OKT:
        r = pT2kt_reg1(p, T);
        break;
    case OG:
        r = pT2g_reg1(p, T);
        break;
    case OF:
        r = pT2f_reg1(p, T);
        break;
    case OJTC:
        r = pT2joule_reg1(p, T);
        break;
        break;
    case OIJTC:
        r = pT2ijoule_reg1(p, T);
        break;
    case OZ:
        r = pT2z_reg1(p, T);
        break;
    case OE:
        r = pT2e_reg1(p, T);
        break;
    case ODPDT:
        r = pT2dpdtcv_reg1(p, T);
        break;
    case ODVDP:
        r = pT2dvdpct_reg1(p, T);
        break;
    case ODVDT:
        r = pT2dvdtcp_reg1(p, T);
        break;
    /*
       OPC => pT2pc_reg1(p, T),
       OBETAP => pT2batap_reg1(p, T),
       OFI => pT2fi_reg1(p, T),
       OFU => pT2fu_reg1(p, T),
       OALFAP => pT2alfap_reg1(p, T),*/
    default:
        r = INVALID_OUTID;
    }
    return r;
}

// k:Isentropic exponent OKISE 11
// * k= -(v/p)*/1000*(dp/dv)s
double pT2k_reg1(double p, double T)
{
    double v = pT2v_reg1(p, T);
    double w = pT2w_reg1(p, T);
    return 1.0E-6 * w * w / v / p;
}

// αv: Isobaric cubic expansion coefficient / Isobaric volume expansion coefficient  1/K
// * αv=(1.0/v)*(∂v/∂T)p ( The book 2019,Page 28)
double pT2ipcec_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // return 1.0 / T - tau * gamma_pitau_reg1(tau, pi) / gamma_pi_reg1(tau, pi) / T
    double poly_pi = 0;
    double poly_pitau = 0;
    // polys_solo_i_ij(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, &poly_pi, &poly_pitau);

    polys_solo_i_ij_reg1(pi, tau, &poly_pi, &poly_pitau);
    return 1.0 / T - tau * poly_pitau / poly_pi / T;
}

/// kt Isothermal compressibility 1/Mpa
// * kt=-(1.0/V)*(dv/dp)T
double pT2kt_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // -gamma_pipi_reg1(tau, pi) / gamma_pi_reg1(tau, pi) / r1pstar
    double poly_pi = 0;
    double poly_pipi = 0;
    // polys_solo_i_ii_reg1(pi, tau, &poly_pi, &poly_pipi);
    polys_solo_i_ii_reg1(pi, tau, &poly_pi, &poly_pipi);
    return -poly_pipi / poly_pi / r1pstar;
}

/// the specific Gibbs free energy, Page 6, Eq(7)
/// *  g=R*t*gamma
double pT2g_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    return rgas_water * T * gamma_reg1(tau, pi);
    // double gamma = poly_solo(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
    // return rgas_water * T * gamma;
}

/// the Helmholtz Specific free energy:
/// *  f=u-T*s=R*T*(gamma-gamma_pi)
double pT2f_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // RGAS_WATER * T * (gamma_reg1(tau, pi) - pi * gamma_pi_reg1(tau, pi))

    double gamma = 0.0;
    double gammapi = 0.0;
    polys_solo_0_i_reg1(pi, tau, &gamma, &gammapi);
    return rgas_water * T * (gamma - pi * gammapi);
}

/// joule ： Joule-Thomson coefficient    K/MPa
/// *  (dt/dp)h
double pT2joule_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;

    // let g1pi: f64 = gamma_pi_reg1(tau, pi);
    // let v: f64 = 0.001 * RGAS_WATER * T * g1pi / r1pstar;
    //  let cp: f64 = -RGAS_WATER * tau * tau * gamma_tautau_reg1(tau, pi);
    //  let TCex_1: f64 = -tau * gamma_pitau_reg1(tau, pi) / g1pi;
    //  (v / cp) * TCex_1

    double gammapi = 0.0;
    double gammapitau = 0.0;
    double gammatautau = 0.0;
    polys_solo_i_ij_jj_reg1(pi, tau, &gammapi, &gammapitau, &gammatautau);
    double v = rgas_water * T * gammapi / r1pstar;
    double cp = -rgas_water * tau * tau * gammatautau;
    double TCex_1 = -tau * gammapitau / gammapi;
    return (v / cp) * TCex_1;
}

//  Isothermal throttling coefficient / Isothermal Joule-Thomson coefficient
///  ijoule: kJ/(kg·MPa)
/// *  (dh/dp)T
double pT2ijoule_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    return 0.001 * rgas_water * r1Tstar * gamma_pitau_reg1(tau, pi) / r1pstar;
    // double gamma_pitau = -poly_solo_ij(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
    // return 0.001 * rgas_water * r1Tstar * gamma_pitau / r1pstar;
}

/// z: Compressibility factor
double pT2z_reg1(double p, double T)
{
    double v = pT2v_reg1(p, T);
    return (1000.0 * p * v / rgas_water / T);
}

/// e  the specific exergy   kJ/kg  in region 1
double pT2e_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // let gumma: f64 = gamma_reg1(tau, pi);
    // let gumma_tau: f64 = gamma_tau_reg1(tau, pi);
    // RGAS_WATER * (T * gumma + (T - 273.16) * (tau * gumma_tau - gumma))

    double gamma = 0.0;
    double gammatau = 0.0;

    polys_solo_0_j_reg1(pi, tau, &gamma, &gammatau);

    return rgas_water * (T * gamma + (T - 273.16) * (tau * gammatau - gamma));
}

/// Region 1 - (dp/dt)v  MPa/K
double pT2dpdtcv_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // let gamma_pitau: f64 = gamma_pitau_reg1(tau, pi);
    // let gamma_pi: f64 = gamma_pi_reg1(tau, pi);
    // let gamma_pipi: f64 = gamma_pipi_reg1(tau, pi);
    // r1pstar * (gamma_pitau * r1Tstar - gamma_pi * T) / (T * T * gamma_pipi)

    double gamma_pi = 0.0;
    double gamma_pipi = 0.0;
    double gamma_pitau = 0.0;
    polys_solo_i_ii_ij_reg1(pi, tau, &gamma_pi, &gamma_pipi, &gamma_pitau);
    return r1pstar * (gamma_pitau * r1Tstar - gamma_pi * T) / (T * T * gamma_pipi);
}

/// dvdp Partial derivative (dV/dP)T  m3/(kg·MPa)
double pT2dvdpct_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    return 0.001 * rgas_water * T * gamma_pipi_reg1(tau, pi) / r1pstar / r1pstar;

    // double gamma_pipi = poly_solo_ii(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
    // return 0.001 * rgas_water * T * gamma_pipi / r1pstar / r1pstar;
}

// (dv/dT)p m3/(kg.K)
double pT2dvdtcp_reg1(double p, double T)
{
    double tau = r1Tstar / T;
    double pi = p / r1pstar;
    // 0.001 * RGAS_WATER * (gamma_pi_reg1(tau, pi) - tau * gamma_pitau_reg1(tau, pi)) / r1pstar
    double gamma_pi = 0.0;
    double gamma_pitau = 0.0;

    polys_solo_i_ij_reg1(pi, tau, &gamma_pi, &gamma_pitau);
    return 0.001 * rgas_water * (gamma_pi - tau * gamma_pitau) / r1pstar;
}
