/*

-------------- Windows ---------------

Dependencies:
------
    1 SEUIF97 for Windows: C:/Windows/system/libseuif97.dll
    2 API for C#: seuif97.cs

Building the C# Application Using SEUIF97：
-------

you may use the C# compiler and set the Platform target of application to the same as the dynamic library to build the C# Application Using SEUIF97

1  C# compiler

you may use the C# compiler in Windows or Install the latest C# compiler

1.1 Using the C# compiler in Windows 
       
    Add the path of C# compiler,for example C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ to the system environment variables #Path# 

1.2 Install and use the latest C# compiler 

    1.2.1 Using #nuget# to install the latest C# compiler (https://github.com/dotnet/roslyn)

        1) mkdir C:\csharp\ for the latest C# compiler,then download #nuget# to the path

        2）In the path C:\csharp\, install the latest release without Visual Studio, run one of the following `nuget` command lines:

           >nuget install Microsoft.Net.Compilers   # Install C# and VB compilers
           >nuget install Microsoft.CodeAnalysis    # Install Language APIs and Services

        then the compiler is installed in the path, for example  C:\csharp\Microsoft.Net.Compilers.2.10.0\tools\

    1.2.2 add the path C:\csharp\Microsoft.Net.Compilers.2.10.0\tools\ to the system environment variables #Path#  

2. Build on x64 libseuif97.dll：

  >csc -out:demo.exe demo_seuif97.cs seuif97.cs /platform:"x64"

3. Run:

  >./demo

------------- Ubuntu -------------------

Dependencies:
------
    1 SEUIF97 for Linux64: /usr/lib/libseuif97.so
    2 API for C#: seuif97.cs

Building the C# Application Using SEUIF97：
-------

1 Install and use the C# compiler under Ubuntu

    1.1 Install Nuget
     
     $sudo apt install nuget
   
    1.1 Install C# compiler 

     $nuget install Microsoft.Net.Compilers   # Install C# and VB compilers
     $nuget install Microsoft.CodeAnalysis    # Install Language APIs and Services

2. Build on x64 libseuif97.so：

  $csc -out:demo demo_seuif97.cs seuif97.cs /platform:"x64"

3. Run:

   $./demo

-----------------------------------------

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
            h = Seuif97.seupt(p, t, 4);
            s = Seuif97.seupt(p, t, 5);
            v = Seuif97.seupt(p, t, 3);
            Console.WriteLine("(p,t) h,s,v {0 :.00} {1:.0} {2:.000} {3:.000} {4:.000}", p, t, h, s, v);

            t = Seuif97.seuph(p, h, 1);
            s = Seuif97.seuph(p, h, 5);
            v = Seuif97.seuph(p, h, 3);
            Console.WriteLine("(p,h) t,s,v {0 :.00} {1:.0} {2:.000} {3:.000} {4:.000}", p, h, t, s, v);
        }
    }
}
