# the general makefile for each test
# make FILE=bench_if97.c
ifneq ($(OS),Windows_NT)
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBFLAGS =-lm
    endif
endif

CC=g++ 

CFLAG=-O3 -march=native

SRCS= ../src/algo/*.c \
	  ../src/common/*.c \
	  ../src/r1/*.c \
	  ../src/r2/*.c \
	  ../src/r3/*.c \
	  ../src/r4/*.c \
	  ../src/r5/*.c 	  
      
OUT=../bin/bench_if97
 
all: test
	$(OUT)

test: $(SRCS)
	$(CC) -o $(OUT) $(CFLAG)  $(SRCS)  c_bench_if97.cpp  $(INC)  $(LIBFLAGS) 

