/*
 * Benchmark: SEUIF97 Performance Test
 */

#include <stdio.h>
#include <stdlib.h>

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
#define OP 0 /* pressure */
#define OT 1 /* temperature */
#define OV 3 /* specific volume */
#define OH 4 /* enthalpy */
#define OS 5 /* entropy */

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

static void benchmark_property_fn_region(const char *name, prop_fn_region fn,
                                         double a, double b, double r, int count)
{
    volatile double sink = 0.0;
    double result;
    hr_time_t start, end;

    for (int i = 0; i < 1000; i++)
    {
        result = fn(a, b);
    }

    HR_TIME_GET(start);
    for (int i = 0; i < count; i++)
    {
        result = fn(a, b);
    }
    HR_TIME_GET(end);

    double elapsed_ns = hr_time_diff_ns(start, end);
    double elapsed_ms = elapsed_ns / 1e6;
    double avg_ns = elapsed_ns / (double)count;
    double error = result - r;
    printf("  %s     %12.6f   %12.6f   %10.3f     %10.3f\n",
           name, result, error, elapsed_ms, avg_ns);
}

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
    double elapsed_ms = elapsed_ns / 1e6;
    double avg_ns = elapsed_ns / (double)count;

    printf("  %s     %12.6f     %10.3f     %10.3f\n",
           name, result, elapsed_ms, avg_ns);
}

typedef struct
{
    const char *label;
    double p;
    double t;
} TestCase;

/* Region 反向方程测试项 */
typedef struct
{
    const char *name;
    prop_fn_region fn;
    double a;
    double b;
    double r;
} RegionBenchItem;

static void run_benchmark_pt(const TestCase *tc, int count)
{
    printf("  Input:  p = %.1f MPa, t = %.2f "
#if defined(_WIN32)
           "\xA1\xE3"
           "C"
#else
           "°C"
#endif
           "\n\n",
           tc->p, tc->t);
    printf("  Property      Value         Total(ms)        Avg(ns/call)\n");
    printf("  --------    ---------      -----------     --------------\n");

    benchmark_property_fn("h", pt, tc->p, tc->t, OH, count);
    benchmark_property_fn("s", pt, tc->p, tc->t, OS, count);
    benchmark_property_fn("v", pt, tc->p, tc->t, OV, count);
    printf("\n");
}

static void run_benchmark_reverse(const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);

    printf("  Forward:  p = %.1f MPa, t = %.2f "
#if defined(_WIN32)
           "\xA1\xE3"
           "C"
#else
           "°C"
#endif
           "  ->  h = %.4f, s = %.4f\n\n",
           tc->p, tc->t, h, s);
    printf("  Property     Value         Total(ms)        Avg(ns/call)\n");
    printf("  --------    ---------      -----------     --------------\n");

    /* 反向计算：给定 (p,h) 求 T，给定 (p,s) 求 T，给定 (h,s) 求 T */
    benchmark_property_fn("phT", ph, tc->p, h, OT, count);
    benchmark_property_fn("psT", ps, tc->p, s, OT, count);
    benchmark_property_fn("hsP", hs, h, s, OP, count);
    printf("\n");
}

static void print_header(const TestCase *tc, double h, double s)
{
    printf("  Forward:  p = %.1f MPa, t = %.2f "
#if defined(_WIN32)
           "\xA1\xE3"
           "C"
#else
           "°C"
#endif
           "  ->  h = %.4f, s = %.4f\n\n",
           tc->p, tc->t, h, s);
    printf("  Property        Value         Error      Total(ms)        Avg(ns/call)\n");
    printf("  --------       ---------     -------   -----------     --------------\n");
}

static void run_benchmark_reverse_region1(const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);
    print_header(tc, h, s);

    RegionBenchItem items[] = {
        {"ph2T_reg1", ph2T_reg1, tc->p, h, tc->t + 273.15},
        {"ps2T_reg1", ps2T_reg1, tc->p, s, tc->t + 273.15},
        {"hs2p_reg1", hs2p_reg1, h, s, tc->p},
    };
    int n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++)
        benchmark_property_fn_region(items[i].name, items[i].fn, items[i].a, items[i].b, items[i].r, count);

    printf("\n");
}

static void run_benchmark_reverse_region2(const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);
    print_header(tc, h, s);

    RegionBenchItem items[] = {
        {"ph2T_reg2", ph2T_reg2, tc->p, h, tc->t + 273.15},
        {"ps2T_reg2", ps2T_reg2, tc->p, s, tc->t + 273.15},
        {"hs2p_reg2", hs2p_reg2, h, s, tc->p},
    };
    int n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++)
        benchmark_property_fn_region(items[i].name, items[i].fn, items[i].a, items[i].b, items[i].r, count);

    printf("\n");
    RegionBenchItem items_sub[] = {
        {"ph2T_reg2a", ph2T_reg2a, 0.001, 3000.0, 0.534433241E+03},
        {"ph2T_reg2b", ph2T_reg2b, 5.0, 3500.0, 0.801299102E+03},
        {"ph2T_reg2c", ph2T_reg2c, 40.0, 2700.0, 0.743056411E+03},
        {"ps2T_reg2a", ps2T_reg2a, 0.1, 7.5, 0.399517097E+03},
        {"ps2T_reg2b", ps2T_reg2b, 8.0, 6.0, 0.600484040E+03},
        {"ps2T_reg2c", ps2T_reg2c, 20.0, 5.75, 0.697992849E+03},
        {"hs2p_reg2a", hs2p_reg2a, 2800.0, 6.5, 1.371012767},
        {"hs2p_reg2b", hs2p_reg2b, 2800.0, 6.0, 4.793911442},
        {"hs2p_reg2c", hs2p_reg2c, 2800.0, 5.1, 9.439202060E+01},
    };
    int k = sizeof(items_sub) / sizeof(items_sub[0]);
    for (int i = 0; i < k; i++)
        benchmark_property_fn_region(items_sub[i].name, items_sub[i].fn, items_sub[i].a, items_sub[i].b, items_sub[i].r, count);
    printf("\n");
}

int main(void)
{
    const int count = 100000;

    const TestCase cases[] = {
        {"Region1: liquid water", 3.0, 26.85},
        {"Region2: superheated", 30.0, 426.85},
        {"Region5: high temp", 0.5, 1226.85},
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

    for (int i = 0; i < n_cases; i++)
    {
        printf("[PT -> %s]\n", cases[i].label);
        run_benchmark_pt(&cases[i], count);
    }

    for (int i = 0; i < n_cases; i++)
    {
        printf("[Reverse -> %s]\n", cases[i].label);
        run_benchmark_reverse(&cases[i], count);
    }

    run_benchmark_reverse_region1(&cases[0], count);
    run_benchmark_reverse_region2(&cases[1], count);

    return EXIT_SUCCESS;
}