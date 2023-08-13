# SEUIF97

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.8233915.svg)](https://doi.org/10.5281/zenodo.8233915)

  The SEUIF97 version is the high-speed shared library of IAPWS-IF97 in C. It is suitable for computation-intensive calculations，such as heat cycle calculations, simulations of non-stationary processes, real-time process monitoring and optimizations.   
 
Through the high-speed library, the results of the IAPWS-IF97 are accurately produced several times faster than repeated squaring method and `math.pow()` of the C standard library.   

In addition to the source code, the repository provides the compiled shared libraries using GCC and the interfaces to multiple programming languages.

*  **The shared libraries**

   * [Windows(x86/64)](./shared_lib/Windows): `libseuif97.dll` 

   * [Linux(x64)](./shared_lib/Linux): `libseuif97.so`

*  **The [API](./api) for the programming languages**

    * Python, C/C++, Excel VBA, C#, Java,MATLAB,Fortran, Rust, Modelica, Pascal

**Publications**

* 王培红,贾俊颖,程懋华. 水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型[J]. 动力工程,2001,21(6)：1564-1567 [[ pdf ]](./doc/水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型.pdf)

* 芮嘉敏,孙振业,程懋华. 基于最短加法链状态空间树的IAPWS-IF97快速计算方法[J]. 汽轮机技术,2017,59(4):245-247 [[ pdf ]](./doc/基于最短加法链状态空间树的IAPWS-IF97快速计算方法.pdf)
 
## Functions of the SEUIF97 Shared Library

Functions of water and steam propertiesand the thermodynamic process of steam turbine are provided in **SEUIF97**

### Water and Steam Properties

Using SEUIF97, you can set the state of steam using various pairs of know properties to get any output properties you wish to know, including in the [30 properties in libseuif97](#properties-in-libseuif97).

The following 12 input pairs are implemented: 

```
(p,t) (p,h) (p,s) (p,v) 

(t,h) (t,s) (t,v) 

(p,x) (t,x) (h,x) (s,x) 

(h,s)  
```

### Thermodynamic Process of Steam Turbine
   
*  1 Isentropic Enthalpy Drop：seuishd(pi,ti,pe)

       pi - double, inlet pressure(MPa); ti - double, inlet temperature(°C)
       pe - double, outlet pressure(MPa)

* 2 Isentropic Efficiency(0~100)： seuief(pi,ti,pe,te) (superheated steam zone)

       pi - double, inlet pressure(MPa);  ti - double, inlet temperature(°C)
       pe - double, outlet pressure(MPa); te - double, outlet temperature(°C)

## The API

* C/C++:  [seuif97.h](./api/seuif97.h) 

* Python: [seuif97.py](./api/seuif97.py) 

* Excel VBA: [seuif97.bas](./demo/ExcelVBA/seuif97.bas)

* C#: [seuif97.cs](./api/seuif97.cs) 

* Java: [seuif97.java](./api/seuif97.java)  

* MATLAB: [seuif97.m](./demo/MATLAB64/seuif97/seuif97.m)

* Rust: [seuif97.rs](./api/seuif97.rs) 

* Fortran: [seuif97.f08](./api/seuif97.f08)  

* Modelica: [seuif97.mo](./api/seuif97.mo) 

* Pascal: [seuif97.pas](./api/seuif97.pas) 

## Install SEUIF97 

Use the shared library from one programming language, you may

1. Put the shared library in the default `Lib` path of OS or the programming language
   * **Windows(x86/64)** 
     * copy `libseuif97.dll` in the [Windows/x86](./shared_lib/Windows/x86) or [Windows/x64](./shared_lib/Windows/x64) folder to a default path of Windows32/64's DLL:  `C:\Windows\System`
   
   * **Linux(x64)** 
     * copy `libseuif97.so` in the [Linux/x64](./shared_lib/Linux/x64) folder to a default path of Linux shared lib : `/usr/lib`/
   
2. Add the API file of the programming language to its `API` path

   * The API paths of different programming languages are different,please refer to the [Examples](./demo/) of different programming languages

## Examples

The examples using the shared library

* [C/C++](./demo/demo-c)  

* [Python](./demo/python)  

* [Excel VBA(32/64)](./demo/ExcelVBA)

* [C#](./demo/demo-csharp)

* [Java](./demo/demo-java)

* [Rust](./demo/demo-rust)

* [MATLAB64](./demo/MATLAB64)

* [Fortran](./demo/demo-Fortran)

* [Modelica](./demo/demo-modelica)

* [Pascal](./demo/demo-pascal)

## The Function Prototypes in C

If you need to modify the APIs provided in the repository or program your own APIs, you can refer to the library's header file: [seuif97.h](./api/seuif97.h). 

```c
// Functions of Properties
double seupt(double p, double t, int propertyID);
double seuph(double p, double h, int propertyID);
double seups(double p, double s, int propertyID);
double seupv(double p, double v, int propertyID);

double seuth(double t, double h, int propertyID);
double seuts(double t, double s, int propertyID);
double seutv(double t, double v,  int propertyID);

double seuhs(double h, double s,  int propertyID);

double seupx(double p, double x,  int propertyID);
double seutx(double t, double x,  int propertyID);
double seuhx(double h, double x,  int propertyID);
double seusx(double s, double x,  int propertyID);

//The Functions for Thermodynamic Process of Steam Turbine
double seuishd(double pi, double ti, double pe);
double seuief(double pi, double ti, double pe, double te);
```

## Properties 

| Propertry                             |    Unit     | Symbol | propertryID |
| ------------------------------------- | :---------: |:-----: |:---------: |
| Pressure                              |     MPa     |      p |          0 |
| Temperature                           |     °C      |      t |          1 |
| Density                               |   kg/m^3    |      ρ |          2 |
| Specific Volume                       |   m^3/kg    |      v |          3 |
| Specific enthalpy                     |    kJ/kg    |      h |          4 |
| Specific entropy                      |  kJ/(kg·K)  |      s |          5 |
| Specific exergy                       |    kJ/kg    |      e |          6 |
| Specific internal energy              |    kJ/kg    |      u |          7 |
| Specific isobaric heat capacity       |  kJ/(kg·K)  |     cp |          8 |
| Specific isochoric heat capacity      |  kJ/(kg·K)  |     cv |          9 |
| Speed of sound                        |     m/s     |      w |         10 |
| Isentropic exponent                   |             |      k |         11 |
| Specific Helmholtz free energy        |    kJ/kg    |      f |         12 |
| Specific Gibbs free energy            |    kJ/kg    |      g |         13 |
| Compressibility factor                |             |      z |         14 |
| Steam quality                         |             |      x |         15 |
| Region                                |             |      r |         16 |
| Isobaric cubic expansion coefficient  |     1/K     |    ɑv  |         17 |
| Isothermal compressibility            |    1/MPa    |     kT |         18 |
| Partial derivative (∂V/∂T)p           |  m3/(kg·K)  |(∂V/∂T)p|         19 |
| Partial derivative (∂V/∂P)T           | m3/(kg·MPa) |(∂V/∂P)T|         20 |
| Partial derivative (∂p/∂t)v           |    MPa/K    |(∂p/∂t)v|         21 |
| Isothermal throttling coefficient     | kJ/(kg·MPa) |    δt  |         22 |
| Joule-Thomson coefficient             |    K/MPa    |     μ  |         23 |
| Dynamic viscosity                     |  kg/(m·s)   |     η  |         24 |
| Kinematic viscosity                   |    m^2/s    |     ν  |         25 |
| Thermal conductivity                  |   W/(m.K)   |     λ  |         26 |
| Thermal diffusivity                   |   um^2/s    |     a  |         27 |
| Prandtl number                        |             |     Pr |         28 |
| Surface tension                       |    mN/m     |     σ  |         29 |

## Cite as

* Cheng Maohua. (2023). The high-speed IAPWS-IF97 C implementation of SEUIF97. Zenodo. https://doi.org/10.5281/zenodo.8233915