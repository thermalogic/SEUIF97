/*
This is header file of SEUIF97 

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn
*/

#ifndef SEUIF97_H
#define SEUIF97_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32

#define IMPORT __declspec(dllimport) double __stdcall 

#else

#define IMPORT double  

#endif

IMPORT pt(double p, double t, int o_id);
IMPORT ph(double p, double h, int o_id);
IMPORT ps(double p, double s, int o_id);
IMPORT pv(double p, double v, int o_id);

IMPORT th(double t, double h, int o_id);
IMPORT ts(double t, double s, int o_id);
IMPORT tv(double t, double v, int o_id);

IMPORT hs(double h, double s, int o_id);

IMPORT px(double p, double x, int o_id);
IMPORT tx(double t, double x, int o_id);

IMPORT hx(double h, double x, int o_id);
IMPORT sx(double s, double x, int o_id);

// Thermodynamic Process of Steam Turbine
IMPORT ishd(double pi, double ti, double pe);
IMPORT ief(double pi, double ti, double pe, double te);


#ifdef __cplusplus
}
#endif

#endif
