.. contents::

What is seuif97?
====================

The package seuif97 is binding the high-speed IAPWS-IF97 shared library for Python

The shared library is written in ANSI C for faster, smaller binaries and better compatibility for accessing the DLL/SO from different C++ compilers.
 
The shared librariy is provided for Windows and Linux users 
 
* Windows64:libseuif97.dll, Linux64:libseuif97.so
 
Through the high-speed library, the results of the IAPWS-IF97  are accurately produced at above 3 times computational speed.
 
Installation
------------

Get the latest version of seuif97 from

https://pypi.python.org/pypi/seuif97/

If you have an installation of Python with pip, simple install it with:

- Windows64

   >pip install seuif97

- Linux64

   $sudo -H python3 -m pip install seuif97


Python API 
------------

Functions 
>>>>>>>>>>>>>>>>>>

.. code:: python

   pt( pressure,    temperature, propertyID)
   ph( pressure,    enthalpy,    propertyID)
   ps( pressure,    entropy,     propertyID)
   ts( temperature, entropy,     propertyID)
   hs( enthalpy,    entropy,     propertyID)
   px( pressure,    quality,     propertyID)
   tx( temperature, quality,     propertyID)

**propertyID** - int, 0-29,(see **propertyIDs in seuif97** for details)

.. code:: python

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


Function for steam turbine process  
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

- 1 Isentropic Enthalpy Drop： 

.. code:: python

   ishd( pi,ti,pe)
    
pi －inlet P，ti - inlet T，pe - outlet P

- 2 Isentropic Efficiency： 

.. code:: python

   ief( pi,ti,pe,te)

pi－inlet P， ti　－inlet T，pe　outlet P; te－ outlet T

        
Demo Python
--------------

.. code:: python

    import seuif97

    p=16.10
    t=535.10

    h=seuif97.pt(p,t,4)
    h=seuif97.pt2h(p,t)


propertyIDs in seuif97
---------------------------


+---------------------------------------+-------------+----------+------------+
|       Properties                      |    Unit     |  symbol  | propertyID |   
+=======================================+=============+==========+============+
| Pressure                              |   MPa       |  P       |       0    |
+---------------------------------------+-------------+----------+------------+
| Temperature                           |   °C        |  t       |       1    |
+---------------------------------------+-------------+----------+------------+
| Density                               | kg/m^3      |  d       |       2    |
+---------------------------------------+-------------+----------+------------+
| Specific Volume                       | m^3/kg      |  v       |       3    |
+---------------------------------------+-------------+----------+------------+
| Specific enthalpy                     | kJ/kg       |  h       |       4    |
+---------------------------------------+-------------+----------+------------+
| Specific entropy                      | kJ/(kg·K)   |  s       |       5    |
+---------------------------------------+-------------+----------+------------+
| Specific  exergy                      | kJ/kg       |  e       |       6    |
+---------------------------------------+-------------+----------+------------+
| Specific internal energy              | kJ/kg       |   u      |       7    |
+---------------------------------------+-------------+----------+------------+
| Specific isobaric heat capacity       | kJ/(kg·K)   |  cp      |       8    |
+---------------------------------------+-------------+----------+------------+
| Specific isochoric heat capacity      | kJ/(kg·K)   |  cv      |       9    |
+---------------------------------------+-------------+----------+------------+		
| Speed of sound                        | m/s         |  w       |      10    |	
+---------------------------------------+-------------+----------+------------+
| Isentropic exponent                   |             |  ks      |      11    |	
+---------------------------------------+-------------+----------+------------+
| Specific Helmholtz free energy        |   kJ/kg     |  f       |      12    |	
+---------------------------------------+-------------+----------+------------+
| Specific Gibbs free energy            |   kJ/kg     |  g       |      13    |	
+---------------------------------------+-------------+----------+------------+
| Compressibility factor                |             |  z       |      14    |
+---------------------------------------+-------------+----------+------------+
| Steam quality                         |             |  x       |      15    |
+---------------------------------------+-------------+----------+------------+
| Region                                |             |  r       |      16    |
+---------------------------------------+-------------+----------+------------+
| Isobaric volume expansion coefficient |   1/K       |  ec      |      17    |
+---------------------------------------+-------------+----------+------------+
| Isothermal compressibility            |   1/MPa     |  kt      |      18    |
+---------------------------------------+-------------+----------+------------+
| Partial derivative (dV/dT)p           | m3/(kg·K)   |  dvdt    |      19    |
+---------------------------------------+-------------+----------+------------+
| Partial derivative (dV/dP)T           | m3/(kg·MPa) |  dvdp    |      20    |
+---------------------------------------+-------------+----------+------------+
| Partial derivative (dP/dT)v           |   MPa/K     | dpdt     |      21    |
+---------------------------------------+-------------+----------+------------+
| Isothermal Joule-Thomson coefficient  | kJ/(kg·MPa) | iJTC	 |      22    |
+---------------------------------------+-------------+----------+------------+
| Joule-Thomson coefficient             |   K/MPa     | JTC      |      23    |
+---------------------------------------+-------------+----------+------------+
| Dynamic viscosity                     |   kg/(m·s)  |  dv      |      24    |
+---------------------------------------+-------------+----------+------------+
| Kinematic viscosity                   |   m^2/s     |  kv      |      25    |
+---------------------------------------+-------------+----------+------------+
| Thermal conductivity                  |   W/(m.K)   |  tc      |      26    |
+---------------------------------------+-------------+----------+------------+
| Thermal diffusivity                   |   um^2/s    |  td      |      27    |
+---------------------------------------+-------------+----------+------------+
| Prandtl number                        |             |  pr      |      28    |
+---------------------------------------+-------------+----------+------------+
| Surface tension                       |   mN/m      |  st      |      29    |
+---------------------------------------+-------------+----------+------------+



