/*
 Backward Equation for Region 3:
 * IAPWS-IF97-S04rev :Supp-phs3-2014.pdf
     (h,s)->p  (3a,3b,3c)
 */
#include <math.h>
#include "../common/constand.h"
#include "../algo/algorithm.h"
#include "region3.h"

double hs2p3a_reg3(double h, double s)
/*  Backward equation for region 3a, P=f(h,s)
     h : Specific enthalpy [kJ/kg]
     s : Specific entropy [kJ/kgK]
      P : Pressure [MPa] */
{
    IJnData IJn[33] = {{0, 0, 0.770889828326934e1},
                       {0, 1, -0.260835009128688e2},
                       {0, 5, 0.267416218930389e3},
                       {1, 0, 0.172221089496844e2},
                       {1, 3, -0.293542332145970e3},
                       {1, 4, 0.614135601882478e3},
                       {1, 8, -0.610562757725674e5},
                       {1, 14, -0.651272251118219e8},
                       {2, 6, 0.735919313521937e5},
                       {2, 16, -0.116646505914191e11},
                       {3, 0, 0.355267086434461e2},
                       {3, 2, -0.596144543825955e3},
                       {3, 3, -0.475842430145708e3},
                       {4, 0, 0.696781965359503e2},
                       {4, 1, 0.335674250377312e3},
                       {4, 4, 0.250526809130882e5},
                       {4, 5, 0.146997380630766e6},
                       {5, 28, 0.538069315091534e20},
                       {6, 28, 0.143619827291346e22},
                       {7, 24, 0.364985866165994e20},
                       {8, 1, -0.254741561156775e4},
                       {10, 32, 0.240120197096563e28},
                       {10, 36, -0.393847464679496e30},
                       {14, 22, 0.147073407024852e25},
                       {18, 28, -0.426391250432059e32},
                       {20, 36, 0.194509340621077e39},
                       {22, 16, 0.666212132114896e24},
                       {22, 28, 0.706777016552858e34},
                       {24, 36, 0.175563621975576e42},
                       {28, 16, 0.108408607429124e29},
                       {28, 36, 0.730872705175151e44},
                       {32, 10, 0.159145847398870e25},
                       {32, 28, 0.377121605943324e41}};

    double nu = h / 2300 - 1.01;
    double sigma = s / 4.4 - 0.75;
    // double suma = 0;
    // for (int i = 0; i < 33; i++)
    // {
    //    suma += n[i] * pow(nu, I[i]) * pow(sigma, J[i]);
    // }
    double suma = poly(nu, sigma, 33, IJn);
    return (99 * suma);
}

double hs2p3b_reg3(double h, double s)
/*Backward equation for region 3b, P=f(h,s)
    h :  Specific enthalpy [kJ/kg]
    s : Specific entropy [kJ/kgK]
    P : Pressure [MPa]*/
{
    IJnData IJn[35] = {
        {-12, 2, 0.125244360717979e-12},
        {-12, 10, -0.126599322553713e-1},
        {-12, 12, 0.506878030140626e1},
        {-12, 14, 0.317847171154202e2},
        {-12, 20, -0.391041161399932e6},
        {-10, 2, -0.975733406392044e-10},
        {-10, 10, -0.186312419488279e2},
        {-10, 14, 0.510973543414101e3},
        {-10, 18, 0.373847005822362e6},
        {-8, 2, 0.299804024666572e-7},
        {-8, 8, 0.200544393820342e2},
        {-6, 2, -0.498030487662829e-5},
        {-6, 6, -0.102301806360030e2},
        {-6, 7, 0.552819126990325e2},
        {-6, 8, -0.206211367510878e3},
        {-5, 10, -0.794012232324823e4},
        {-4, 4, 0.782248472028153e1},
        {-4, 5, -0.586544326902468e2},
        {-4, 8, 0.355073647696481e4},
        {-3, 1, -0.115303107290162e-3},
        {-3, 3, -0.175092403171802e1},
        {-3, 5, 0.257981687748160e3},
        {-3, 6, -0.727048374179467e3},
        {-2, 0, 0.121644822609198e-3},
        {-2, 1, 0.393137871762692e-1},
        {-1, 0, 0.704181005909296e-2},
        {0, 3, -0.829108200698110e2},
        {2, 0, -0.265178818131250},
        {2, 1, 0.137531682453991e2},
        {5, 0, -0.522394090753046e2},
        {6, 1, 0.240556298941048e4},
        {8, 1, -0.227361631268929e5},
        {10, 1, 0.890746343932567e5},
        {14, 3, -0.239234565822486e8},
        {14, 7, 0.568795808129714e10},
    };

    double nu = h / 2800 - 0.681;
    double sigma = s / 5.3 - 0.792;
    // double suma = 0;
    // for (int i = 0; i < 35; i++)
    //{
    //     suma += n[i] * pow(nu, I[i]) * pow(sigma, J[i]);
    // }
    double suma = poly(nu, sigma, 35, IJn);
    return (16.6 / suma);
}

double hs2p_reg3(double h, double s)
/*  Backward equation for region 3, P=f(h,s)
        h : Specific enthalpy [kJ/kg]
        s : Specific entropy [kJ/kgK]
        P : Pressure [MPa]
  */
{

    double p;
    if (s <= sc_water)
        p = hs2p3a_reg3(h, s);
    else
        p = hs2p3b_reg3(h, s);

    return (p);
}