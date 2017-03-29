all: demo

clean:
	rm demo *.o

demo: demo.o 
	gcc -o demo demo.o -L/usr/lib/ -lseuif97
	rm *.o

demo.o: demo.c seuif97.h
	gcc -c demo.c 
