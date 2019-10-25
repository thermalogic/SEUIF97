/*
The C# API of libseuif97.dll

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2019.01.05
*/

using System;
using System.Runtime.InteropServices;

namespace seuif97
{
    public class Seuif97
    {
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seupt(double p, double t, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuph(double p, double h, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seups(double p, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seupv(double p, double v, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuth(double t, double h, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuts(double t, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seutv(double t, double v, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuhs(double t, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seupx(double p, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seutx(double t, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuishd(double pi, double ti, double pe);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double seuief(double pi, double ti, double pe, double te);

    }
}

