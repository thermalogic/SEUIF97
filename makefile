LIBDIR=./bin/
ifeq ($(OS),Windows_NT)
    LIBNAME =$(LIBDIR)libseuif97.dll 
	LIBFLAGES=-static-libstdc++ -static-libgcc -static -Wl,--add-stdcall-alias,--output-def=$(LIBDIR)libseuif97.def,-out-implib=$(LIBDIR)libseuif97.lib
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBNAME =$(LIBDIR)libseuif97.so
    endif
endif

CFLAGS=-O3

# __stdcall for Windows VBA X64
#CFLAGS=-O3 -DBUILD_DLL
# __stdcall for Windows VBA X86
#CFLAGS=-O3 -DBUILD_DLL -m32

CC=gcc

INC =-I ./src/common \
	 -I ./src/algo \
	 -I ./src/r1 \
	 -I ./src/r2 \
	 -I ./src/r3 \
	 -I ./src/r4 \
	 -I ./src/r5 

SRCS= ./src/algo/*.c \
	  ./src/common/*.c \
	  ./src/r1/*.c \
	  ./src/r2/*.c \
	  ./src/r3/*.c \
	  ./src/r4/*.c \
	  ./src/r5/*.c 	

all: $(LIBNAME)

$(LIBNAME): $(SRCS) 
	$(CC) -shared -o $@ -fPIC $(CFLAGS) $^  $(INC) $(LIBFLAGES)

tests:
	$(MAKE) -C ./test/ FILE=test_hs.c
	$(MAKE) -C ./test/ FILE=test_hxsx.c
	$(MAKE) -C ./test/ FILE=test_ph.c
	$(MAKE) -C ./test/ FILE=test_ps.c
	$(MAKE) -C ./test/ FILE=test_pv.c
	$(MAKE) -C ./test/ FILE=test_pt.c
	$(MAKE) -C ./test/ FILE=test_th.c
	$(MAKE) -C ./test/ FILE=test_ts.c
	$(MAKE) -C ./test/ FILE=test_tv.c
	
	
	

 