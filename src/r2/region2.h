/*-------------------------------------------------------------
     If97 and supp release

      1: IF97 IAPWS, R7-97(2012)
            IF97-Rev.pdf: P12-32
               1)fundamental: (p,t)->v,u,s,h,cp,cv,w
               2)backward: (p,h)->T, (p,s)->T

      2: IAPWS, SR2-01(2014)
             Supp-PHS12-2014.pdf  (h,s)->p
--------------------------------------------------------------*/
#pragma once

#include "../common/common.h"

double gamma0_reg2(double tau, double pi);
double gamma0_pi_reg2(double pi);
double gamma0_pipi_reg2(double pi);
double gamma0_tau_reg2(double tau);
double gamma0_tautau_reg2(double tau, double pi);
double gamma0_pitau_reg2();

double gammar_reg2(double pi, double tau);
double gammar_pi_reg2(double pi, double tau);
double gammar_pipi_reg2(double pi, double tau);
double gammar_pitau_reg2(double pi, double tau);
double gammar_tau_reg2(double pi, double tau);
double gammar_tautau_reg2(double pi, double tau);
void polys_solo_0_i_reg2(double pi, double tau, double *poly, double *poly_pi);
void polys_solo_0_j_reg2(double pi, double tau, double *poly, double *poly_tau);
void polys_solo_i_j_reg2(double pi, double tau, double *poly_pi, double *poly_tau);
void polys_solo_i_ii_reg2(double pi, double tau, double *poly_pi, double *poly_pipi);
void polys_solo_i_ij_reg2(double pi, double tau, double *poly_pi, double *poly_pitau);
void polys_solo_i_ii_ij_reg2(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau);
void polys_solo_i_ij_jj_reg2(double pi, double tau, double *poly_pi, double *poly_pitau, double *poly_tautau);
void polys_solo_i_ii_ij_jj_reg2(double pi, double tau, double *poly_pi, double *poly_pipi, double *poly_pitau, double *poly_tautau);

// IF97 fundamental: (p,t)
double pT2v_reg2(double p, double T);
double pT2u_reg2(double p, double T);
double pT2s_reg2(double p, double T);
double pT2h_reg2(double p, double T);
double pT2cv_reg2(double p, double T);
double pT2cp_reg2(double p, double T);
double pT2w_reg2(double p, double T);

// IF97 extended: (p,t)
double pT2k_reg2(double p, double T);
double pT2ipcec_reg2(double p, double T);
double pT2kt_reg2(double p, double T);

double pT2g_reg2(double p, double T);
double pT2f_reg2(double p, double T);

double pT2joule_reg2(double p, double T);
double pT2ijoule_reg2(double p, double T);

double pT2z_reg2(double p, double T);
double pT2e_reg2(double p, double T);

double pT2dpdtcv_reg2(double p, double T);
double pT2dvdpct_reg2(double p, double T);
double pT2dvdtcp_reg2(double p, double T);

double pT2v_reg2(double p, double T);
double pT2u_reg2(double p, double T);
double pT2s_reg2(double p, double T);
double pT2h_reg2(double p, double T);
double pT2cp_reg2(double p, double T);
double pT2cv_reg2(double p, double T);
double pT2w_reg2(double p, double T);

double ph2T_reg2(double p, double h);
double ps2T_reg2(double p, double s);
double hs2p_reg2(double h, double s);

double ph2T_reg2a(double p, double h);
double ph2T_reg2b(double p, double h);
double ph2T_reg2c(double p, double h);

double ps2T_reg2a(double p, double s);
double ps2T_reg2b(double p, double s);
double ps2T_reg2c(double p, double s);

double hs2p_reg2a(double h, double s);
double hs2p_reg2b(double h, double s);
double hs2p_reg2c(double h, double s);

// (p,T) ->properties
double pT_ext_reg2(double p, double T, int o_id);
double pT_thermal_reg2(double p, double T, int o_id);

// the extend input pairs
//  (p,v)->T (T,v)->p (T,s)->p
double pv2T_reg2(double p, double v);
double Tv2p_reg2(double T, double v);
double Ts2p_reg2(double T, double s);
double Th2p_reg2(double T, double h);

// pairs s
double pT_reg2(double p, double T, int o_id);
double ph_reg2(double p, double h, int o_id);
double ps_reg2(double p, double h, int o_id);
double hs_reg2(double p, double h, int o_id);
// the extend input pairs
//  (p,v) (T,v)p (T,s) (T,h)
double pv_reg2(double p, double v, int o_id);
double Tv_reg2(double T, double v, int o_id);
double Ts_reg2(double T, double s, int o_id);
double Th_reg2(double T, double h, int o_id);
