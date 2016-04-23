# SEUIF97

[![Gitter](https://badges.gitter.im/Py03013052/SEUIF97.svg)](https://gitter.im/Py03013052/SEUIF97?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

IF97 Library (Windows, Linux); Excel Macro; Python Interface

SEUIF97水和水蒸汽物性计算库是以IAPWS　IF97公式为标准，C语言实现的高速、多平台适用共享库。

# Windows平台下Python使用SEUIF97 
  
1. 将SEUIF97.dll拷贝到Windows动态库的默认搜索路径
      
        C:\Windows\system
   
2. 将seuif97.py拷贝Python库的默认搜索路径：Python安装目录下的Lib子目录
    
       C:\Python35\Lib 
   
#  Linux平台下Python使用SEUIF97   
    
 1. 将SEUIF97.so拷贝Linux动态库的默认搜索路径
   
        $ sudo cp SEUIF97.so /usr/lib/

 2. 将seuif97.py拷贝Python库的默认搜索路径：python3.5的lib所在子目录
   
        $ sudo cp seuif97.py /usr/lib/python3.5/
 
详见：Introduction_SEUIF97.ipynb
