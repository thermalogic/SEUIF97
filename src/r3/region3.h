#pragma once

#include "../common/common.h"

double phi_reg3(double tau, double delta);
double phi_delta_reg3(double tau, double delta);
double phi_deltadelta_reg3(double tau, double delta);
double phi_tau_reg3(double tau, double delta);
double phi_tautau_reg3(double tau, double delta);
double phi_deltatau_reg3(double tau, double delta);

void polys_solo_0_j_reg3(double delta, double tau, double *poly, double *poly_tau);
void polys_solo_i_j_reg3(double delta, double tau, double *poly_delta, double *poly_tau);
void polys_solo_i_ii_ij_jj_reg3(double delta, double tau,
                                double *poly_delta,
                                double *poly_deltatau,
                                double *poly_deltadelta, double *poly_tautau);



double Td2p_reg3(double T, double d);
double Td2u_reg3(double T, double d);
double Td2s_reg3(double T, double d);
double Td2h_reg3(double T, double d);
double Td2cp_reg3(double T, double d);
double Td2cv_reg3(double T, double d);
double Td2w_reg3(double T, double d);

// the extended
double Td2e_reg3(double T, double d);
double Td2k_reg3(double T, double d);
double Td2f_reg3(double T, double d);
double Td2g_reg3(double T, double d);
double Td2z_reg3(double T, double d);
double Td2kt_reg3(double T, double d);
double Td2dvdpct_reg3(double T, double d);
double Td2dvdtcp_reg3(double T, double d);
double Td2dpdtcv_reg3(double T, double d);
double Td2ipcec_reg3(double T, double d);
double Td2joule_reg3(double T, double d);
double Td2ijoule_reg3(double T, double d);
//


// -------- p,h ->T v--------------------------
double ph2T3a_reg3(double p, double h);
double ph2T3b_reg3(double p, double h);

double ph2v3a_reg3(double p, double h);
double ph2v3b_reg3(double p, double h);

double ph2T_reg3(double p, double h);
double ph2v_reg3(double p, double h);

// -------- p,s -> T,v  --------------------------
double ps2T3a_reg3(double p, double s);
double ps2T3b_reg3(double p, double s);

double ps2v3a_reg3(double p, double s);
double ps2v3b_reg3(double p, double s);

double ps2T_reg3(double p, double s);
double ps2v_reg3(double p, double s);

// --- p(h,s) ------------------
double hs2p3a_reg3(double h, double s);
double hs2p3b_reg3(double h, double s);

double hs2p_reg3(double h, double s);

// --- v(p T) ------------------
// TODO： pT2vSatreg3待测试
double Vpt_3subreg(double p, double t, char subreg);

double pT2vSat_reg3(double p, double T, double x);
double pT2v_reg3(double p, double T);

// (T,d) ->properties
double Td_thermal_reg3(double T, double d, int o_id);
double Td_ext_reg3(double T, double d, int o_id);
double Td_transport_reg3(double T, double d, int o_id);

// the extend input pairs
double pv2T_reg3(double p, double v);
double Th2d_reg3(double T, double h);
double Ts2d_reg3(double T, double s);

// input pairs
double Td_reg3(double T, double d, int o_id);

double pT_reg3(double p, double T, int o_id);
double ph_reg3(double p, double h, int o_id);
double ps_reg3(double p, double s, int o_id);
double hs_reg3(double h, double s, int o_id);

// the extend input pairs
double pv_reg3(double p, double v, int o_id);
double Tv_reg3(double T, double v, int o_id);
double Th_reg3(double T, double h, int o_id);
double Ts_reg3(double T, double s, int o_id);

