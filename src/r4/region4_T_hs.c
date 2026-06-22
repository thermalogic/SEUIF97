
/**
 * @file region4_T_hs.c
 * @brief Backward equation for Tsat(h,s) in Region 4
 * 
 * This file implements the backward equation for Tsat(h,s)
 * in Region 4.
 *  http://www.iapws.org/relguide/Supp-phs3-2014.pdf. Eq 9
 *    Page30  Supp-phs3-2014.pdf Page25
 *           5.3 Backward Equation Tsat(h,s)
 *               s> 5.210 887 825
 *               temperature range is T（273.15,623.15）
 *
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "../algo/algorithm.h"
#include "../common/common.h"
#include "../common/constant.h"
#include "../r1/region1.h"
#include "../r2/region2.h"
#include "../r3/region3.h"
#include "region4.h"

static double s4L_623 = 3.778281340;       // T=623.16 ，Sature Liquid s
static double s4V_623 = 5.210887825;       // T=623.16 ，Sature steam   s
static double h4V_623 = 2.5635920043 + 03; // Page 25  Sature steam   h
static double s4L_273 = -1.545495919e-04;  // T=273.15 ，Sature Liquid
static double s4V_273 = 9.155759395;       // T=273.15 ，Sature steam

double hs2T_reg43(double h, double s)
/* Backward equation for region 4, T=f(h,s)
    h :        Specific enthalpy [kJ/kg]
    s :        Specific entropy [kJ/kgK]
 */
{
    IJnData IJn[] = {
        {0, 0, .179882673606601},
        {0, 3, -.267507455199603},
        {0, 12, .116276722612600e1},
        {1, 0, .147545428713616},
        {1, 1, -.512871635973248},
        {1, 2, .421333567697984},
        {1, 5, .563749522189870},
        {2, 0, .429274443819153},
        {2, 5, -.335704552142140e1},
        {2, 8, .108890916499278e2},
        {3, 0, -.248483390456012},
        {3, 2, .304153221906390},
        {3, 3, -.494819763939905},
        {3, 4, .107551674933261e1},
        {4, 0, .733888415457688e-1},
        {4, 1, .140170545411085e-1},
        {5, 1, -.106110975998808},
        {5, 2, .168324361811875e-1},
        {5, 4, .125028363714877e1},
        {5, 16, .101316840309509e4},
        {6, 6, -.151791558000712e1},
        {6, 8, .524277865990866e2},
        {6, 22, .230495545563912e5},
        {8, 1, .249459806365456e-1},
        {10, 20, .210796467412137e7},
        {10, 36, .366836848613065e9},
        {12, 24, -.144814105365163e9},
        {14, 1, -.179276373003590e-2},
        {14, 28, .489955602100459e10},
        {16, 12, .471262212070518e3},
        {16, 32, -.829294390198652e11},
        {18, 14, -.171545662263191e4},
        {18, 22, .355777682973575e7},
        {18, 36, .586062760258436e12},
        {20, 24, -.129887635078195e8},
        {28, 36, .317247449371057e11}};

    if (s < s4V_623)
        return INVALID_S;

    double nu = h / 2800;
    double sigma = s / 9.2;
    // double suma = 0;
    // for (int i = 0; i < 36; i++)
    //    suma += IJn[i].n * IPOW(nu - 0.119, IJn[i].I) * IPOW(sigma - 1.07, IJn[i].J);
    return 550.0 * poly(nu - 0.119, sigma - 1.07, 36, IJn);
}

/// residual: r(T) = (h-hl)/(hv-hl) - (s-sl)/(sv-sl)
/// At the correct saturation temperature, 
/// the x calculated from h and s respectively should be consistent.
double residual_T(double T, double h, double s)
{
    double p =pSat(T);
    double hl = pT2h_reg1(p, T);
    double hv = pT2h_reg2(p, T);
    double sl = pT2s_reg1(p, T);
    double sv = pT2s_reg2(p, T);
    return (h - hl)/(hv - hl) - (s - sl)/ (sv - sl);
}

double bisect_T(double h, double s, double a, double b, double tol)
 {
    double ra = residual_T(a, h, s);
    double rb = residual_T(b, h, s);
    //Same sign at endpoints: expand the search interval outward
    int n_expand = 0;
    while (ra * rb > 0.0 && n_expand < 200) {
        double width = b - a;
        a = fmax(a - width, TMIN4);
        b = fmin(b + width,tc_water - 1.0);
        ra = residual_T(a, h, s);
        rb = residual_T(b, h, s);
        n_expand += 1;
        if (a <= TMIN4 + 0.5 && b >= tc_water - 1.5) {
            break;
        }
    }

    if (ra * rb > 0.0) {
        // Scan the entire interval to find sign changes.
        int n_steps = 60;
        double step = (tc_water - 1.0 - TMIN4) / n_steps;
        double prev_r = residual_T(TMIN4, h, s);
        double found_lo = TMIN4;
        double found_hi = TMIN4 + step;
        for(int i=1; i<n_steps; i++) {
            double Ti = TMIN4 + step * i;
            double ri = residual_T(Ti, h, s);
            if (prev_r * ri < 0.0) {
                found_lo = Ti - step;
                found_hi = Ti;
                break;
            }
            prev_r = ri;
        }
        a = found_lo;
        b = found_hi;
        ra = residual_T(a, h, s);
        rb = residual_T(b, h, s);
    }
    // bisection
    for(int i=0; i<200; i++) {
        double mid = 0.5 * (a + b);
        double rm = residual_T(mid, h, s);
        if (fabs(rm) < tol || (b - a) < 1.0e-10) {
             return mid;
        }
        if (ra * rm < 0.0) {
            b = mid;
            rb = rm;
        } else {
            a = mid;
            ra = rm;
        }
    }
   return (0.5 * (a + b));
}

double hs2T_reg4(double h, double s)
{
    double T=0.0;
    if (s > s4V_623 && s < s4V_273)
    {
        T = hs2T_reg43(h, s);
        return T;
    };
    T = hs2T_reg43(h, s);
    if (T < TMIN4 || T > tc_water) {
        T = 300.0;
    }
    T=bisect_T(h, s, T - 0.5, T + 0.5, 1.0e-8);   
    return T;
}