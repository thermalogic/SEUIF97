/*
  boundaries

*/
#include <math.h>
#include "common.h"
#include "constand.h"
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r4/region4.h"

double B23_T2p(double T)
// IF97-rev Boundary between Regions 2 and 3
// T in K
// returns p between regions 2 and 3 in MPa
{
    const double n23[] = {0.34805185628969e3, -0.11671859879975e1, 0.10192970039326e-2};
    double result = n23[0] + (n23[1] + n23[2] * T) * T;
    return result;
}

double B23_p2T(double p)
//IF97-rev Table 5, pag 9
// Auxiliary equation for the boundary 2-3
// p is pressure in MPa
// returns temperature between regions 2 and 3 in K
{
    const double n23[] = {0.10192970039326e-2, 0.57254459862746e3, 0.13918839778870e2};
    double result = n23[1] + pow((p - n23[2]) / n23[0], 0.5);
    return result;
}

//-------------------------------------------------------
//  http://www.iapws.org/relguide/Supp-Tv(ph,ps)-2014.pdf
//----------------------------------------------------------

double h2pSat_reg3(double h)
/* 
   03 – IAPWS-IF97-S03 rev :supp tv(ph,ps)2 2014 supplementary 03 for region 3 
  http://www.iapws.org/relguide/Supp-Tv(ph,ps)-2014.pdf, Eq 10

  The equation p 3sat(h) describes the saturated liquid line and the
saturated vapor line including the critical point in the enthalpy range (see Figure 3):

   h'(623.15K) ≤ h ≤ h''(623.15K)
     _PSat_h(1700)    17.24175718
     _PSat_h(2400)    20.18090839
*/
{
    // Table 18 page 18
    const int I[] = {0, 1, 1, 1, 1, 5, 7, 8, 14, 20, 22, 24, 28, 36};
    const int J[] = {0, 1, 3, 4, 36, 3, 0, 24, 16, 16, 3, 18, 8, 24};
    const double n[] = {0.600073641753024, -0.936203654849857e1, 0.246590798594147e2,
                        -0.107014222858224e3, -0.915821315805768e14, -0.862332011700662e4,
                        -0.235837344740032e2, 0.252304969384128e18, -0.389718771997719e19,
                        -0.333775713645296e23, 0.356499469636328e11, -0.148547544720641e27,
                        0.330611514838798e19, 0.813641294467829e38};

    double hmin_Ps3 = pT2h_reg1(Ps_623, 623.15);
    double hmax_Ps3 = pT2h_reg2(Ps_623, 623.15);
    if (h < hmin_Ps3 || h > hmax_Ps3)
        return INVALID_H;

    double nu = h / 2600;
    double suma = 0;
    for (int i = 0; i < 14; i++)
        suma += n[i] * pow(nu - 1.02, I[i]) * pow(nu - 0.608, J[i]);
    return 22 * suma;
}

double s2pSat_reg3(double s)
/* http://www.iapws.org/relguide/Supp-Tv%28ph,ps%293-2014.pdf, Eq 11
   Define the saturated line, P=f(s) for region 3
    s'(623.15K) ≤ s ≤ s''(623.15K)
    _PSat_s(3.8)  ->  16.87755057
    _PSat_s(5.2)  -> 16.68968482
 */
{
    double sigma = s / 5.2;
    const int I[] = {0, 1, 1, 4, 12, 12, 16, 24, 28, 32};
    const int J[] = {0, 1, 32, 7, 4, 14, 36, 10, 0, 18};
    const double n[] = {0.639767553612785, -0.129727445396014e2, -0.224595125848403e16,
                        0.177466741801846e7, 0.717079349571538e10, -0.378829107169011e18,
                        -0.955586736431328e35, 0.187269814676188e24, 0.119254746466473e12,
                        0.110649277244882e37};

    // Check input parameters
    double smin_Ps3 = pT2s_reg1(Ps_623, 623.15);
    double smax_Ps3 = pT2s_reg2(Ps_623, 623.15);
    if (s < smin_Ps3 || s > smax_Ps3)
        return INVALID_S;

    double suma = 0;
    for (int i = 0; i < 10; i++)
        suma += n[i] * pow(sigma - 1.03, I[i]) * pow(sigma - 0.699, J[i]);
    return 22 * suma;
}

//------------------------------------------------------------------------
//   http://www.iapws.org/relguide/Supp-phs3-2014.pdf. region3 （h,s) ->p
//---------------------------------------------------------------------

double _h1_s(double s)
/* Define the saturated line boundary between Region 1 and 4, h=f(s)
   http://www.iapws.org/relguide/Supp-phs3-2014.pdf. Eq 3

    >>> _h1_s(1) 308.5509647
    >>> _h1_s(3)  1198.359754
*/
{

    const int I[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 7, 8, 12, 12, 14, 14, 16, 20,
                     20, 22, 24, 28, 32, 32};
    const int J[] = {14, 36, 3, 16, 0, 5, 4, 36, 4, 16, 24, 18, 24, 1, 4, 2, 4, 1, 22, 10,
                     12, 28, 8, 3, 0, 6, 8};
    const double n[] = {0.332171191705237, 0.611217706323496e-3, -0.882092478906822e1,
                        -0.455628192543250, -0.263483840850452e-4, -0.223949661148062e2,
                        -0.428398660164013e1, -0.616679338856916, -0.146823031104040e2,
                        0.284523138727299e3, -0.113398503195444e3, 0.115671380760859e4,
                        0.395551267359325e3, -0.154891257229285e1, 0.194486637751291e2,
                        -0.357915139457043e1, -0.335369414148819e1, -0.664426796332460,
                        0.323321885383934e5, 0.331766744667084e4, -0.223501257931087e5,
                        0.573953875852936e7, 0.173226193407919e3, -0.363968822121321e-1,
                        0.834596332878346e-6, 0.503611916682674e1, 0.655444787064505e2};

    // Check input parameters
    if (s < -1.545495919e-4 || s > 3.77828134)
        return INVALID_S;

    double sigma = s / 3.8;
    double suma = 0;
    for (int i = 0; i < 27; i++)
        suma += n[i] * pow(sigma - 1.09, I[i]) * pow(sigma + 0.366e-4, J[i]);
    return 1700 * suma;
}

double _h3a_s(double s) // _h3a_s
/*  Supp-phs3-2014.pdf. Eq 4
    the saturated line boundary between Region 4 and 3a, h=f(s)
   * s'(623.15K) ≤ s ≤ sc
    >>> _h3a_s(3.8)
    1685.025565
    >>> _h3a_s(4.2)
    1949.352563
  */
{
    double sigma = s / 3.8;
    const int I[] = {0, 0, 0, 0, 2, 3, 4, 4, 5, 5, 6, 7, 7, 7, 10, 10, 10, 32, 32};
    const int J[] = {1, 4, 10, 16, 1, 36, 3, 16, 20, 36, 4, 2, 28, 32, 14, 32, 36, 0, 6};
    const double n[] = {0.822673364673336, 0.181977213534479, -0.112000260313624e-1,
                        -0.746778287048033e-3, -0.179046263257381, 0.424220110836657e-1,
                        -0.341355823438768, -0.209881740853565e1, -0.822477343323596e1,
                        -0.499684082076008e1, 0.191413958471069, 0.581062241093136e-1,
                        -0.165505498701029e4, 0.158870443421201e4, -0.850623535172818e2,
                        -0.317714386511207e5, -0.945890406632871e5, -0.139273847088690e-5,
                        0.631052532240980};
    // Check input parameters
    if (s < 3.77828134 || s > sc_water)
        return INVALID_S;

    double suma = 0;
    for (int i = 0; i < 19; i++)
        suma += n[i] * pow(sigma - 1.09, I[i]) * pow(sigma + 0.366e-4, J[i]);
    return 1700 * suma;
}

double _h2ab_s(double s)
/*  http://www.iapws.org/relguide/Supp-phs3-2014.pdf. Eq 5
    Define the saturated line boundary between Region 4 and 2a-2b, h=f(s)
    _h2ab_s(7)  2723.729985
    _h2ab_s(9)  2511.861477
*/
{
    double sigma1 = s / 5.21;
    double sigma2 = s / 9.2;
    const int I[] = {1, 1, 2, 2, 4, 4, 7, 8, 8, 10, 12, 12, 18, 20, 24, 28, 28, 28, 28, 28,
                     32, 32, 32, 32, 32, 36, 36, 36, 36, 36};
    const int J[] = {8, 24, 4, 32, 1, 2, 7, 5, 12, 1, 0, 7, 10, 12, 32, 8, 12, 20, 22, 24,
                     2, 7, 12, 14, 24, 10, 12, 20, 22, 28};
    const double n[] = {-0.524581170928788e3, -0.926947218142218e7, -0.237385107491666e3,
                        0.210770155812776e11, -0.239494562010986e2, 0.221802480294197e3,
                        -0.510472533393438e7, 0.124981396109147e7, 0.200008436996201e10,
                        -0.815158509791035e3, -0.157612685637523e3, -0.114200422332791e11,
                        0.662364680776872e16, -0.227622818296144e19, -0.171048081348406e32,
                        0.660788766938091e16, 0.166320055886021e23, -0.218003784381501e30,
                        -0.787276140295618e30, 0.151062329700346e32, 0.795732170300541e7,
                        0.131957647355347e16, -0.325097068299140e24, -0.418600611419248e26,
                        0.297478906557467e35, -0.953588761745473e20, 0.166957699620939e25,
                        -0.175407764869978e33, 0.347581490626396e35, -0.710971318427851e39};

    // Check input parameters
    if (s < 5.85 || s > 9.155759395)
        return INVALID_S;

    double suma = 0;
    for (int i = 0; i < 30; i++)
        suma += n[i] * pow(1 / sigma1 - 0.513, I[i]) * pow(sigma2 - 0.524, J[i]);
    return 2800 * exp(suma);
}

double _h2c3b_s(double s)
/*  http://www.iapws.org/relguide/Supp-phs3-2014.pdf. Eq 6
     Define the saturated line boundary between Region 4 and 2c-3b, h=f(s)
    * sc ≤ s ≤ 5.85
   >>> _h2c3b_s(5.5)     2687.693850
    >>> _h2c3b_s(4.5)     2144.360448
 */
{
    double sigma = s / 5.9;
    const int I[] = {0, 0, 0, 1, 1, 5, 6, 7, 8, 8, 12, 16, 22, 22, 24, 36};
    const int J[] = {0, 3, 4, 0, 12, 36, 12, 16, 2, 20, 32, 36, 2, 32, 7, 20};
    const double n[] = {0.104351280732769e1, -0.227807912708513e1, 0.180535256723202e1,
                        0.420440834792042, -0.105721244834660e6, 0.436911607493884e25,
                        -0.328032702839753e12, -0.678686760804270e16, 0.743957464645363e4,
                        -0.356896445355761e20, 0.167590585186801e32, -0.355028625419105e38,
                        0.396611982166538e12, -0.414716268484468e41, 0.359080103867382e19,
                        -0.116994334851995e41};

    // Check input parameters
    if (s < sc_water || s > 5.85)
        return INVALID_S;

    double suma = 0;
    for (int i = 0; i < 16; i++)
        suma += n[i] * pow(sigma - 1.02, I[i]) * pow(sigma - 0.726, J[i]);
    return 2800 * pow(suma, 4);
}

double _h13_s(double s)
/*   Supp-phs3-2014.pdf. Eq 7
    Define the boundary between Region 1 and 3, h=f(s)
     _h13_s(3.7)    1632.525047
     _h13_s(3.5)     1566.104611
*/
{
    if (s < 3.397782955 || s > 3.77828134)
        return INVALID_S;

    double sigma = s / 3.8;
    const int I[] = {0, 1, 1, 3, 5, 6};
    const int J[] = {0, -2, 2, -12, -4, -3};
    const double n[] = {0.913965547600543, -0.430944856041991e-4, 0.603235694765419e2,
                        0.117518273082168e-17, 0.220000904781292, -0.690815545851641e2};

    double suma = 0;
    for (int i = 0; i < 6; i++)
        suma += n[i] * pow(sigma - 0.884, I[i]) * pow(sigma - 0.864, J[i]);
    return 1700 * suma;
}

double _t_hs(double h, double s) // _t23_hs(h, s)
                                 /* 
   http://www.iapws.org/relguide/Supp-phs3-2014.pdf. Eq 8 
   Page25
     4.6 Equation TB23(h,s) for the Boundary between Regions 2 and 3
    Define the boundary between Region 2 and 3, T=f(h,s)
    >>> _t_hs(2600, 5.1)  713.5259364
    >>> _t_hs(2800, 5.2)   817.6202120
 */
{

    const int I[] = {-12, -10, -8, -4, -3, -2, -2, -2, -2, 0, 1, 1, 1, 3, 3, 5, 6, 6, 8, 8,
                     8, 12, 12, 14, 14};
    const int J[] = {10, 8, 3, 4, 3, -6, 2, 3, 4, 0, -3, -2, 10, -2, -1, -5, -6, -3, -8,
                     -2, -1, -12, -1, -12, 1};
    const double n[] = {0.629096260829810e-3, -0.823453502583165e-3, 0.515446951519474e-7,
                        -0.117565945784945e1, 0.348519684726192e1, -0.507837382408313e-11,
                        -0.284637670005479e1, -0.236092263939673e1, 0.601492324973779e1,
                        0.148039650824546e1, 0.360075182221907e-3, -0.126700045009952e-1,
                        -0.122184332521413e7, 0.149276502463272, 0.698733471798484,
                        -0.252207040114321e-1, 0.147151930985213e-1, -0.108618917681849e1,
                        -0.936875039816322e-3, 0.819877897570217e2, -0.182041861521835e3,
                        0.261907376402688e-5, -0.291626417025961e5, 0.140660774926165e-4,
                        0.783237062349385e7};

    double nu = h / 3000;
    double sigma = s / 5.3;
    // Check input parameters
    if (s < 5.048096828 || s > 5.260578707 ||
        h < 2.563592004e3 || h > 2.812942061e3)
        return INVALID_HS;

    double suma = 0;
    for (int i = 0; i < 25; i++)
        suma += n[i] * pow(nu - 0.727, I[i]) * pow(sigma - 0.864, J[i]);
    return 900 * suma;
}
