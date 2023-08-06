/*
Add  SEUIF97 the paths of lib and header file to  the  environment variables of GCC/MinGW-W64  :
    1 Windows: C:/Windows/system/libseuif97.dll
    2 Linux: ./usr/lib/libseuif97.so
    3 ./include/seuif97.h

Build:
Windows with MinGW-W64：
>gcc -o demo.exe demo.c -I./include  -LC:/Windows/system/  -lseuif97

Linux：
$gcc -o demo demo.c  -I./include  -L/usr/lib/ -lseuif97 -lm

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
    double h, s, v;

    h = seupt(p, t, 4);
    s = seupt(p, t, 5);
    v = seupt(p, t, 3);
    printf("(p,t)(%.2f,%.2f) h= %.2f, s= %.4f, v= %.4f\n", p, t, h, s, v);
    return EXIT_SUCCESS;
}
