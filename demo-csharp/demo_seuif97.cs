/*
SEUIF97 Library:
    1 Windows: C:/Windows/system/libseuif97.dll
    2 seuif97.cs

you should set the Platform target of application is the same as  the dynamic library  

1)Build with C#5 compiler on x64 libseuif97.dll：

  >C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc demo_seuif97.cs seuif97.cs /platform:"x64"

2)Build with the latest compiler on x64 libseuif97.dll：

  2.1 Using nuget to install the latest version of  C# compiler (https://github.com/dotnet/roslyn)

    2.1.1 mkdir C:\cs harp\ for the latest version of  C# compiler,then download nuget to the path

    2.1.2 In the path C:\csharp\, Install the latest release without Visual Studio, run one of the following `nuget` command lines:

      >nuget install Microsoft.Net.Compilers   # Install C# and VB compilers
      >nuget install Microsoft.CodeAnalysis    # Install Language APIs and Services

      then the  compiler is installed in the path  C:\csharp\Microsoft.Net.Compilers.2.10.0\tools\

   2,2 Build:
     
     >C:\csharp\Microsoft.Net.Compilers.2.10.0\tools\csc demo_seuif97.cs seuif97.cs /platform:"x64"

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2019.01.05

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
