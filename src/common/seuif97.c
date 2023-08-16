/*
   The API 

*/
#include <math.h>
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r3/region3.h"
#include "../r4/region4.h"
#include "../r5/region5.h"
#include "common.h"
#include "constand.h"
#include "../algo/algorithm.h"
#include "seuif97.h"

IF97_DLL double pt(double p, double t, int o_id)
{
    if (o_id == OT)
    {
        return t;
    }
    else
        return pair_prop(p, t + 273.15, o_id, pT_region, pT_reg1, pT_reg2, pT_reg3, pT_reg4, pT_reg5);
}

IF97_DLL double ph(double p, double h, int o_id)
{
    if (o_id == OT)
    {
        return pair_prop(p, h, o_id, ph_region, ph_reg1, ph_reg2, ph_reg3, ph_reg4, ph_reg5) - 273.15;
    }
    else
        return pair_prop(p, h, o_id, ph_region, ph_reg1, ph_reg2, ph_reg3, ph_reg4, ph_reg5);
}

IF97_DLL double ps(double p, double s, int o_id)
{
    if (o_id == OT)
    {
        return pair_prop(p, s, o_id, ps_region, ps_reg1, ps_reg2, ps_reg3, ps_reg4, ps_reg5) - 273.15;
    }
    else
        return pair_prop(p, s, o_id, ps_region, ps_reg1, ps_reg2, ps_reg3, ps_reg4, ps_reg5);
}

IF97_DLL double hs(double h, double s, int o_id)
{
    if (o_id == OT)
    {
        return pair_prop(h, s, o_id, hs_region, hs_reg1, hs_reg2, hs_reg3, hs_reg4, hs_reg5) - 273.15;
    }
    else
        return pair_prop(h, s, o_id, hs_region, hs_reg1, hs_reg2, hs_reg3, hs_reg4, hs_reg5);
}

IF97_DLL double px(double p, double x, int o_id)
{
    if (o_id == OT)
    {
        return px_reg4(p, x, o_id) - 273.15;
    }
    else
        return px_reg4(p, x, o_id);
}

IF97_DLL double tx(double t, double x, int o_id)
{
    double T = t + 273.15;
    return Tx_reg4(T, x, o_id);
}

IF97_DLL double pv(double p, double v, int o_id)
{
    double value = pair_prop(p, v, o_id, pv_region, pv_reg1, pv_reg2, pv_reg3, pv_reg4, pv_reg5);

    if (o_id == OT)
    {
        return value - 273.15;
    }
    else
    {
        return value;
    }
}

IF97_DLL double th(double t, double h, int o_id)
{
    if (o_id == OT)
    {
        return t;
    }
    else if (o_id == OH)
    {
        return h;
    }
    double T = t + 273.15;
    double value = pair_prop(T, h, o_id, Th_region, Th_reg1, Th_reg2, Th_reg3, Th_reg4, Th_reg5);
    return value;
}

IF97_DLL double ts(double t, double s, int o_id)
{
    if (o_id == OT)
    {
        return t;
    }
    else if (o_id == OS)
    {
        return s;
    }
    double T = t + 273.15;
    double value = pair_prop(T, s, o_id, Ts_region, Ts_reg1, Ts_reg2, Ts_reg3, Ts_reg4, Ts_reg5);
    return value;
}

IF97_DLL double tv(double t, double v, int o_id)
{
    if (o_id == OT)
    {
        return t;
    }
    else if (o_id == OV)
    {
        return v;
    }
    else if (o_id == OD)
    {
        return 1.0 / v;
    }
    double T = t + 273.15;
    double value = pair_prop(T, v, o_id, Tv_region, Tv_reg1, Tv_reg2, Tv_reg3, Tv_reg4, Tv_reg5);
    return value;
}

// sehx(h,x,o_id) - the propertry of `o_id`(thermodynamic)
IF97_DLL double hx(double h, double x, int o_id)
{
    if ((h > HMAX4) || (h < HMIN4) || (x > 1.0) || (x < 0.0))
    {
        return INVALID_VALUE;
    }
    if (o_id == OH)
        return h;
    else if (o_id == OX)
        return x;
    double value = hx_reg4(h, x, o_id);
    if (o_id == OT)
    {
        return value - 273.15;
    }
    return value;
}

// seusx(s,x,o_id) - the propertry of `o_id`(thermodynamic)
IF97_DLL double sx(double s, double x, int o_id)
{
    if ((s > SMAX4) || (s < SMIN4) || (x > 1.0) || (x < 0.0))
    {
        return INVALID_VALUE;
    };
    if (o_id == OS)
        return s;
    else if (o_id == OX)
        return x;
    double value = sx_reg4(s, x, o_id);
    if (o_id == OT)
    {
        return value - 273.15;
    }
    return value;
}
