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
        public static extern double pt(double p, double t, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double ph(double p, double h, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double ps(double p, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double pv(double p, double v, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double th(double t, double h, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double ts(double t, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double tv(double t, double v, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double hs(double h, double s, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double px(double p, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double tx(double t, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double hx(double h, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double sx(double s, double x, int wid);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
       
        public static extern double ishd(double pi, double ti, double pe);
        [DllImport("libseuif97", CallingConvention = CallingConvention.StdCall)]
        public static extern double ief(double pi, double ti, double pe, double te);

    }
}

