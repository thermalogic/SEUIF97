/*
 Region 4 - The extended input pairs: (p,v)->x, (t,v),(t,h),(t,s) ->x
    x: Steam quality
*/
#include <math.h>
#include <stdio.h>
#include "../algo/algorithm.h"
#include "../common/common.h"
#include "../common/constand.h"
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r3/region3.h"
#include "region4.h"

/// Region 4: (p,v)-> x
double pv2x_reg4(double p, double v)
{
    double v_sat_w = p2SatWater(p, OV);
    double v_sat_s = p2SatSteam(p, OV);
    return (v - v_sat_w) / (v_sat_s - v_sat_w);
}

/// Region 4: (T,v)-> x
double Tv2x_reg4(double T, double v)
{
    double v_sat_w = T2SatWater(T, OV);
    double v_sat_s = T2SatSteam(T, OV);
    return (v - v_sat_w) / (v_sat_s - v_sat_w);
}

/// Region 4: (T,h)-> x
double Th2x_reg4(double T, double h)
{
    double h_sat_w = T2SatWater(T, OH);
    double h_sat_s = T2SatSteam(T, OH);
    return (h - h_sat_w) / (h_sat_s - h_sat_w);
}

/// Region 4: (T,s)-> x
double Ts2x_reg4(double T, double s)
{
    double s_sat_w = T2SatWater(T, OS);
    double s_sat_s = T2SatSteam(T, OS);
    return (s - s_sat_w) / (s_sat_s - s_sat_w);
}
