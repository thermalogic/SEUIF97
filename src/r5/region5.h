#pragma once

#include "../common/common.h"

double gamma0_reg5(double pi, double tau);
double gamma0_pi_reg5(double pi);
double gamma0_pipi_reg5(double pi);
double gamma0_pitau_reg5();
double gamma0_tau_reg5(double tau);
double gamma0_tautau_reg5(double tau);

double gammar_reg5(double pi, double tau);
double gammar_pi_reg5(double pi, double tau);
double gammar_pipi_reg5(double pi, double tau);
double gammar_pitau_reg5(double pi, double tau);
double gammar_tau_reg5(double pi, double tau);
double gammar_tautau_reg5(double pi, double tau);


// IF97 fundamental :(p,t)
double pT2h_reg5(double p, double T);
double pT2s_reg5(double p, double T);
double pT2v_reg5(double p, double T);
double pT2u_reg5(double p, double T);
double pT2cv_reg5(double p, double T);
double pT2cp_reg5(double p, double T);
double pT2w_reg5(double p, double T);
// extend 
double pT2k_reg5(double p, double T);
double pT2g_reg5(double p, double T);
double pT2f_reg5(double p, double T);
double pT2e_reg5(double p, double T);
double pT2joule_reg5(double p, double T);
double pT2ijoule_reg5(double p, double T);
double pT2z_reg5(double p, double T);
double pT2kt_reg5(double p, double T);
double pT2ipcec_reg5(double p, double T);
double pT2dpdtcv_reg5(double p, double T);
double pT2dvdpct_reg5(double p, double T);
double pT2dvdtcp_reg5(double p, double T);




// IF97 backward:(p,h)->T
double ph2T_reg5(double p, double h);
// IF97 backward: (p,s)->T
double ps2T_reg5(double p, double s);
// Supp:backward（h,s)->p
double hs2p_reg5(double h, double s);

// the extend input pairs
//  (p,v)->T (T,v)->p (T,s)->p (T,h)->p
double pv2T_reg5(double p, double v);
double Tv2p_reg5(double T, double v);
double Ts2p_reg5(double T, double s);
double Th2p_reg5(double T, double s);


// (p,T) ->properties
double pT_thermal_reg5(double p, double T, int o_id);
double pT_ext_reg5(double p, double T, int o_id);

// input pairs
double pT_reg5(double p, double T, int o_id);

double ph_reg5(double p, double h, int o_id);
double ps_reg5(double p, double h, int o_id);
double hs_reg5(double p, double h, int o_id);

// the extend input pairs
//  (p,v) (T,v)p (T,s)
double pv_reg5(double p, double v, int o_id);
double Tv_reg5(double T, double v, int o_id);
double Ts_reg5(double T, double s, int o_id);
double Th_reg5(double T, double h, int o_id);