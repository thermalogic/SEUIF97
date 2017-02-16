all: demo

clean:
	rm demo *.o

demo: demo.o libseuif97.so
	gcc -o demo demo.o -lseuif97
	rm *.o

demo.o: demo.c seuif97.h
	gcc -c demo.c 
