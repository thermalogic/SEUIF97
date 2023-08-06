/*
  Check the region
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

int pT_region(double p, double T)
// 温度升序，判断区域 ，直接return。判定逻辑简单，避免了多重if
// p in MPa。T in K returns the region
{
    if (p < Pmin || p > 100)
        return INVALID_P;
    if (T < 273.15 || T > 2273.15)
        return INVALID_T;
    if (T > 1073.15 && T <= 2273.15 && p > 50.0)
        return INVALID_P;

    // ON TOP: Saturaton lines、critical point等特殊点判断在前
    // 以后区域判断中没有这些特殊，减少区域判断的复杂度

    // TODO: Saturaton Pressure Tolerance
    const double psatTol = 1.0e-6;
    if (T >= 273.15 && T < tc_water)
    {
        double ps = pSat(T);
        if (fabs(p - ps) / ps < psatTol)
            return 4;
    }
    // TODO: critical point 放在4区,如果放在3区？
    if (T == tc_water && p == pc_water)
        return 4;

    if (T >= 273.15 && T <= 623.15)
    {
        if (p >= pSat(T) && p <= 100.0)
            return 1;
        if (p < pSat(T) && p > Pmin)
            return 2;
    };

    // T（623.15,tc_water)之间的饱和线，critical point情况，已在前面处理，这里无需判断，简化了区域判断
    if (T > 623.15 && T <= 863.15)
    {
        if (p >= Pmin && p <= B23_T2p(T))
            return 2;
        if (p > B23_T2p(T) && p <= 100.0)
            return 3;
    };

    if (T > 863.15 && T <= 1073.15 &&
        p >= Pmin && p <= 100.0)
        return 2;

    if (1073.15 < T && T <= 2273.15 &&
        Pmin <= p && p <= 50)
        return 5;
}

//-----------------------------------------------------------------
//  p,h
//------------------------------------------------------------------

int ph_region(double p, double h)
{

    // 压力Pmin - Ps_623- pc_water- 100升序，分3段判断区域
    //    每个压力区域 hmin  hmax 分段判断区域
    double hmin = pT2h_reg1(p, 273.15);
    double hmax = pT2h_reg5(p, 2273.15);

    if (Pmin <= p && p <= Ps_623) // Ps_623 PMIN3 3区的最小压力
    {
        double h14 = pT2h_reg1(p, TSat(p));
        double h24 = pT2h_reg2(p, TSat(p));
        double h25 = pT2h_reg2(p, 1073.15);

        if (hmin <= h && h <= h14)
            return 1;
        if (h14 < h && h < h24)
            return 4;
        if (h24 <= h && h <= h25)
            return 2;
        if (h25 < h && h <= hmax)
            return 5;
    };

    if (Ps_623 < p && p < pc_water)
    {

        double h13 = pT2h_reg1(p, 623.15);
        double h32 = pT2h_reg2(p, B23_p2T(p));
        double h25 = pT2h_reg2(p, 1073.15);

        if (hmin <= h && h <= h13)
            return 1;

        if (h13 < h && h < h32)
        {
            double p34 = h2pSat_reg3(h);
            if (p < p34)
                return 4;
            else
                return 3;
        };

        if (h32 <= h && h <= h25)
            return 2;
        if (h25 < h && h <= hmax)
            return 5;
    };

    if (pc_water <= p && p <= 100)
    {
        double h13 = pT2h_reg1(p, 623.15);
        double h32 = pT2h_reg2(p, B23_p2T(p));
        double h25 = pT2h_reg2(p, 1073.15);

        if (hmin <= h && h <= h13)
            return 1;
        if (h13 < h && h < h32)
            return 3;
        if (h32 <= h && h <= h25)
            return 2;
        if ((p <= 50) && (h25 <= h && h <= hmax))
            return 5;
    };
    return (-1000);
}

int ps_region(double p, double s)
{

    // 压力Pmin - Ps_623- pc_water- 100升序，分3段判断区域
    //    每个压力区域 smin  smax 分段判断区域
    double smin = pT2s_reg1(p, 273.15);
    double smax = pT2s_reg5(p, 2273.15);
    if (Pmin <= p && p <= Ps_623)
    {

        double s14 = pT2s_reg1(p, TSat(p));
        double s24 = pT2s_reg2(p, TSat(p));
        double s25 = pT2s_reg2(p, 1073.15);

        if (smin <= s && s <= s14)
            return 1;
        if (s14 < s && s < s24)
            return 4;
        if (s24 <= s && s <= s25)
            return 2;
        if (s25 < s && s <= smax)
            return 5;
    };

    if (Ps_623 < p && p < pc_water)
    {
        double s13 = pT2s_reg1(p, 623.15);
        double s32 = pT2s_reg2(p, B23_p2T(p));
        double s25 = pT2s_reg2(p, 1073.15);
        if (smin <= s && s <= s13)
            return 1;
        if (s13 < s && s < s32)
        {
            double p34 = s2pSat_reg3(s);
            if (p < p34)
                return 4;
            else
                return 3;
        };

        if (s32 <= s && s <= s25)
            return 2;
        if (s25 < s && s <= smax)
            return 5;
    };

    if (pc_water <= p && p <= 100)
    {
        double s13 = pT2s_reg1(p, 623.15);
        double s32 = pT2s_reg2(p, B23_p2T(p));
        double s25 = pT2s_reg2(p, 1073.15);
        if (smin <= s && s <= s13)
            return 1;
        if (s13 < s && s < s32)
            return 3;
        if (s32 <= s && s <= s25)
            return 2;

        if (p <= 50 && s25 <= s && s <= smax)
            return 5;
    };
}

int hs_region(double h, double s)

// 1,2,3,4 区 smin ->smax。5区另外处理
{
    double s13 = pT2s_reg1(100, 623.15);
    double s13s = pT2s_reg1(Ps_623, 623.15);
    double sTPmax = pT2s_reg2(100, 1073.15);
    double s2ab = pT2s_reg2(4, 1073.15); // TODO： p=4 2ab s2ab 的意义？

    // Left point in h-s plot
    double smin = pT2s_reg1(100, 273.15);
    double hmin = pT2h_reg1(Pmin, 273.15);

    // Right point in h-s plot
    double hmax = pT2h_reg2(Pmin, 1073.15);
    double smax = pT2s_reg2(Pmin, 1073.15);

    // Region 4 left and right point
    double h4l = pT2h_reg1(Pmin, 273.15);
    double s4l = pT2s_reg1(Pmin, 273.15);

    double h4v = pT2h_reg2(Pmin, 273.15);
    double s4v = pT2s_reg2(Pmin, 273.15);

    // !!!! Check region 5 MUST On TOP !!!
    // if （s4v <= s && s<= smax） (h,s)may be setup to error region2
    if (pT2s_reg5(50, 1073.15) < s && s <= pT2s_reg5(Pmin, 2273.15) &&
        pT2h_reg5(50, 1073.15) < h && h <= pT2h_reg5(Pmin, 2273.15))
    {
        double P = hs2p_reg5(h, s);
        double T = ph2T_reg5(P, h);
        if (1073.15 < T && T <= 2273.15 && Pmin <= P && P <= 50)
            return 5;
    };

    if (smin <= s && s <= s13)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h1_s(s);
        double T = ps2T_reg1(100, s) - 0.0218;
        double hmax = pT2h_reg1(100.0, T);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 1;
    };

    if (s13 < s && s <= s13s)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h1_s(s);
        double h13 = _h13_s(s);
        double v = ps2v_reg3(100, s) * (1 + 9.6e-5);
        double T = ps2T_reg3(100, s) - 0.0248;
        double hmax = Td2h_reg3(T, 1 / v);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h < h13)
            return 1;
        if (h13 <= h && h <= hmax)
            return 3;
    };

    if (s13s < s && s <= sc_water)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h3a_s(s);
        double v = ps2v_reg3(100, s) * (1 + 9.6e-5);
        double T = ps2T_reg3(100, s) - 0.0248;
        double hmax = Td2h_reg3(T, 1 / v);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 3;
    };

    if (sc_water < s && s < 5.049096828)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2c3b_s(s);
        double v = ps2v_reg3(100, s) * (1 + 9.6e-5);
        double T = ps2T_reg3(100, s) - 0.0248;
        double hmax = Td2h_reg3(T, 1 / v);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 3;
    };

    if (5.049096828 <= s && s < 5.260578707)
    {
        // Specific zone with 2-3 boundary in s shape
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2c3b_s(s);
        double h23max = pT2h_reg2(100, 863.15);
        double h23min = pT2h_reg2(Ps_623, 623.15);
        double T = ps2T_reg2(100, s) - 0.019;
        double hmax = pT2h_reg2(100, T);

        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h < h23min)
            return 3;

        if (h23min <= h && h < h23max)
            if (hs2p_reg2c(h, s) <= B23_T2p(_t_hs(h, s)))
                return 2;
            else
                return 3;

        if (h23max <= h && h <= hmax)
            return 2;
    };

    if (5.260578707 <= s && s < 5.85)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2c3b_s(s);
        double T = ps2T_reg2(100, s) - 0.019;
        double hmax = pT2h_reg2(100, T);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 2;
    }

    if (5.85 <= s && s < sTPmax)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2ab_s(s);
        double T = ps2T_reg2(100, s) - 0.019;
        double hmax = pT2h_reg2(100, T);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 2;
    };

    if (sTPmax <= s && s < s2ab)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2ab_s(s);
        double P = hs2p_reg2(h, s);
        double hmax = pT2h_reg2(P, 1073.15);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 2;
    };

    if (s2ab <= s && s < s4v)
    {
        double hmin = h4l + (s - s4l) / (s4v - s4l) * (h4v - h4l);
        double hs = _h2ab_s(s);
        double P = hs2p_reg2(h, s);
        double hmax = pT2h_reg2(P, 1073.15);
        if (hmin <= h && h < hs)
            return 4;
        if (hs <= h && h <= hmax)
            return 2;
    }

    if (s4v <= s && s <= smax)
    {
        double hmin = pT2h_reg2(Pmin, 273.15);
        double P = hs2p_reg2a(h, s);
        double hmax = pT2h_reg2(P, 1073.15);
        if (Pmin <= P && P <= 100 && hmin <= h && h <= hmax)
            return 2;
    }

    return -1000;
}

//--------------------------------------------
// the extended pairs(p,v)
//----------------------------------------

int pv_region(double p, double v)
{
    double x, T1, vt273, vT1073, vt2273, vt623, vB23, vsw, vss;
    if ((p < PMIN2) || (p > PMAX2))
        return INVALID_VALUE;
    vt273 = pT2v_reg1(p, 273.15);   // T=273.15
    vT1073 = pT2v_reg2(p, 1073.15); // T=1073.15
    if ((p >= PMIN5) && (p <= PMAX5))
        vt2273 = pT2v_reg5(p, 2273.15); // T=2273.15
    if ((p > 0.000611213) && (p <= PMIN3))
    {
        T1 = TSat(p);
        vsw = pT2v_reg1(p, T1); //
        vss = pT2v_reg2(p, T1); //
    }
    else if ((p > PMIN3) && (p <= PMAX3))
    {
        vt623 = pT2v_reg1(p, 623.15); // T=623.15
        T1 = B23_p2T(p);
        vB23 = pT2v_reg2(p, T1); //
        if (p <= pc_water)
        {
            T1 = TSat(p);
            vsw = pT2vSat_reg3(p, T1, 0);
            vss = pT2vSat_reg3(p, T1, 1);
        }
    }
    if (((p >= PMIN1) && (p <= PMIN3)) && ((v >= vt273) && (v <= vsw)) ||
        ((p > PMIN3) && (p <= PMAX1)) && ((v >= vt273) && (v <= vt623)))
    {
        return (1);
    };
    if (((p >= PMIN2) && (p <= PMIN3) && (v > vss) && (v <= vT1073)) ||
        ((p > PMIN3) && (p <= PMAX2) && (v >= vB23) && (v <= vT1073)))
    {
        return (2);
    };
    if (((p > PMIN3) && (p <= pc_water) && (((v > vt623) && (v < vsw)) || ((v > vss) && (v < vB23)))) ||
        ((p > pc_water) && (p <= PMAX3) && (v > vt623) && (v < vB23)))
    {
        return (3);
    };
    if ((p > 0) && (p <= pc_water) && (v >= vsw) && (v <= vss))
    {
        return 4; // x is obtained in r4::region4_pair_ext::pv2x_reg4
    };
    if ((p > PMIN5) && (p <= PMAX5) && (v > vT1073) && (v <= vt2273))
    {
        return (5);
    };
    return (INVALID_VALUE);
}

//---------------- T ---------------------------
int Th_region(double T, double h)
{
    double x, v, p1, hpmax2, hpmax5, hpm50, hp100, hsw, hss, hB23;
    if ((T < 273.15) || (T > 2273.15))
        return (-1);
    //  if ((h>HMAX)||(h<HMIN)) return (-2);
    if ((T >= TMIN2) && (T <= TMAX2))
        hpmax2 = pT2h_reg2(PMIN2, T);
    if ((T > TMIN5) && (T <= TMAX5))
    {
        hpm50 = pT2h_reg5(PMAX5, T);
        hpmax5 = pT2h_reg5(PMIN5, T);
    }
    // p=100MPa
    if ((T >= TMIN1) && (T <= TMAX1))
        hp100 = pT2h_reg1(100, T);
    if ((T > TMIN3) && (T <= TMAX3))
        hp100 = pT_reg3(100, T, OH);
    if ((T >= TMIN1) && (T <= TMAX1))
    {
        p1 = pSat(T);
        hsw = pT2h_reg1(p1, T); //
        hss = pT2h_reg2(p1, T); //
    }
    else if ((T > TMIN3) && (T <= TMAX3))
    {
        p1 = B23_T2p(T);
        hB23 = pT2h_reg2(p1, T); //
        if (T <= tc_water)
        {
            p1 = pSat(T);
            v = pT2vSat_reg3(p1, T, 0);
            hsw = Td2h_reg3(T, 1.0 / v);
            v = pT2vSat_reg3(p1, T, 0);
            hss = Td2h_reg3(T, 1.0 / v);
        };
    };

    // (P+->h+)/h>hsw(t,h)
    if ((T >= TMIN1) && (T <= TMAX1) && (h > hsw) && (h <= hp100))
    {
        return 1;
    }
    //  (t,h) (p>Ps,p+,h--,Hmin,p+,h++) h<hsw
    if ((T >= (250 + 273.15)) && (T <= TMAX1) && (h < hsw) && (h <= hp100))
    {
        double Hmin = hsw;
        double p11 = p1 + 0.1;
        double Hmid = pT2h_reg1(p11, T);
        if (Hmid < Hmin)
        {
            int HminFounded = 0;
            while (HminFounded == 0)
            {
                p11 += 0.1;
                Hmid = pT2h_reg1(p11, T);
                if (Hmid < Hmin)
                    Hmin = Hmid;
                else
                    HminFounded = 1;
            }
            if (h >= Hmin)
                return (1.0);
            else
                return (INVALID_VALUE);
        }
        else
            return (INVALID_VALUE);
    };
    if ((T >= TMIN2) && (T <= TMAX1) && (h > hss) && (h < hpmax2))
    {
        return (2);
    };
    if ((T > TMAX1) && (T <= TMAX3) && (h >= hB23) && (h < hpmax2))
    {
        return (2);
    };
    if (((T > TMIN3) && (T <= tc_water) && (((h > hss) && (h < hB23)) || ((h >= hp100) && (h < hsw)))) ||
        ((T > tc_water) && (T <= TMAX3) && (h >= hp100) && (h < hB23)))
    {
        return 3;
    };

    //  (t,h)
    if ((T >= TMIN1) && (T <= tc_water) && (h >= hsw) && (h <= hss))
    {
        return 4;
    };

    if ((T > TMIN5) && (T <= TMAX5) && (h >= hpm50) && (h <= hpmax5))
    {
        return 5;
    };
    return (INVALID_VALUE);
}

int Ts_region(double T, double s)
{
    double x, v, p1, spmax2, spmax5, sp50, sp100, ssw, sss, sB23;
    if ((T < 273.15) || (T > 2273.15))
        return (-1);
    if ((s > SMAX) || (s < SMIN))
        return (-2);

    if ((T >= TMIN2) && (T <= TMAX2))
        spmax2 = pT2s_reg2(PMIN2, T);
    if ((T >= TMIN5) && (T <= TMAX5))
    {
        spmax5 = pT2s_reg5(PMIN5, T);
        sp50 = pT2s_reg5(PMAX5, T);
    }
    // p=100MPa
    if ((T >= TMIN1) && (T <= TMAX1))
        sp100 = pT2s_reg1(100, T);
    if ((T > TMIN3) && (T <= TMAX3))
        sp100 = pT_reg3(100, T, OS);
    if ((T > TMAX3) && (T <= TMAX2))
        sp100 = pT2s_reg2(100, T);
    if ((T >= TMIN1) && (T <= TMAX1))
    {
        p1 = pSat(T);
        ssw = pT2s_reg1(p1, T); //
        sss = pT2s_reg2(p1, T); //
    }
    else if ((T > TMIN3) && (T <= TMAX3))
    {
        p1 = B23_T2p(T);
        sB23 = pT2s_reg2(p1, T); //
        if (T <= tc_water)
        {
            p1 = pSat(T);
            v = pT2vSat_reg3(p1, T, 0);
            ssw = Td2s_reg3(T, 1.0 / v);
            v = pT2vSat_reg3(p1, T, 1);
            sss = Td2s_reg3(T, 1.0 / v);
        };
    };
    if ((T >= TMIN1) && (T <= TMAX1) && (s < ssw) && (s > sp100))
    {
        return 1;
    };
    if (((T >= TMIN2) && (T <= TMAX1) && (s > sss) && (s < spmax2)) ||
        ((T > TMAX1) && (T <= TMAX3) && (s >= sB23) && (s < spmax2)))
    {
        return 2;
    };
    if (((T > TMIN3) && (T <= tc_water) && (((s > sss) && (s < sB23)) || ((s >= sp100) && (s < ssw)))) ||
        ((T > tc_water) && (T <= TMAX3) && (s >= sp100) && (s < sB23)))
    {
        return 3;
    };
    if ((T >= TMIN1) && (T <= tc_water) && (s >= ssw) && (s <= sss))
    {
        return 4;
    };
    if ((T > TMIN5) && (T <= TMAX5) && (s >= sp50) && (s <= spmax5))
    {
        return 5;
    };
    return INVALID_VALUE;
}

int Tv_region(double T, double v)
{
    double x, p1, vpmax2, vpmax5, vp50, vp100, vsw, vss, vB23;
    if ((T < 273.15) || (T > 2273.15))
        return (-1);
    if ((T >= TMIN2) && (T <= TMAX2))
        vpmax2 = pT2v_reg2(PMIN2, T);
    if ((T >= TMIN5) && (T <= TMAX5))
    {
        vpmax5 = pT2v_reg5(PMIN5, T);
        vp50 = pT2v_reg5(PMAX5, T);
    }
    // p=100MPa
    if ((T >= TMIN1) && (T <= TMAX1))
        vp100 = pT2v_reg1(100, T);
    if ((T > TMIN3) && (T <= TMAX3))
        vp100 = pT2v_reg3(100, T); //
    if ((T > TMAX3) && (T <= TMAX2))
        vp100 = pT2v_reg2(100, T);
    if ((T >= TMIN1) && (T <= TMAX1))
    {
        p1 = pSat(T);
        vsw = pT2v_reg1(p1, T); //
        vss = pT2v_reg2(p1, T); //
    }
    else if ((T > TMIN3) && (T <= TMAX3))
    {
        p1 = B23_T2p(T);
        vB23 = pT2v_reg2(p1, T); //
        if (T <= tc_water)
        {
            p1 = pSat(T);
            vsw = pT2vSat_reg3(p1, T, 0);
            vss = pT2vSat_reg3(p1, T, 1);
        };
    };
    if ((T >= TMIN1) && (T <= TMAX1) && (v < vsw) && (v > vp100))
    {
        return 1;
    };
    if (((T >= TMIN2) && (T <= TMAX1) && (v > vss) && (v < vpmax2)) ||
        ((T > TMAX1) && (T <= TMAX3) && (v >= vB23) && (v < vpmax2)))
    {
        return 2;
    };
    if (((T > TMIN3) && (T <= tc_water) && (((v > vss) && (v < vB23)) || ((v >= vp100) && (v < vsw)))) ||
        ((T > tc_water) && (T <= TMAX3) && (v >= vp100) && (v < vB23)))
    {
        return 3;
    };
    if ((T >= TMIN1) && (T <= tc_water) && (v >= vsw) && (v <= vss))
    {
      return 4;
    };
    if ((T > TMIN5) && (T <= TMAX5) && (v >= vp50) && (v <= vpmax5))
    {
        return 5;
    };
    return (INVALID_VALUE);
}

