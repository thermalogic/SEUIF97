/*
 ============================================================================
 Name        : SEUIF97Demo.c
 Author      : Cheng Maohua
 Version     :
 Copyright   : Cheng Maohua
 Description : Hello World in C, Ansi-style

  The MinGW toolchain is perfectly happy to directly link against the created DLL.

  It is worth mentioning that the same executable may be built without

  an import library using the following command:

g++ -o SEUIF97Demo.exe SEUIF97Demo.o libSEUIF97.dll

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "seuif97.h"

int main(void) {

		double p=16.13;
		double t=535;
		double h;

	   h=seupt(p,t,4);
	   printf("%f",h);
	   return EXIT_SUCCESS;
}
