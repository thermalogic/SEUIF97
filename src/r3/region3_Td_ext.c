// Region3: The extended Properties
//
//  Td_ext_reg3(T: f64, d: f64, o_id: i32) -> f64
//
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"
#include "region3.h"
#include "region3_coff.h"
#include "region3_solo_ij.h"

double Td_ext_reg3(double T, double d, int o_id)
{
    double r = 0.0;
    switch (o_id)
    {
    case OE:
        r = Td2e_reg3(T, d);
        break;
    case OKISE:
        r = Td2k_reg3(T, d);
        break;
    case OF:
        r = Td2f_reg3(T, d);
        break;
    case OG:
        r = Td2g_reg3(T, d);
        break;
    case OZ:
        r = Td2z_reg3(T, d);
        break;
    case OKT:
        r = Td2kt_reg3(T, d);
        break;
    case OIPCEC:
        r = Td2ipcec_reg3(T, d);
        break;
    case ODVDP:
        r = Td2dvdpct_reg3(T, d);
        break;

    case ODVDT:
        r = Td2dvdtcp_reg3(T, d);
        break;
    case ODPDT:
        r = Td2dpdtcv_reg3(T, d);
        break;
    case OJTC:
        r = Td2joule_reg3(T, d);
        break;
    case OIJTC:
        r = Td2ijoule_reg3(T, d);
        break;
    default:
        r = INVALID_OUTID;
    }
    return r;
}

//  the specific Gibbs free energy,
//    g=R*T*(phi+delta* phi_delta )
double Td2g_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    double phi = phi_reg3(delta, tau);
    double phi_delta = phi_delta_reg3(delta, tau);
    return rgas_water * T * (phi + delta * phi_delta);
}

// the Helmholtz Specific free energy
double Td2f_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    double phi = phi_reg3(delta, tau);
    return rgas_water * T * phi;
}

// k: Isentropic exponent
//  k= -(v/p)*/1000*(dp/dv) The book 2019 Page 37
double Td2k_reg3(double T, double d)
{
    double w = Td2w_reg3(T, d);
    double p = Td2p_reg3(T, d);
    return 1.0E-6 * w * w * d / p;
}

/// z: Compressibility factor
double Td2z_reg3(double T, double d)
{
    double v = 1.0 / d;
    double p = Td2p_reg3(T, d);
    return 1000.0 * p * v / rgas_water / T;
}

// (dv/dp)T
double Td2dvdpct_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    double ddeltadpi = 2.0 * phi_delta_reg3(delta, tau) + delta * phi_deltadelta_reg3(delta, tau);
    ddeltadpi = d * rgas_water * T * ddeltadpi;
    return -1000.0 * dc_water / d / d / ddeltadpi;
}

/// (dv/dt)p
double Td2dvdtcp_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    double ddelta = phi_delta_reg3(delta, tau);
    double d1 = ddelta - tau * phi_deltatau_reg3(delta, tau);
    double d2 = 2.0 * ddelta + delta * phi_deltadelta_reg3(delta, tau);
    return d1 / d2 / T / d;
}

// kT: Isothermal compressibility, 1/MPa
double Td2kt_reg3(double T, double d)
{
    return -d * Td2dvdpct_reg3(T, d);
}

/// ipcec-Isobaric cubic expansion coefficient  1/K
double Td2ipcec_reg3(double T, double d)
{
    return d * Td2dvdtcp_reg3(T, d);
}

/// e: Specific exergy    kJ/kg
double Td2e_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    double phi = phi_reg3(delta, tau);
    double phi_delta = phi_delta_reg3(delta, tau);
    double phi_tau = phi_tau_reg3(delta, tau);
    return rgas_water * (T * (phi + delta * phi_delta) + (T - Tt) * tau * (phi_tau - phi));
}

//  (dp/dT)v
double Td2dpdtcv_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    return 0.001 * rgas_water * d * delta * (phi_delta_reg3(delta, tau) - tau * phi_deltatau_reg3(delta, tau));
}

// joule ： Joule-Thomson coefficient    K/MPa
// *  (dt/dp)h
double Td2joule_reg3(double T, double d)
{
    double tau = tc_water / T;
    double delta = d / dc_water;

    double v = 1.0 / d;
    double ddelta = phi_delta_reg3(delta, tau);
    double ddeltatau = phi_deltatau_reg3(delta, tau);
    double ddeltadelta = phi_deltadelta_reg3(delta, tau);

    double cp1 = delta * (ddelta - tau * ddeltatau);
    cp1 *= cp1;
    double cp2 = delta * (2.0 * ddelta + delta * ddeltadelta);
    double cp = rgas_water * (-1.0 * tau * tau * phi_tautau_reg3(delta, tau) + cp1 / cp2);

    double d1 = ddelta - tau * ddeltatau;           // dpdtcv
    double d2 = 2.0 * ddelta + delta * ddeltadelta; // dvdpct
    double cex = d1 / d2 / T;
    return 1000.0 * (v / cp) * (T * cex - 1.0);
}

//  Isothermal throttling coefficient
//  iJTC Isothermal Joule-Thomson coefficient kJ/(kg·MPa)
// *  (dh/dp)t
double Td2ijoule_reg3(double T, double d)
{
    return -Td2cp_reg3(T, d) * Td2joule_reg3(T, d) / 1000.0;
}
