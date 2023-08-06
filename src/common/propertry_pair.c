// Transport
//  1.  pT_transport -> 1，2，5
//  2  Td_transport_reg3  in region3_out.c
#include "../common/common.h"
#include "../common/propertry_id.h"
#include "../common/constand.h"
#include "../algo/algorithm.h"
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r3/region3.h"
#include "../r4/region4.h"
#include "../r5/region5.h"

double pT_transport(double p, double T, int o_id, properties_region fn)
{
    double value;
    double d;
    double cp;
    double tc;
    double dv;
    switch (o_id)
    {
    case ODV:
    {
        d = (*fn)(p, T, OD);
        value = viscosity(d, T);
        break;
    }
    case OKV:
    {
        d = (*fn)(p, T, OD);
        value = kinematic_viscosity(d, T);
        break;
    }
    case OTC:
    {
        d = (*fn)(p, T, OD);
        value = thCond(d, T);
        break;
    }
    case OTD:
    {
        d = (*fn)(p, T, OD);
        cp = (*fn)(p, T, OCP);
        tc = thCond(d, T);
        value = thermal_diffusivity(tc, cp, d);
        break;
    }
    case OPR:
    {
        d = (*fn)(p, T, OD);
        dv = viscosity(d, T);
        cp = (*fn)(p, T, OCP);
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

double pair_prop(double v1, double v2, int o_id, region_fn regfn,
                 prop_fn fn1,
                 prop_fn fn2,
                 prop_fn fn3,
                 prop_fn fn4,
                 prop_fn fn5)
{

    int region = (*regfn)(v1, v2);
    double v;
    switch (region)
    {
    case 1:
        v = fn1(v1, v2, o_id);
        break;
    case 2:
        v = fn2(v1, v2, o_id);
        break;
    case 3:
        v = fn3(v1, v2, o_id);
        break;
    case 4:
        v = fn4(v1, v2, o_id);
        break;
    case 5:
        v = fn5(v1, v2, o_id);
        break;
    default:
        v = region;
        break;
    }
    return v;
}

double pT(double p, double T, int o_id)
{
    return pair_prop(p, T, o_id, pT_region, pT_reg1, pT_reg2, pT_reg3, pT_reg4, pT_reg5);
}

double pT_reg(double p, double T, int o_id, properties_region pT_thermal, properties_region pT_ext)
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
    case OD:
    case OH:
    case OS:
    case OU:
    case OCV:
    case OCP:
    case OW:
        value = pT_thermal(p, T, o_id);
        break;
    case ODV:
    case OKV:
    case OTC:
    case OTD:
    case OPR:
    case OST:
        value = pT_transport(p, T, o_id, pT_thermal);
        break;
    default:
        value = pT_ext(p, T, o_id);
        break;
    }
    return value;
}
