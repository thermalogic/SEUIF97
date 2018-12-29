/*
 H-S(Mollier) Diagram of Steam Turbine Expansion using Gnuplot

 4 lines:

    1  Isobar line:p inlet
    2  Isobar line:p outlet
    3  isentropic line:  (p inlet ,t inlet h inlet,s inlet), (p outlet,s inlet)
    4  Expansion line: inlet,outlet

SEUIF97 Library:
    1 Winodws: C:/Windows/system/libseuif97.dll
    2 Linux:  /usr/lib/libseuif97.so
    3 ./seuif97.h

Build:

 Windows：
>g++ -o turbine Turbine_H-S.cpp -LC:/Windows/system/  -lseuif97

Linux：
$g++ -o turbine Turbine_H-S.cpp -L/usr/lib  -lseuif97 -lm

Run:
./turbine

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn
*/

#include <iostream>
#include <iomanip>
#include "seuif97.h"

using namespace std;

struct wmstatus
{
    double p, t, h, s;
};

class Turbine
{
  private:
    double his;

  public:
    wmstatus win, wex;
    double ef;

    Turbine(double pin, double tin, double pex, double tex);
    void analysis(void);
    void output(void);
    void expansionline(void);
};

Turbine::Turbine(double pin, double tin, double pex, double tex)
{
    win.p = pin;
    win.t = tin;
    wex.p = pex;
    wex.t = tex;
}

void Turbine::analysis(void)
{
    ef = seuief(win.p, win.t, wex.p, wex.t);
    his = seuishd(win.p, win.t, wex.p);

    win.h = seupt(win.p, win.t, 4);
    win.s = seupt(win.p, win.t, 5);

    wex.h = seupt(wex.p, wex.t, 4);
    wex.s = seupt(wex.p, wex.t, 5);
};

void Turbine::output(void)
{
    cout << "(Pin,Tin) = (" << win.p << "," << win.t << ")" << endl;
    cout << "(Pex,Tex) = (" << wex.p << "," << wex.t << ")" << endl;
    cout << "The isentropic efficiency = " << setiosflags(ios::fixed) << setprecision(2) << ef << "%" << endl;
};

void Turbine::expansionline(void)
{
    double sdelta = 0.01;

    // 1 Isobar pin
    double s_isopin[2] = {win.s - sdelta, win.s + sdelta};
    double h_isopin[2] = {seups(win.p, s_isopin[0], 4), seups(win.p, s_isopin[1], 4)};

    // 2 Isobar pex
    double s_isopex[2] = {s_isopin[0], wex.s + sdelta};
    double h_isopex[2] = {seups(wex.p, s_isopex[0], 4), seups(wex.p, s_isopex[1], 4)};

    // 3 isentropic lines
    double h_isos[2] = {win.h, win.h - his};
    double s_isos[2] = {win.s, win.s};

    // 4 expansion Line
    double h_expL[2] = {win.h, wex.h};
    double s_expL[2] = {win.s, wex.s};

    // plot lines with gnuplot

    FILE *pipe = popen("gnuplot -persist", "w"); // Open a pipe to gnuplot
    if (pipe)                                    // If gnuplot is found
    {
        fprintf(pipe, "set term wx\n");             // set the terminal
        fprintf(pipe, "set termoption enhanced\n"); //  set enhanced text mode
        fprintf(pipe, "set xlabel 's(kJ/(kg.K))'\n");
        fprintf(pipe, "set ylabel 'h(kJ/kg)'\n");
        fprintf(pipe, "set title 'H-S(Mollier) Diagram of Steam Turbine Expansion'\n");
        fprintf(pipe, "set yrange [%lf:%lf]\n", h_isopex[0] - 20, h_isopin[1] + 20);
        fprintf(pipe, "set xrange [%lf:%lf]\n", s_isopex[0] - 0.01, s_isopex[1] + 0.01);

        fprintf(pipe, "set label 'The isentropic efficiency=(h_1-h_2)/(h_1-h_{2s})= %.2f%%' at %lf,%lf left\n", ef, s_isopin[1] + 0.01, h_isopin[1] - 50);

        fprintf(pipe, "plot '-' title '' with line lc rgb 'blue', \
                       '-' title '' with line lc rgb 'blue',\
                       '-' title '' with linespoints lc rgb 'orange',\
                       '-' title 'Expansion Line' with linespoints lc rgb 'red'\n");

        // 1 Isobar line : pin
        for (int i = 0; i < 2; i++)
        {
            fprintf(pipe, "%lf %lf\n", s_isopin[i], h_isopin[i]);
        }
        fprintf(pipe, "e");

        // 2 Isobar line : pex
        fprintf(pipe, "\n"); // draw a new item!
        for (int i = 0; i < 2; i++)
        {
            fprintf(pipe, "%lf %lf\n", s_isopex[i], h_isopex[i]);
        }
        fprintf(pipe, "e");

        // 3 isentropic lines
        fprintf(pipe, "\n");
        for (int i = 0; i < 2; i++)
        {
            fprintf(pipe, "%lf %lf\n", s_isos[i], h_isos[i]);
        }
        fprintf(pipe, "e");

        // 4 Expansion Line
        fprintf(pipe, "\n");
        for (int i = 0; i < 2; i++)
        {
            fprintf(pipe, "%lf %lf\n", s_expL[i], h_expL[i]);
        }
        fprintf(pipe, "e");

        fflush(pipe);
        fprintf(pipe, "exit\n"); // exit gnuplot
        pclose(pipe);            //close pipe
    };                           // end of if
};

int main(void)
{
    double pin = 16.0;
    double tin = 535.0;
    double pex = 3.56;
    double tex = 315.0;
    Turbine tb1 = Turbine(pin, tin, pex, tex);
    tb1.analysis();
    tb1.output();
    tb1.expansionline();
    return 0;
}
