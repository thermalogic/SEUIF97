/*
SEUIF97 Library:
    1 Windows: C:/Windows/system/libseuif97.dll
    3 seuif97.cs

you should set the Platform target of application  is the same as  the dynamic library  

Build using x64 libseuif97.dll：
>C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc demo_seuif97.cs seuif97.cs /platform:"x64"

 */
using System;

using seuif97;

namespace demo_seuif97
{
    class demo_seuif97
    {

        static void Main(string[] args)
        {
            double p = 16.13;
            double t = 535.0;
            double h, s, v;
            h = seuif97.Seuif97.seupt(p, t, 4);
            s = seuif97.Seuif97.seupt(p, t, 5);
            v = seuif97.Seuif97.seupt(p, t, 3);
            Console.WriteLine("(p,t) h,s,v {0 :.00} {1:.0} {2:.000} {3:.000} {4:.000}", p, t, h, s, v);

            t = seuif97.Seuif97.seuph(p, h, 1);
            s = seuif97.Seuif97.seuph(p, h, 5);
            v = seuif97.Seuif97.seuph(p, h, 3);
            Console.WriteLine("(p,h) t,s,v {0 :.00} {1:.0} {2:.000} {3:.000} {4:.000}", p, h, t, s, v);
        }
    }
}
