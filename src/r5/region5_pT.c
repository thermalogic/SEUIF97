/* 
  Region 5 : Basic Eq (p,T)->v,h,s,cp,cv,w,
	http://www.iapws.org/relguide/IF97-Rev.html, Eq 32-34P39
			  
*/

#include <math.h>
#include "region5.h"
#include "../common/constand.h"
#include "../common/propertry_id.h"
#include "region5_coff.h"

double pT_thermal_reg5(double p, double T, int o_id)
// o_id: output propertry 
{
    double value;
    switch (o_id)
    {
      case OT:
          value = T;
          break;
      case OP:
          value = p;
          break;
      case OV:
          value = pT2v_reg5(p, T);
          break;
      case OD:
          value = 1.0/pT2v_reg5(p, T);
           break;
      case OH:
          value = pT2h_reg5(p, T);
           break;
      case OU:
          value = pT2u_reg5(p, T);
           break;     
      case OS:
           value = pT2s_reg5(p, T);
          break;
      case OCV:
           value = pT2cv_reg5(p, T);
          break;
      case OCP:
           value = pT2cp_reg5(p, T);
          break;  
       case OW:
           value = pT2w_reg5(p, T);
          break;       
       default:
          value = INVALID_OUTID;
       break;
    }
    return value;
    
}


double pT2v_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, v;
	a = pi * (gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau));
	v = rgas_water * T / p * a;
	return v * 0.001;
}

double pT2u_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, u;
	a = tau * (gamma0_tau_reg5(tau) + gammar_tau_reg5(pi, tau)) - pi * (gamma0_pi_reg5(pi) + gammar_pi_reg5(pi, tau));
	u = rgas_water * T * a;
	return u;
}

double pT2s_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, s;
	a = tau * (gamma0_tau_reg5(tau) + gammar_tau_reg5(pi, tau)) - (gamma0_reg5(pi, tau) + gammar_reg5(pi, tau));
	s = rgas_water * a;
	return s;
}

double pT2h_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, h;
	a = tau * (gamma0_tau_reg5(tau) + gammar_tau_reg5(pi, tau));
	h = rgas_water * T * a;
	return h;
}

double pT2cp_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, cp;
	a = -tau*tau * (gamma0_tautau_reg5(tau) + gammar_tautau_reg5(pi, tau));
	cp = rgas_water * a;
	return cp;
}

double pT2cv_reg5(double p, double T)
{ // t[K],	p[MPa]
	double pi = p / r5Pstar;
	double tau = r5Tstar / T;
	double a, b, c; // for temp
	double cv;
	a = (-pow(tau, 2.0)) * (gamma0_tautau_reg5(tau) + gammar_tautau_reg5(pi, tau));
	b = 1.0 + pi * gammar_pi_reg5(pi, tau) - tau * pi * gammar_pitau_reg5(pi, tau);
	c = 1.0 - pow(pi, 2.0) * gammar_pipi_reg5(pi, tau);
	cv = rgas_water * (a - pow(b, 2.0) / c);
	return cv;
}

double pT2w_reg5(double p, double T)
{
	double w;
	double a, b, c, d, w2;
	double tau = r5Tstar / T;
	double pi = p / r5Pstar;
	double dgammar_pi = gammar_pi_reg5(pi, tau);

	a = pow(1.0 + pi * dgammar_pi, 2.0);
	b = 1.0 - pi * pi * gammar_pipi_reg5(pi, tau);
	c = 1.0 + pi * dgammar_pi - tau * pi * gammar_pitau_reg5(pi, tau);
	d = tau * tau * (gamma0_tautau_reg5(tau) + gammar_tautau_reg5(pi, tau));
	w2 = rgas_water * T * a / (b + (c * c) / d) * 1000.0;
	if (w2 < 0.0)
		w2 = 0.0;
	w = sqrt(w2);
	return w;
}
