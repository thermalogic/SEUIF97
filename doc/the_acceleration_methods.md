# The code snippets of the acceleration methods

## Acceleration Methods

* Shortest Addition Chain Algorithm: Used for the rapid computation of integer powers via optimal multiplication sequences.
* Power Caching Strategy: Precomputes only distinct powers to avoid redundant calculations, directly retrieving them to speed up polynomial evaluation.
* Scaling for Derivatively Related Polynomial Evaluation: Computes a base polynomial, then utilizes derivative relationships to derive the rest via base scaling to maximize efficiency.

## Shortest Addition Chain Algorithm

The code snippets demonstrate the Shortest Addition Chain Algorithm to calculate the $T(p,h)$ in region 1, illustrating the flow from the optimized kernel to the final physical property calculation:

### Backward Equation $T(p,h)$ in region 1

The backward equation $T(p,h)$ for region 1 has the following dimensionless:

$$\frac{T(p,h)}{T^*} = \theta(\pi, \eta) = \sum_{i=1}^{20} n_i \pi^{I_i} (\eta + 1)^{J_i}$$

where

$\theta = T/T^* \quad  T^* = 1 \text{K}$

$\pi = p/p^*  \quad  p^* = 1 \text{MPa}$

$\eta = h/h^* \quad  h^* = 2500 \text{ kJ kg}^{-1}$

### C Code

```c
// algo/algorithm.h
#define IPOW ipowsac

// algo/sac.c
double possac(double x, int n)
{
  // the shortest addition chains, [0,58]
	double x2, x3, x4, x5, x6, x7, x8, x9;
	double x10, x11, x12, x13, x14, x15, x16, x17, x18, x19;
	double x20, x21, x22, x23, x24, x25, x26, x27, x28, x29;
	double x32, x33, x36, x37, x46,x48, x49, x54;

	switch (n)
	{
	case 0:
		return (1);
	case 1:
		return (x);
	case 2:
		return (x * x);
  ...
  case 13:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		return (x8 * x4 * x);
  ...
  }  
}    

double ipowsac(double x, int n)
{
...
}

// algo/polynomial_solo.c
double poly(double vi, double vj, int size, IJnData *IJn)
{
  double v = 0.0;
  for (int k = 0; k < size; k++)
    v += IJn[k].n * IPOW(vi, IJn[k].I) * IPOW(vj, IJn[k].J);
  return v;
}

// r1/region1_T_phps.c
double ph2T_reg1(double p, double h)
{
  // Page 11, Table6 :Initialize coefficients and exponents (P,H)->T for region 1
  IJnData IJn[] = {
    ...
    };

  double pi, eta;
  double theta;
  pi = p / 1.0;
  eta = h / 2500.0 + 1.0;
  theta = poly(pi, eta, 20, IJn);
  return (1.0 *theta);
}
```

## Power Caching and Scaling for Derivatively Related Polynomial Evaluation

The code snippets demonstrate the acceleration methods to calculate the specific internal energy in region 1, illustrating the flow from the optimized kernel to the final physical property calculation:

### The IAPWS-IF97 Equations

The basic equation for this region 1 is a fundamental equation for the specific **Gibbs free energy** $g$. 

$$\frac{g(p,T)}{RT} = \gamma(\pi,\tau) = \sum_{i=1}^{34} n_i (7.1-\pi)^{I_i} (\tau-1.222)^{J_i}$$

where 

$\pi = p/p^{*}$

$\tau = T^{*}/T$

To derive the **specific internal energy**

$$u = g - T \left( \frac{\partial g}{\partial T} \right)_p - p \left( \frac{\partial g}{\partial p} \right)_T$$

$$\frac{u(\pi, \tau)}{RT} = \tau \gamma_{\tau} - \pi \gamma_{\pi}$$

### C code

```c
// algo/polynomial_solo.c
void polys_solo_i_j(double vi, double vj, int size, IJnData *IJn, int *i2soI, int *j2soJ, solo_power_fn solo_i_j_power, double *poly_i, double *poly_j)
{
  (*solo_i_j_power)(vi, vj, soI_pow, soJ_pow);
  double item = 0.0;
  for (int k = 0; k < size; k++)
  {
    item = IJn[k].n * soI_pow[i2soI[k]] * soJ_pow[j2soJ[k]];
    *poly_i += item * IJn[k].I;
    *poly_j += item * IJn[k].J;
  }
  *poly_i /= vi;
  *poly_j /= vj;
}

// r1/region1_solo_ij.h
static const int soI[13] = {0, 1, 2, 3, 4, 5, 8, 21, 23, 29, 30, 31, 32};
static int i2soI[34] = {0, 0, 0, 0, 0,
                      0, 0, 0, 1, 1,
                      1, 1, 1, 1, 2,
                      2, 2, 2, 2, 3,
                      3, 3, 4, 4, 4,
                      5, 6, 6, 7, 8,
                      9, 10, 11, 12};

static const int soJ[25] = {-2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -3, 17, -4, 6, -5, 10,
                            -8, -11, -6, -29, -31, -38, -39, -40, -41};

static int j2soJ[34] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 5, 10, 2, 3, 5, 11, 12, 2,
                      13, 14, 0, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

void solo_ij_pow_reg1(double vi, double vj, double *soI_pow, double *soJ_pow);


// r1/region1_solo_power.c
void solo_ij_pow_reg1(double vi,double vj,double *soI_pow,double *soJ_pow)
{
    // [0, 1, 2, 3, 4, 5, 8, 21, 23, 29, 30, 31, 32];
   
    soI_pow[0] = 1.0;
    for(int k=1; k<=5;k++) {
        soI_pow[k] = soI_pow[k - 1] * vi;
    }
    double vi2 = vi * vi;
    soI_pow[6] = soI_pow[5] * vi2 * vi; //8
    soI_pow[7] = soI_pow[6] * soI_pow[6] * soI_pow[5]; //21
    soI_pow[8] = soI_pow[7] * vi2; //23
    soI_pow[9] = soI_pow[6] * soI_pow[7];
    for(int k=10; k<=12;k++) {
        soI_pow[k] = soI_pow[k - 1] * vi;
    }

    //  -2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -3, 17, -4, 6, -5, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41,
    ...
}

// r1/region1_gef.c
void polys_solo_i_j_reg1(double pi, double tau, double *poly_pi, double *poly_tau)
{
    polys_solo_i_j(7.1 - pi, tau - 1.222, 34, IJn, i2soI, j2soJ, solo_ij_pow_reg1, poly_pi, poly_tau);
    *poly_pi = -(*poly_pi);
}

// r1/region1_pT.c
double pT2u_reg1(double p, double T)
// specific internal energy in region 1
{
  double pi, tau;
  tau = r1Tstar / T;
  pi = p / r1pstar;

  double gammapi = 0.0;
  double gammatau = 0.0;

  polys_solo_i_j_reg1(pi, tau, &gammapi, &gammatau);
  
  return rgas_water * T * (tau * gammatau - pi * gammapi);
}
```
