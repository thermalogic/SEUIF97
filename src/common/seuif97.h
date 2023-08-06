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

    IF97_DLL double seupt(double p, double t, int o_id);
    IF97_DLL double seuph(double p, double h, int o_id);
    IF97_DLL double seups(double p, double s, int o_id);
    IF97_DLL double seupv(double p, double v, int o_id);
    IF97_DLL double seuth(double t, double h, int o_id);

    IF97_DLL double seuts(double t, double s, int o_id);
    IF97_DLL double seutv(double t, double v, int o_id);
    IF97_DLL double seuhs(double h, double s, int o_id);
    IF97_DLL double seupx(double p, double x, int o_id);
    IF97_DLL double seutx(double t, double x, int o_id);
    //
    IF97_DLL double seuhx(double h, double x, int o_id);
    IF97_DLL double seusx(double s, double x, int o_id);

    //  Functions of Thermodynamic Process
    IF97_DLL double seuishd(double pi, double ti, double pe);
    IF97_DLL double seuief(double pi, double ti, double pe, double te);

    // -------------------------------
    IF97_DLL double seupt2eu(double p, double t, double tu);
    IF97_DLL double seups2eu(double p, double s, double tu);
    IF97_DLL double seuph2eu(double p, double h, double tu);
    IF97_DLL double seupv2eu(double p, double v, double tu);
    IF97_DLL double seuth2eu(double t, double h, double tu);

    IF97_DLL double seuts2eu(double t, double s, double tu);
    IF97_DLL double seutv2eu(double t, double v, double tu);

    IF97_DLL double seuhs2eu(double h, double s, double tu);
    IF97_DLL double seupx2eu(double p, double x, double tu);
    IF97_DLL double seutx2eu(double t, double x, double tu);

#ifdef __cplusplus
}
#endif

#endif
