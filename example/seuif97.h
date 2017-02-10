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

#define IMPORT __stdcall __declspec(dllimport)

IMPORT double seupt(double p, double t, int propertyID);
IMPORT double seuph(double p, double h, int propertyID);
IMPORT double seups(double p, double s, int propertyID);
IMPORT double seupv(double p, double v, int propertyID);
IMPORT double seuth(double t, double h, int propertyID);
IMPORT double seuthHi(double t, double h, int propertyID);
IMPORT double seuthLo(double t, double h, int propertyID);
IMPORT double seuts(double t, double s, int propertyID);
IMPORT double seutv(double t, double v, int propertyID);
IMPORT double seuhs(double h, double s, int propertyID);
IMPORT double seupx(double p, double x, int propertyID);
IMPORT double seutx(double t, double x, int propertyID);

IMPORT double seuishd(double pi, double ti, double pe);
IMPORT double seuief(double pi, double ti, double pe, double te);
IMPORT double seupt2eu(double p, double t, double tu);
IMPORT double seups2eu(double p, double s, double tu);
IMPORT double seuph2eu(double p, double h, double tu);
IMPORT double seupv2eu(double p, double v, double tu);
IMPORT double seuth2eu(double t, double h, double tu);
IMPORT double seuth2euHi(double t, double h, double tu);
IMPORT double seuth2euLo(double t, double h, double tu);

IMPORT double seuts2eu(double t, double s, double tu);
IMPORT double seutv2eu(double t, double v, double tu);

IMPORT double seuhs2eu(double h, double s, double tu);
IMPORT double seupx2eu(double p, double x, double tu);
IMPORT double seutx2eu(double t, double x, double tu);

#ifdef __cplusplus
}
#endif

#endif
