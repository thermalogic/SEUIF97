# SEUIF97 in C Software Design 

## 1. Document Overview

### 1.1 Document Purpose
This document serves as the software design specification for SEUIF97 in C, the high-speed calculation library for water and steam physical properties. It describes in detail the system architecture, module partitioning, interface definitions, and algorithm implementations, providing a complete technical reference for future maintenance, extension, and secondary development.

### 1.2 Scope
This document applies to the core C implementation code of the SEUIF97 project, covering all functional modules for water and steam thermodynamic property calculation, transport property calculation, and steam turbine thermodynamic process calculation.

### 1.3 Glossary
| Term | Definition |
|-----|------|
| IAPWS-IF97 | The industrial formulation standard for thermodynamic properties released by the International Association for the Properties of Water and Steam in 1997 |
| Region 1 | Subcritical water region |
| Region 2 | Superheated steam region |
| Region 3 | Near-critical region |
| Region 4 | Saturation line region |
| Region 5 | High-temperature region (above 800°C) |
| Shortest Addition Chain | Optimal multiplication sequence algorithm for fast integer power computation |
| Power Caching | Precompute and cache distinct powers to avoid redundant power calculations |

---

## 2. System Overview

### 2.1 System Objectives
SEUIF97 is a high-performance C-implemented calculation library compliant with the IAPWS-IF97 standard. It is specifically designed for computation-intensive scenarios such as non-stationary process simulation, on-line process monitoring and optimization. Its calculation speed significantly surpasses the standard library's math.pow() and the repeated squaring method, while maintaining full IAPWS-IF97 precision.

### 2.2 Key Features
1. Fully compliant with the IAPWS-IF97-Rev international industrial standard
2. Three original core acceleration algorithms
3. Cross-platform support for Windows and Linux operating systems
4. Provides interface support for 11 programming languages
5. Supports 12 distinct input state pairs, computing 36 thermodynamic and transport properties

### 2.3 Performance Metrics
- Calculation Speed: Several times faster than the standard C library's math.pow()
- Precision: Fully meets the accuracy requirements of the IAPWS-IF97 standard
- Concurrency Safety: Pure mathematical computation with no global mutable state
- Memory Footprint: Extremely low memory usage, suitable for embedded and high-performance scenarios

---

## 3. System Architecture Design

### 3.1 Overall Layered Architecture
SEUIF97 adopts a clear modular layered architecture, divided into 6 core subsystems:

```
┌──────────────────────────────────────────────────────────────┐
│                   Public Interface Layer (seuif97.h)        │
│  pt, ph, ps, pv, th, ts, tv, hs, px, tx, hx, sx, ishd, ief  │
├──────────────────────────────────────────────────────────────┤
│                   Common Function Layer (common/)            │
│  Region detection, boundary equations, property pair dispatch,│
│  transport properties, thermodynamic processes               │
├──────────────────────────────────────────────────────────────┤
│                 Acceleration Algorithm Layer (algo/)         │
│  Shortest Addition Chain, Power Caching, Polynomial Recurrence│
│  Secant Root Finding                                          │
├──────────────────────────────────────────────────────────────┤
│            Region Implementation Layer (r1/, r2/, r3/,       │
│            r4/, r5/) - 5 independent IAPWS-IF97 regions     │
└──────────────────────────────────────────────────────────────┘
```

### 3.2 Directory Structure
```
SEUIF97/
├── src/                          # Main source code directory
│   ├── common/                   # Common functional modules
│   ├── algo/                     # Core acceleration algorithm modules
│   ├── r1/                       # Region 1 - Subcritical water
│   ├── r2/                       # Region 2 - Superheated steam
│   ├── r3/                       # Region 3 - Near-critical
│   ├── r4/                       # Region 4 - Saturation line
│   └── r5/                       # Region 5 - High-temperature
├── demo/                         # Multi-language examples and interfaces
├── shared_lib/                   # Precompiled cross-platform shared libraries
├── test/                         # Unit test suite
├── doc/                          # Technical documentation directory
└── CMakeLists.txt / makefile     # Build scripts
```

---

## 4. Detailed Module Design

### 4.1 Common Functional Module (common/)

#### 4.1.1 Module Responsibilities
- Uniform definition of output property ID enumeration
- Provide cross-region region detection functions
- Implement boundary equation solving
- Dispatch 12 property pairs to corresponding region implementations
- Calculate transport properties (viscosity, thermal conductivity, etc.)
- Steam turbine thermodynamic process calculation interfaces

#### 4.1.2 Core Header Files
- `seuif97.h`: Public API declarations
- `property_id.h`: Property ID constant definitions (0-29)
- `common.h`: General data structures and function pointer type definitions
- `constant.h`: Physical constant definitions

#### 4.1.3 Main Functionality List
| Filename | Function |
|-------|------|
| seuif97.c | Top-level API entry dispatcher |
| property_pair.c | General dispatch logic for 12 input state pairs |
| region.c | Region detection for input pairs like p/T, p/h, p/s, h/s |
| boundaries.c | Region boundary equation implementations (e.g., B23 boundary) |
| transport.c | Transport properties including dynamic viscosity, kinematic viscosity, thermal conductivity |
| thermodynamic_process.c | Steam turbine isentropic enthalpy drop and isentropic efficiency calculation |

### 4.2 Acceleration Algorithm Module (algo/)

#### 4.2.1 Module Responsibilities
This module is the core innovation of SEUIF97, implementing three original acceleration algorithms.

#### 4.2.2 Core Algorithm Implementations

**1. Shortest Addition Chain Algorithm (sac.c)**
- Algorithm Idea: Generate the shortest addition chain sequence for a given integer n to compute x^n with the minimum number of multiplications
- File: `sac.c`
- Function: `ipowsac(double x, int n)`
- Supported exponent range: 0-58

**2. Power Caching Strategy (polynomial_solo.c)**
- Algorithm Idea: Precompute and cache all distinct power exponents to avoid redundant x^i calculations inside polynomial loops
- Key Optimization: Extract all distinct I and J from the polynomial terms n_i π^I_i η^J_i, and compute only these distinct powers
- Data Structures: `soI_pow[]`, `soJ_pow[]` are power caching arrays
- Function Pointer: `solo_power_fn` for power precomputation callbacks

**3. Multi-Polynomial Recurrence Method (polynomial_solo.c)**
- Algorithm Idea: Compute the base polynomial (zero order) first, then directly derive the first-order and second-order mixed partial derivative polynomials through derivative relationships, maximizing shared computation results
- Typical Implementation: `polys_solo_i_ii_ij_jj()` returns 6 polynomial results in a single computation

**4. Secant Root Finding (root.c)**
- Used for inverse equation solving (e.g., T(p, h), etc.)
- Functions: `rtsec1()`, `rtsec2()`
- Precision: `xacc = 1.0E-08`
- Maximum iterations: 100

**5. Traditional Fast Power Reference Implementation (rqm.c)**
- ipowrqm(): Fast exponentiation method for performance comparison and debugging

### 4.3 Region Implementation Modules (r1-r5)

Each region follows the exact same architectural pattern, ensuring code consistency and maintainability:

| Region | Physical Meaning | Core Characteristic Equation |
|-----|---------|-------------|
| r1 | Subcritical Water Region | Gibbs free energy equation g(π, τ) |
| r2 | Superheated Steam Region | Gibbs free energy equation g(π, τ) |
| r3 | Near-Critical Region | Helmholtz free energy equation |
| r4 | Saturation Line Region | p/T → saturation temperature-pressure relation, wet steam properties |
| r5 | High-Temperature Region (>800°C) | Gibbs free energy equation g(π, τ) |

Each region subdirectory contains:
- `regionX.h`: Header file declarations for the region
- `regionX_coff.h`: Hardcoded polynomial coefficient tables
- `regionX_solo_ij.h`: Power index mapping arrays
- `regionX_solo_power.c`: Region-specific power precomputation logic
- `regionX_gfe.c / regionX_hfe.c`: Basic characteristic equations
- `regionX_pT.c`: Property calculations for the pT input pair
- `regionX_pT_ext.c`: pT extended properties (derivatives, transport properties, etc.)
- `regionX_p_hs.c`: Inverse equations (p, h), (p, s), (h, s)
- `regionX_T_phps.c`: Temperature inverse equations T(p, h), T(p, s)
- `regionX_pair_ext.c`: Extended property pair dispatcher

---

## 5. Interface Design Specification

### 5.1 Public API (seuif97.h)

#### 5.1.1 Property Pair Calculation Interfaces (12 groups)

```c
// (p,t) → any property o_id
double pt(double p, double t, int o_id);

// (p,h) → any property o_id
double ph(double p, double h, int o_id);

// (p,s) → any property o_id
double ps(double p, double s, int o_id);

// (p,v) → any property o_id
double pv(double p, double v, int o_id);

// (t,h) → any property o_id
double th(double t, double h, int o_id);

// (t,s) → any property o_id
double ts(double t, double s, int o_id);

// (t,v) → any property o_id
double tv(double t, double v, int o_id);

// (h,s) → any property o_id
double hs(double h, double s, int o_id);

// (p,x) → wet steam any property o_id
double px(double p, double x, int o_id);

// (t,x) → wet steam any property o_id
double tx(double t, double x, int o_id);

// (h,x) → wet steam any property o_id
double hx(double h, double x, int o_id);

// (s,x) → wet steam any property o_id
double sx(double s, double x, int o_id);
```

#### 5.1.2 Steam Turbine Thermodynamic Process Interfaces

```c
// Isentropic Enthalpy Drop: given inlet (p,t) and outlet pressure pe, compute isentropic enthalpy drop
double ishd(double pi, double ti, double pe);

// Isentropic Efficiency: given inlet state (pi,ti) and outlet state (pe,te), return isentropic efficiency in 0~100 range
double ief(double pi, double ti, double pe, double te);
```

### 5.2 Property ID Definitions (property_id.h)

Supported 30+ property IDs:

| o_id | Property | Symbol | Unit |
|------|-----|-----|------|
| 0 | Pressure | p | MPa |
| 1 | Temperature | t | °C |
| 2 | Density | ρ | kg/m³ |
| 3 | Specific Volume | v | m³/kg |
| 4 | Specific Enthalpy | h | kJ/kg |
| 5 | Specific Entropy | s | kJ/(kg·K) |
| 6 | Specific Exergy | e | kJ/kg |
| 7 | Specific Internal Energy | u | kJ/kg |
| 8 | Specific Isobaric Heat Capacity | cp | kJ/(kg·K) |
| 9 | Specific Isochoric Heat Capacity | cv | kJ/(kg·K) |
| 10 | Speed of Sound | w | m/s |
| 11 | Isentropic Exponent | k | - |
| 12 | Specific Helmholtz Free Energy | f | kJ/kg |
| 13 | Specific Gibbs Free Energy | g | kJ/kg |
| 14 | Compressibility Factor | z | - |
| 15 | Steam Quality | x | - |
| 16 | Region | r | - |
| 17 | Isobaric Cubic Expansion Coefficient | αv | 1/K |
| 18 | Isothermal Compressibility | kT | 1/MPa |
| 19 | Partial Derivative (∂V/∂T)p | - | m³/(kg·K) |
| 20 | Partial Derivative (∂V/∂P)T | - | m³/(kg·MPa) |
| 21 | Partial Derivative (∂p/∂t)v | - | MPa/K |
| 22 | Isothermal Throttling Coefficient | δt | kJ/(kg·MPa) |
| 23 | Joule-Thomson Coefficient | μ | K/MPa |
| 24 | Dynamic Viscosity | η | kg/(m·s) |
| 25 | Kinematic Viscosity | ν | m²/s |
| 26 | Thermal Conductivity | λ | W/(m·K) |
| 27 | Thermal Diffusivity | a | µm²/s |
| 28 | Prandtl Number | Pr | - |
| 29 | Surface Tension | σ | N/m |

---

## 6. Data Structure Design

### 6.1 Core Data Structure Definitions

Base data structures defined in `src/common/common.h`:

```c
// Polynomial coefficient structure: stores (I, J, n) triples
typedef struct {
  int I, J;     // Exponents of the two dimensionless variables π and τ
  double n;     // Polynomial coefficient
} IJnData;

// Region property calculation function pointer type
typedef double (*properties_region)(double, double, int);

// Region detection function pointer type
typedef int (*region_fn)(double, double);

// General property calculation function pointer type
typedef double (*prop_fn)(double, double, int o_id);

// Secant root-finding objective function pointer type
typedef double (*callfunc)(double, double);

// Fast cache power precomputation function pointer type
typedef void (*solo_power_fn)(double, double, double *, double *);
```

---

## 7. Build System Design

### 7.1 Supported Build Methods

SEUIF97 provides two mainstream fully cross-platform build methods:

#### Method 1: Makefile Build (MinGW-GCC / GCC)
```makefile
make          # Directly compile to generate shared library
make tests    # Compile all unit test programs
```
- Windows output: `./bin/libseuif97.dll`
- Linux output: `./bin/libseuif97.so`

#### Method 2: CMake Build (Supports MSVC, GCC, Clang, and all compilers)
```bash
cmake -B ./build/
cmake --build ./build/ --config Release
```

### 7.2 Compilation Optimization Flags
Uses `-O3` maximum optimization level in the Makefile to maximize calculation performance. Also supports the `BUILD_DLL` macro definition to generate `__stdcall` calling convention exports compatible with 32-bit/64-bit VBA.

### 7.3 MSVC Special Handling

MSVC does not support `__stdcall` calling convention exports via `__declspec(dllexport)`. 
Therefore, a module definition file (.def) is used to export `__stdcall` functions.

```makefile
if(MSVC)
    # Use module definition file for __stdcall exports
    target_sources(seuif97 PRIVATE src/common/seuif97.def)
endif()
```
---

## 8. Cross-Language Interface Architecture

Through the C shared library exporting a unified API, SEUIF97 supports seamless integration with over 11 programming languages:

| Language Environment | Interface File | Directory Location |
|---------|---------|---------|
| C/C++ | seuif97.h | demo/demo-c |
| Python | seuif97.py | demo/demo-python |
| C# | seuif97.cs | demo/demo-csharp |
| Java | seuif97.java | demo/demo-java |
| Excel VBA | seuif97.bas | demo/ExcelVBA |
| MATLAB 64 | seuif97.m | demo/MATLAB64 |
| Rust | seuif97.rs | demo/demo-rust |
| Fortran | seuif97.f08 | demo/demo-fortran |
| Pascal | seuif97.pas | demo/demo-pascal |
| Golang | demo.go | demo/demo-go |
| Modelica | seuif97.mo | demo/demo-modelica |

---

## 9. Performance Design Highlights

1. **-O3 Maximum Optimization Level**: Compiler automatically performs deep optimizations such as loop unrolling and instruction scheduling
2. **No Global Mutable State**: All calculation functions are pure functions, 100% thread-safe
3. **Stack Local Variables**: No dynamic memory allocation (malloc/free), zero GC pauses
4. **Polynomial Loop Optimization**: Three acceleration algorithms drastically reduce multiplication operations
5. **No Redundant Branch Checks**: Region detection is executed only once, all subsequent property calculations reuse the region result

---

## 10. Test Framework Design

The test/ directory contains a complete unit test suite, covering all property input pairs:

- test_pt.c
- test_ph.c
- test_ps.c
- test_pv.c
- test_th.c
- test_ts.c
- test_tv.c
- test_hs.c
- test_hxsx.c

All test cases are verified against IAPWS-IF97 official standard reference values to ensure authoritative correctness of calculation results.

---

## 11. Version History and Author Information

- Project Version: 1.2.0
- Author: Cheng Maohua, School of Energy and Environment, Southeast University
- Email: cmh@seu.edu.cn
- DOI: 10.5281/zenodo.8242452

Main References:
1. Wang Peihong, Jia Junying, Cheng Maohua. A General Calculation Model for IAPWS-IF97 Formulations of Thermodynamic Properties of Water and Steam[J]. Proceedings of the Chinese Society of Power Engineering, 2001, 21(6): 1564-1567
2. Rui Jiamin, Sun Zhenye, Cheng Maohua. Fast IAPWS-IF97 Calculation Method Based on Shortest Addition Chain State Space Tree[J]. Steam Turbine Technology, 2017, 59(4): 245-247
