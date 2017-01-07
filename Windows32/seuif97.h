
#ifndef SEUIF97H
#define SEUIF97H

#ifdef __cplusplus
	extern  "C"
	{
#endif

#define IMPORT __stdcall __declspec(dllimport)

IMPORT double pt(double p,double t,int wp);
IMPORT double ph(double  p,double h,int wp);
IMPORT double ps(double  p,double s,int wp);
IMPORT double pv(double  p,double v,int wp);
IMPORT double th(double  t,double h,int wp);
IMPORT double thHi(double  t,double h,int wp);
IMPORT double thLo(double  t,double h,int wp);
IMPORT double ts(double  t,double s,int wp);
IMPORT double tv(double  t,double v,int wp);
IMPORT double hs(double  h,double s,int wp);
IMPORT double px(double  p,double x,int wp);
IMPORT double tx(double  t,double x,int wp);

//IMPORT double hx(long ID, double  h,double x,int wp);
//IMPORT double sx(long ID, double  s,double x,int wp);
//IMPORT double vx(long ID, double  v,double x,int wp);
  
IMPORT double ishd(double  pi, double ti,double pe);
IMPORT double ief(double  pi, double ti,double pe,double te);
IMPORT double pt2eu(double  p,double t,double tu);
IMPORT double ps2eu(double  p,double s,double tu);
IMPORT double ph2eu(double  p,double h,double tu);
IMPORT double pv2eu(double  p,double v,double tu);
IMPORT double th2eu(double  t,double h,double tu);
IMPORT double th2euHi(double  t,double h,double tu);
IMPORT double th2euLo(double  t,double h,double tu);

IMPORT double ts2eu(double  t,double s,double tu);
IMPORT double tv2eu(double  t,double v,double tu);

IMPORT double hs2eu(double  h,double s,double tu);
IMPORT double px2eu(double  p,double x,double tu);
IMPORT double tx2eu(double t,double x,double tu);

#ifdef __cplusplus
	}
#endif

#endif
