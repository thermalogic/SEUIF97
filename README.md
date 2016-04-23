# SEUIF97

[![Gitter](https://badges.gitter.im/Py03013052/SEUIF97.svg)](https://gitter.im/Py03013052/SEUIF97?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

**Purpose:** Provide a library for developers to calculate the properties of water and steam using the IAPWS-IF97 industry-standard steam properties correlations

        IF97 shared library: Windows(32/64), Linux(64)
        
        Python API：Windows, Linux
        
        Microsoft Excel Macro

**Author:** Cheng Maohua， Southeast University， Nanjing，China  ( cmh@seu.edu.cn )

# Python 

## Windows 
  
1. copy SEUIF97.dll  to a default path of Windows dll
      
        C:\Windows\system
   
2. copy seuif97.py to a default path of Python lib
    
        C:\Python35\Lib 
   
##  Linux   
    
 1. copy SEUIF97.so  to a default path of Linux shared lib
   
        $ sudo cp SEUIF97.so /usr/lib/

 2. copy seuif97.py to a default path of Python lib
   
        $ sudo cp seuif97.py /usr/lib/python3.5/
        
# Quick start

```python
import seuif97

p=16.10
t=535.10

h=seuif97.pt2h(p,t)
```
 
## Details:

        Introduction_SEUIF97.ipynb
