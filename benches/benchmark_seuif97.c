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

#define OH 4
#define OS 5
#define OV 3

extern double pt(double p, double t, int o_id);


static void benchmark_property(const char *name, double p, double t, short o_id, int count)
{
    volatile double result = 0.0;
    hr_time_t start, end;

    /* 预热：让 CPU 进入稳定频率并填充缓存 */
    for (int i = 0; i < 1000; i++)
    {
        result = pt(p, t, o_id);
    }

    HR_TIME_GET(start);
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, o_id);
    }
    HR_TIME_GET(end);

    double elapsed_ns = hr_time_diff_ns(start, end);
    double elapsed_ms = elapsed_ns / 1e6;
    double avg_ns = elapsed_ns / (double)count;

    printf("  %4s     %12.6f     %10.3f     %10.3f\n",
           name, result, elapsed_ms, avg_ns);
}

typedef struct {
    const char *label;
    double p;
    double t;
} TestCase;

static void run_benchmark_group(const TestCase *tc, int count)
{
    printf("  Input:  p = %.1f MPa, t = %.2f "
#if defined(_WIN32)
           "\xA1\xE3""C"
#else
           "°C"
#endif
           "\n\n", tc->p, tc->t);
    printf("  Property     Value         Total(ms)        Avg(ns/call)\n");
    printf("  --------    ---------      -----------     --------------\n");

    benchmark_property("h", tc->p, tc->t, OH, count);
    benchmark_property("s", tc->p, tc->t, OS, count);
    benchmark_property("v", tc->p, tc->t, OV, count);
    printf("\n");
}

int main(void)
{
    const int count = 1000000;

    const TestCase cases[] = {
        {"Region1: liquid water",   3.0,  300.0 - 273.15},
        {"Region2: superheated",   30.0,  700.0 - 273.15},
        {"Region5: high temp",      0.5, 1500.0 - 273.15},
    };
    const int n_cases = sizeof(cases) / sizeof(cases[0]);

    hr_timer_init();

    printf("\nSEUIF97 C Library Benchmark (%d iterations)\n", count);
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
        printf("[%s]\n", cases[i].label);
        run_benchmark_group(&cases[i], count);
    }

    return EXIT_SUCCESS;
}