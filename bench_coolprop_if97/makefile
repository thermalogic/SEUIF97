
ifeq ($(OS),Windows_NT)
	LIBFLAGS= -L. -lseuif97  
	EXEDIR=./
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBFLAGS= -L. -Wl,-rpath=./  -lseuif97 -lm	
		EXEDIR=./
    endif
endif

CFLAGS= -O3 -march=native -flto -funroll-loops -ffast-math

all: 
	g++ bench_if97.cpp $(CFLAGS) -o$(EXEDIR)bench_if97 $(LIBFLAGS) 
	$(EXEDIR)bench_if97

run: 
	$(EXEDIR)bench_if97

save: 
	g++ bench_if97.cpp $(CFLAGS) -o$(EXEDIR)bench_if97 $(LIBFLAGS) 
	$(EXEDIR)bench_if97 > benchmark_results.txt

clean:
	rm -f $(EXEDIR)bench_if97 benchmark_results.txt