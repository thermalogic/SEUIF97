/**
 * @file region5_gfe.c
 * @brief Gibbs free energy and derivatives for Region 5
 * 
 * This file implements the dimensionless Gibbs free energy (gamma) and
 * its derivatives for Region 5 (high temperature steam).
 * Reference: IAPWS-IF97, Section 4.5, Page 38-39
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "region5.h"
#include "region5_coff.h"
#include "../algo/ipow.h"

//	P37 Table 37
//  Ideal properties for Region 5
// Table 37. Numerical values of the coefficients and exponents of ideal-gas part  of the
// dimensionless Gibbs free energy for region 5, Eq. (33)

// P36 The equation for the ideal-gas part of the dimensionless Gibbs free energy reads eq33
double gamma0_reg5(double pi, double tau)
{
	double value = log(pi);
    double tau_inv = 1.0 / tau;
	double tau_inv2 = tau_inv * tau_inv;
	// 0, 1, -3, -2, -1, 2
	value += no[0];
    value += no[1]*tau;
	value += no[2]*tau_inv2*tau_inv;
    value += no[3]*tau_inv2;
    value += no[4]*tau_inv;
    value += no[5]*tau*tau;
    //	for (unsigned i = 0; i < 6; i++)
    //		value += no[i] * IPOW(tau, Jo[i]);
	return value;
}

// 38p
double gamma0_pi_reg5(double pi)
{
	return 1.0 / pi;
}

// 38p
double gamma0_pipi_reg5(double pi)
{
	double p_inv=1.0/pi;
	return -1.0*p_inv*p_inv;
}

double gamma0_tau_reg5(double tau)
{
	double value = 0.0;
   //  0, 1, -3, -2, -1, 2
   // -1, 0, -4, -3, -2, 1
    double tau_inv = 1.0 / tau;
	double tau_inv2 = tau_inv * tau_inv;
    value += no[1];
	value += no[2]*(-3.0)*tau_inv2*tau_inv2;
    value += no[3]*(-2.0)*tau_inv2*tau_inv;
    value += no[4]*(-1.0)*tau_inv2;
    value += no[5]*(2.0)*tau;
  	// for (unsigned i = 0; i < 6; i++)
    //		value += no[i] * Jo[i] * IPOW(tau, Jo[i] - 1);
	return value;
}

double gamma0_tautau_reg5(double tau)
{
	double value = 0.0;
	//  0, 1, -3, -2, -1, 2
    // -2, -1, -5, -4, -3, 0
	for (unsigned i = 0; i < 6; i++)
		value += no[i] * Jo[i] * (Jo[i] - 1) * IPOW(tau, Jo[i] - 2);
	return value;
}

double gamma0_pitau_reg5()
{
	return 0.0;
}

double gammar_reg5(double pi, double tau)
{
	double value = 0.0;
	// I 1 1 1 2 2 3
	// J 1 2 3 3 9 7
	double pi_2=pi*pi;
	double tau_2=tau*tau;
	double tau_3=tau_2*tau;
	double tau_6=tau_3*tau_3;
	value += IJn[0].n * pi*tau;
    value += IJn[1].n * pi*tau_2;
	value += IJn[2].n * pi*tau_3;
	value += IJn[3].n * pi_2*tau_3;
	value += IJn[4].n * pi_2*tau_6*tau_3;
	value += IJn[5].n * pi_2*pi*tau_6*tau;
	
	//for (int i = 0; i < 6; i++)
	//	value += IJn[i].n * IPOW(pi, IJn[i].I) * IPOW(tau, IJn[i].J);
	return value;
}

// Table 41. The residual part  r of the dimensionless Gibbs free energy and its
// derivatives  valueaccording to Eq. (34)
double gammar_pi_reg5(double pi, double tau)
{
	
	double value = 0.0;
	//   I  1 1 1 2 2 3
	// I-1  0 0 0 1 1 2
	//   J  1 2 3 3 9 7
	double tau_2=tau*tau;
	double tau_3=tau_2*tau;
	double tau_6=tau_3*tau_3;
	value += IJn[0].n *tau;
    value += IJn[1].n * tau_2;
	value += IJn[2].n * tau_3;
	value += IJn[3].n * 2.0 * pi*tau_3;
	value += IJn[4].n * 2.0 *pi*tau_6*tau_3;
	value += IJn[5].n * 3.0 *pi*pi*tau_6*tau;
	
	//for (unsigned i = 0; i < 6; i++)
	//	value += IJn[i].n * IJn[i].I * IPOW(pi, IJn[i].I - 1) * IPOW(tau, IJn[i].J);
	return value;
}

double gammar_pipi_reg5(double pi, double tau)
{
	double value = 0.0;
	//   I   1  1  1  2  2  3
	// I-1   0  0  0  1  1  2
	// I-2  -1 -1 -1  0  0  1
	//   J   1  2  3  3  9  7
	double tau_2=tau*tau;
	double tau_3=tau_2*tau;
	double tau_6=tau_3*tau_3;
	value += IJn[3].n * 2.0 * tau_3;
    value += IJn[4].n * 2.0 * tau_6*tau_3;
	value += IJn[5].n *6.0 *pi*tau_6*tau;

	//for (unsigned i = 0; i < 6; i++)
	//	value += IJn[i].n * IJn[i].I * (IJn[i].I - 1) * IPOW(pi, IJn[i].I - 2) * IPOW(tau, IJn[i].J);
	return value;
}

double gammar_tau_reg5(double pi, double tau)
{
	double value = 0.0;
	//   I   1  1  1  2  2  3
	//   J   1  2  3  3  9  7
	// J-1   0  1  2  2  8  6
	double pi_2 = pi * pi;
    double tau_2 = tau * tau;
	double tau_6 = tau_2 * tau_2 * tau_2;
    
    value += IJn[0].n * pi;                               // J=1
    value += IJn[1].n * 2.0 * pi * tau;                   // J=2
    value += IJn[2].n * 3.0 * pi * tau_2;                 // J=3
    value += IJn[3].n * 3.0 * pi_2 * tau_2;               // J=3
    value += IJn[4].n * 9.0 * pi_2 * tau_6* tau_2;        // J=9
    value += IJn[5].n * 7.0 * pi_2 * pi * tau_6;          // J=7

	 //for (unsigned i = 0; i < 6; i++)
     //value += IJn[i].n * IPOW(pi, IJn[i].I) * IJn[i].J * IPOW(tau, IJn[i].J - 1);
	return value;
}

// 39p
double gammar_tautau_reg5(double pi, double tau)
{
	double value = 0.0;
	//   I   1  1  1  2  2  3
	//   J   1  2  3  3  9  7
	// J-1   0  1  2  2  8  6
	// J-2  -1  0  1  1  7  5

	double pi_2 = pi * pi;
    double tau_2 = tau * tau;
    double tau_5 = tau_2 * tau_2 * tau;
    // i=0: J=1, J×(J-1)=0 
    value += IJn[1].n * 2.0 * pi;                            // J=2,  2
    value += IJn[2].n * 6.0 * pi * tau;                      // J=3,  6
    value += IJn[3].n * 6.0 * pi_2 * tau;                    // J=3,  6
    value += IJn[4].n * 72.0 * pi_2 * tau_5*tau_2;           // J=9, 72
    value += IJn[5].n * 42.0 * pi_2 * pi * tau_5; 
	
	//for (unsigned i = 0; i < 6; i++)
	//	value += IJn[i].n * IPOW(pi, IJn[i].I) * IJn[i].J * (IJn[i].J - 1) * IPOW(tau, IJn[i].J - 2);
	return value;
}

double gammar_pitau_reg5(double pi, double tau)
{
	double value = 0.0;
	//   I   1  1  1  2  2  3
	// I-1   0  0  0  1  1  2
	//   J   1  2  3  3  9  7
	// J-1   0  1  2  2  8  6
	double tau_2 = tau * tau;
    double tau_6 = tau_2 * tau_2 * tau_2;
    
    value += IJn[0].n;                                 // I=1,J=1,  1
    value += IJn[1].n * 2.0 * tau;                     // I=1,J=2,  2
    value += IJn[2].n * 3.0 * tau_2;                   // I=1,J=3,  3
    value += IJn[3].n * 6.0 * pi * tau_2;              // I=2,J=3,  6
    value += IJn[4].n * 18.0 * pi * tau_6*tau_2;       // I=2,J=9,  18
	value += IJn[5].n * 21.0 * pi*pi * tau_6;          // I=3,J=27, 21
	
	//for (unsigned i = 0; i < 6; i++)
    //		value += IJn[i].n * IJn[i].I * IPOW(pi, IJn[i].I - 1) * IJn[i].J * IPOW(tau, IJn[i].J - 1);
	return value;
}