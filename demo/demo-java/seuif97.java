/*
The interface of libseuif97 through JNA 
    https://github.com/java-native-access/jna

Java Native Access (JNA) 
  ./jna.jar

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2019.01.07

*/
import com.sun.jna.Native;
import com.sun.jna.Library;

public interface seuif97 extends Library { 
  
    seuif97 INSTANCE = (seuif97)Native.load("libseuif97",  seuif97.class);

    public double seupt(double p, double t, int propertyID);  
    public double seuph(double p, double h, int propertyID);
    public double seups(double p, double s, int propertyID);
    public double seupv(double p, double v, int propertyID);

    public double seuth(double t, double s, int propertyID);
    public double seuts(double t, double s, int propertyID);
    public double seutv(double t, double v, int propertyID);
    
    public double seuhs(double h, double s, int propertyID);
    
    public double seupx(double p, double x, int propertyID);
    public double seutx(double t, double x, int propertyID);

    public double seuishd(double pi, double ti, double pe);
    public double seuief(double pi, double ti, double pe, double te);
}