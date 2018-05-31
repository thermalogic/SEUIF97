# SEUIF97

**Purpose:** Provide a high-speed shared library for developers to calculate the properties of water and steam  in extensive process simulations, such as Computational Fluid Dynamics (CFD), heat cycle calculations, simulations of non-stationary processes, and real-time process optimizations, where the direct IAPWS-IF97 implementation may be unsuitable because of their computing time consumption.
 
 Through the high-speed library, the results of the IAPWS-IF97  are accurately produced at above 3 times computational speed.
 
Algorithm of the High-speed IAPWS-IF97 Library: 

* 王培红,贾俊颖,程懋华. 水和水蒸汽热力性质IAPWS-IF97公式的通用计算模型[J]. 动力工程,2001,21(6)：1564-1567

* 芮嘉敏,孙振业,程懋华. 基于最短加法链状态空间树的IAPWS-IF97快速计算方法[J]. 汽轮机技术,2017,59(4):245-247 

 This library is written in ANSI C for faster, smaller binaries and better compatibility for accessing the DLL/SO from different C++ compilers.
 
For Windows and Linux users, convenient binary packages are provided.
 
* IF97 shared library: Windows(32/64):libseuif97.dll, Linux(64):libseuif97.so
 
The package includes bindings for Python, Microsoft Excel, Java 
        
* Python API：seuif97.py
        
* Microsoft Excel Macro: DEMO_SEUIF97.xlsm,SEUIF97.xlam

* Java API: SEUIF97.java
 
**Author:** Cheng Maohua, Southeast University, Nanjing，China  (cmh@seu.edu.cn)

## Install the shared library

you may use pip to install for Python or download the repo,then install manually for more languages

### Install through pip for Python (Windows64,Linux64)

#### Windows64

```bash
>pip install seuif97
```
#### Linux64

```bash
$sudo -H python3 -m pip install seuif97
```
### Download the repo,install manually for more languages

#### Windows32/64 
  
1. copy **libseuif97.dll**  to a default path of Windows dll
      
        C:\Windows\system
   
2. copy **seuif97.py** to a default path of Python lib
    
        C:\Python35\Lib 

####  Linux64(Ubuntu 18.04)  
    
 1. copy **libseuif97.so**  to a default path of Linux shared lib
   
        $sudo cp libseuif97.so /usr/lib/

 2. copy **seuif97.py** to a default path of Python lib
   
        $sudo cp seuif97.py /usr/lib/python3.6/

## Python API 

### Functions 

```python
   pt( pressure,    temperature, propertyID)
   ph( pressure,    enthalpy,    propertyID)
   ps( pressure,    entropy,     propertyID)
   ts( temperature, entropy,     propertyID)
   hs( enthalpy,    entropy,     propertyID)
   px( pressure,    quality,     propertyID)
   tx( temperature, quality,     propertyID)
```
**propertyID** - int, 0-29,(see **propertyIDs in seuif97** for details)

```python
   pt2v( pressure,    temperature)
   pt2h( pressure,    temperature)
   pt2s( pressure,    temperature)
   pt2xs( pressure,    temperature)
  
   ph2t( pressure,    enthalpy)
   ph2v( pressure,    enthalpy)
   ph2s( pressure,    enthalpy)
   ph2x( pressure,    enthalpy)
 
   ps2v( pressure,    entropy)
   ps2h( pressure,    entropy)
   ps2t( pressure,    entropy)
   ps2x( pressure,    entropy)
  
   ts2v( temperature,    entropy)
   ts2h( temperature,    entropy)
   ts2p( temperature,    entropy)
   ts2x( temperature,    entropy)
  
   hs2p( enthalpy,    entropy)
   hs2t( enthalpy,    entropy)
   hs2v( enthalpy,    entropy)
   hs2x( enthalpy,    entropy)
 
   px2t( pressure,    quality)
   px2v( pressure,    quality)
   px2h( pressure,    quality)
   px2s( pressure,    quality)
 
   tx2p( temperature, quality)
   tx2v( temperature, quality)
   tx2h( temperature, quality)
   tx2s( temperature, qualityD)
```

### Function for steam turbine process  
   
#### 1 Isentropic Enthalpy Drop： 

```python
ishd( pi,ti,pe)
```
    
pi －inlet P，ti - inlet T，pe - outlet P

* 2 Isentropic Efficiency： 

```python
ief( pi,ti,pe,te)
```
pi－inlet P， ti　－inlet T，pe　outlet P; te－ outlet T


        
## Demo Python

```python
import seuif97

p=16.10
t=535.10

h=seuif97.pt(p,t,４)
h=seuif97.pt2h(p,t)
```

## propertyIDs in seuif97

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
