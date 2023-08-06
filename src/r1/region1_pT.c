/* -------------------------------------------------------------------------
  IAPWS-IF97 Region1:
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
----------------------------------------------------------------*/
#include <math.h>
#include <stdint.h>
#include "../common/constand.h"
#include "../algo/algorithm.h"
#include "region1.h"
#include "region1_coff.h"
#include "region1_solo_ij.h"

double pT_thermal_reg1(double p, double T, int o_id)
// o_id: output propertry
{
    double value;
    switch (o_id)
    {
    case OV:
        value = pT2v_reg1(p, T);
        break;
    case OD:
        value = 1.0 / pT2v_reg1(p, T);
        break;
    case OH:
        value = pT2h_reg1(p, T);
        break;
    case OS:
        value = pT2s_reg1(p, T);
        break;
    case OU:
        value = pT2u_reg1(p, T);
        break;
    case OCV:
        value = pT2cv_reg1(p, T);
        break;
    case OCP:
        value = pT2cp_reg1(p, T);
        break;
    case OW:
        value = pT2w_reg1(p, T);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}


double pT2v_reg1(double p, double T)
// specific volume in region 1
{
  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;
  return 0.001 * rgas_water * T * pi * gamma_pi_reg1(pi,tau) / p;
}

double pT2u_reg1(double p, double T)
// specific internal energy in region 1
{
  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;
  // return rgas_water * T *
  //       (tau * gammatau_reg1(pi,tau) - pi * gammapi_reg1(pi,tau));

  double gammapi = 0.0;
  double gammatau = 0.0;
  //polys_solo_i_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, &gammapi, &gammatau);

  polys_solo_i_j_reg1(pi, tau, &gammapi, &gammatau);
  return rgas_water * T * (tau * gammatau - pi * gammapi);
}

double pT2s_reg1(double p, double T)
// specific entropy in region 1
{

  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;
  // return rgas_water * (tau * gammatau_reg1(pi,tau) - gamma_reg1(pi,tau));

  double gamma = 0.0;
  double gammatau = 0.0;

  // polys_0_j(7.1 - pi, tau - 1.222,34,IJn,&gamma,&gammatau);
  polys_solo_0_j_reg1(pi, tau, &gamma, &gammatau);  
  return rgas_water * (tau * gammatau - gamma);
}

double pT2h_reg1(double p, double T)
// specific enthalpy in region 1
{
  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;
  return rgas_water * T * tau * gamma_tau_reg1(pi,tau);

  //double gammatau = poly_solo_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
  //return rgas_water * T * tau * gammatau;
}

double pT2cp_reg1(double p, double T)
// specific isobaric heat capacity in region 1
{
  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;
   return -rgas_water * tau * tau * gamma_tautau_reg1(pi, tau);

  //double gammatautau = poly_solo_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1);
  //return -rgas_water * tau * tau * gammatautau;
}

double pT2cv_reg1(double p, double T)
// specific isochoric heat capacity in region 1
// cv in kJ/(kg K), T in K, p in MPa
{

  double pi, tau, a, b;
  tau = r1Tstar / T;
  pi = p / r1pstar;

  // a = -tau * tau * gammatautau_reg1(pi,tau);
  // b = gammapi_reg1(pi,tau) - tau * gammapitau_reg1(pi,tau);
  // b *= b;
  // return rgas_water * (a + b / gammapipi_reg1(pi,tau));

  double poly_pi = 0;
  double poly_pitau = 0;
  double poly_pipi = 0;
  double poly_tautau = 0;
  // polys_i_ii_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);

  //polys_solo_i_ii_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);
  polys_solo_i_ii_ij_jj_reg1(pi, tau, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);
  a = -tau * tau * poly_tautau;
  b = poly_pi - tau * poly_pitau;
  b *= b;
  return rgas_water * (a + b / poly_pipi);
}

double pT2w_reg1(double p, double T)
// speed of sound in region 1
// w in m/s, T in K, p in Mpa
{
  double pi, tau, gammapi, a, b;
  tau = r1Tstar / T;
  pi = p / r1pstar;

  /*
  gammapi = gammapi_reg1(pi,tau);
  a = gammapi - tau * gammapitau_reg1(pi,tau);
  a *= a;
  b = a / (tau * tau * gammatautau_reg1(pi,tau));
  b = b - gammapipi_reg1(pi,tau);
  return gammapi * sqrt(1000.0 * rgas_water * T / b);
*/

  double poly_pi = 0;
  double poly_pitau = 0;
  double poly_pipi = 0;
  double poly_tautau = 0;
//  polys_i_ii_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);

  //polys_solo_i_ii_ij_jj(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);

  polys_solo_i_ii_ij_jj_reg1(pi, tau, &poly_pi, &poly_pipi, &poly_pitau, &poly_tautau);
  a = poly_pi - tau * poly_pitau;
  a *= a;
  b = a / (tau * tau * poly_tautau);
  b = b - poly_pipi;
  return poly_pi * sqrt(1000.0 * rgas_water * T / b);
}
