# the general makefile for each test
# make FILE=test_hs.c
ifneq ($(OS),Windows_NT)
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBFLAGS =-lm
    endif
endif

CC=gcc 
FLAG=-O3 -march=native

INC = -I ../src/common/ \
	-I ../algo/  \
	-I ../src/r1/  \
	-I ../src/r2/	 \
	-I ../src/r3/	 \
    -I ../src/r4/ \
	-I ../src/r5/

SRCS= ../src/algo/*.c \
	  ../src/common/*.c \
	  ../src/r1/*.c \
	  ../src/r2/*.c \
	  ../src/r3/*.c \
	  ../src/r4/*.c \
	  ../src/r5/*.c 	  
      
OUT=../bin/test
 
all: test
	$(OUT)

test: $(SRCS)
	$(CC) -o $(OUT) $(FLAG)  $(SRCS)  $(FILE)  ../unity/unity.c  $(INC)  $(LIBFLAGS) 

