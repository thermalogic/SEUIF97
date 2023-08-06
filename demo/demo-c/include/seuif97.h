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

IMPORT seuhx(double h, double x, int propertyID);
IMPORT seusx(double s, double x, int propertyID);

// Thermodynamic Process of Steam Turbine
IMPORT seuishd(double pi, double ti, double pe);
IMPORT seuief(double pi, double ti, double pe, double te);


#ifdef __cplusplus
}
#endif

#endif
