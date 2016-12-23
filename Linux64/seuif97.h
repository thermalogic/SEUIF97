
#ifndef SEUIF97H
#define SEUIF97H

#ifdef __cplusplus
	extern  "C"
	{
#endif

 double seupt(double p,double t,int wp);
 double seuph(double  p,double h,int wp);
 double seups(double  p,double s,int wp);
 double seupv(double  p,double v,int wp);
 double seuth(double  t,double h,int wp);
 double seuthHi(double  t,double h,int wp);
 double seuthLo(double  t,double h,int wp);
 double seuts(double  t,double s,int wp);
 double seutv(double  t,double v,int wp);
 double seuhs(double  h,double s,int wp);
 double seupx(double  p,double x,int wp);
 double seutx(double  t,double x,int wp);

//EXPORT double hx(long ID, double  h,double x,int wp);
//EXPORT double sx(long ID, double  s,double x,int wp);
//EXPORT double vx(long ID, double  v,double x,int wp);
  
 double seuishd(double  pi, double ti,double pe);
 double seuief(double  pi, double ti,double pe,double te);
 double seupt2eu(double  p,double t,double tu);
 double seups2eu(double  p,double s,double tu);
 double seuph2eu(double  p,double h,double tu);
 double seupv2eu(double  p,double v,double tu);
 double seuth2eu(double  t,double h,double tu);
 double seuth2euHi(double  t,double h,double tu);
 double seuth2euLo(double  t,double h,double tu);

 double seuts2eu(double  t,double s,double tu);
 double seutv2eu(double  t,double v,double tu);

 double seuhs2eu(double  h,double s,double tu);
 double seupx2eu(double  p,double x,double tu);
 double seutx2eu(double t,double x,double tu);

  double seuishd(double  pi, double ti,double pe);
 double seuief(double  pi, double ti,double pe,double te);

#ifdef __cplusplus
	}
#endif

#endif
