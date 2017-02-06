all: SEUIF97Demo.exe

clean:
	del SEUIF97Demo.exe *.o

SEUIF97Demo.exe: SEUIF97Demo.o libseuif97.dll
	gcc -o SEUIF97Demo SEUIF97Demo.o  -L./ -llibseuif97
	del *.o

SEUIF97Demo.o: SEUIF97Demo.c seuif97.h
	gcc -c SEUIF97Demo.c 
