/*

SEUIF97 Library with MSVC:
    1 C:/Windows/system/libseuif97.dll
    2 ./include/seuif97.h
    3 ./lib/libseuif97.lib (the lib:x64)

Build: MSVC：
>cl /Fedemo.exe /Fo./obj/demo.obj demo.c -I./include/  ./lib/libseuif97.lib

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
