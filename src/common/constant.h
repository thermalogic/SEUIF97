/**
 * @file constant.h
 * @brief Constants and error codes for IAPWS-IF97
 * 
 * This header file defines physical constants, critical point values,
 * triple point values, and error codes used throughout the library.
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

/**
 * @file constant.h
 * @brief Constants and error codes for IAPWS-IF97
 * 
 * This header file defines physical constants, critical point values,
 * triple point values, and error codes used throughout the library.
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#pragma once

#define INVALID_OUTID -1000

#define INVALID_P -2100
#define INVALID_T -2101
#define INVALID_V -2102
#define INVALID_S -2103
#define INVALID_H -2104
#define INVALID_PT -2201
#define INVALID_PH -2202
#define INVALID_PS -2203
#define INVALID_PV -2204
#define INVALID_HS -2205
#define INVALID_TH -2206
#define INVALID_TS -2207
#define INVALID_TV -2208
#define INVALID_VALUE -9999

#define P_TOL 1.0e-15
#define T_TOL 1.0e-5

#define K 273.15
/// const for none region input
#define rgas_water  0.461526 // gas constant in KJ/(kg K)
// critical point
#define tc_water 647.096          // critical temperature in K
#define pc_water 22.064           // critical p in MPa
#define dc_water 322.0            // critical density in kg/m**3
#define sc_water 4.41202148223476 // Critical entropy
#define hc_water 2.087546845e+03  // Critical enthalpy h
// triple point
#define Pt 611.657e-6     // the triple point
#define Tt 273.16         // the triple point
#define st_water 5.85     // the triple point
#define ht_water 0.611783 // the triple point
// T=623.15 region (1,3)
#define Ps_623 16.5291642526045 // PMIN3 Ps_623 = _PSat_T(623.15)  P Saturation at 623.15K boundary region 1-3

#define PMIN 0.000611212677444 // Pmin = _PSat_T(273.15)  Minimum pressure
#define PMAX 100.0
#define TMIN 273.15
#define TMAX 2273.15
#define HMAX 7376.99
#define HMIN 0.0
#define SMAX 11.92105507   // 18.992 - 1.0E-8, 2273.15
#define SMIN 0.0
#define VMAX 1.71645345e3  // P=6.112127e-4 MPa, T=2273.15
#define VMIN 0.00095       //  P=6.112127e-4 MPa, T=273.15 K v=1.00020698e-3

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