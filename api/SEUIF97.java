/*
   access to the shared libraries through JNA 
    https://github.com/java-native-access/jna

*/
import com.sun.jna.Library;  
import com.sun.jna.Native;  
  
public interface SEUIF97 extends Library{  

    SEUIF97 instance  = (SEUIF97)Native.loadLibrary("libseuif97",SEUIF97.class);    
    
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
    