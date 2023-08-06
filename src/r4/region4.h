//---------------------------------------------------------------------------
#pragma once

#include "../common/common.h"

double pSat(double T);
double TSat(double p);

double p2SatWater(double p, int o_id);
double p2SatSteam(double p, int o_id);

double T2SatWater(double T, int o_id);
double T2SatSteam(double T, int o_id);

double hs2T_reg4(double h, double s);

// input pairss
double px_reg4(double p, double x, int o_id);
double Tx_reg4(double T, double x, int o_id);

double ph_reg4(double p, double h, int o_id);
double ps_reg4(double p, double s, int o_id);
double hs_reg4(double h, double s, int o_id);

double pT_reg4(double p, double T, int o_id);

// the extend input pairs
//  (p,v) (T,v)p (T,s) (T,h)
double pv2x_reg4(double p,double v);
double Tv2x_reg4(double T,double v);
double Th2x_reg4(double T,double h);
double Ts2x_reg4(double T,double s); 

double pv_reg4(double p, double v, int o_id);
double Tv_reg4(double T, double v, int o_id);
double Ts_reg4(double T, double s, int o_id);
double Th_reg4(double T, double h, int o_id);
//
double hx_reg4(double h, double x, int o_id);
double sx_reg4(double s, double x, int o_id);

