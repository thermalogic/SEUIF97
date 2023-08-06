/*
Region 5: the extended properties

*/
#include <math.h>
#include "../common/constand.h"
#include "region5_coff.h"
#include "region5.h"

#include <math.h>
#include <stdint.h>
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region5.h"
#include "region5_coff.h"

// Region 5: the extended properties
double pT_ext_reg5(double p, double T, int o_id)
{
    double r = 0.0;
    switch (o_id)
    {
    case OKISE:
        r = pT2k_reg5(p, T);
        break;
    case OG:
        r = pT2g_reg5(p, T);
        break;
    case OF:
        r = pT2f_reg5(p, T);
        break;
    case OIJTC:
        r = pT2ijoule_reg5(p, T);
        break;
    case OZ:
        r = pT2z_reg5(p, T);
        break;
    case OKT:
        r = pT2kt_reg5(p, T);
        break;
    case OJTC:
        r = pT2joule_reg5(p, T);
        break;
    case OIPCEC:
        r = pT2ipcec_reg5(p, T);
        break;
    case OE:
        r = pT2e_reg5(p, T);
        break;
    case ODPDT:
        r = pT2dpdtcv_reg5(p, T);
        break;
    case ODVDP:
        r = pT2dvdpct_reg5(p, T);
        break;
    case ODVDT:
        r = pT2dvdtcp_reg5(p, T);
        break;
    default:
        r = INVALID_OUTID;
    }
    return r;
}

// k: isentropic exponent  T K,	p MPa OKISE 11
//    k= -(v/p)*/1000*(dp/dv)s
double pT2k_reg5(double p, double T)
{
    double k;
    double a, b, c, d, e;
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double dgammar_pi = gammar_pi_reg5(pi, tau);

    a = IPOW(1.0 + pi * dgammar_pi, 2);
    b = 1.0 - pi * pi * gammar_pipi_reg5(pi, tau);
    c = 1.0 + pi * (dgammar_pi - tau * gammar_pitau_reg5(pi, tau));
    d = tau * tau * (gamma0_tautau_reg5(tau) + gammar_tautau_reg5(pi, tau));
    e = pi * (gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau));
    k = a / (b + (c * c) / d) / e;
    return k;
}

// kt: Isothermal compressibility, [1/MPa]
//* kt=-(1.0/V)*(dv/dp)T
double pT2kt_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pipi = gamma0_pipi_reg5(pi) + gammar_pipi_reg5(pi, tau);
    double gumma_pi = gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau);
    return -(gumma_pipi / gumma_pi);
}

//  the specific Gibbs free energy, Page 6, Eq(7)
//   g=R*t*gamma
double pT2g_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    return rgas_water * T * (gamma0_reg5(pi, tau) + gammar_reg5(pi, tau));
}

// the Helmholtz Specific free energy:
//  f=u-T*s=R*T(gamma-gamma_pi)
double pT2f_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    return rgas_water * T * (gamma0_reg5(pi, tau) + gammar_reg5(pi, tau) - p * (gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau)));
}

// e
double pT2e_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma = gamma0_reg5(pi, tau) + gammar_reg5(pi, tau);
    double gumma_tau = gamma0_tau_reg5(tau) + gammar_tau_reg5(pi, tau);
    return rgas_water * (T * gumma + (T - Tt) * (tau * gumma_tau - gumma));
}

// coefficient of thermal expansion,
// ipcec-Isobaric cubic expansion coefficient  1/K
// α=(1.0/V)*(dv/dT)p
double pT2ipcec_reg5(double p, double T)
{
    double d = 1.0 / pT2v_reg5(p, T);
    return d * pT2dvdtcp_reg5(p, T);
}

// joule ： Joule-Thomson coefficient    K/MPa
//*  (dt/dp)h
double pT2joule_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pi = gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau);
    double gumma_tautau = gamma0_tautau_reg5(tau) + gammar_tautau_reg5(pi, tau);
    double gumma_pitau = gamma0_pitau_reg5() + gammar_pitau_reg5(pi, tau);
    double v = 0.001 * rgas_water * T * gumma_pi;
    double cp = -rgas_water * tau * tau * gumma_tautau;
    double TCex_1 = -tau * gumma_pitau / gumma_pi;
    return 1000.0 * (v / cp) * TCex_1;
}

//  Isothermal throttling coefficient
// iJTC Isothermal Joule-Thomson coefficient kJ/(kg·MPa)
//*  (dh/dp)t
double pT2ijoule_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pitau = gamma0_pitau_reg5() + gammar_pitau_reg5(pi, tau);
    return 0.001 * rgas_water * r5Tstar * gumma_pitau;
}

// z: Compressibility factor
double pT2z_reg5(double p, double T)
{
    double v = pT2v_reg5(p, T);
    return 1000.0 * p * v / rgas_water / T;
}

// (dp/dt)v MPa/K
double pT2dpdtcv_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pi = gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau);
    double gumma_pitau = gamma0_pitau_reg5() + gammar_pitau_reg5(pi, tau);
    double gumma_pipi = gamma0_pipi_reg5(pi) + gammar_pipi_reg5(pi, tau);
    return r5Pstar * (gumma_pitau * r5Tstar - gumma_pi * T) / (T * T * gumma_pipi);
}

// (dv/dp)T  m3/MPa
double pT2dvdpct_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pipi = gamma0_pipi_reg5(pi) + gammar_pipi_reg5(pi, tau);
    return 0.001 * rgas_water * T * gumma_pipi;
}

// dvdt, cp m3/(kg.K)
double pT2dvdtcp_reg5(double p, double T)
{
    double tau = r5Tstar / T;
    double pi = p / r5Pstar;
    double gumma_pi = gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau);
    double gumma_pitau = gamma0_pitau_reg5() + gammar_pitau_reg5(pi, tau);
    return 0.001 * rgas_water * (gumma_pi - tau * gumma_pitau);
}