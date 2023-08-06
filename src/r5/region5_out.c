/*
 The API of region5

*/
#include "region5.h"
#include "../common/propertry_id.h"
#include "../common/constand.h"

double pT_reg5(double p, double T, int o_id)
// o_id: output propertry
{
    double value = 0.0;
    switch (o_id)
    {
    case OX:
        value = 2.0;
        break;
    case OR:
        value = 5.0;
        break;
    default:
        value = pT_reg(p, T, o_id, pT_thermal_reg5, pT_ext_reg5);
        break;
    }
    return value;
}

double ph_reg5(double p, double h, int o_id)
// o_id: output propertry
{
    double T, value;
    switch (o_id)
    {
    case OP:
        value = p;
        break;
    case OH:
        value = h;
        break;
    case OT:
        value = ph2T_reg5(p, h);
        break;
    case OV:
        T = ph2T_reg5(p, h);
        value = pT2v_reg5(p, T);
        break;
    case OD:
        T = ph2T_reg5(p, h);
        value = 1.0 / pT2v_reg5(p, T);
        break;
    case OS:
        T = ph2T_reg5(p, h);
        value = pT2s_reg5(p, T);
        break;
    case OCV:
        T = ph2T_reg5(p, h);
        value = pT2cv_reg5(p, T);
        break;
    case OCP:
        T = ph2T_reg5(p, h);
        value = pT2cp_reg5(p, T);
        break;
    case OW:
        T = ph2T_reg5(p, h);
        value = pT2w_reg5(p, T);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}

double ps_reg5(double p, double s, int o_id)
// o_id: output propertry
{
    double T, value;
    switch (o_id)
    {
    case OP:
        value = p;
        break;
    case OS:
        value = s;
        break;
    case OT:
        value = ps2T_reg5(p, s);
        break;
    case OV:
        T = ps2T_reg5(p, s);
        value = pT2v_reg5(p, T);
        break;
    case OD:
        T = ps2T_reg5(p, s);
        value = 1.0 / pT2v_reg5(p, T);
        break;
    case OH:
        T = ps2T_reg5(p, s);
        value = pT2h_reg5(p, T);
        break;
    case OCV:
        T = ps2T_reg5(p, s);
        value = pT2cv_reg5(p, T);
        break;
    case OCP:
        T = ps2T_reg5(p, s);
        value = pT2cp_reg5(p, T);
        break;
    case OW:
        T = ph2T_reg5(p, s);
        value = pT2w_reg5(p, T);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}

double hs_reg5(double h, double s, int o_id)
// o_id: output propertry
{
    double p, value;
    switch (o_id)
    {
    case OH:
        value = h;
        break;
    case OS:
        value = s;
        break;
    case OP:
        value = hs2p_reg5(h, s);
        break;
    case OT:
    case OV:
    case OCP:
    case OCV:
    case OW:
    case OU:
        p = hs2p_reg5(h, s);
        value = ph_reg5(p, h, o_id);
        break;
    default:
        value = INVALID_OUTID;
        break;
    }
    return value;
}

//-----------------------------------------------------
// Region 5 : The extended input pair: (p,v), (t,v),(t,h),(t,s)
//-----------------------------------------------
//  Region 5 :(p,v) T
double pv_reg5(double p, double v, int o_id)
{
    double T = pv2T_reg5(p, v);
    if (o_id == OT)
    {
        return T;
    };
    return pT_reg5(p, T, o_id);
}

//  Region 5 : (T,v)
double Tv_reg5(double T, double v, int o_id)
{
    if (o_id == OD)
    {
        return 1.0 / v;
    };
    double p = Tv2p_reg5(T, v);
    if (o_id == OP)
    {
        return p;
    };
    return pT_reg5(p, T, o_id);
}

///   Region 5 :(T,h)
double Th_reg5(double T, double h, int o_id)
{
    double p = Th2p_reg5(T, h);
    if (o_id == OP)
    {
        return p;
    };
    return pT_reg5(p, T, o_id);
}

///  Region 5 : (T,s)
double Ts_reg5(double T, double s, int o_id)
{
    double p = Ts2p_reg5(T, s);
    if (o_id == OP)
    {
        return p;
    };
    return pT_reg5(p, T, o_id);
}
