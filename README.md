# SEUIF97

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.8242452.svg)](https://doi.org/10.5281/zenodo.8242452)

This is the C implementation of the high-speed IAPWS-IF97 package **seuif97**. It is suitable for computation-intensive calculations，such as heat cycle calculations, simulations of non-stationary processes, real-time process monitoring and optimizations.   
 
Through the high-speed library, the results of the IAPWS-IF97 are accurately produced several times faster than repeated squaring method and `math.pow()` of the C standard library.   

**The Fast Methods**

* the shortest addition chain algorithm computes the integer power of a number quickly
* apply Horner's rule to compute a set of powers and avoid calculate the power of same exponential once again
* the recursive method computes the value of multiple polynomials to avoid calculate the same item once again

In addition to the source code, the repository provides 

* the compiled shared libraries using GCC: [/shared_lib/](./shared_lib/)

* the interfaces and examples of multiple programming languages:  [/demo/](./demo)

   *  C/C++, Python, C#, Java, Excel VBA, MATLAB, Fortran, Rust, Pascal, Modelica 

## Building the shared library

* make

```bash
make
```

* cmake

```bash
cmake -B ./build/   
cmake --build ./build/ --config Release
```

**The compiled shared libraries  using GCC**

* [Windows(x86/64)](./shared_lib/Windows): `libseuif97.dll` 

* [Linux(x64)](./shared_lib/Linux): `libseuif97.so`

## Functions of the SEUIF97 Shared Library

Functions of water and steam propertiesand the thermodynamic process of steam turbine are provided in the **SEUIF97**

**Water and Steam Properties**

Using the SEUIF97, you can set the state of steam using various pairs of know properties to get any output properties you wish to know, including in the [30 properties in libseuif97](#properties-in-libseuif97).

The following 12 input pairs are implemented: 

```
(p,t) (p,h) (p,s) (p,v) 

(t,h) (t,s) (t,v) 

(p,x) (t,x) (h,x) (s,x) 

(h,s)  
```

The type of propertry functions are provided in the package

```c 
  ??(in1,in2,o_id)
```

* the first,second input parameters : the input propertry pairs
* the third input parametes: the property ID of the calculated property - [o_id](#properties)
* the return: the calculated property value of `o_id`

**Thermodynamic Process of Steam Turbine**
   
* Isentropic Enthalpy Drop：seuishd(pi,ti,pe)

  ```txt
    pi - double, inlet pressure(MPa); ti - double, inlet temperature(°C)
    pe - double, outlet pressure(MPa)
  ```
*  Isentropic Efficiency(0~100)： seuief(pi,ti,pe,te) (superheated steam zone)
   ```txt
       pi - double, inlet pressure(MPa);  ti - double, inlet temperature(°C)
       pe - double, outlet pressure(MPa); te - double, outlet temperature(°C)
   ```

**The Function Prototype in C**

```c
// Functions of Properties
double seupt(double p, double t, int o_id);
double seuph(double p, double h, int o_id);
double seups(double p, double s, int o_id);
double seupv(double p, double v, int o_id);

double seuth(double t, double h, int o_id);
double seuts(double t, double s, int o_id);
double seutv(double t, double v,  int o_id);

double seuhs(double h, double s,  int o_id);

double seupx(double p, double x,  int o_id);
double seutx(double t, double x,  int o_id);
double seuhx(double h, double x,  int o_id);
double seusx(double s, double x,  int o_id);

//The Functions for Thermodynamic Process of Steam Turbine
double seuishd(double pi, double ti, double pe);
double seuief(double pi, double ti, double pe, double te);
```

## Install SEUIF97 

Use the shared library from one programming language, you may

1. Put the shared library in the default `Lib` path of OS or the programming language
   * **Windows(x86/64)** 
     * copy `libseuif97.dll` in the [Windows/x86](./shared_lib/Windows/x86) or [Windows/x64](./shared_lib/Windows/x64) folder to a default path of Windows32/64's DLL:  `C:\Windows\System`
   
   * **Linux(x64)** 
     * copy `libseuif97.so` in the [Linux/x64](./shared_lib/Linux/x64) folder to a default path of Linux shared lib : `/usr/lib`/
   
2. Add the API file of the programming language to its `API` path

   * The API paths of different programming languages are different,please refer to the [Examples](./demo/) of different programming languages

## Interfaces and Examples

* [./demo/](./demo)

|  Language                           |    Interface                                     | 
|:-----------------------------------:|:-------------------------------------------------|
| [C/C++](./demo/demo-c)              |  [seuif97.h](./demo/demo-c/include/seuif97.h)    |
| [Python](./demo/demo-python)        |  [seuif97.py](./demo/demo-python/seuif97.py)     |
| [C#](./demo/demo-csharp)            |  [seuif97.cs](./demo/demo-csharp/seuif97.cs)     |
| [Excel VBA](./demo/ExcelVBA)        |  [seuif97.bas](./demo/ExcelVBA/seuif97.bas)      |
| [Java](./demo/demo-java)            |  [seuif97.java](./demo/demo-java/seuif97.java)   |
| [MATLAB64](./demo/MATLAB64)         |  [seuif97.m](./demo/MATLAB64/seuif97/seuif97.m)  |
| [Rust](./demo/demo-rust)            |  [seuif97.rs](./demo/demo-rust/src/seuif97.rs)   |
| [Fortran](./demo/demo-Fortran)      |  [seuif97.f08](./demo/demo-fortran/seuif97.f08)  |
| [Pascal](./demo/demo-pascal)        |  [seuif97.pas](./demo/demo-pascal/seuif97.pas)   |
| [Modelica](./demo/demo-modelica)    |  [seuif97.mo](./demo/demo-modelica/demomodelica/seuif97.mo) |

You can modify these interfaces provided in the repository to your own APIs.

## Properties 

| Propertry                             |    Unit     | Symbol | o_id       |
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

## Publications

* 王培红,贾俊颖,程懋华. 水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型[J]. 动力工程,2001,21(6)：1564-1567 [[ pdf ]](./doc/水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型.pdf)

* 芮嘉敏,孙振业,程懋华. 基于最短加法链状态空间树的IAPWS-IF97快速计算方法[J]. 汽轮机技术,2017,59(4):245-247 [[ pdf ]](./doc/基于最短加法链状态空间树的IAPWS-IF97快速计算方法.pdf)
 

## Cite as

* Cheng Maohua. (2023). The C implementation of the high-speed IAPWS-IF97 package: SEUIF97 (1.2.0). Zenodo. https://doi.org/10.5281/zenodo.8242452