# SEUIF97 vs CoolProp-IF97 Performance Benchmark Report

## Test Environment

- **Iterations per test**: 1,000,000
- **Number of test cases**: 4
- **Comparison**: SEUIF97 (C Source) vs CoolProp-IF97

---

## Test Cases Overview

| Case | Name | Input Conditions | Region |
|------|------|------------------|--------|
| Case 1 | High Pressure | p = 3.0 MPa, t = 26.85 °C | Region 1 (Compressed Liquid Water) |
| Case 2 | Low Pressure | p = 0.0035 MPa, t = 26.85 °C | Region 2 (Superheated Steam) |
| Case 3 | Critical | t = 376.85 °C, v = 0.002 m³/kg | Region 3 (Supercritical Region) |
| Case 4 | High Temperature | p = 0.5 MPa, t = 1226.85 °C | Region 5 (High Temperature Region) |

---

## Case 1: High Pressure (Region 1)

**Input**: p = 3.0000 MPa, t = 26.85 °C

| Property | CoolProp Value | SEUIF97 Value | CoolProp Time | SEUIF97 Time | Speedup |
|----------|----------------|---------------|---------------|--------------|---------|
| h (kJ/kg) | 115.3313 | 115.3313 | 122.9 ns | 53.8 ns | **2.29x** |
| s (kJ/kg·K) | 0.392295 | 0.392295 | 223.3 ns | 128.8 ns | **1.73x** |
| v (m^3/kg) | 0.001002 | 0.001002 | 170.9 ns | 53.5 ns | **3.20x** |
| **Average** | - | - | **172.4 ns** | **78.7 ns** | **2.19x** |

---

## Case 2: Low Pressure (Region 2)

**Input**: p = 0.0035 MPa, t = 26.85 °C

| Property | CoolProp Value | SEUIF97 Value | CoolProp Time | SEUIF97 Time | Speedup |
|----------|----------------|---------------|---------------|--------------|---------|
| h (kJ/kg) | 2549.9115 | 2549.9115 | 179.4 ns | 74.6 ns | **2.40x** |
| s (kJ/kg·K) | 8.522390 | 8.522390 | 335.3 ns | 197.0 ns | **1.70x** |
| v (m^3/kg) | 39.4914 | 39.4914 | 173.1 ns | 62.1 ns | **2.79x** |
| **Average** | - | - | **229.3 ns** | **111.2 ns** | **2.06x** |

---

## Case 3: Critical (Region 3)

**Input**: t = 376.85 °C, v = 0.002000 m³/kg

| Property | CoolProp Value | SEUIF97 Value | CoolProp Time | SEUIF97 Time | Speedup |
|----------|----------------|---------------|---------------|--------------|---------|
| h (kJ/kg) | 1863.4302 | 1863.4302 | 210.3 ns | 109.9 ns | **1.91x** |
| s (kJ/kg·K) | 4.054273 | 4.054273 | 202.7 ns | 109.4 ns | **1.85x** |
| **Average** | - | - | **137.7 ns** | **73.9 ns** | **1.86x** |

---

## Case 4: High Temperature (Region 5)

**Input**: p = 0.5000 MPa, t = 1226.85 °C

| Property | CoolProp Value | SEUIF97 Value | CoolProp Time | SEUIF97 Time | Speedup |
|----------|----------------|---------------|---------------|--------------|---------|
| h (kJ/kg) | 5219.7686 | 5219.7686 | 26.3 ns | 26.0 ns | **1.01x** |
| s (kJ/kg·K) | 9.654089 | 9.654089 | 52.9 ns | 46.9 ns | **1.13x** |
| v (m^3/kg) | 1.3846 | 1.3846 | 21.1 ns | 19.0 ns | **1.11x** |
| **Average** | - | - | **33.4 ns** | **30.7 ns** | **1.09x** |

---

## Overall Performance Comparison

### Average Speedup by Region

| Region | Test Case | CoolProp Avg Time | SEUIF97 Avg Time | Speedup |
|--------|-----------|-------------------|------------------|---------|
| Region 1 | High Pressure | 172.4 ns | 78.7 ns | **2.19x** |
| Region 2 | Low Pressure | 229.3 ns | 111.2 ns | **2.06x** |
| Region 3 | Critical | 137.7 ns | 73.9 ns | **1.86x** |
| Region 5 | High Temperature | 33.4 ns | 30.7 ns | **1.09x** |

### Speedup Summary by Property

| Property | Region 1 | Region 2 | Region 3 | Region 5 |
|----------|----------|----------|----------|----------|
| h (Specific Enthalpy) | 2.29x | 2.40x | 1.91x | 1.01x |
| s (Specific Entropy) | 1.73x | 1.70x | 1.85x | 1.13x |
| v (Specific Volume) | 3.20x | 2.79x | - | 1.11x |

---

## Conclusions

1. **Identical Calculation Accuracy**: In all test cases, SEUIF97 and CoolProp-IF97 produce identical results (matching to 6 decimal places), confirming that both implementations strictly adhere to the IAPWS-IF97 standard.

2. **SEUIF97 Performance Leads Across All Regions**:
   - **Region 1 (Compressed Liquid Water)**: Average speedup of **2.19x**, with specific volume calculation reaching up to **3.20x**
   - **Region 2 (Superheated Steam)**: Average speedup of **2.06x**, with specific enthalpy calculation reaching up to **2.40x**
   - **Region 3 (Supercritical Region)**: Average speedup of **1.86x**, with specific enthalpy calculation reaching **1.91x**
   - **Region 5 (High Temperature Region)**: Average speedup of **1.09x**, with both implementations showing comparable performance

3. **Reasons for Performance Differences**:
   - SEUIF97 employs precomputed power tables, reducing redundant exponentiation operations
   - Significant speedups in Region 1/2/3 are attributed to optimized polynomial summation algorithms
   - Region 5 calculations are inherently simpler (dominated by ideal gas components), resulting in smaller performance gaps

4. **Optimal Application Scenarios**: SEUIF97 delivers substantial performance improvements in engineering simulations and thermodynamic cycle optimization scenarios that require extensive Region 1/2/3 calculations.

---

*Test Date: 2026-06-11*
*Test Tool: bench_coolprop_if97/c_bench_if97.cpp*
