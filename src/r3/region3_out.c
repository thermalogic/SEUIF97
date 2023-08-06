/*
 Tha API of region3

*/
#include "region3.h"
#include "../common/propertry_id.h"
#include "../common/common.h"
#include "../common/constand.h"

double Td_reg3(double T, double d, int o_id)
// o_id: output propertry
{
    double value;
    switch (o_id)
    {
    case OX:
        value = 1.0;
        break;
    case OR:
        value = 3.0;
        break;
    case OT:
        value = T;
        break;
    case OD:
        value = d;
        break;
    case OV:
        value = 1.0 / d;
        break;
    case OP:
    case OH:
    case OS:
    case OU:
    case OCV:
    case OCP:
    case OW:
        value = Td_thermal_reg3(T, d, o_id);
        break;
    case ODV:
    case OKV:
    case OTC:
    case OTD:
    case OPR:
    case OST:
        value = Td_transport_reg3(T, d, o_id);
        break;
    default:
        value = Td_ext_reg3(T, d, o_id);
        break;
    }
    return value;
}

double Td_transport_reg3(double T, double d, int o_id)
{
    double value;
    double cp;
    double tc;
    double dv;
    switch (o_id)
    {
    case ODV:
    {
        value = viscosity(d, T);
        break;
    }
    case OKV:
    {
        value = kinematic_viscosity(d, T);
        break;
    }
    case OTC:
    {
        value = thCond(d, T);
        break;
    }
    case OTD:
    {
        cp = Td2cp_reg3(T, d);
        tc = thCond(d, T);
        value = thermal_diffusivity(tc, cp, d);
        break;
    }
    case OPR:
    {
        dv = viscosity(d, T);
        cp = Td2cp_reg3(T, d);
        tc = thCond(d, T);
        value = prandtl_number(dv, cp, tc);
        break;
    }
    case OST:
    {
        value = tension(T);
        break;
    }
    default:
    {
        value = INVALID_OUTID;
        break;
    }
    }
    return value;
}

double pT_reg3(double p, double T, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OT)
        return T;
    double d;
    d = 1.0 / pT2v_reg3(p, T);
    return Td_reg3(T, d, o_id);
}

double ph_reg3(double p, double h, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OH)
        return h;

    double d, T;
    d = 1.0 / ph2v_reg3(p, h);
    T = ph2T_reg3(p, h);
    return Td_reg3(T, d, o_id);
}

double ps_reg3(double p, double s, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OS)
        return s;

    double d, T;
    d = 1.0 / ps2v_reg3(p, s);
    T = ps2T_reg3(p, s);
    return Td_reg3(T, d, o_id);
}

double hs_reg3(double h, double s, int o_id)
// o_id: output propertry
{
    if (o_id == OH)
        return h;
    if (o_id == OS)
        return s;

    double p, T, d;
    p = hs2p_reg3(h, s);

    T = ph2T_reg3(p, h);
    d = 1.0 / ph2v_reg3(p, h);

    return Td_reg3(T, d, o_id);
}

// IAPWS-IF97 Region3: The extended input pair
// * (p,v) (t,v), (t,h),(t,s)

///  Region3:  (p,v) T
double pv_reg3(double p, double v, int o_id)
{
    double d = 1.0 / v;
    if (o_id == OD)
    {
        return d;
    };
    double T = pv2T_reg3(p, v);
    if (o_id == OT)
    {
        return T;
    };
    return Td_reg3(T, d, o_id);
}

///  Region3:  (T,v)
double Tv_reg3(double T, double v, int o_id)
{
    double d = 1.0 / v;
    if (o_id == OD)
    {
        return d;
    };
    return Td_reg3(T, d, o_id);
}

//  Region3:  (T,h)
double Th_reg3(double T, double h, int o_id)
{
    double d = Th2d_reg3(T, h);
    if (o_id == OD)
    {
        return d;
    };
    if (o_id == OV)
    {
        return 1.0 / d;
    };
    return Td_reg3(T, d, o_id);
}

//  Region3:  (T,s)
double Ts_reg3(double T, double s, int o_id)
{
    double d = Ts2d_reg3(T, s);
    if (o_id == OD)
    {
        return d;
    };
    if (o_id == OV)
    {
        return 1.0 / d;
    };
    return Td_reg3(T, d, o_id);
}