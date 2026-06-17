# SEUIF97

![PyPI](https://img.shields.io/pypi/v/seuif97) [![Downloads](https://static.pepy.tech/badge/seuif97)](https://pepy.tech/project/seuif97) [![Downloads](https://static.pepy.tech/badge/seuif97/month)](https://pepy.tech/project/seuif97)

**Note:** A new **Rust version** offers a major upgrade with **~2× speedup**, **36 properties** (vs 30), and multi-ecosystem package support. See [RustSEUIF97](https://github.com/thermalogic/RustSEUIF97).
 
This is the C implementation of the high-speed IAPWS-IF97 package **SEUIF97**. It is suitable for computation-intensive calculations, such as the simulation of non-stationary processes, on-line process monitoring and optimizations.
 
Through the high-speed library, IAPWS-IF97 results are generated with high accuracy and at speeds significantly faster than the **repeated squaring method** or the standard C library's `math.pow()`

This package supports **12 distinct input state pairs** for calculating **36 thermodynamic, transport, and derived properties** (see [Properties](#properties)), and **thermodynamic process functions**.

## Acceleration Methods

* Shortest Addition Chain Algorithm: Used for the rapid computation of integer powers via optimal multiplication sequences.
* Power Caching Strategy: Precomputes only distinct powers to avoid redundant calculations, directly retrieving them to speed up polynomial evaluation.
* Shared-Power Scaling: By leveraging the mathematical relationship between polynomials and their derivatives, we compute shared power terms only once. Subsequent results are derived through exponent scaling, thereby eliminating redundant calculations and significantly improving computational efficiency.

Please refer to [The acceleration methods](./doc/the_acceleration_methods.md) for more details on the algorithm.

## Performance Comparison

SEUIF97 achieves **2.5-5.6x speedup** over [CoolProp IF97](https://github.com/CoolProp/IF97) in Region 1, 2, and 3.  Benchmarking code and data are available in the [bench_coolprop_if97](./bench_coolprop_if97) directory. 

## The Shared Library

You can build the library using either [make or cmake](./doc/building_the_library.md):

Pre-compiled dynamic link libraries for Windows, Linux and macOS are available in [GitHub Releases](https://github.com/thermalogic/SEUIF97/releases).

Legacy pre-compiled libraries `libseuif97.dll` built with **MinGW-GCC/GCC** are also provided in the [./shared_lib/](./shared_lib/) directory.

* [Windows(x64)](./shared_lib/Windows/x64)
* [Windows(x86)](./shared_lib/Windows/x86)
* [Linux(x64)](./shared_lib/Linux/x64)

## Functions of the SEUIF97 Shared Library

**Water and Steam Properties**

Each function accepts an input pair, an output property ID ([o_id](#properties)). For example: the input pair (p,t): `pt(p,t,o_id)`

The following 12 input pairs are implemented:

* $(p,t), (p,h), (p,s), (p,v)$
* $(t,h),(t,s), (t,v)$
* $(p,x), (t,x),(h,x),(s,x)$
* $(h,s)$

**Thermodynamic Process of Steam Turbine**

- `ishd(pi, ti, pe)`: isentropic enthalpy drop for steam expansion (kJ/kg)
- `ief(pi, ti, pe, te)`: isentropic efficiency for superheated steam expansion (%)

**Function Prototype in C**

```c
// Functions of Properties
double pt(double p, double t, int o_id);
double ph(double p, double h, int o_id);
double ps(double p, double s, int o_id);
double pv(double p, double v, int o_id);

double th(double t, double h, int o_id);
double ts(double t, double s, int o_id);
double tv(double t, double v,  int o_id);

double hs(double h, double s,  int o_id);

double px(double p, double x,  int o_id);
double tx(double t, double x,  int o_id);
double hx(double h, double x,  int o_id);
double sx(double s, double x,  int o_id);

//Functions for Thermodynamic Process of Steam Turbine
double ishd(double pi, double ti, double pe);
double ief(double pi, double ti, double pe, double te);
```

> **Note:** Only linearly related thermodynamic properties are calculable in the wet steam region.

## Using SEUIF97 Library

To use the shared library in your preferred programming language, follow these steps:

1. Place the shared library in the default path of the OS or the programming language. For example: Windows `C:\Windows\System`, Linux `/usr/lib`.
   
2. Add the specific API file for your programming language to the appropriate location.

> **Note:** API paths vary by language. Please refer to the specific [Examples](./demo/) provided for your programming language to locate the correct path and setup instructions.

## Interfaces and Examples

Interfaces and examples are provided in the [/demo/](./demo) directory, supporting a wide range of languages and environments.

* C/C++, Python, C#, Java, Excel VBA, MATLAB, Rust, Fortran, Pascal, Golang, Modelica

You can modify the provided interfaces to match your own API needs.

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
| [Golang](./demo/demo-go)            |  [seuif97.h](./demo/demo-go/seuif97.h)            |
| [Modelica](./demo/demo-modelica)    |  [seuif97.mo](./demo/demo-modelica/demomodelica/seuif97.mo) |

**The Selected Examples**

**Python**

* [T-S Diagram](./demo/demo-python/Diagram_T-S.py)

* [H-S Diagram](./demo/demo-python/Diagram_H-S.py)

* [H-S Diagram of Steam Turbine Expansion](./demo/demo-python/Turbine_H-S.py)

**C++**

* [H-S Diagram of Steam Turbine Expansion](./demo/demo-c/Turbine_H-S.cpp)

## Properties 

| Property                              |    Unit     | Symbol | o_id       |
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
| Isobaric cubic expansion coefficient  |     1/K     |    αv  |         17 |
| Isothermal compressibility            |    1/MPa    |     kT |         18 |
| Partial derivative (∂V/∂T)p           |  m^3/(kg·K) |(∂V/∂T)p|         19 |
| Partial derivative (∂V/∂P)T           | m^3/(kg·MPa)|(∂V/∂P)T|         20 |
| Partial derivative (∂p/∂t)v           |    MPa/K    |(∂p/∂t)v|         21 |
| Isothermal throttling coefficient     | kJ/(kg·MPa) |    δt  |         22 |
| Joule-Thomson coefficient             |    K/MPa    |     μ  |         23 |
| Dynamic viscosity                     |  kg/(m·s)   |     η  |         24 |
| Kinematic viscosity                   |    m²/s    |     ν  |         25 |
| Thermal conductivity                  |   W/(m·K)   |     λ  |         26 |
| Thermal diffusivity                   |   µm²/s   |     a  |         27 |
| Prandtl number                        |             |     Pr |         28 |
| Surface tension                       |     N/m     |     σ  |         29 |

## Publications

* 王培红,贾俊颖,程懋华. 水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型[J]. 动力工程,2001,21(6):1564-1567 [[ pdf ]](./doc/水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型.pdf)

* 芮嘉敏,孙振业,程懋华. 基于最短加法链状态空间树的IAPWS-IF97快速计算方法[J]. 汽轮机技术,2017,59(4):245-247 [[ pdf ]](./doc/基于最短加法链状态空间树的IAPWS-IF97快速计算方法.pdf)

