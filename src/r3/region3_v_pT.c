/*
   region3: (p,T)->v
*/
#include <math.h>
#include <string.h>
#include "region3.h"
#include "../algo/algorithm.h"
#include "../r4/region4.h"

double T_atRegionBoundary(double p, char *boundary)
{
    // p is pressure in MPa
    // boundary is one of 3ab, 3cd, ...
    // returns the temperature at the boundary in K

    double t = 0.0; // temperature at the boundary in K

    int I3ab[] = {0, 0, 1, 2, -1, -2};
    int I3cd[] = {0, 0, 1, 2, 3};
    int I3gh[] = {0, 0, 1, 2, 3, 4};
    int I3ij[] = {0, 0, 1, 2, 3, 4};
    int I3jk[] = {0, 0, 1, 2, 3, 4};
    int I3mn[] = {0, 0, 1, 2, 3};
    int I3op[] = {0, 0, 1, 2, -1, -2};
    int I3qu[] = {0, 0, 1, 2, 3};
    int I3rx[] = {0, 0, 1, 2, 3};
    int I3uv[] = {0, 0, 1, 2, 3};
    int I3wx[] = {0, 0, 1, 2, -1, -2};

    double n3ab[] = {0.0, 0.154793642129415e4, -0.187661219490113e3, 0.213144632222113e2,
                     -0.191887498864292e4, 0.918419702359447e3};
    double n3cd[] = {0.0, 0.585276966696349e3, 0.278233532206915e1, -0.127283549295878e-1,
                     0.159090746562729e-3};
    double n3gh[] = {0.0, -0.249284240900418e5, 0.428143584791546e4, -0.269029173140130e3,
                     0.751608051114157e1, -0.787105249910383e-1};
    double n3ij[] = {0.0, 0.584814781649163e3, -0.616179320924617, 0.260763050899562,
                     -0.587071076864459e-2, 0.515308185433082e-4};
    double n3jk[] = {0.0, 0.617229772068439e3, -0.770600270141675e1, 0.697072596851896,
                     -0.157391839848015e-1, 0.137897492684194e-3};
    double n3mn[] = {0.0, 0.535339483742384e3, 0.761978122720128e1, -0.158365725441648,
                     0.192871054508108e-2};
    double n3op[] = {0.0, 0.969461372400213e3, -0.332500170441278e3, 0.642859598466067e2,
                     0.773845935768222e3, -0.152313732937084e4};
    double n3qu[] = {0.0, 0.565603648239126e3, 0.529062258221222e1, -0.102020639611016,
                     0.122240301070145e-2};
    double n3rx[] = {0.0, 0.584561202520006e3, -0.102961025163669e1, 0.243293362700452,
                     -0.294905044740799e-2};
    double n3uv[] = {0.0, 0.528199646263062e3, 0.890579602135307e1, -0.222814134903755,
                     0.286791682263697e-2};
    double n3wx[] = {0.0, 0.728052609145380e1, 0.973505869861952e2, 0.147370491183191e2,
                     0.329196213998375e3, 0.873371668682417e3};

    if (strcmp(boundary, "3ab") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3ab[i] * IPOW(log(p), I3ab[i]);
    }
    else if (strcmp(boundary, "3op") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3op[i] * IPOW(log(p), I3op[i]);
    }
    else if (strcmp(boundary, "3ef") == 0)
    {
        t = 3.727888004 * (p - 22.064) + 647.096;
    }
    else if (strcmp(boundary, "3cd") == 0)
    {
        for (int i = 1; i <= 4; i++)
            t += n3cd[i] * IPOW(p, I3cd[i]);
    }
    else if (strcmp(boundary, "3gh") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3gh[i] * IPOW(p, I3gh[i]);
    }
    else if (strcmp(boundary, "3ij") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3ij[i] * IPOW(p, I3ij[i]);
    }
    else if (strcmp(boundary, "3jk") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3jk[i] * IPOW(p, I3jk[i]);
    }
    else if (strcmp(boundary, "3mn") == 0)
    {
        for (int i = 1; i <= 4; i++)
            t += n3mn[i] * IPOW(p, I3mn[i]);
    }
    else if (strcmp(boundary, "3qu") == 0)
    {
        for (int i = 1; i <= 4; i++)
            t += n3qu[i] * IPOW(p, I3qu[i]);
    }
    else if (strcmp(boundary, "3rx") == 0)
    {
        for (int i = 1; i <= 4; i++)
            t += n3rx[i] * IPOW(p, I3rx[i]);
    }
    else if (strcmp(boundary, "3uv") == 0)
    {
        for (int i = 1; i <= 4; i++)
            t += n3uv[i] * IPOW(p, I3uv[i]);
    }
    else if (strcmp(boundary, "3wx") == 0)
    {
        for (int i = 1; i <= 5; i++)
            t += n3wx[i] * IPOW(log(p), I3wx[i]);
    }

    return t;
}

double pT2vSat_reg3(double p, double T, double x)
{
    // p is pressure in MPa
    // t is temperature in K
    // x = 0 is liquid, =1 is steam]  x : integer    Vapor quality [-]
    // returns density in kg/m3

    double v;
    char subRegion;
    // set the region
    // force the region if density of saturated water is asked for
    if (x == 0)
    {
        if (p < 19.0088)
        {
            subRegion = 'c';
        }
        else
        {
            if (p < 21.0434)
            {
                subRegion = 's';
            }
            else
            {
                if (p < 21.9316)
                    subRegion = 'u';
                else
                    subRegion = 'y';
            }
        }
    }
    else
    {
        if (p < 20.5)
        {
            subRegion = 't';
        }
        else
        {
            if (p < 21.0434)
                subRegion = 'r';
            else if (p < 21.9009)
                subRegion = 'x';
            else
                subRegion = 'z';
        }
    }

    v = Vpt_3subreg(p, T, subRegion);
    return v;
}

//-------------------------------------------------------------------------

char SubRegion3(double p, double t)
{
    // p is pressure in MPa
    // T is temperature in K
    // sets the subregion

    char subRegion;

    if (p > 40.0 && p <= 100.0)
    {
        double tB = T_atRegionBoundary(p, "3ab");
        if (t > tB)
            subRegion = 'b';
        else
            subRegion = 'a';
    }
    else if (p > 25.0)
    {
        double tBab = T_atRegionBoundary(p, "3ab");
        double tBcd = T_atRegionBoundary(p, "3cd");
        double tBef = T_atRegionBoundary(p, "3ef");

        if (t <= tBcd)
            subRegion = 'c';
        else if (t <= tBab)
            subRegion = 'd';
        else if (t <= tBef)
            subRegion = 'e';
        else
            subRegion = 'f';
    }
    else if (p > 23.5)
    {
        double tBcd = T_atRegionBoundary(p, "3cd");
        double tBef = T_atRegionBoundary(p, "3ef");
        double tBgh = T_atRegionBoundary(p, "3gh");
        double tBij = T_atRegionBoundary(p, "3ij");
        double tBjk = T_atRegionBoundary(p, "3jk");

        if (t <= tBcd)
            subRegion = 'c';
        else if (t <= tBgh)
            subRegion = 'g';
        else if (t <= tBef)
            subRegion = 'h';
        else if (t <= tBij)
            subRegion = 'i';
        else if (t <= tBjk)
            subRegion = 'j';
        else
            subRegion = 'k';
    }
    else if (p > 23.0)
    {
        double tBcd = T_atRegionBoundary(p, "3cd");
        double tBef = T_atRegionBoundary(p, "3ef");
        double tBgh = T_atRegionBoundary(p, "3gh");
        double tBij = T_atRegionBoundary(p, "3ij");
        double tBjk = T_atRegionBoundary(p, "3jk");

        if (t <= tBcd)
            subRegion = 'c';
        else if (t <= tBgh)
            subRegion = 'l';
        else if (t <= tBef)
            subRegion = 'h';
        else if (t <= tBij)
            subRegion = 'i';
        else if (t <= tBjk)
            subRegion = 'j';
        else
            subRegion = 'k';
    }
    else if (p > 22.5)
    {
        double tBcd = T_atRegionBoundary(p, "3cd");
        double tBef = T_atRegionBoundary(p, "3ef");
        double tBgh = T_atRegionBoundary(p, "3gh");
        double tBij = T_atRegionBoundary(p, "3ij");
        double tBjk = T_atRegionBoundary(p, "3jk");
        double tBmn = T_atRegionBoundary(p, "3mn");
        double tBop = T_atRegionBoundary(p, "3op");

        if (t <= tBcd)
            subRegion = 'c';
        else if (t <= tBgh)
            subRegion = 'l';
        else if (t <= tBmn)
            subRegion = 'm';
        else if (t <= tBef)
            subRegion = 'n';
        else if (t <= tBop)
            subRegion = 'o';
        else if (t <= tBij)
            subRegion = 'p';
        else if (t <= tBjk)
            subRegion = 'j';
        else
            subRegion = 'k';
    }
    else
    {
        double pSat97 = pSat(643.15);
        if (p > pSat97)
        {
            double tBcd = T_atRegionBoundary(p, "3cd");
            double tBqu = T_atRegionBoundary(p, "3qu");
            double tBrx = T_atRegionBoundary(p, "3rx");
            double tBjk = T_atRegionBoundary(p, "3jk");

            if (t <= tBcd)
                subRegion = 'c';
            else if (t <= tBqu)
            {
                subRegion = 'q';
                // 这里的判断算法有点问题，下面这个 subRegion会被重新设定u
                //  简便处理，这个判断后，立即返回
                return subRegion;
            }

            if (t > tBrx && t <= tBjk)
            {
                subRegion = 'r';
                // 这里的判断算法有点问题，下面这个 subRegion会被重新设定u
                // 简便处理，这个判断后，立即返回
                return subRegion;
            }

            if (t > tBjk)
                subRegion = 'k';

            // tBqu < T <= tBrx
            // small regions right around critical point
            // 3u, 3x, 3y, 3z, 3v and 3w

            double tBuv = T_atRegionBoundary(p, "3uv");
            double tBwx = T_atRegionBoundary(p, "3wx");
            double tBef = T_atRegionBoundary(p, "3ef");

            if (p > 22.11)
            {
                if (t <= tBuv)
                    subRegion = 'u';
                else if (t < tBef)
                    subRegion = 'v';
                else if (t < tBwx)
                    subRegion = 'w';
                else
                    subRegion = 'x';
            }
            else if (p > 22.064)
            {
                double tBwx = T_atRegionBoundary(p, "3wx");
                double tBuv = T_atRegionBoundary(p, "3uv");
                if (t <= tBuv)
                    subRegion = 'u';
                else if (t <= tBef)
                    subRegion = 'y';
                else if (t <= tBwx)
                    subRegion = 'z';
                else
                    subRegion = 'x';
            }
            else
            {
                double tSat97 = TSat(p);

                if (t <= tSat97)
                {
                    if (p > 21.93161551)
                    {
                        if (t < tBuv)
                            subRegion = 'u';
                        else
                            subRegion = 'y';
                    }
                    else
                        subRegion = 'u';
                }
                else
                {
                    if (p > 21.90096265)
                    {
                        if (t < tBwx)
                            subRegion = 'z';
                        else
                            subRegion = 'x';
                    }
                    else
                        subRegion = 'x';
                }
            }
        }
        else if (p > 20.5)
        {
            double tBcd = T_atRegionBoundary(p, "3cd");
            double tBjk = T_atRegionBoundary(p, "3jk");
            double tSat97 = TSat(p);

            if (t <= tBcd)
                subRegion = 'c';
            else if (t <= tSat97)
                subRegion = 's';
            else if (t <= tBjk)
                subRegion = 'r';
            else
                subRegion = 'k';
        }
        else if (p > 19.00881189173929)
        {
            double tBcd = T_atRegionBoundary(p, "3cd");
            double tSat97 = TSat(p);

            if (t <= tBcd)
                subRegion = 'c';
            else if (t <= tSat97)
                subRegion = 's';
            else
                subRegion = 't';
        }
        else
        {
            double tSat97 = TSat(p);
            if (t <= tSat97)
                subRegion = 'c';
            else
                subRegion = 't';
        }
    }
    return subRegion;
}

double pT2v_reg3(double p, double T)
{
    // p is pressure in MPa
    // t is temperature in K
    // returns density in kg/m3
    char subRegion;
    // set the region
    subRegion = SubRegion3(p, T);
    double v = Vpt_3subreg(p, T, subRegion);
    return v;
}
