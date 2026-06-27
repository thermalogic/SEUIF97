/**
 * @file root.c
 * @brief Root finding algorithms for IAPWS-IF97
 * 
 * This file implements numerical root finding methods 
 * for solving implicit equations in thermodynamic property calculations.
 * Reference: Numerical Recipes, Chapter 9, Pages 347 ~ 368
 *   - bisection method
 *   - secant method
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */

#include <math.h>
#include "algorithm.h"
#include "../common/constant.h"

/**
 * Finds the root of the equation f(x) = 0 using the bisection method.
 *
 * @param t1           Left boundary of the search interval
 * @param t2           Right boundary of the search interval
 * @param f            Target function pointer f(double, double)
 * @param fvar          Fixed parameter value
 * @param r            Target value (solve for f = r)
 * @param fvar_position Position of the fixed parameter: FIRST_FIXED=f(fvar,t), SECOND_FIXED=f(t,fvar)
 * @param max_iter     Maximum number of iterations
 * @param tol          Function value tolerance (|f(x)| < tol)
 * @param x_tol        Interval length tolerance (|t1 - t2| < x_tol)
 * @return             Approximate root satisfying the precision requirement
 */
double bisection(calfn fn, double fvar, double target, double x1, double x2, int fvar_position, int max_iter, double tol, double x_tol) {
    double r_x1, r_x2;
    
    // Calculate function values based on variable position
    if (fvar_position == FIRST_FIXED) {
        // f(fvar, x) - first parameter is fixed
        r_x1 = target - fn(fvar, x1);
        r_x2 = target - fn(fvar, x2);
    } else {
        // f(x, fvar) - second parameter is fixed
        r_x1 = target - fn(x1, fvar);    
        r_x2 = target - fn(x2, fvar);
    }
    
    if (r_x1 * r_x2 > 0.0 || isnan(r_x1) || isnan(r_x2)) {
        return INVALID_VALUE;
    }

    for (int i = 0; i < max_iter; i++) {
        double tm = 0.5 * (x1 + x2);
        double r_tm;
        
        // Calculate function value based on variable position
        if (fvar_position == FIRST_FIXED) {
            r_tm = target - fn(fvar, tm);
        } else {
            r_tm = target - fn(tm, fvar);
        }
        
        if (fabs(r_tm) < tol || fabs(x1 - x2) < x_tol) {
            return tm;
        }
        
        if (r_x1 * r_tm < 0.0) {
            x2 = tm;
            r_x2 = r_tm;
        } else {
            x1 = tm;
            r_x1 = r_tm;
        }
    }
    return 0.5 * (x1 + x2);
}

//----------------------------------------------------------------------------
// SECANT METHOD : Ch.9.2: Pages 357, 
// Using the secant method, find the root of a func throught lie between x1 and
// x2. The root returned as rtsec, is refined until its accuracy is ABS(xacc)
//----------------------------------------------------------------------------

/**
 * Finds the root of the equation f(x) = target using the secant method.
 *
 * @param func         Target function pointer f(double, double)
 * @param fvar         Fixed parameter value
 * @param target       Target value (solve for f = target)
 * @param x1           Left boundary of the search interval
 * @param x2           Right boundary of the search interval
 * @param fvar_position Position of the fixed parameter: FIRST_FIXED=f(fvar,x), SECOND_FIXED=f(x,var)
 * @param xacc         Convergence precision
 * @param max_iter     Maximum number of iterations
 * @return             Approximate root satisfying the precision requirement
 */
double rtsec(calfn fn, double fvar, double target, double x1,double x2, int fvar_position,int max_iter, double xacc)
{
  double xl, rts, swap, dx;
  double fl, f;
  
  // Calculate function values based on variable position
  if (fvar_position == FIRST_FIXED) {
      // f(fvar, x) - first parameter is fixed
      fl = target - fn(fvar, x1);
      f = target - fn(fvar, x2);
  } else {
      // f(x, fvar) - second parameter is fixed
      fl = target - fn(x1, fvar);
      f = target - fn(x2, fvar);
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
          // rts must be bounded 
          if (rts <= 0)  {  
            rts = 0.000001;
          }
          if (fvar_position == FIRST_FIXED) {
              f = target - fn(fvar, rts);
          } else {
              f = target - fn(rts, fvar);
          }
          i++;
      }
      while (fabs(dx) > xacc && i < max_iter &&
              f != 0.0 && (f - fl) != 0.0); // Convergence
  }
  
  return rts;
}

