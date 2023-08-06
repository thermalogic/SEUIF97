/*  The transfort rroperties:
  Properties():

| Propertry                             |    Unit     | Symbol |   o_id     |
| ------------------------------------- | :---------: |:-----: |:---------: |
|  Dynamic viscosity                    |  kg/(m·s)   |     η  |         24 |
| Kinematic viscosity                   |    m^2/s    |     ν  |         25 |
| Thermal conductivity                  |   W/(m.K)   |     λ  |         26 |
| Thermal diffusivity                   |   um^2/s    |     a  |         27 |
| Prandtl number                        |             |     Pr |         28 |
| Surface tension                       |    mN/m     |     σ  |         29 |

*/
#include <math.h>
#include "../common/constand.h"
#include "../common/common.h"
#include "../common/propertry_id.h"
#include "../algo/algorithm.h"

// Prandtl number=dv*cp/tc
// * dv: Dynamic viscosity Pa.s
// * cp: specific isobaric heat capacity
// * tc: Thermal conductivity   W/(m.K)
double prandtl_number(double dv, double cp, double tc)
{
    return 1.0E+3 * dv * cp / tc;
}

// Thermal diffusivity  m²/s
// * Thermal diffusivity  = 1.0e-3*tc /(cp*d)
//    * cp: specific isobaric heat capacity
//    * tc: Thermal conductivity   W/(m.K)
//    * d  : Density kg/m³
double thermal_diffusivity(double tc, double cp, double d)
{
    return 1.0e-3 * tc / (cp * d);
}

double kinematic_viscosity(double rho, double T)
{
    double dv = viscosity(rho, T);
    return dv / rho;
}

double viscosity(double rho, double T)
/*
   rho : float
       Density [kg/m³]
   T : float
       Temperature [K]
   mu : float
       Viscosity [Pa·s]
   IAPWS, Release on the IAPWS Formulation 2008 for the Viscosity of Ordinary
   Water Substance, http://www.iapws.org/relguide/viscosity.html
*/
{
    double Tr = T / tc_water;
    double Dr = rho / dc_water;

    double no[4] = {1.67752, 2.20462, 0.6366564, -0.241605};
    double suma = 0.0;
    for (int i = 0; i < 4; i++)
    {
        suma += no[i] / IPOW(Tr, i);
    }
    double fi0 = 100.0 * sqrt(Tr) / suma;

    // Page 5 Table2 Coefficients Hij
    IJnData ijH[21] = {
        {0, 0, 5.20094e-1},
        {1, 0, 8.50895e-2},
        {2, 0, -1.08374},
        {3, 0, -2.89555e-1},
        {0, 1, 2.22531e-1},
        {1, 1, 9.99115e-1},
        {2, 1, 1.88797},
        {3, 1, 1.26613},
        {5, 1, 1.20573e-1},
        {0, 2, -2.81378e-1},
        {1, 2, -9.06851e-1},
        {2, 2, -7.72479e-1},
        {3, 2, -4.89837e-1},
        {4, 2, -2.57040e-1},
        {0, 3, 1.61913e-1},
        {1, 3, 2.57399e-1},
        {0, 4, -3.25372e-2},
        {3, 4, 6.98452e-2},
        {4, 5, 8.72102e-3},
        {3, 6, -4.35673e-3},
        {5, 6, -5.93264e-4},
    };

    suma = poly(1.0 / Tr - 1.0, Dr - 1.0, 21, ijH);
    double fi1 = exp(Dr * suma);
    double fi2 = 1.0;
    return fi0 * fi1 * fi2 * 1.0e-6;
}

double thCond(double rho, double T)
/* quation for the thermal conductivity

    rho : float
        Density [kg/m³]
    T : float
        Temperature [K]
    k : float
        Thermal conductivity [W/mK]
    IAPWS, Release on the IAPWS Formulation 2011 for the Thermal Conductivity
    of Ordinary Water Substance, http://www.iapws.org/relguide/ThCond.html
 */
{
    double d = rho / dc_water;
    double Tr = T / tc_water;
    // Page 6 Table 1.  Coefficients Lk in Eq.(16)
    double no[5] = {
        2.443221e-3,
        1.323095e-2,
        6.770357e-3,
        -3.454586e-3,
        4.096266e-4,
    };
    double suma = 0.0;
    for (int i = 0; i < 5; i++)
    {
        suma += no[i] / IPOW(Tr, i);
    }
    double L0 = sqrt(Tr) / suma;
    // Page 6 Table 2.  Coefficients Lij in Eq(17)
    double nij[5][6] = {
        {1.60397357, -0.646013523, 0.111443906, 0.102997357, -0.0504123634, 0.00609859258},
        {2.33771842, -2.78843778, 1.53616167, -0.463045512, 0.0832827019, -0.00719201245},
        {2.19650529, -4.54580785, 3.55777244, -1.40944978, 0.275418278, -0.0205938816},
        {-1.21051378, 1.60812989, -0.621178141, 0.0716373224, 0.0, 0.0},
        {-2.7203370, 4.57586331, -3.18369245, 1.1168348, -0.19268305, 0.012913842},
    };
    suma = 0.0;

    for (int i = 0; i < 5; i++)
    {
        double suma2 = 0.0;
        for (int j = 0; j < 6; j++)

        {
            suma2 += nij[i][j] * IPOW(d - 1.0, j);
        }
        suma += IPOW(1.0 / Tr - 1.0, i) * suma2;
    };

    double L1 = exp(d * suma);

    double L2 = 0.0;
    return 1e-3 * (L0 * L1 + L2);
}

double tension(double T)
/* T : float      Temperature [K]

   Returns  sigma : float    Surface tension [N/m]

   Raises
       * 248.15 ≤ T ≤ 647
       * Estrapolate to -25ºC in supercooled liquid metastable state

   IAPWS, Revised Release on Surface Tension of Ordinary Water Substance
   June 2014, http://www.iapws.org/relguide/Surf-H2O.html
*/
{
    if (248.15 <= T && T <= tc_water)
    {
        double Tr = T / tc_water;
        return 1e-3 * (235.8 * pow(1.0 - Tr, 1.256) * (1.0 - 0.625 * (1.0 - Tr)));
    }
    else
    {
        return INVALID_VALUE;
    };
}
