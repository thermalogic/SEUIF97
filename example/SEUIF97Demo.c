/*
* Name        : SEUIF97Demo.c
* Author      : Cheng Maohua
*/

#include <stdio.h>
#include <stdlib.h>

#include "seuif97.h"

int main(void)
{

    double p = 16.13;
    double t = 535;
    double h;

    h = seupt(p, t, 4);
    printf("(p,t) (%f,%f) h= %f", p, t, h);
    return EXIT_SUCCESS;
}
