# Using SEUIF97 with C/C++ 

## SEUIF97 

1. dynamic library: 
   * Windows `C:/Windows/system/libseuif97.dll`
   * Linux `./usr/lib/libseuif97.so`
2. header file: `./include/seuif97.h`
3. lib file `./lib/libseuif97.lib` (the lib:x64)

## Build and Run the Demo

demo code: [demo.c](./demo.c)

### MSVC

```
>cl /Fedemo.exe /Fo./obj/demo.obj demo.c -I./include/  ./lib/libseuif97.lib
```

### GCC

**Windows with MinGW-W64：**

```
>gcc -o demo.exe demo.c -I./include  -LC:/Windows/system/  -lseuif97
```

**Linux**：

```
$gcc -o demo demo.c  -I./include  -L/usr/lib/ -lseuif97 -lm
```

**Run:**

./demo
