# Using SEUIF97 with Microsoft C++ (MSVC) 

## SEUIF97 

1. dynamic library:  `C:/Windows/system/libseuif97.dll`
2. header file: `./include/seuif97.h`
3. lib file `./lib/libseuif97.lib` (the lib:x64)

## Build and Run the Demo

demo code: [demo.c](./demo.c)

Build:

```
>cl /Fedemo.exe /Fo./obj/demo.obj demo.c -I./include/  ./lib/libseuif97.lib
```

Run:

```
>./demo
```

