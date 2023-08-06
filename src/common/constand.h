#pragma once

#define INVALID_OUTID -1000

#define INVALID_P -2100
#define INVALID_T -2101
#define INVALID_S -2102
#define INVALID_H -2103
#define INVALID_PT -2201
#define INVALID_HS -2202
#define INVALID_VALUE -9999

#define K 273.15;

static double rgas_water = 0.461526; // gas constant in KJ/(kg K)
// critical point
static double tc_water = 647.096;          // critical temperature in K
static double pc_water = 22.064;           // critical p in Mpa
static double dc_water = 322.0;            // critical density in kg/m**3
static double sc_water = 4.41202148223476; // Critic entropy
static double hc_water = 2.087546845e+03;  // Critic entropy h
// triple point
static double Pt = 611.657e-6;     // the triple point
static double Tt = 273.16;         // the triple point
static double st_water = 5.85;     // the triple point
static double ht_water = 0.611783; // the triple point

// T=623.15 region (1,3)
static double Ps_623 = 16.5291642526045; // PMIN3 Ps_623 = _PSat_T(623.15)  P Saturation at 623.15 K, boundary region 1-3
// T=273.15 Tmin
static double Pmin = 0.000611212677444; // Pmin = _PSat_T(273.15)  Minimum pressure

#define P01 16.53
#define T01 1386.0
#define TMAX1 623.15
#define TMIN1 273.15
#define PMAX1 100.00
#define PMIN1 0.000611212677444

#define T02 540.0
#define P02 1.0
#define TMAX2 1073.15
#define TMIN2 273.15
#define PMAX2 100.00
#define PMIN2 1.0E-8

#define D03 322.0
#define T03 647.096
#define TMAX3 863.15
#define TMIN3 623.15
#define PMAX3 100.0
#define PMIN3 16.5291643

#define TMAX4 647.096
#define TMIN4 273.15
#define PMAX4 22.064
#define PMIN4 0.000611212677444
#define HMAX4 2803.2738880203456
#define HMIN4 0.38039218566765925
#define SMAX4 9.153081306725117
#define SMIN4 0.33567511183921145

#define T05 1000.0
#define P05 1.0
#define TMAX5 2273.15
#define TMIN5 1073.15
#define PMAX5 50.0
#define PMIN5 1.0E-8

#define VMAX 1.0E+10
#define VMIN 0.00095
#define HMAX 7376.99
#define HMIN -0.1
#define SMAX 18.992    // 1.0E-8, 2273.15
#define SMIN -0.008583 // 100,273.15