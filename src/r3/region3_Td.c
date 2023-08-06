
#include <math.h>
#include <stdio.h>
#include "../algo/algorithm.h"
#include "../common/constand.h"
#include "../common/common.h"
#include "region3_solo_ij.h"
#include "region3_coff.h"
#include "region3.h"
#include "../common/propertry_id.h"

double Td_thermal_reg3(double T, double d, int o_id)
// o_id: output propertry
{
    double value;
    switch (o_id)
    {
    case OT:
        value = T;
        break;
    case OD:
        value = d;
        break;
    case OV:
        value = 1 / d;
        break;
    case OP:
        value = Td2p_reg3(T, d);
        break;
    case OH:
        value = Td2h_reg3(T, d);
        break;
    case OS:
        value = Td2s_reg3(T, d);
        break;
    case OU:
        value = Td2u_reg3(T, d);
        break;
    case OCV:
        value = Td2cv_reg3(T, d);
        break;
    case OCP:
        value = Td2cp_reg3(T, d);
        break;
    case OW:
        value = Td2w_reg3(T, d);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}

double Td2p_reg3(double T, double d)
//
// pressure in region 3
// preg3 in bar
// T: temperature in K
// density in kg/m^3
//
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    // return 0.001 * d * rgas_water * T * delta * phidelta_reg3(delta,tau);
    double phidelta = phi_delta_reg3(delta, tau);
    return 0.001 * d * rgas_water * T * delta * phidelta;
}

double Td2u_reg3(double T, double d)
// speciphic internal energy in region 3
// energyreg3 in kJ/kg
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    // return rgas_water * T * tau * phi_tau_reg3(delta,tau);
    double phi_tau = phi_tau_reg3(delta, tau);
    return rgas_water * T * tau * phi_tau;
}

double Td2s_reg3(double T, double d)
// speciphic entropy in region 3
// entropyreg3 in kJ/(kg K)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    // return rgas_water * (tau * phi_tau_reg3(delta,tau) - phi_reg3(delta,tau));

    double phi = 0.0;
    double phi_tau = 0.0;
    polys_solo_0_j_reg3(delta, tau, &phi, &phi_tau);
    return rgas_water * (tau * phi_tau - phi);
}

double Td2h_reg3(double T, double d)
// speciphic enthalpy in region 3
// enthalpyreg3 in kJ/kg
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    // return rgas_water * T * (tau * phi_tau_reg3(delta,tau) + delta * phidelta_reg3(delta,tau));
    double phidelta = 0.0;
    double phi_tau = 0.0;
    polys_solo_i_j_reg3(delta, tau, &phidelta, &phi_tau);
    return rgas_water * T * (tau * phi_tau + delta * phidelta);
}

double Td2cp_reg3(double T, double d)
// speciphic isobaric heat capacity in region 3
// cpreg3 in kJ/(kg K)
{
    double tau = tc_water / T;
    double delta = d / dc_water;

    // double a = delta * (phidelta_reg3(delta,tau) - tau * phideltatau_reg3(delta,tau));
    // a *= a;
    // double b = delta * (2.0 * phidelta_reg3(delta,tau) + delta * phideltadelta_reg3(delta,tau));
    // return rgas_water * (-tau * tau * phi_tautau_reg3(delta,tau) + a / b);

    double poly_delta = 0;
    double poly_deltatau = 0;
    double poly_deltadelta = 0;
    double poly_tautau = 0;
    polys_solo_i_ii_ij_jj_reg3(delta, tau, &poly_delta, &poly_deltadelta, &poly_deltatau, &poly_tautau);

    double a = delta * (poly_delta - tau * poly_deltatau);
    a *= a;
    double b = delta * (2.0 * poly_delta + delta * poly_deltadelta);
    return rgas_water * (-tau * tau * poly_tautau + a / b);
}

double Td2cv_reg3(double T, double d)
// speciphic isochoric heat capacity in region 3
// cvreg3 in kJ/(kg K)
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    // return rgas_water * (-tau * tau * phi_tautau_reg3(delta,tau));

    double phi_tautau = phi_tautau_reg3(delta, tau);
    return rgas_water * (-tau * tau * phi_tautau);
}

double Td2w_reg3(double T, double d)
// speed of sound in region 3 in m/s
{
    double tau = tc_water / T;
    double delta = d / dc_water;
    /*

        double a = delta * phidelta_reg3(delta,tau) - delta * tau * phideltatau_reg3(delta,tau);
        a *= a;
        double r=1000.0 * rgas_water * T * (2 * delta * phidelta_reg3(delta,tau) + delta * delta * phideltadelta_reg3(delta,tau) - a / (tau * tau * phi_tautau_reg3(delta,tau)));
        return sqrt(1000.0 * rgas_water * T * (2 * delta * phidelta_reg3(delta,tau) + delta * delta * phideltadelta_reg3(delta,tau) - a / (tau * tau * phi_tautau_reg3(delta,tau))));
    */
    double poly_delta = 0;
    double poly_deltatau = 0;
    double poly_deltadelta = 0;
    double poly_tautau = 0;

    polys_solo_i_ii_ij_jj_reg3(delta, tau, &poly_delta, &poly_deltadelta, &poly_deltatau, &poly_tautau);
    double a = delta * (poly_delta - tau * poly_deltatau);
    a *= a;
    double r = 1000.0 * rgas_water * T * (delta * (2.0 * poly_delta + delta * poly_deltadelta) - a / (tau * tau * poly_tautau));
    return sqrt(r);
}
