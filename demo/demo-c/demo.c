/*
Add  SEUIF97 the paths of lib and header file to  the  environment variables of GCC/MinGW-W64  :
    1 Windows: C:/Windows/system/libseuif97.dll
    2 Linux: ./usr/lib/libseuif97.so
    3 ./include/seuif97.h

Build:
Windows with MinGW-W64：
   gcc -o demo.exe demo.c -I./include  -LC:/Windows/system/  -lseuif97

Linux：
   gcc -o demo demo.c  -I./include  -L/usr/lib/ -lseuif97 -lm

Run:
./demo

Windows  MSVC: seuif97.dll
   cl /Fedemo.exe /Fo./obj/demo.obj demo.c -I./include/  ./lib/seuif97.lib

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

    h = pt(p, t, 4);
    s = pt(p, t, 5);
    v = pt(p, t, 3);
    printf("(p,t)(%.2f,%.2f) h= %.2f, s= %.4f, v= %.4f\n", p, t, h, s, v);
    return EXIT_SUCCESS;
}
