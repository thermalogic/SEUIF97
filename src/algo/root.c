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

#define EPS 3.0e-8
//----------------------------------------------------------------------------
// SECANT METHOD : Ch.9.2: Pages 357, 
// Using the secant method, find the root of a func throught lie between x1 and
// x2. The root returned as rtsec, is refined until its accuracy is ABS(xacc)
//----------------------------------------------------------------------------

double rtsec2(callfunc func, double cVar1,double fr,double x1,
             double x2, double fl,double f, double xacc, int iMAX)
// rtsec2: (*func)(cVar1, x) solves for the second parameter: x, x={x1, x2}
// First parameter cVar1 remains unchanged during iteration
// fr: Input result of (*func)(double, double)
// fl: fr - (*func)(cVar1, x1)
// f: fr - (*func)(cVar1, x2)
// rts: Returns the solution for x
{
  double xl,rts,swap,dx;
  // pick the bound with the smaller function value as the most recent guess
  if (fabs(fl) < fabs(f)) {
        rts=x1;
        xl=x2;
        swap=fl;
        fl=f;
        f=swap;
  } else {
        xl=x1;
        rts=x2;
  }
  //secant loop
  int i=0;
  if ((f-fl)!=0.0)
  {
      do
      {
          dx=(xl-rts)*f/(f-fl); // increment with respect to latest value
          xl=rts;
          fl=f;
          rts += dx;
          // TODO: Pass solution bounds as parameters to ensure iteration stays within bounds
          // rts must be bounded in region X
          f=fr-(*func)(cVar1,rts);
          i++;
      }
    //  while ((fabs(dx) > xacc)&&(i<iMAX)); // Convergence
    //  while ((fabs(dx) > xacc)&&(i<iMAX)&&(f!=0.0)); //Convergence
      while ( fabs(dx) > xacc && i<iMAX &&
              f!=0.0 && (f-fl)!=0.0 ); // Convergence
     // printf("rtsec2 i= %d \n",i);
  }
  
  return rts;
}


double rtsec1(callfunc func, double cVar2,double fr,double x1,
           double x2, double fl,double f, double xacc,int iMAX)
// rtsec1: (*func)(x, cVar2) solves for the first parameter: x, x={x1, x2}
// Second parameter cVar2 remains unchanged during iteration
// fr: Input result of (*func)(x, cVar2)
// fl: fr - (*func)(x1, cVar2)
// f: fr - (*func)(x2, cVar2)
// rts: Returns the solution for x
{
  double xl,rts,swap,dx;
  // pick the bound with the smaller function value as the most recent guess
  if (fabs(fl) < fabs(f)) { 
      rts=x1;
      xl=x2;
      swap=fl;
      fl=f;
      f=swap;
  }  else {
      xl=x1;
      rts=x2;
  }
  //secant  loop
  int i=0;
  if ((f-fl)!=0.0)
  {
     do
     {
        dx=(xl-rts)*f/(f-fl); // increment with respect to latest value
        xl=rts;
        fl=f;
        rts += dx;
        // TODO: Pass solution bounds as parameters to ensure iteration stays within bounds
        // rts may be out-of-bounds in region X
        if (rts<=0) rts=0.000001;
        //if (rts>100) rts=100;
      
        f=fr-(*func)(rts,cVar2);
        i++;
     
     }
    //  while ((fabs(dx) > xacc)&&(i<iMAX)); // Convergence
     while ((fabs(dx) > xacc)&&(i<iMAX)&&(f!=0.0)&&((f-fl)!=0.0)); //Convergence
    
     //printf("rtsec1 i= %d \n",i);
  
  };
  
  return (rts);
}

#undef EPS