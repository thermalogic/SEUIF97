/*
 
 SEUIF97 Library:
 
  1 Windows: C:/Windows/system/libseuif97.dll
  2 Linux:  /usr/lib/libseuif97.so
  3 The Module: ./seuif97.java

Java Native Access (JNA) 
  ./jna.jar

Build:

 javac -cp jna.jar seuif97.java demoseuif97.java
 java -cp .;jna.jar demoseuif97

License: this code is in the public domain

Author:   Cheng Maohua
Email:    cmh@seu.edu.cn

Last modified: 2019.01.07

*/
public class demoseuif97 {

    public static void main(String[] args){
        double p=16.0;
        double t=540.0;
        double h;
        h=seuif97.INSTANCE.seupt(p,t,4);
        System.out.printf("(p,t)->h: (%.1f %.1f) h: %.2f\n",p,t,h);
        t=seuif97.INSTANCE.seuph(p,h,1);
        System.out.printf("(p,h)->t: (%.1f %.2f) t: %.2f ",p,h,t);
   }
}