
# Building the Shared Library

## Make

### GCC at Linux

```bash
make
```

Clean:
```bash
make clean
```

Build output location:
- `bin/libseuif97.so`

### MinGW-GCC at Windows

64bit __stdcall  dll(VBA)

```bash
#CFLAGS=-O3 -DBUILD_DLL 
```

32bit  __stdcall DLL(VBA)

```bash
#CFLAGS=-O3 -DBUILD_DLL -m32
```

Clean:
```bash
mingw32-make clean
```

Build output location:
- `bin/libseuif97.dll`

## CMake

### GCC at Linux

```bash
cmake -B ./build/   
cmake --build ./build/ --config Release
```

Clean:
```bash
rm -rf ./build/
```

Build output location:
- `bin/libseuif97.so`

###  MinGW-GCC at Windows 

64bit __stdcall  dll(VBA)
```bash
cmake -B ./build -G "MinGW Makefiles"  -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS=-m64
cmake --build ./build/ --config Release
```

32bit __stdcall  dll(VBA)
```bash
cmake -B ./build -G "MinGW Makefiles"  -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS=-m32
cmake --build ./build/ --config Release
```

Clean:
```powershell
Remove-Item -Recurse -Force ./build/
```

Build output location:
- `bin/libseuif97.dll`

###  Windows: Microsoft Visual Studio c++ 

**Note:** CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS is incompatible with __stdcall

For 64-bit __stdcall DLL 

```bash
cmake -B ./build/  -DBUILD_DLL=ON -DBUILD_DEMO=ON -G "Visual Studio 18 2026" -A x64
cmake --build ./build/ --config Release
```

For 32-bit __stdcall DLL:
```bash
cmake -B ./build/  -DBUILD_DLL=ON -G "Visual Studio 18 2026" -A Win32
cmake --build ./build/ --config Release
```

Clean:
```powershell
Remove-Item -Recurse -Force ./build/
```

Build output location:
- `build/Release/seuif97.dll`