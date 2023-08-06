/*
 ipow:  public domain by Mark Stephen with suggestions by Keiichi Nakasato 
  repeated squaring method 
	  
	  https://en.wikipedia.org/wiki/Exponentiation_by_squaring
      
	   returns 0.0^0 = 0.0
*/

#include "algorithm.h"

double posipowrqm(double x, unsigned int n)
{
	double value = 1.0;
	if (!n)
        return 1.0; /* x^0 = 1 */

	if (x == 0.0)
        return 0.0;
		
	do
	{
		if (n & 1)
			value *= x; /* for n odd */
		n >>= 1;
		x *= x;
	} while (n);

	return value;
}

double ipowrqm(double x, int n)
{
	unsigned int un;
	if (n < 0)
	{
		x = 1.0 / x;
		un = -n;
	}
	else
	{
		un = n;
	}

	return posipowrqm(x, un);
}

