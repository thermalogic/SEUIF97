.. contents::

What is seuif97?
====================

The **seuif97** package is the Python API of the high-speed IAPWS-IF97 shared library.

Through the high-speed library, the results of the IAPWS-IF97 are accurately produced at about 3 times computational speed than the repeated squaring method for fast computation of large positive integer powers.

The shared library is written in ANSI C for faster, smaller binaries and better compatibility for accessing the DLL/SO from different programming language.

For Windows and Linux users, the convenient binary library and APIs are provided

- Windows64 dynamic library: libseuif97.dll

- Linux64 shared library: libseuif97.so

- APIs: Python, C/C++, Excel VBA, MATLAB, Java, Fortran, C#.

You may visit https://github.com/PySEE/SEUIF97 for more information about the shared library and APIs

Installation
====================

If you have an installation of Python with pip, install it with:

- Windows64

  >python -m pip install seuif97

- Linux64

  $sudo -H python3 -m pip install seuif97

Python API
====================

Functions of water and steam properties, thermodynamic process of steam turbine are provided in **seuif97** package

Functions of water and steam properties
-----------------------------------------

Using seuif97, you can set the state of steam using various pairs of know properties to get any output properties you wish to know,
including in the **30** properties (`propertyIDs in seuif97`_)

The following input pairs are implemented:

  (p,t) (p,h) (p,s) (p,v)

  (t,h) (t,s) (t,v)

  (h,s)

  (p,x) (t,x)

The two type of functions are provided in the seuif97 pacakge:

* ??(in1,in2,propertyID):h=pt(p,t,4), the propertyID h is 4
* ??2?(in1,in2): h=pt2h(p,t)

??(in1,in2,propertyID)
:::::::::::::::::::::::::::

.. code:: python

  pt(pressure,    temperature, propertyID)
  ph(pressure,    enthalpy,    propertyID)
  ps(pressure,    entropy,     propertyID)

  ts(temperature, entropy,     propertyID)
  tv(temperature, volume,      propertyID)

  hs(enthalpy,    entropy,     propertyID)

  px(pressure,    quality,     propertyID)
  tx(temperature, quality,     propertyID)

- p (pressure) : MPa ;

- t (temperature) : °C

- v (volume)  : m^3/kg

- h (enthalpy)  : kJ/kg

- s (entropy)  : kJ/(kg·K)

- x (quality) :

- **propertyID** - int, 0-29,(see `propertyIDs in seuif97`_ for details)

??2?(in1,in2)
:::::::::::::::::::::::::::
.. code:: python

   pt2v(pressure, temperature)
   pt2h(pressure, temperature)
   pt2s(pressure, temperature)
   pt2x(pressure, temperature)
  
   ph2t(pressure, enthalpy)
   ph2v(pressure, enthalpy)
   ph2s(pressure, enthalpy)
   ph2x(pressure, enthalpy)
 
   ps2v(pressure, entropy)
   ps2h(pressure, entropy)
   ps2t(pressure, entropy)
   ps2x(pressure, entropy)
  
   ts2v(temperature, entropy)
   ts2h(temperature, entropy)
   ts2p(temperature, entropy)
   ts2x(temperature, entropy)

   tv2p(temperature,  volume)
   tv2h(temperature,  volume)
   tv2s(temperature,  volume)
   tv2x(temperature,  volume)
  
   hs2p(enthalpy,  entropy)
   hs2t(enthalpy,  entropy)
   hs2v(enthalpy,  entropy)
   hs2x(enthalpy,  entropy)
 
   px2t(pressure, quality)
   px2v(pressure, quality)
   px2h(pressure, quality)
   px2s(pressure, quality)
 
   tx2p(temperature, quality)
   tx2v(temperature, quality)
   tx2h(temperature, quality)
   tx2s(temperature, quality)

Functions for the Thermodynamic Process of Steam Turbine
---------------------------------------------------------------------------------

Isentropic Enthalpy Drop
:::::::::::::::::::::::::::

.. code:: python

   ishd(pi,ti,po)

- pi：inlet P，MPa；　ti：inlet T，°C

- po：outlet P，MPa；

Isentropic Efficiency(0~100)
::::::::::::::::::::::::::::::

.. code:: python

  ief(pi,ti,po,to)

- pi：inlet P，MPa； 　ti：inlet T，°C
- po：outlet P，MPa；　to：outlet T，°C

Examples
====================

.. code:: python

  import seuif97

  p，t=16.10,535.10

  # ??2?(in1,in2)
  h=seuif97.pt2h(p,t)
  s=seuif97.pt2s(p,t)
  v=seuif97.pt2v(p,t)
  print("(p,t),h,s,v:",
        "{:>.2f}\t {:>.2f}\t {:>.2f}\t {:>.3f}\t {:>.4f}".format(p, t, h, s, v))

  # ??(in1,in2,propertyid)
  t = seuif97.ph(p, h, 1)
  s = seuif97.ph(p, h, 5)
  v = seuif97.ph(p, h, 3)

  print("(p,h),t,s,v:",
       "{:>.2f}\t {:>.2f}\t {:>.2f}\t {:>.3f}\t {:>.4f}".format(p, h, t, s, v))

propertyIDs in seuif97
================================

+---------------------------------------+-------------+----------+------------+
|       Properties                      |    Unit     |  symbol  | propertyID |
+=======================================+=============+==========+============+
| Pressure                              |   MPa       |  p       |       0    |
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



