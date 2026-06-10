/*
 * Benchmark: C Source SEUIF97 VS CoolProp-IF97
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <chrono>
#include "IF97.h"

extern "C" double pt(double p, double t, int o_id);
extern "C" double tv(double t, double v, int o_id);
extern "C" double Tv_reg3(double T, double v, int o_id);

#define OH 4
#define OS 5
#define OV 3
#define OD 2

static void benchmark_if97_h(double p, double t, int count)
{
    volatile double result = 0.0;
    double T_K = t + 273.15;
    double p_Pa = p * 1e6;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = IF97::hmass_Tp(T_K, p_Pa);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "h", result / 1000.0, elapsed_us / 1000.0, avg_ns);
}

static void benchmark_if97_s(double p, double t, int count)
{
    volatile double result = 0.0;
    double T_K = t + 273.15;
    double p_Pa = p * 1e6;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = IF97::smass_Tp(T_K, p_Pa);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "s", result / 1000.0, elapsed_us / 1000.0, avg_ns);
}

static void benchmark_if97_v(double p, double t, int count)
{
    volatile double result = 0.0;
    double T_K = t + 273.15;
    double p_Pa = p * 1e6;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = 1.0 / IF97::rhomass_Tp(T_K, p_Pa);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "v", result * 1000.0, elapsed_us / 1000.0, avg_ns);
}

// Benchmark for CoolProp-IF97 with (T, v) input via Region3::hmass/smass
static void benchmark_if97_tv(double t, double v, int count)
{
    volatile double result = 0.0;
    double T = t + 273.15;       // C -> K
    double rho = 1.0 / v;        // v (m3/kg) -> rho (kg/m3)
    static const IF97::Region3 R3;

    // h
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = R3.hmass(T, rho);
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;
    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "h", result / 1000.0, elapsed_us / 1000.0, avg_ns);

    // s
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = R3.smass(T, rho);
    end = std::chrono::high_resolution_clock::now();
    elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    avg_ns = elapsed_us * 1000.0 / count;
    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "s", result / 1000.0, elapsed_us / 1000.0, avg_ns);

    // v (trivial)
    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "v", v * 1000.0, 0.0, 0.0);
}

// Benchmark for SEUIF97 C Source
static void benchmark_seuif97_h(double p, double t, int count)
{
    volatile double result = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OH);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "h", result, elapsed_us / 1000.0, avg_ns);
}

static void benchmark_seuif97_s(double p, double t, int count)
{
    volatile double result = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OS);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "s", result, elapsed_us / 1000.0, avg_ns);
}

static void benchmark_seuif97_v(double p, double t, int count)
{
    volatile double result = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OV);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_ns = elapsed_us * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n",
           "v", result, elapsed_us / 1000.0, avg_ns);
}

// Test case types
typedef enum {
    TEST_PT,  // Test with p, t inputs
    TEST_TV   // Test with t, v inputs
} TestType;

// Test case structure
typedef struct {
    const char* name;
    TestType type;
    double p;  // MPa
    double t;  // C
    double v;  // m3/kg (for TV type)
} TestCase;

// Struct to store benchmark results
typedef struct {
    double h_avg_ns;
    double s_avg_ns;
    double v_avg_ns;
    double h_val;
    double s_val;
    double v_val;
} BenchmarkResult;

static BenchmarkResult run_coolprop_benchmark_pt(double p, double t, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;
    double T_K = t + 273.15;
    double p_Pa = p * 1e6;

    // h
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = IF97::hmass_Tp(T_K, p_Pa);
    auto end = std::chrono::high_resolution_clock::now();
    res.h_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.h_val = result / 1000.0;

    // s
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = IF97::smass_Tp(T_K, p_Pa);
    end = std::chrono::high_resolution_clock::now();
    res.s_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.s_val = result / 1000.0;

    // v
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = 1.0 / IF97::rhomass_Tp(T_K, p_Pa);
    end = std::chrono::high_resolution_clock::now();
    res.v_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.v_val = result * 1000.0;

    return res;
}

static BenchmarkResult run_coolprop_benchmark_tv(double t, double v, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;
    double T = t + 273.15;       // C -> K
    double rho = 1.0 / v;        // v (m3/kg) -> rho (kg/m3)

    // Use static Region3 instance for (T, rho) input benchmarking
    static const IF97::Region3 R3;

    // h via Region3::hmass(T, rho)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = R3.hmass(T, rho);
    auto end = std::chrono::high_resolution_clock::now();
    res.h_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.h_val = result / 1000.0;

    // s via Region3::smass(T, rho)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = R3.smass(T, rho);
    end = std::chrono::high_resolution_clock::now();
    res.s_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.s_val = result / 1000.0;

    // v (trivial: input v itself)
    res.v_avg_ns = 0.0;
    res.v_val = v * 1000.0;

    return res;
}

static BenchmarkResult run_seuif97_benchmark_pt(double p, double t, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;

    // h
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = pt(p, t, OH);
    auto end = std::chrono::high_resolution_clock::now();
    res.h_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.h_val = result;

    // s
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = pt(p, t, OS);
    end = std::chrono::high_resolution_clock::now();
    res.s_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.s_val = result;

    // v
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = pt(p, t, OV);
    end = std::chrono::high_resolution_clock::now();
    res.v_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.v_val = result;

    return res;
}

static BenchmarkResult run_seuif97_benchmark_tv(double t, double v, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;
    double T_K = t + 273.15;

    // h
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = Tv_reg3(T_K, v, OH);
    auto end = std::chrono::high_resolution_clock::now();
    res.h_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.h_val = result;

    // s
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = Tv_reg3(T_K, v, OS);
    end = std::chrono::high_resolution_clock::now();
    res.s_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.s_val = result;

    // v
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) result = Tv_reg3(T_K, v, OV);
    end = std::chrono::high_resolution_clock::now();
    res.v_avg_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 1000.0 / count;
    res.v_val = result * 1000.0;

    return res;
}

static void run_single_test(const TestCase* tc, int count)
{
    printf("\n---------------------------------------------------------\n");
    printf("Test Case: %s\n", tc->name);
    
    if (tc->type == TEST_PT) {
        printf("  Input:      p = %.4f MPa, t = %.2f C\n", tc->p, tc->t);
    } else {
        printf("  Input:      t = %.2f C, v = %.4f m3/kg\n", tc->t, tc->v);
    }
    printf("---------------------------------------------------------\n\n");

    // Run CoolProp-IF97 benchmark
    printf("[1] CoolProp-IF97\n");
    printf("  Property      Value          Total Time     Avg Time\n");
    printf("  --------      -----          ----------     --------\n");
    
    if (tc->type == TEST_PT) {
        benchmark_if97_h(tc->p, tc->t, count);
        benchmark_if97_s(tc->p, tc->t, count);
        benchmark_if97_v(tc->p, tc->t, count);
    } else {
        benchmark_if97_tv(tc->t, tc->v, count);
    }
    printf("\n");

    // Run SEUIF97 benchmark
    printf("[2] SEUIF97 (C Source)\n");
    printf("  Property      Value          Total Time     Avg Time\n");
    printf("  --------      -----          ----------     --------\n");
    
    if (tc->type == TEST_PT) {
        benchmark_seuif97_h(tc->p, tc->t, count);
        benchmark_seuif97_s(tc->p, tc->t, count);
        benchmark_seuif97_v(tc->p, tc->t, count);
    } else {
        // TV type - direct Region 3 call (skip region detection)
        volatile double result;
        double T_K = tc->t + 273.15;
        
        // h
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++) result = Tv_reg3(T_K, tc->v, OH);
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        double avg_ns = elapsed_us * 1000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n", "h", result, elapsed_us / 1000.0, avg_ns);
        
        // s
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++) result = Tv_reg3(T_K, tc->v, OS);
        end = std::chrono::high_resolution_clock::now();
        elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        avg_ns = elapsed_us * 1000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n", "s", result, elapsed_us / 1000.0, avg_ns);
        
        // v
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++) result = Tv_reg3(T_K, tc->v, OV);
        end = std::chrono::high_resolution_clock::now();
        elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        avg_ns = elapsed_us * 1000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.1f ns/call\n", "v", result * 1000.0, elapsed_us / 1000.0, avg_ns);
    }
    printf("\n");

    // Performance comparison analysis
    printf("Performance Comparison\n");
    if (tc->type == TEST_PT) {
        printf("  Input: p=%.4f MPa, t=%.2f C\n", tc->p, tc->t);
    } else {
        printf("  Input: t=%.2f C, v=%.6f m3/kg\n", tc->t, tc->v);
    }
    printf("  ------------------------------------------------------------------------\n");
    printf("  Property    CoolProp Val   SEUIF97 Val  CoolProp    SEUIF97         Speedup\n");
    printf("  --------    -----------   -----------  --------    ---------       -------\n");

    BenchmarkResult coolprop, seuif97;
    if (tc->type == TEST_PT) {
        coolprop = run_coolprop_benchmark_pt(tc->p, tc->t, count);
        seuif97 = run_seuif97_benchmark_pt(tc->p, tc->t, count);
    } else {
        coolprop = run_coolprop_benchmark_tv(tc->t, tc->v, count);
        seuif97 = run_seuif97_benchmark_tv(tc->t, tc->v, count);
    }

    printf("  h (kJ/kg)    %11.4f   %10.4f     %6.1f ns      %6.1f ns       %6.2fx\n",
           coolprop.h_val, seuif97.h_val,
           coolprop.h_avg_ns, seuif97.h_avg_ns, coolprop.h_avg_ns / seuif97.h_avg_ns);
    printf("  s (kJ/kgK)   %11.6f   %10.6f     %6.1f ns      %6.1f ns       %6.2fx\n",
           coolprop.s_val, seuif97.s_val,
           coolprop.s_avg_ns, seuif97.s_avg_ns, coolprop.s_avg_ns / seuif97.s_avg_ns);
    printf("  v (L/kg)     %11.6f   %10.6f     %6.1f ns      %6.1f ns       %6.2fx\n",
           coolprop.v_val, seuif97.v_val,
           coolprop.v_avg_ns, seuif97.v_avg_ns, coolprop.v_avg_ns / seuif97.v_avg_ns);

    double avg_coolprop = (coolprop.h_avg_ns + coolprop.s_avg_ns + coolprop.v_avg_ns) / 3.0;
    double avg_seuif97 = (seuif97.h_avg_ns + seuif97.s_avg_ns + seuif97.v_avg_ns) / 3.0;

    printf("  --------    --------    ------------    -------\n");
    printf("  Average      %6.1f ns      %6.1f ns       %6.2fx\n",
           avg_coolprop, avg_seuif97, avg_coolprop / avg_seuif97);
    printf("\n");
}

int main(void)
{
    const int count = 1000000;

    // Define 4 test cases
    TestCase test_cases[] = {
        {"Case 1: High Pressure", TEST_PT, 3.0, 300 - 273.15, 0.0},
        {"Case 2: Low Pressure", TEST_PT, 0.0035, 300 - 273.15, 0.0},
        //{"Case 3: Critical", TEST_PT, 50.0, 630.0-273.15, 0.0},
        {"Case 3: Critical", TEST_TV, 0.0,650.0-273.15, 0.002},
        {"Case 4: High Temperature", TEST_PT, 0.5, 1500 - 273.15, 0.0}
    };
    const int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("\n=========================================================\n");
    printf("          SEUIF97 vs CoolProp-IF97 Benchmark\n");
    printf("=========================================================\n");
    printf("  Iterations per test: %d\n", count);
    printf("  Number of test cases: %d\n", num_cases);
    printf("=========================================================\n");

    // Run all test cases
    for (int i = 0; i < num_cases; i++) {
        run_single_test(&test_cases[i], count);
    }

    printf("=========================================================\n");
    printf("  Note: Values > 1 indicate SEUIF97 is faster\n");
    printf("=========================================================\n");

    return EXIT_SUCCESS;
}