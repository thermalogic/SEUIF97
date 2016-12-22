# SEUIF97

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

## Properties in SEUIF97 Lib

|   物性       |    单位     |  符号  |  编码   |   
| -------------|:----------:| ------:|-------:|
| 压力         |   MPa     |  P     |   0     |  
| 温度         |   °C      |  t     |   1     |
| 密度         | kg/m^3    |  d     |   2     |
| 比容         | m^3/kgd   |  v     |   3     |
| 焓           | kJ/kg     |  h     |   4     |
| 熵           | kJ/(kg·K) |  s     |   5     |
| 用           | kJ/kg     |  e     |   6     |
| 内能         | kJ/kg     |  u     |   7     |
| 定压比热容    | kJ/(kg·K) |  cp    |   8     |
| 定容比热容    | kJ/(kg·K) |  cv    |   9     |		
| 声速         | m/s       |   w     | 10      |	
| 定熵指数   |             |  ks     | 11      |	
|亥姆霍兹自由能   |   kJ/kg          |  f     | 12      |	
|吉布斯自由能     |   kJ/kg           | g     | 13      |	


可压缩性因子	/	z	14

干度	/	x	15

区域	/	r	16

定压热膨胀系数	1/K	ec	17

等温压缩率	1/MPa	kt	18

偏导数 (dV/dT)p	m3/(kg·K)	dvdt	19

偏导数 (dV/dP)T	m3/(kg·Mpa)	dvdp	20

偏导数 (dP/dT)v	Mpa/K	dpdt	21

等温Joule-Thomson系数	kJ/(kg·MPa)	iJTC	22

Joule-Thomson系数	K/MPa	JTC	23

动力粘度	kg/(m·s)	dv	24

运动粘度	m^2/s	kv	25

导热系数	W/(m.K)	tc	26

热扩散系数	um^2/s	td	27

普朗特数	/	pr	28

表面张力	mN/m	st	29
