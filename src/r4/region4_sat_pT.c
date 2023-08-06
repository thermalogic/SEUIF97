
/*
   saturation pressure of water
   saturation temperature of water
*/ 
#include <math.h>
#include "region4.h"
#include "../algo/algorithm.h"
//
//  Initialize coefficients for region 4
//
static double n[11] = {0, 0.11670521452767E+04, -0.72421316703206E+06, -0.17073846940092E+02,
                       0.12020824702470E+05, -0.32325550322333E+07, 0.14915108613530E+02,
                       -0.48232657361591E+04, 0.40511340542057E+06, -0.23855557567849E+00,
                       0.65017534844798E+03};

double pSat(double T)
// saturation pressure of water
// pSatW in bar
// T :temperaturein K
//
// pSat = -1: temperature outside range
//
{
    double pS;
    if (T < 273.15 || T > 647.096) // tc_water=647.096
        pS = -1.0;
    else
    {
        double del = T + n[9] / (T - n[10]);
        double aco = del * (del + n[1]) + n[2];
        double bco = del * (n[3] * del + n[4]) + n[5];
        double cco = del * (n[6] * del + n[7]) + n[8];
        pS = IPOW(2 * cco / (-bco + sqrt(bco * bco - 4 * aco * cco)), 4);
    }
    return pS;
}

double TSat(double p)
//
// saturation temperature of water
// tSatW in K
// p :pressure in bar
//
// tSatW=-1: pressure outside range
//
{
    double TS;
    if (p < 0.000611212677 || p > 22.064)
        TS = -1.0;
    else
    {
        double bet = pow(p, 0.25);
        double eco = bet * (bet + n[3]) + n[6];
        double fco = bet * (n[1] * bet + n[4]) + n[7];
        double gco = bet * (n[2] * bet + n[5]) + n[8];
        double dco = 2.0 * gco / (-fco - sqrt(fco * fco - 4.0 * eco * gco));
        TS = 0.5 * (n[10] + dco - sqrt((n[10] + dco) * (n[10] + dco) - 4.0 * (n[9] + n[10] * dco)));
    }
    return TS;
}
