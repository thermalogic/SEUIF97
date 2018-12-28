/*

For Windows:
>gcc -o demo.exe demo.c -LC:/Windows/system/ -lseuif97

For Linux
$gcc -o demo demo.c -L/usr/lib/ -lseuif97 -lm

Run:
./demo

Author: Cheng Maohua
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
    printf("(p,t) (%f,%f) h= %f \n", p, t, h);
    return EXIT_SUCCESS;
}
