/*
 * Benchmark: SEUIF97 C Shared Library Performance Test
    gcc -o speed.exe speed.c -I./include -L./ lseuif97
  
    libseuif97.dll is in the demo-c directory

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

extern double pt(double p, double t, short o_id);

#define OH 4
#define OS 5
#define OV 3

static void benchmark_property(const char *name, double p, double t, short o_id, int count)
{
    volatile double result = 0.0;

    clock_t start = clock();
    for (int i = 0; i < count; i++)
    {
        result = pt(p, t, o_id);
    }
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avg_us = elapsed_ms * 1000.0 / count;

    printf("  %-4s = %12.6f   Total: %8.3f ms   Avg: %8.3f us/call\n",
           name, result, elapsed_ms, avg_us);
}

int main(void)
{
    const int count = 1000000;
    const double p = 30.0;
    const double t = 700.0 - 273.15;

    printf("\nSEUIF97 C Library Benchmark (%d iterations)\n", count);
    printf("  Input:  p = %.1f MPa, t = %.2f C\n\n", p, t);
    printf("  Property      Value          Total Time     Avg Time\n");
    printf("  --------      -----          ----------     --------\n");

    benchmark_property("h", p, t, OH, count);
    benchmark_property("s", p, t, OS, count);
    benchmark_property("v", p, t, OV, count);

    printf("\n");

    return EXIT_SUCCESS;
}
