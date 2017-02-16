all: demo.exe

clean:
	del demo.exe *.o

demo.exe: demo.o libseuif97.dll
	gcc -o demo demo.o  -L./ -lseuif97
	del *.o

demo.o: demo.c seuif97.h
	gcc -c demo.c 
