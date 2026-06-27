// bench/bench_iapws.cpp
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"
#include <cmath>

// 通用接口
extern "C" double pt(double p, double t, int o_id);
extern "C" double ph(double p, double h, int o_id);
extern "C" double ps(double p, double s, int o_id);
extern "C" double hs(double h, double s, int o_id);
extern "C" double tv(double t, double v, int o_id);

// Region 1 backward equations
extern "C" double ph2T_reg1(double p, double h);
extern "C" double ps2T_reg1(double p, double s);
extern "C" double hs2p_reg1(double h, double s);

// Region 2 backward equations
extern "C" double ph2T_reg2a(double p, double h);
extern "C" double ph2T_reg2b(double p, double h);
extern "C" double ph2T_reg2c(double p, double h);
extern "C" double ps2T_reg2a(double p, double s);
extern "C" double ps2T_reg2b(double p, double s);
extern "C" double ps2T_reg2c(double p, double s);
extern "C" double hs2p_reg2a(double h, double s);
extern "C" double hs2p_reg2b(double h, double s);
extern "C" double hs2p_reg2c(double h, double s);

typedef struct {
    const char *label;
    double p;
    double t;
} TestCase;

int main() {
    const TestCase cases[] = {
        {"Region1: liquid water",   3.0,  300.0 - 273.15},
        {"Region2: superheated",   30.0,  700.0 - 273.15},
    };
    const int n_cases = sizeof(cases) / sizeof(cases[0]);

    // (p,t) -> h , s
    double h_vals[3], s_vals[3];
    for (int i = 0; i < n_cases; i++) {
        h_vals[i] = pt(cases[i].p, cases[i].t, 4);  // OH = 4
        s_vals[i] = pt(cases[i].p, cases[i].t, 5);  // OS = 5
    }

    // Region 1: p=3.0, h/s  cases[0]
    double p1 = cases[0].p, h1 = h_vals[0], s1 = s_vals[0];
    // Region 2: p=30.0, h/s cases[1]
    double p2 = cases[1].p, h2 = h_vals[1], s2 = s_vals[1];

    ankerl::nanobench::Bench()
        .title("IAPWS-IF97 Backward Equations")
        .warmup(100)
        .minEpochIterations(100000)

        // Region 1 (p=3.0 MPa, liquid water)
        .run("r1 ph2T_reg1", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ph2T_reg1(p1, h1));
        })
        .run("r1 ps2T_reg1", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ps2T_reg1(p1, s1));
        })

       .run("r1 hs2p_reg1", [&]() {
           ankerl::nanobench::doNotOptimizeAway(hs2p_reg1(h1, s1));
        })

        // Region 2 (p=30.0 MPa, superheated)
        .run("r2a ph2T_reg2a", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ph2T_reg2a(p2, h2));
        })
        .run("r2b ph2T_reg2b", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ph2T_reg2b(p2, h2));
        })
        .run("r2c ph2T_reg2c", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ph2T_reg2c(p2, h2));
        })
        .run("r2a ps2T_reg2a", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ps2T_reg2a(p2, s2));
        })
        .run("r2b ps2T_reg2b", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ps2T_reg2b(p2, s2));
        })
        .run("r2c ps2T_reg2c", [&]() {
            ankerl::nanobench::doNotOptimizeAway(ps2T_reg2c(p2, s2));
        })

        .run("r2a hs2p_reg2a", [&]() {
            ankerl::nanobench::doNotOptimizeAway(hs2p_reg2a(h2, s2));
        })
        
        .run("r2a hs2p_reg2b", [&]() {
            ankerl::nanobench::doNotOptimizeAway(hs2p_reg2b(h2, s2));
        })
        
        .run("r2a hs2p_reg2c", [&]() {
            ankerl::nanobench::doNotOptimizeAway(hs2p_reg2c(h2, s2));
        });
    
    return 0;
}