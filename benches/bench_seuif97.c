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

typedef enum { BT_PROP, BT_REGION } BenchType;

typedef struct {
    const char *name;
    BenchType type;
    double a, b;
    union {
        struct { prop_fn fn; short o_id; } prop;
        prop_fn_region fn_reg;
    };
} BenchItem;

#define PROP_ITEM(n, f, a, b, o) {n, BT_PROP, a, b, .prop={f, o}}
#define REG_ITEM(n, f, a, b)     {n, BT_REGION, a, b, .fn_reg=f}
#define ITEM_END                 {NULL, BT_PROP, 0, 0, .prop={NULL, 0}}

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
        result = fn(a, b);
    HR_TIME_GET(end);

    double elapsed_ns = hr_time_diff_ns(start, end);
    double avg_ns = elapsed_ns / (double)count;
    printf("  %-10s %12.6f %14.3f\n", name, result, avg_ns);
}

static void bench_item(const BenchItem *item, int count)
{
    if (item->type == BT_PROP)
        benchmark_property_fn(item->name, item->prop.fn, item->a, item->b, item->prop.o_id, count);
    else
        benchmark_property_fn_region(item->name, item->fn_reg, item->a, item->b, count);
}

static void print_benchmark_header(void)
{
    printf("  Property     Value         Avg(ns/call)\n");
    printf("  --------    ---------     --------------\n");
}

static void run_bench_suite(const char *title, const BenchItem *items, int count)
{
    printf("%s\n", title);
    print_benchmark_header();
    for (int i = 0; items[i].name != NULL; i++)
        bench_item(&items[i], count);
    printf("\n");
}

typedef struct {
    const char *label;
    double p;
    double t;
} TestCase;

static void run_pt_suite(const TestCase *tc, int count)
{
    char title[128];
    snprintf(title, sizeof(title), "[PT -> %s]  p=%.6f MPa, t=%.2f C", tc->label, tc->p, tc->t);

    BenchItem items[] = {
        PROP_ITEM("h", pt, tc->p, tc->t, OH),
        PROP_ITEM("s", pt, tc->p, tc->t, OS),
        PROP_ITEM("v", pt, tc->p, tc->t, OV),
        ITEM_END
    };
    run_bench_suite(title, items, count);
}

static void run_backward_suite(const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);
    char title[128];
    snprintf(title, sizeof(title), "[Backward -> %s]  p=%.6f, t=%.2f -> h=%.4f, s=%.4f",
             tc->label, tc->p, tc->t, h, s);

    BenchItem items[] = {
        PROP_ITEM("phT", ph, tc->p, h, OT),
        PROP_ITEM("psT", ps, tc->p, s, OT),
        PROP_ITEM("hsP", hs, h,   s, OP),
        ITEM_END
    };
    run_bench_suite(title, items, count);
}

static void run_region_suite(const char *label, const BenchItem *region_items, const TestCase *tc, int count)
{
    double h = pt(tc->p, tc->t, OH);
    double s = pt(tc->p, tc->t, OS);
    char title[128];
    snprintf(title, sizeof(title), "[Backward %s]  p=%.6f, t=%.2f -> h=%.4f, s=%.4f",
             label, tc->p, tc->t, h, s);

    BenchItem items[] = {
        {region_items[0].name, BT_REGION, tc->p, h, .fn_reg=region_items[0].fn_reg},
        {region_items[1].name, BT_REGION, tc->p, s, .fn_reg=region_items[1].fn_reg},
        {region_items[2].name, BT_REGION, h, s, .fn_reg=region_items[2].fn_reg},
        ITEM_END
    };
    run_bench_suite(title, items, count);
}

static void run_region2_sub_suite(const TestCase *tc, int count)
{
    BenchItem items[] = {
        REG_ITEM("ph2T_reg2a", ph2T_reg2a, r2a_phT[0].p, r2a_phT[0].h),
        REG_ITEM("ph2T_reg2b", ph2T_reg2b, r2b_phT[0].p, r2b_phT[0].h),
        REG_ITEM("ph2T_reg2c", ph2T_reg2c, r2c_phT[0].p, r2c_phT[0].h),
        REG_ITEM("ps2T_reg2a", ps2T_reg2a, r2a_psT[0].p, r2a_psT[0].s),
        REG_ITEM("ps2T_reg2b", ps2T_reg2b, r2b_psT[0].p, r2b_psT[0].s),
        REG_ITEM("ps2T_reg2c", ps2T_reg2c, r2c_psT[0].p, r2c_psT[0].s),
        REG_ITEM("hs2p_reg2a", hs2p_reg2a, r2a_hsP[0].h, r2a_hsP[0].s),
        REG_ITEM("hs2p_reg2b", hs2p_reg2b, r2b_hsP[0].h, r2b_hsP[0].s),
        REG_ITEM("hs2p_reg2c", hs2p_reg2c, r2c_hsP[0].h, r2c_hsP[0].s),
        ITEM_END
    };
    run_bench_suite("[Backward Region2 Sub-regions]", items, count);
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

    for (int i = 0; i < n_cases; i++)
        run_pt_suite(&cases[i], count);

    for (int i = 0; i < n_cases; i++)
        run_backward_suite(&cases[i], count);

    static const BenchItem region1_items[] = {
        REG_ITEM("ph2T_reg1", ph2T_reg1, 0, 0),
        REG_ITEM("ps2T_reg1", ps2T_reg1, 0, 0),
        REG_ITEM("hs2p_reg1", hs2p_reg1, 0, 0),
        ITEM_END
    };
    static const BenchItem region2_items[] = {
        REG_ITEM("ph2T_reg2", ph2T_reg2, 0, 0),
        REG_ITEM("ps2T_reg2", ps2T_reg2, 0, 0),
        REG_ITEM("hs2p_reg2", hs2p_reg2, 0, 0),
        ITEM_END
    };

    run_region_suite("Region1", region1_items, &cases[0], count);
    run_region_suite("Region2", region2_items, &cases[1], count);
    run_region2_sub_suite(&cases[1], count);

    return EXIT_SUCCESS;
}