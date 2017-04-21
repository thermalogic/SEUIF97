all: demo.exe

clean:
	del demo.exe *.o

demo.exe: demo.o 
	gcc -o demo demo.o -LC:/Windows/system/ -lseuif97
	del *.o

demo.o: demo.c seuif97.h
	gcc -c demo.c 
