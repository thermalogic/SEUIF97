/*
 The APT of region 2

*/
#include "region2.h"
#include "../common/propertry_id.h"
#include "../common/common.h"

double pT_reg2(double p, double T, int o_id)
// o_id: output propertry
{
    double value = 0.0;
    switch (o_id)
    {
    case OX:
        value = 1.0;
        break;
    case OR:
        value = 2.0;
        break;
    default:
        value = pT_reg(p, T, o_id, pT_thermal_reg2, pT_ext_reg2);
        break;
    }
    return value;
}

double ph_reg2(double p, double h, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OH)
        return h;

    double T;
    T = ph2T_reg2(p, h);
    return pT_reg2(p, T, o_id);
}

double ps_reg2(double p, double s, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OS)
        return s;

    double T;
    T = ps2T_reg2(p, s);
    return pT_reg2(p, T, o_id);
}

double hs_reg2(double h, double s, int o_id)
// o_id: output propertry
{
    if (o_id == OH)
        return h;
    if (o_id == OS)
        return s;

    double p;
    p = hs2p_reg2(h, s);
    return ph_reg2(p, h, o_id);
}

//----------------------------------------
// the extend input pairs (p,v) T
//------------------------------------------------------------------
double pv_reg2(double p, double v, int o_id)
// o_id: output propertry
{
    if (o_id == OP)
        return p;
    if (o_id == OV)
        return v;

    double T;
    T = pv2T_reg2(p, v);
    return pT_reg2(p, T, o_id);
}

double Tv_reg2(double T, double v, int o_id)
// o_id: output propertry
{
    if (o_id == OT)
        return T;
    if (o_id == OV)
        return v;

    double p;
    p = Tv2p_reg2(T, v);
    return pT_reg2(p, T, o_id);
}

// (T,s)
double Ts_reg2(double T, double s, int o_id)
// o_id: output propertry
{
    if (o_id == OT)
        return T;
    if (o_id == OS)
        return s;

    double p;
    p = Ts2p_reg2(T, s);
    return pT_reg2(p, T, o_id);
}

// (T,h)
double Th_reg2(double T, double h, int o_id)
// o_id: output propertry
{
    if (o_id == OT)
        return T;
    if (o_id == OH)
        return h;

    double p = Th2p_reg2(T, h);
    if (o_id == OP)
        return p;

    return pT_reg2(p, T, o_id);
}