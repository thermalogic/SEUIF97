/**
 * @file root.c
 * @brief Root finding algorithms for IAPWS-IF97
 * 
 * This file implements numerical root finding methods (secant method)
 * for solving implicit equations in thermodynamic property calculations.
 * Reference: Numerical Recipes, Chapter 9, Pages 347 ~ 368
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "algorithm.h"
#include "../common/constant.h"

#define EPS 3.0e-8

//----------------------------------------------------------------------------
// SECANT METHOD : Ch.9.2: Pages 357, 
// Using the secant method, find the root of a func throught lie between x1 and
// x2. The root returned as rtsec, is refined until its accuracy is ABS(xacc)
//----------------------------------------------------------------------------

/**
 * Finds the root of the equation f(x) = target using the secant method.
 *
 * @param func         Target function pointer f(double, double)
 * @param var          Fixed parameter value
 * @param target       Target value (solve for f = target)
 * @param x1           Left boundary of the search interval
 * @param x2           Right boundary of the search interval
 * @param var_position Position of the fixed parameter: 1=f(var,x), 2=f(x,var)
 * @param xacc         Convergence precision
 * @param iMAX         Maximum number of iterations
 * @return             Approximate root satisfying the precision requirement
 */
double rtsec(callfunc func, double var, double target, double x1,
             double x2, int var_position, double xacc, int iMAX)
{
  double xl, rts, swap, dx;
  double fl, f;
  
  // Calculate function values based on variable position
  if (var_position == 1) {
      // f(var, x) - first parameter is fixed
      fl = target - func(var, x1);
      f = target - func(var, x2);
  } else {
      // f(x, var) - second parameter is fixed
      fl = target - func(x1, var);
      f = target - func(x2, var);
  }
  
  // pick the bound with the smaller function value as the most recent guess
  if (fabs(fl) < fabs(f)) {
        rts = x1;
        xl = x2;
        swap = fl;
        fl = f;
        f = swap;
  } else {
        xl = x1;
        rts = x2;
  }
  
  // secant loop
  int i = 0;
  if ((f - fl) != 0.0)
  {
      do
      {
          dx = (xl - rts) * f / (f - fl); // increment with respect to latest value
          xl = rts;
          fl = f;
          rts += dx;
          
          // rts must be bounded in region X
          if (var_position == 1) {
              f = target - func(var, rts);
          } else {
              // rts may be out-of-bounds in region X
              if (rts <= 0) rts = 0.000001;
              f = target - func(rts, var);
          }
          i++;
      }
      while (fabs(dx) > xacc && i < iMAX &&
              f != 0.0 && (f - fl) != 0.0); // Convergence
  }
  
  return rts;
}

/**
 * Finds the root of the equation f(x) = 0 using the bisection method.
 *
 * @param t1           Left boundary of the search interval
 * @param t2           Right boundary of the search interval
 * @param f            Target function pointer f(double, double)
 * @param var          Fixed parameter value
 * @param r            Target value (solve for f = r)
 * @param var_position Position of the fixed parameter: 1=f(var,t), 2=f(t,var)
 * @param max_iter     Maximum number of iterations
 * @param tol          Function value tolerance (|f(x)| < tol)
 * @param x_tol        Interval length tolerance (|t1 - t2| < x_tol)
 * @return             Approximate root satisfying the precision requirement
 */
double bisection(double t1, double t2, double (*f)(double,double), double var, double r, int var_position, int max_iter, double tol, double x_tol) {
    double r_t1, r_t2;
    
    // Calculate function values based on variable position
    if (var_position == 1) {
        // f(var, t) - first parameter is fixed
        r_t1 = r - f(var, t1);
        r_t2 = r - f(var, t2);
    } else {
        // f(t, var) - second parameter is fixed
        r_t1 = r - f(t1, var);
        r_t2 = r - f(t2, var);
    }
    
    if (r_t1 * r_t2 > 0.0) {
        return INVALID_VALUE;
    }

    for (int i = 0; i < max_iter; i++) {
        double tm = 0.5 * (t1 + t2);
        double r_tm;
        
        // Calculate function value based on variable position
        if (var_position == 1) {
            r_tm = r - f(var, tm);
        } else {
            r_tm = r - f(tm, var);
        }
        
        if (fabs(r_tm) < tol || fabs(t1 - t2) < x_tol) {
            return tm;
        }
        
        if (r_t1 * r_tm < 0.0) {
            t2 = tm;
            r_t2 = r_tm;
        } else {
            t1 = tm;
            r_t1 = r_tm;
        }
    }
    
    return 0.5 * (t1 + t2);
}

#undef EPS