/*
This is header file of SEUIF97 

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2016.4.20
*/

#ifndef SEUIF97H
#define SEUIF97H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32

#define IMPORT __declspec(dllimport) double __stdcall 

#else

#define IMPORT double  

#endif

IMPORT seupt(double p, double t, int propertyID);
IMPORT seuph(double p, double h, int propertyID);
IMPORT seups(double p, double s, int propertyID);
IMPORT seupv(double p, double v, int propertyID);

IMPORT seuth(double t, double h, int propertyID);
IMPORT seuts(double t, double s, int propertyID);
IMPORT seutv(double t, double v, int propertyID);

IMPORT seuhs(double h, double s, int propertyID);

IMPORT seupx(double p, double x, int propertyID);
IMPORT seutx(double t, double x, int propertyID);

// Thermodynamic Process of Steam Turbine
IMPORT seuishd(double pi, double ti, double pe);
IMPORT seuief(double pi, double ti, double pe, double te);

// Exergy 
IMPORT seupt2eu(double p, double t, double tu);
IMPORT seups2eu(double p, double s, double tu);
IMPORT seuph2eu(double p, double h, double tu);
IMPORT seupv2eu(double p, double v, double tu);

IMPORT seuth2eu(double t, double h, double tu);
IMPORT seuts2eu(double t, double s, double tu);
IMPORT seutv2eu(double t, double v, double tu);

IMPORT seuhs2eu(double h, double s, double tu);

IMPORT seupx2eu(double p, double x, double tu);
IMPORT seutx2eu(double t, double x, double tu);

// thHi and thLO
IMPORT seuthHi(double t, double h, int propertyID);
IMPORT seuthLo(double t, double h, int propertyID);

IMPORT seuth2euHi(double t, double h, double tu);
IMPORT seuth2euLo(double t, double h, double tu);

#ifdef __cplusplus
}
#endif

#endif
