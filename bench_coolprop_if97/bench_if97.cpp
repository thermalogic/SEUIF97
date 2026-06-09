/*
  Benchmark: SEUIF97 in C VS CoolProp-IF97
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "IF97.h"
#include "seuif97.h"

#define OH 4
#define OS 5
#define OV 3

static void benchmark_if97_h(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        // Convert pressure from MPa to Pa, temperature from C to K
        result = IF97::hmass_Tp((t + 273.15), (p * 1e6));
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "h", result / 1000.0, elapsed_ms, avg_ns);
}

static void benchmark_if97_s(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = IF97::smass_Tp((t + 273.15), (p * 1e6));
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "s", result / 1000.0, elapsed_ms, avg_ns);
}

static void benchmark_if97_v(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = 1.0 / IF97::rhomass_Tp((t + 273.15), (p * 1e6));
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "v", result * 1000.0, elapsed_ms, avg_ns);
}

// Benchmark for Rust SEUIF97 C Shared Library
static void benchmark_rust_seuif97_h(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OH);
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "h", result, elapsed_ms, avg_ns);
}

static void benchmark_rust_seuif97_s(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OS);
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "s", result, elapsed_ms, avg_ns);
}

static void benchmark_rust_seuif97_v(double p, double t, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, OV);
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_ns = elapsed_ms * 1000000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n",
           "v", result, elapsed_ms, avg_ns);
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
    clock_t start, end;

    // h
    start = clock();
    for (int i = 0; i < count; i++) result = IF97::hmass_Tp((t + 273.15), (p * 1e6));
    end = clock();
    res.h_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.h_val = result / 1000.0;

    // s
    start = clock();
    for (int i = 0; i < count; i++) result = IF97::smass_Tp((t + 273.15), (p * 1e6));
    end = clock();
    res.s_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.s_val = result / 1000.0;

    // v
    start = clock();
    for (int i = 0; i < count; i++) result = 1.0 / IF97::rhomass_Tp((t + 273.15), (p * 1e6));
    end = clock();
    res.v_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.v_val = result * 1000.0;

    return res;
}

static BenchmarkResult run_coolprop_benchmark_tv(double t, double v, int count)
{
    // CoolProp-IF97 does not have direct TV input functions in public API
    // Region3 internally uses (T, rho), but there's no public TV interface
    BenchmarkResult res = {-1.0, -1.0, -1.0};
    return res;
}

static BenchmarkResult run_rust_seuif97_benchmark_pt(double p, double t, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;
    clock_t start, end;

    // h
    start = clock();
    for (int i = 0; i < count; i++) result = pt(p, t, OH);
    end = clock();
    res.h_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.h_val = result;

    // s
    start = clock();
    for (int i = 0; i < count; i++) result = pt(p, t, OS);
    end = clock();
    res.s_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.s_val = result;

    // v
    start = clock();
    for (int i = 0; i < count; i++) result = pt(p, t, OV);
    end = clock();
    res.v_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;
    res.v_val = result;

    return res;
}

static BenchmarkResult run_rust_seuif97_benchmark_tv(double t, double v, int count)
{
    BenchmarkResult res = {0};
    volatile double result = 0.0;
    clock_t start, end;

    // h
    start = clock();
    for (int i = 0; i < count; i++) result = tv(t, v, OH);
    end = clock();
    res.h_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;

    // s
    start = clock();
    for (int i = 0; i < count; i++) result = tv(t, v, OS);
    end = clock();
    res.s_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;

    // v
    start = clock();
    for (int i = 0; i < count; i++) result = tv(t, v, OV);
    end = clock();
    res.v_avg_ns = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC * 1000000.0 / count;

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
    }
    printf("\n");

    // Run Rust SEUIF97 benchmark
    printf("[2] Rust SEUIF97 (C Shared Library)\n");
    printf("  Property      Value          Total Time     Avg Time\n");
    printf("  --------      -----          ----------     --------\n");
    
    if (tc->type == TEST_PT) {
        benchmark_rust_seuif97_h(tc->p, tc->t, count);
        benchmark_rust_seuif97_s(tc->p, tc->t, count);
        benchmark_rust_seuif97_v(tc->p, tc->t, count);
    } else {
        // TV type - just show tv results
        volatile double result;
        clock_t start, end;
        double elapsed_ms, avg_ns;
        
        // h
        start = clock();
        for (int i = 0; i < count; i++) result = tv(tc->t, tc->v, OH);
        end = clock();
        elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        avg_ns = elapsed_ms * 1000000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n", "h", result, elapsed_ms, avg_ns);
        
        // s
        start = clock();
        for (int i = 0; i < count; i++) result = tv(tc->t, tc->v, OS);
        end = clock();
        elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        avg_ns = elapsed_ms * 1000000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n", "s", result, elapsed_ms, avg_ns);
        
        // v
        start = clock();
        for (int i = 0; i < count; i++) result = tv(tc->t, tc->v, OV);
        end = clock();
        elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        avg_ns = elapsed_ms * 1000000.0 / count;
        printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f ns/call\n", "v", result, elapsed_ms, avg_ns);
    }
    printf("\n");

    // Performance comparison analysis
    printf("Performance Comparison\n");
    printf("  Input: p=%.4f MPa, t=%.2f C\n", tc->p, tc->t);
    printf("  ------------------------------------------------------------------------\n");
    printf("  Property    CoolProp Val   Rust Val     CoolProp    Rust SEUIF97    Speedup\n");
    printf("  --------    -----------   --------     --------    ------------    -------\n");

    BenchmarkResult coolprop = run_coolprop_benchmark_pt(tc->p, tc->t, count);
    BenchmarkResult rust_seuif97 = run_rust_seuif97_benchmark_pt(tc->p, tc->t, count);

    printf("  h (kJ/kg)    %11.4f   %10.4f     %6.0f ns      %6.0f ns       %6.2fx\n",
           coolprop.h_val, rust_seuif97.h_val,
           coolprop.h_avg_ns, rust_seuif97.h_avg_ns, coolprop.h_avg_ns / rust_seuif97.h_avg_ns);
    printf("  s (kJ/kgK)   %11.6f   %10.6f     %6.0f ns      %6.0f ns       %6.2fx\n",
           coolprop.s_val, rust_seuif97.s_val,
           coolprop.s_avg_ns, rust_seuif97.s_avg_ns, coolprop.s_avg_ns / rust_seuif97.s_avg_ns);
    printf("  v (L/kg)     %11.6f   %10.6f     %6.0f ns      %6.0f ns       %6.2fx\n",
           coolprop.v_val, rust_seuif97.v_val,
           coolprop.v_avg_ns, rust_seuif97.v_avg_ns, coolprop.v_avg_ns / rust_seuif97.v_avg_ns);

    double avg_coolprop = (coolprop.h_avg_ns + coolprop.s_avg_ns + coolprop.v_avg_ns) / 3.0;
    double avg_rust = (rust_seuif97.h_avg_ns + rust_seuif97.s_avg_ns + rust_seuif97.v_avg_ns) / 3.0;

    printf("  --------    --------    ------------    -------\n");
    printf("  Average      %6.0f ns      %6.0f ns       %6.2fx\n",
           avg_coolprop, avg_rust, avg_coolprop / avg_rust);
    printf("\n");
}

int main(void)
{
    const int count = 1000000;

    // Define 4 test cases
    TestCase test_cases[] = {
        {"Case 1: High Pressure", TEST_PT, 3.0, 300 - 273.15, 0.0},
        {"Case 2: Low Pressure", TEST_PT, 0.0035, 300 - 273.15, 0.0},
        {"Case 3: Critical", TEST_PT, 50.0, 630.0-273.15, 0.0},
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
    printf("  Note: Speedup = CoolProp time / Rust SEUIF97 time\n");
    printf("        Values > 1 indicate Rust SEUIF97 is faster\n");
    printf("=========================================================\n");

    return EXIT_SUCCESS;
}