# SEUIF97

 The high-speed shared library is provided for developers to calculate the properties of water and steam where the direct IAPWS-IF97 implementation may be unsuitable because of their computing time consumption, such as Computational Fluid Dynamics (CFD), heat cycle calculations, simulations of non-stationary processes, and real-time process optimizations. 
 
Through the high-speed library, the results of the IAPWS-IF97 are accurately produced at about 3 times computational speed than the repeated squaring method for fast computation of large positive integer powers.
 
The library is written in ANSI C for faster, smaller binaries and better compatibility for accessing the DLL/SO from different C++ compilers.
 
For Windows and Linux users, the convenient binary library and APIs are provided.
 
* The shared library: Windows(32/64): `libseuif97.dll`; Linux(64): `libseuif97.so`

* The binding API: Python, C/C++, Java,Microsoft Excel VBA
       
**Publications:**

* 王培红,贾俊颖,程懋华. 水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型[J]. 动力工程,2001,21(6)：1564-1567 [[ pdf ]](./doc/水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型.pdf)

* 芮嘉敏,孙振业,程懋华. 基于最短加法链状态空间树的IAPWS-IF97快速计算方法[J]. 汽轮机技术,2017,59(4):245-247 [[ pdf ]](./doc/基于最短加法链状态空间树的IAPWS-IF97快速计算方法.pdf)
 
**Author:** Cheng Maohua, Southeast University, Nanjing，China  (cmh@seu.edu.cn)

## The Functions of the SEUIF97 Shared Library

### The Functions for Properties

Using SEUIF97, you can set the state of steam using various pairs of know properties to get any output properties you wish to know, including in the [30 properties in libseuif97](#properties-in-libseuif97).

The following input pairs are implemented: 

```c
(p,t) 
(p,h) 
(p,s) 
(p,v)

(t,h) 
(t,s) 
(t,v) 

(h,s) 

(p,x) 
(t,x) 
```

### Functions for Thermodynamic Process of Steam Turbine
   
*  1 Isentropic Enthalpy Drop： ishd(pi,ti,pe)

       pi - double,inlet pressure; ti - double,inlet temperature
       pe - double,outlet pressure

* 2 Isentropic Efficiency： ief(pi,ti,pe,te)

       pi - double，inlet pressure   ti  - double,inlet temperature
       pe - double，outlet pressure; te  - double, outlet temperature

### [API](./api)

* Python API: [seuif97.py](./api/seuif97.py) 

* C API: [seuif97.h](./api/seuif97.h)  

* Java API: [SEUIF97.java](./api/SEUIF97.java)  

* Microsoft Excel VBA API:  [SEUIF97.xlam](./ExcelVBA/SEUIF97.xlam)

## Install SEUIF97 Library

 Download the repository,then install the library and APIs manually.

 For Python, you may conveniently use **pip** to install from [The Python Package Index](https://pypi.org/project/seuif97/) ![Downloads](https://pepy.tech/badge/seuif97)

### 1 Using `pip` to Install(Windows64,Linux64)

#### Windows64

```bash
>python -m pip install seuif97
```
#### Linux64

```bash
$sudo -H python3 -m pip install seuif97
```
### 2 Install Manually

Download **SEUIF97.zip** of the repository

![Download SEUIF97.zip](./doc/downloadseuif97.jpg)

 Then unzip and install the shared library and APIs manually

 #### Windows32/64 
  
1. copy **libseuif97.dll**  to a default path of Windows dll
      
       C:\Windows\system
   
2. copy **seuif97.py** to a default path of Python lib. If you have installed Python3.7 in the C:\Python37\, copy to
    
       C:\Python37\Lib 

####  Linux64 
    
 1. copy **libseuif97.so**  to a default path of Linux shared lib
   
        $sudo cp libseuif97.so /usr/lib/

 2. copy **seuif97.py** to a default path of Python lib, if you have installed Python3.6(Ubuntu 18.04) 
   
        $sudo cp seuif97.py /usr/lib/python3.6/

## [Demo Python](./demo-python)

```python
import seuif97

p=16.10
t=535.10

h=seuif97.pt2h(p,t)
```

In Python, using syntax like `h = seuif97.pt2h(p,t)`

### T-s Diagram:

 * [Diagram_T-S.py](./demo-python/Diagram_T-S.py)

 ![T-s Diagram](./doc/T-s.jpg)

## [ExcelVBA32/64](./ExcelVBA)

* Excel Add-in Macro: SEUIF97.xlam

* Excel VBA Demo:  DEMO_SEUIF97.xlsm

* Guide: [SEUIF97-Excel-VBA-Add-in-Macro(Chinese).pdf](./ExcelVBA/SEUIF97-Excel-VBA-Add-in-Macro(Chinese).pdf)

## [Demo Java](./demo-java)

```java
/*
   access to the shared libraries through JNA   
   https://github.com/java-native-access/jna
*/
import com.sun.jna.Library;  
import com.sun.jna.Native;  
  
public interface SEUIF97 extends Library{  

    SEUIF97 instance  = (SEUIF97)Native.loadLibrary("libseuif97",SEUIF97.class);    
    public double  seupt(double p, double t,int w);  
}   
```

## [Demo C/C++ Using GCC](./demo-gcc)  

```c
/*
For Windows:
>gcc -o demo.exe demo.c -LC:/Windows/system/ -lseuif97

For Linux
$gcc -o demo demo.c -L/usr/lib/ -lseuif97 -lm

Run:
./demo

*/

#include <stdio.h>
#include <stdlib.h>

#include "seuif97.h"

int main(void) {

    double p=16.13;
    double t=535;
    double h;

    h=seupt(p,t,4);
    printf("(p,t) (%f,%f) h= %f",p,t,h);
    return EXIT_SUCCESS;
}
```

In C/C++, using syntax like `h =  seupt(p, t, 4)`

* first,second input parameters: the input properties(double)
* third input parameter: the propertyID of the calculated property(int, 0-29), see [Properties in libseuif97](#properties-in-libseuif97)
* the return: the calculated property value(double)

### The Functions for Properties in C 

```cpp
double seupt(double pressure, double temperature, int propertyID)
double seuph(double pressure, double enthalpy,    int  propertyID)
double seups(double pressure, double entropy,     int  propertyID)
double seupv(double pressure, double volume,      int  propertyID)

double seuth(double temperature, double enthalpy,  int  propertyID)
double seuts(double temperature, double entropy,   int  propertyID)
double seutv(double temperature, double volume,    int  propertyID)

double seuhs(double enthalpy,    double entropy,   int propertyID)

double seupx(double pressure,    double quality,   int  propertyID)
double seutx(double temperature, double quality,   int  propertyID)
```

## Properties in libseuif97

|   Properties |    Unit     |  symbol  |  propertyID   |   
| ----------------|:----------:| ------:|-------:|
| Pressure        |   MPa     |  P     |   0     |  
| Temperature     |   °C      |  t     |   1     |
| Density         | kg/m^3    |  d     |   2     |
| Specific Volume | m^3/kg    |  v     |   3     |
| Specific enthalpy  | kJ/kg     |  h     |   4     |
| Specific entropy   | kJ/(kg·K) |  s     |   5     |
| Specific  exergy   | kJ/kg     |  e     |   6     |
| Specific internal energy   | kJ/kg     |  u     |   7     |
| Specific isobaric heat capacity  | kJ/(kg·K) |  cp    |   8     |
| Specific isochoric heat capacity  | kJ/(kg·K) |  cv    |   9     |		
| Speed of sound          | m/s       |   w     | 10      |	
| Isentropic exponent     |             |  ks     | 11      |	
| Specific Helmholtz free energy   |   kJ/kg          |  f     | 12      |	
| Specific Gibbs free energy       |   kJ/kg           | g     | 13      |	
| Compressibility factor           |                      | z      | 14      |
| Steam quality                    |                      | x      | 15      |
| Region                           |                      | r       | 16      |
| Isobaric volume expansion coefficient  |        1/K       | ec     | 17      |
| Isothermal compressibility             |        1/MPa   | kt     | 18      |
| Partial derivative (dV/dT)p            |    m3/(kg·K)	     | dvdt     | 19      |
| Partial derivative (dV/dP)T            |    m3/(kg·MPa)	  | dvdp    | 20      |
| Partial derivative (dP/dT)v            |    MPa/K	         | dpdt	    | 21      |
| Isothermal Joule-Thomson coefficient   |   kJ/(kg·MPa)        | iJTC	    | 22      |
| Joule-Thomson coefficient              |  K/MPa        | JTC	    | 23      |
| Dynamic viscosity                      |        kg/(m·s)   | dv     | 24      |
| Kinematic viscosity                    |       m^2/s       | kv     | 25      |
| Thermal conductivity                   |       W/(m.K)	  | tc     | 26      |
| Thermal diffusivity                    |       um^2/s	 | td     | 27      |
| Prandtl number                         |            	  | pr     | 28      |
| Surface tension                        |       mN/m    	  | st     | 29      |
