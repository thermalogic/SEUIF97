/*
 * Benchmark: SEUIF97 Performance Test
 */

#include <stdio.h>
#include <stdlib.h>
#include "../test/if97_data.h"

#if defined(_WIN32)
    #include <windows.h>
    typedef LARGE_INTEGER hr_time_t;
    #define HR_TIME_GET(var) QueryPerformanceCounter(&(var))
    static double hr_timer_freq_hz = 0.0;
    static void hr_timer_init(void)
    {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        hr_timer_freq_hz = (double)freq.QuadPart;
    }
    static double hr_time_diff_ns(hr_time_t start, hr_time_t end)
    {
        return (double)(end.QuadPart - start.QuadPart) * 1e9 / hr_timer_freq_hz;
    }
#else
    #include <time.h>
    typedef struct timespec hr_time_t;
    #define HR_TIME_GET(var) clock_gettime(CLOCK_MONOTONIC, &(var))
    static void hr_timer_init(void) {}
    static double hr_time_diff_ns(hr_time_t start, hr_time_t end)
    {
        return (double)(end.tv_sec - start.tv_sec) * 1e9 + (double)(end.tv_nsec - start.tv_nsec);
    }
#endif

/* 输出属性 ID */
#define OP 0   /* pressure */
#define OT 1   /* temperature */
#define OV 3   /* specific volume */
#define OH 4   /* enthalpy */
#define OS 5   /* entropy */

extern double pt(double p, double t, int o_id);
extern double ph(double p, double h, int o_id);
extern double ps(double p, double s, int o_id);
extern double hs(double h, double s, int o_id);

// Region 1 backward equations
extern double ph2T_reg1(double p, double h);
extern double ps2T_reg1(double p, double s);
extern double hs2p_reg1(double h, double s);

// Region 2 backward equations
extern double ph2T_reg2(double p, double h);
extern double ps2T_reg2(double p, double s);
extern double hs2p_reg2(double h, double s);

extern double ph2T_reg2a(double p, double h);
extern double ph2T_reg2b(double p, double h);
extern double ph2T_reg2c(double p, double h);
extern double ps2T_reg2a(double p, double s);
extern double ps2T_reg2b(double p, double s);
extern double ps2T_reg2c(double p, double s);
extern double hs2p_reg2a(double h, double s);
extern double hs2p_reg2b(double h, double s);
extern double hs2p_reg2c(double h, double s);

typedef double (*prop_fn)(double, double, int);
typedef double (*prop_fn_region)(double, double);


/* Region 反向方程测试项 */
typedef struct {
    const char *name;
    prop_fn_region fn;
    double a;
    double b;
} RegionBenchItem;

static void benchmark_property_fn(const char *name, prop_fn fn,
                                  double a, double b, short o_id, int count)
{
    volatile double result = 0.0;
    hr_time_t start, end;

    for (int i = 0; i < 1000; i++)
        result = fn(a, b, o_id);

    HR_TIME_GET(start);
    for (int i = 0; i < count; i++)
        result = fn(a, b, o_id);
    HR_TIME_GET(end);

    double elapsed_ns = hr_time_diff_ns(start, end);
    double avg_ns = elapsed_ns / (double)count;
    printf("  %-10s %12.6f %14.3f\n", name, result, avg_ns);
}

static void benchmark_property_fn_region(const char *name, prop_fn_region fn,
                                  double a, double b, int count)
{
    volatile double result = 0.0;
    hr_time_t start, end;

    for (int i = 0; i < 1000; i++)
        result = fn(a, b);

    HR_TIME_GET(start);
    for (int i = 0; i < count; i++)
    {    result = fn(a, b);
    }
    HR_TIME_GET(end);

    double elapsed_ns = hr_time_diff_ns(start, end);
    double avg_ns = elapsed_ns / (double)count;

    printf("  %-10s %12.6f %14.3f\n",
           name, result,  avg_ns);
}

static void print_benchmark_header(void)
{
    printf("  Property     Value         Avg(ns/call)\n");
    printf("  --------    ---------     --------------\n");
}

static void print_forward_info(double p, double t, double h, double s)
{
    printf("  Forward:  p = %.1f MPa, t = %.2f C  ->  h = %.4f, s = %.4f\n\n", p, t, h, s);
}

typedef struct {
    const char *label;
    double p;
    double t;
} TestCase;

static void run_benchmark_pt(const TestCase *tc, int count)
{
    printf("  Input:  p = %.1f MPa, t = %.2f C\n\n", tc->p, tc->t);
    print_benchmark_header();
    benchmark_property_fn("h",  pt, tc->p, tc->t, OH, count);
    benchmark_property_fn("s",  pt, tc->p, tc->t, OS, count);
    benchmark_property_fn("v",  pt, tc->p, tc->t, OV, count);
    printf("\n");
}

static void run_benchmark_backward(const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);

    print_forward_info(tc->p, tc->t, h, s);
    print_benchmark_header();

    benchmark_property_fn("phT", ph, tc->p, h, OT, count);
    benchmark_property_fn("psT", ps, tc->p, s, OT, count);
    benchmark_property_fn("hsP", hs, h,   s, OP, count);
    printf("\n");
}

static void run_benchmark_backward_region(const char *region_label,
                                          prop_fn_region fn_ph2T,
                                          prop_fn_region fn_ps2T,
                                          prop_fn_region fn_hs2p,
                                          const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);

    print_forward_info(tc->p, tc->t, h, s);
    print_benchmark_header();

    RegionBenchItem items[] = {
        {"ph2T", fn_ph2T, tc->p, h},
        {"ps2T", fn_ps2T, tc->p, s},
        {"hs2p", fn_hs2p, h, s},
    };
    int n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++)
        benchmark_property_fn_region(items[i].name, items[i].fn, items[i].a, items[i].b, count);
    printf("\n");
}

static void run_benchmark_backward_region2_sub(const TestCase *tc, int count)
{
    RegionBenchItem items[] = {
        {"ph2T_reg2a", ph2T_reg2a, r2a_phT[0].p, r2a_phT[0].h},
        {"ph2T_reg2b", ph2T_reg2b, r2b_phT[0].p, r2b_phT[0].h},
        {"ph2T_reg2c", ph2T_reg2c, r2c_phT[0].p, r2c_phT[0].h},
        {"ps2T_reg2a", ps2T_reg2a, r2a_psT[0].p, r2a_psT[0].s},
        {"ps2T_reg2b", ps2T_reg2b, r2b_psT[0].p, r2b_psT[0].s},
        {"ps2T_reg2c", ps2T_reg2c, r2c_psT[0].p, r2c_psT[0].s},
        {"hs2p_reg2a", hs2p_reg2a, r2a_hsP[0].h, r2a_hsP[0].s},
        {"hs2p_reg2b", hs2p_reg2b, r2b_hsP[0].h, r2b_hsP[0].s},
        {"hs2p_reg2c", hs2p_reg2c, r2c_hsP[0].h, r2c_hsP[0].s},
    };
    int n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++)
        benchmark_property_fn_region(items[i].name, items[i].fn, items[i].a, items[i].b, count);
    printf("\n");
}

int main(void)
{
    const int count = 100000;

    const TestCase cases[] = {
        {"Region1: ", r1_pT[0].p, r1_pT[0].T - 273.15},
        {"Region2: ", r2_pT[0].p, r2_pT[0].T - 273.15},
        {"Region5: ", r5_pT[0].p, r5_pT[0].T - 273.15},
    };
    const int n_cases = sizeof(cases) / sizeof(cases[0]);

    hr_timer_init();

    printf("\nSEUIF97 C Benchmark (%d iterations)\n", count);
    printf("  Timer:  %s\n",
#if defined(_WIN32)
           "QueryPerformanceCounter (ns resolution)"
#else
           "clock_gettime(CLOCK_MONOTONIC) (ns resolution)"
#endif
    );
    printf("  Cases:  %d\n", n_cases);
    printf("\n");

    for (int i = 0; i < n_cases; i++) {
        printf("[PT -> %s]\n", cases[i].label);
        run_benchmark_pt(&cases[i], count);
    }

    for (int i = 0; i < n_cases; i++) {
        printf("[Reverse -> %s]\n", cases[i].label);
        run_benchmark_backward(&cases[i], count);
    }

    printf("[Reverse Region1 -> %s]\n", cases[0].label);
    run_benchmark_backward_region("Region1", ph2T_reg1, ps2T_reg1, hs2p_reg1, &cases[0], count);

    printf("[Reverse Region2 -> %s]\n", cases[1].label);
    run_benchmark_backward_region("Region2", ph2T_reg2, ps2T_reg2, hs2p_reg2, &cases[1], count);
    run_benchmark_backward_region2_sub(&cases[1], count);

    return EXIT_SUCCESS;
}