# Using SEUIF97 with Microsoft C++ (MSVC) under Windows

## SEUIF97 

1. dynamic library:  `C:/Windows/system/libseuif97.dll`
2. header file: `./include/seuif97.h`
3. lib file `./lib/libseuif97.lib` (this lib of the demo is x64)

## Build and Run the Demo
D
demo code: [demo.c](./demo.c)

Build:

```
>cl /Fedemo.exe /Fo./obj/demo.obj demo.c -I./include/  ./lib/libseuif97.lib
```

Run:

```
>./demo
```

## Setup the Microsoft C++ toolset for the command line

https://github.com/PySEE/home/blob/S2020/guide/MSVC_CMD.md