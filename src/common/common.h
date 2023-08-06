#pragma once

typedef struct
{
  int I, J;
  double n;
} IJnData;

// methods
typedef double (*properties_region)(double, double, int);
// tansport properties
double viscosity(double rho, double T);
double kinematic_viscosity(double rho, double T);
double thCond(double rho, double T);
double thermal_diffusivity(double tc, double cp, double d);
double tension(double T);
double prandtl_number(double dv, double cp, double tc);
double thermal_diffusivity(double tc, double cp, double d);

// double dielectric(double rho, double T);
// double refractive(double rho, double T);
// double Kw(double rho, double T);

double pT_transport(double p, double T, int o_id, properties_region fn);
double pT_reg(double p, double T, int o_id, properties_region pT_thermal, properties_region pT_ext);


typedef int (*region_fn)(double, double);
typedef double (*prop_fn)(double, double, int o_id);

double pair_prop(double v1, double v2, int o_id, region_fn regfn,
                 prop_fn fn1,
                 prop_fn fn2,
                 prop_fn fn3,
                 prop_fn fn4,
                 prop_fn fn5);


double pT(double p, double T, int o_id);

// Boundary equations:

// IF97-Rev, Region2-Region3
double B23_T2p(double T); // IF97-Rev, Eq 5
double B23_p2T(double p); // IF97-Rev, Eq 5

// （p,h)-> subregion 3
double h2pSat_reg3(double h); // Supp-Tv(ph,ps)-2014.pdf, Eq 10
// （p,s)-> subregion
double s2pSat_reg3(double s); // Supp-Tv(ph,ps)-2014.pdf, Eq 11

// reg3 （h,s) ->p
double _h1_s(double s);           // Supp-phs3-2014.pdf. Eq 3
double _h3a_s(double s);          // Supp-phs3-2014.pdf. Eq 4
double _h2ab_s(double s);         // Supp-phs3-2014.pdf. Eq 5
double _h2c3b_s(double s);        // Supp-phs3-2014.pdf. Eq 6
double _h13_s(double s);          // Supp-phs3-2014.pdf. Eq 7
double _t_hs(double h, double s); // Supp-phs3-2014.pdf. Eq 8

// region
int pT_region(double p, double T);
int ph_region(double p, double h);
int ps_region(double p, double s);
int hs_region(double h, double s);
// the extended pairs 
int pv_region(double p, double v);
int Th_region(double T, double h);
int Ts_region(double T, double s);
int Tv_region(double T, double v);