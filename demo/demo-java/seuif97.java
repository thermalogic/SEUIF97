/*
The interface of libseuif97 through JNA 
    https://github.com/java-native-access/jna

Java Native Access (JNA) 
  ./jna.jar

SEUIF97 Library:
 
  1 Windows: C:/Windows/system/libseuif97.dll
  2 Linux:  /usr/lib/libseuif97.so

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2019.01.07

*/
import com.sun.jna.Native;
import com.sun.jna.Library;

public interface seuif97 extends Library { 
  
    seuif97 INSTANCE = (seuif97)Native.load("libseuif97",  seuif97.class);

    public double pt(double p, double t, int o_id);  
    public double ph(double p, double h, int o_id);
    public double ps(double p, double s, int o_id);
    public double pv(double p, double v, int o_id);

    public double th(double t, double s, int o_id);
    public double ts(double t, double s, int o_id);
    public double tv(double t, double v, int o_id);
    
    public double hs(double h, double s, int o_id);
    
    public double px(double p, double x, int o_id);
    public double tx(double t, double x, int o_id);

    public double hx(double h, double x, int o_id);
    public double sx(double s, double x, int o_id);

    public double ishd(double pi, double ti, double pe);
    public double ief(double pi, double ti, double pe, double te);
}