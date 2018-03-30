/*
   access to the shared libraries through JNA   
   https://github.com/java-native-access/jna

*/
import com.sun.jna.Library;  
import com.sun.jna.Native;  
  
public interface SEUIF97 extends Library{  

    SEUIF97 instance  = (SEUIF97)Native.loadLibrary("libseuif97",SEUIF97.class);    
    
    public double  seupt(double p, double t,int w);  
      
}  
    