/*
The header file of SEUIF97

   Author:   Cheng Maohua
   Email:    cmh@seu.edu.cn
*/

#ifndef SEUIF97_H

#define SEUIF97_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef IF97_DLL
#ifdef WIN32 //  || _WIN32 /* To Microsoft Visual Basic for Application */
#if defined(BUILD_DLL)
#define IF97_DLL __stdcall __declspec(dllexport)
#elif defined(USE_DLL)
#define IF97_DLL __stdcall __declspec(dllimport)
#else
#define IF97_DLL
#endif
#else
#define IF97_DLL
#endif
#endif

    IF97_DLL double pt(double p, double t, int o_id);
    IF97_DLL double ph(double p, double h, int o_id);
    IF97_DLL double ps(double p, double s, int o_id);
    IF97_DLL double pv(double p, double v, int o_id);
    IF97_DLL double th(double t, double h, int o_id);

    IF97_DLL double ts(double t, double s, int o_id);
    IF97_DLL double tv(double t, double v, int o_id);
    IF97_DLL double hs(double h, double s, int o_id);
    IF97_DLL double px(double p, double x, int o_id);
    IF97_DLL double tx(double t, double x, int o_id);
    //
    IF97_DLL double hx(double h, double x, int o_id);
    IF97_DLL double sx(double s, double x, int o_id);

    //  Functions of Thermodynamic Process
    IF97_DLL double ishd(double pi, double ti, double pe);
    IF97_DLL double ief(double pi, double ti, double pe, double te);
 
#ifdef __cplusplus
}
#endif

#endif
