/*
  >javac -cp jna.jar SEUIF97.java demoseuif97.java
  >java -cp .;jna.jar demoseuif97
*/
public class demoseuif97 {

   //public native static String pirntStr(String msg);//函数声明
   public static void main(String[] args){
        double p=16.0;
        double t=540.0;
        double h;
        h=SEUIF97.instance.seupt(p,t,4);
        System.out.printf("(p,t)->h: (%.1f %.1f) h: %.4f ",p,t,h);
   }
}