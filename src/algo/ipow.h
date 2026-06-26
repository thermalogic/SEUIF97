
/**
 * @file ipow.h
 * @brief Integer Power functions for IAPWS-IF97
 * 
 * This file implements integer power functions for IAPWS-IF97
 * Note: __builtin_powi and custom ipow have equivalent performance.
 * 
 * @author Cheng Maohua
 * @email cmh@seu.edu.cn
 */
 
#pragma once

#define IPOW ipowsac
// #define IPOW ipowrqm
// #define IPOW powf
// #define IPOW __builtin_powi //GCC/Clang

static inline double ipowrqm(double x, int i)
{
        double ans = 1.0;
        if (i < 0) {
            x = 1.0 / x;
            i = -i;
        }
        for (; i > 0; i >>= 1) {
            if (i & 1) ans *= x;
            x *= x;
        }
        return ans;
}

#define SAC5(x, x2, x3, x5) (x2 = (x) * (x), x3 = x2 * (x), x5 = x3 * x2)
#define SAC6(x, x2, x3, x6) (x2 = (x) * (x), x3 = x2 * (x), x6 = x3 * x3)
#define SAC8(x, x2, x4, x8) (x2 = (x) * (x), x4 = x2 * x2, x8 = x4 * x4)
#define SAC9(x, x2, x4, x8, x9) (x2 = (x) * (x), x4 = x2 * x2, x8 = x4 * x4, x9 = x8 * (x))
#define SAC10(x, x2, x3, x5, x10) (x2 = (x) * (x), x3 = x2 * (x), x5 = x3 * x2, x10 = x5 * x5)
#define SAC12(x, x2, x3, x6, x12) (x2 = (x) * (x), x3 = x2 * (x), x6 = x3 * x3, x12 = x6 * x6)
#define SAC16(x, x2, x4, x8, x16) (x2 = (x) * (x), x4 = x2 * x2, x8 = x4 * x4, x16 = x8 * x8)
#define SAC18(x, x2, x4, x8, x18) (x2 = (x) * (x), x4 = x2 * x2, x8 = x4 * x4, x18 = x8 * x8 * x2)
#define SAC17(x, x2, x4, x8, x9, x17) (x2 = (x) * (x), x4 = x2 * x2, x8 = x4 * x4, x9 = x8 * (x), x17 = x8 * x9)
#define SAC20(x, x2, x3, x5, x10, x20) (x2 = (x) * (x), x3 = x2 * (x), x5 = x3 * x2, x10 = x5 * x5, x20 = x10 * x10)
#define SAC24(x, x2, x3, x6, x12, x24) (x2 = (x) * (x), x3 = x2 * (x), x6 = x3 * x3, x12 = x6 * x6, x24 = x12 * x12)

static inline double possac(double x, int n)
{
	// the shortest addition chains, [0,58]
	double x2, x3, x4, x5, x6, x7, x8, x9;
	double x10, x12, x13, x14, x15, x16, x17, x18, x19;
	double x20, x21, x22, x23, x24, x25, x26, x27, x28, x29;
	double x32, x33, x36, x37, x46, x48, x49, x54;

	switch (n)
	{
	case 0:
		return (1.0);
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
	    SAC5(x, x2, x3, x5);
	  	return (x5);
	case 6:
	    SAC6(x, x2, x3, x6);
		return (x6);
	case 7:
        SAC5(x, x2, x3, x5);
	    return (x5 * x2);
	case 8:
		SAC8(x, x2, x4, x8);
		return (x8);
	case 9:
		SAC8(x, x2, x4, x8);
		return (x * x8);
	case 10:
        SAC5(x, x2, x3, x5);
    	return (x5 * x5);
	case 11:
	    SAC10(x, x2, x3, x5,x10);
		return (x10 * x);
	case 12:
	    SAC6(x, x2, x3, x6);
		return (x6 * x6);
	case 13:
		SAC8(x, x2, x4, x8);
		return (x8 * x4 * x);
	case 14:
	    SAC5(x, x2, x3, x5);
		x7 = x5 * x2;
		return (x7 * x7);
	case 15:
	    SAC6(x, x2, x3, x6);
		return (x6 * x6 * x3);
	case 16:
	    SAC8(x, x2, x4, x8);
		return (x8 * x8);
	case 17:
	    SAC9(x, x2, x4, x8,x9);
	    return (x8 * x9);
	case 18:
		SAC8(x, x2, x4, x8);
		return (x8 * x8 * x2);
	case 19:
		SAC18(x, x2, x4, x8,x18);
		return (x18 * x);
	case 20:
	    SAC10(x, x2, x3, x5,x10);
		return (x10 * x10);
	case 21:
	    SAC12(x, x2, x3, x6,x12);
		return (x12 * x6 * x3);
	case 22:
	    SAC20(x, x2, x3, x5,x10, x20);
		return (x20 * x2);
	case 23:
	    SAC20(x, x2, x3, x5,x10, x20);
		return (x20 * x3);
	case 24:
	    SAC12(x, x2, x3, x6,x12);
		return (x12 * x12);
	case 25:
	    SAC17(x, x2, x4, x8,x9,x17);
		return (x17 * x8);
	case 26:
	    SAC9(x, x2, x4, x8,x9);
  		x13 = x9 * x4;
		return (x13 * x13);
	case 27:
	    SAC12(x, x2, x3, x6,x12);
		return (x12 * x12 * x3);
	case 28:
	    SAC5(x, x2, x3, x5);
		x7 = x5 * x2;
		x14 = x7 * x7;
		return (x14 * x14);
	case 29:
		SAC17(x, x2, x4, x8,x9,x17);
		return (x17 * x8 * x4);
	case 30:
	    SAC12(x, x2, x3, x6,x12);
		x15 = x12 * x3;
		return (x15 * x15);
	case 31:
	    SAC5(x, x2, x3, x5);
		x7 = x5 * x2;
		x14 = x7 * x7;
		return (x14 * x14 * x3);
	case 32:
		SAC16(x, x2, x4, x8,x16);
		return (x16 * x16);
	case 33:
		SAC16(x, x2, x4, x8,x16);
		return (x16 * x16 * x);
	case 34:
		SAC17(x, x2, x4, x8,x9,x17);
		return (x17 * x17);
	case 35:
		SAC9(x, x2, x4, x8,x9);
    	x13 = x4 * x9;
		return (x13 * x13 * x9);
	case 36:
		SAC18(x, x2, x4, x8,x18);
		return (x18 * x18);
	case 37:
		SAC18(x, x2, x4, x8,x18);
		return (x18 * x18 * x);
	case 38:
		SAC18(x, x2, x4, x8,x18);
		x19 = x18 * x;
		return (x19 * x19);
	case 39:
	  	SAC24(x, x2, x3, x6, x12, x24); 
		return (x24 * x12 * x3);
	case 40:
	    SAC20(x, x2, x3, x5,x10,x20);
		return (x20 * x20);
	case 41:
	    SAC20(x, x2, x3, x5,x10,x20);
		return (x20 * x20 * x);
	case 42:
	    SAC12(x, x2, x3, x6,x12);
		x21 = x12 * x3 * x6;
		return (x21 * x21);
	case 43:
		SAC17(x, x2, x4, x8,x9,x17);
		return (x17 * x17 * x9);
	case 44:
	    SAC10(x, x2, x3, x5,x10);
		x22 = x10 * x10 *x2;
		return (x22 * x22);
	case 45:
	    SAC12(x, x2, x3, x6,x12);
		x15 = x12 * x3;
		return (x15 * x15 * x15);
	case 46:
	    SAC20(x, x2, x3, x5,x10,x20);
		x23 = x20 * x3;
		return x23 * x23;
	case 47:
	   SAC20(x, x2, x3, x5,x10,x20);
		x23 = x20 * x3;
		x46 = x23 * x23;
		return x46 * x;
	case 48:
 	 	SAC24(x, x2, x3, x6, x12, x24); 
		return x24 * x24;
	case 49:
		SAC16(x, x2, x4, x8,x16);
		x32 = x16 * x16;
		x33 = x32 * x;
		return x33 * x16;
	case 50:
		SAC17(x, x2, x4, x8,x9,x17);
		x25 = x17 * x8;
		return x25 * x25;
	case 51:
 	 	SAC24(x, x2, x3, x6, x12, x24); 
		x48 = x24 * x24;
		return x48 * x3;
	case 52:
	    SAC5(x, x2, x3, x5);
		x8 = x5 * x3;
		x13 = x8 * x5;
		x26 = x13 * x13;
		return x26 * x26;
	case 53:
		SAC16(x, x2, x4, x8,x16);
		x18 = x16 * x2;
		x36 = x18 * x18;
		x37 = x36 * x;
		return x37 * x16;
	case 54:
 	 	SAC24(x, x2, x3, x6, x12, x24); 
		x27 = x24 * x3;
		return x27 * x27;
	case 55:
 	 	SAC24(x, x2, x3, x6, x12, x24); 
		x27 = x24 * x3;
		x54 = x27 * x27;
		return x54 * x;
	case 56:
	    SAC5(x, x2, x3, x5);
		x7 = x5 * x2;
		x14 = x7 * x7;
		x28 = x14 * x14;
		return x28 * x28;
	case 57:
		SAC16(x, x2, x4, x8,x16);
		x32 = x16 * x16;
		x33 = x32 * x;
		x49 = x33 * x16;
		return x49 * x8;
    case 58:
		SAC17(x, x2, x4, x8,x9,x17);
		x25 = x17 * x8;
		x29 = x25 * x4;
		return x29 * x29;
	default:
		return ipowrqm(x, n);
	}
}

static inline double ipowsac(double x, int n)
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