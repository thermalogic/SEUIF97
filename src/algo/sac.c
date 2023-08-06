/*
   the shortest addition chains [-58,58]
*/
#include <math.h>
#include "algorithm.h"

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
	case 3:
		x2 = x * x;
		return (x2 * x);
	case 4:
		x2 = x * x;
		return (x2 * x2);
	case 5:
		x2 = x * x;
		x3 = x2 * x;
		return (x3 * x2);
	case 6:
		x2 = x * x;
		x3 = x2 * x;
		return (x3 * x3);
	case 7:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		return (x5 * x2);
	case 8:
		x2 = x * x;
		x4 = x2 * x2;
		return (x4 * x4);
	case 9:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		return (x * x8);
	case 10:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		return (x5 * x5);
	case 11:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		return (x5 * x5 * x);
	case 12:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		return (x6 * x6);
	case 13:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		return (x8 * x4 * x);
	case 14:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x7 = x5 * x2;
		return (x7 * x7);
	case 15:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		return (x6 * x6 * x3);
	case 16:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		return (x8 * x8);
	case 17:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		return (x8 * x9);
	case 18:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		return (x8 * x8 * x2);
	case 19:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x18 = x8 * x8 * x2;
		return (x18 * x);
	case 20:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x10 = x5 * x5;
		return (x10 * x10);
	case 21:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		return (x12 * x6 * x3);
	case 22:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x10 = x5 * x5;
		x11 = x10 * x;
		return (x11 * x11);
	case 23:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x10 = x5 * x5;
		return (x10 * x10 * x3);
	case 24:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		return (x12 * x12);
	case 25:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		return (x17 * x8);
	case 26:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x13 = x9 * x4;
		return (x13 * x13);
	case 27:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		return (x12 * x12 * x3);
	case 28:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x7 = x5 * x2;
		x14 = x7 * x7;
		return (x14 * x14);
	case 29:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		return (x17 * x8 * x4);
	case 30:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x15 = x12 * x3;
		return (x15 * x15);
	case 31:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x7 = x5 * x2;
		x14 = x7 * x7;
		return (x14 * x14 * x3);
	case 32:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		return (x16 * x16);
	case 33:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		return (x16 * x16 * x);
	case 34:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		return (x17 * x17);
	case 35:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x13 = x4 * x9;
		return (x13 * x13 * x9);
	case 36:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x18 = x8 * x8 * x2;
		return (x18 * x18);
	case 37:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x18 = x8 * x8 * x2;
		return (x18 * x18 * x);
	case 38:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		x18 = x16 * x2;
		x19 = x18 * x;
		return (x19 * x19);
	case 39:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x24 = x12 * x12;
		return (x24 * x12 * x3);
	case 40:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x10 = x5 * x5;
		x20 = x10 * x10;
		return (x20 * x20);
	case 41:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x3 * x2;
		x10 = x5 * x5;
		x20 = x10 * x10;
		return (x20 * x20 * x);
	case 42:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x21 = x12 * x3 * x6;
		return (x21 * x21);
	case 43:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		return (x17 * x17 * x9);
	case 44:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x2 * x3;
		x11 = x5 * x5 * x;
		x22 = x11 * x11;
		return (x22 * x22);
	case 45:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x15 = x12 * x3;
		return (x15 * x15 * x15);
	case 46:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x2 * x3;
		x10 = x5 * x5;
		x20 = x10 * x10;
		x23 = x20 * x3;
		return x23 * x23;

	case 47:
		x2 = x * x;
		x3 = x2 * x;
		x5 = x2 * x3;
		x10 = x5 * x5;
		x20 = x10 * x10;
		x23 = x20 * x3;
		x46 = x23 * x23;
		return x46 * x;

	case 48:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x24 = x12 * x12;
		return x24 * x24;
	case 49:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		x32 = x16 * x16;
		x33 = x32 * x;
		return x33 * x16;
	case 50:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		x25 = x17 * x8;
		return x25 * x25;

	case 51:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x24 = x12 * x12;
		x48 = x24 * x24;
		return x48 * x3;

	case 52:
		x2 = x * x;
		x4 = x2 * x2;
		x5 = x4 * x;
		x8 = x4 * x4;
		x13 = x8 * x5;
		x26 = x13 * x13;
		return x26 * x26;

	case 53:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		x18 = x16 * x2;
		x36 = x18 * x18;
		x37 = x36 * x;
		return x37 * x16;

	case 54:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x24 = x12 * x12;
		x27 = x24 * x3;
		return x27 * x27;

	case 55:
		x2 = x * x;
		x3 = x2 * x;
		x6 = x3 * x3;
		x12 = x6 * x6;
		x24 = x12 * x12;
		x27 = x24 * x3;
		x54 = x27 * x27;
		return x54 * x;

	case 56:
		x2 = x * x;
		x3 = x2 * x;
		x4 = x2 * x2;
		x7 = x4 * x3;
		x14 = x7 * x7;
		x28 = x14 * x14;
		return x28 * x28;

	case 57:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x16 = x8 * x8;
		x32 = x16 * x16;
		x33 = x32 * x;
		x49 = x33 * x16;
		return x49 * x8;

	case 58:
		x2 = x * x;
		x4 = x2 * x2;
		x8 = x4 * x4;
		x9 = x8 * x;
		x17 = x8 * x9;
		x25 = x17 * x8;
		x29 = x25 * x4;
		return x29 * x29;

	default:
		return ipowrqm(x, n);
	}
}

double ipowsac(double x, int n)
{
	if (n >= 0)
	{
		return possac(x, n);
	}
	else
	{
		return 1.0 / possac(x, -n);
	}
}
