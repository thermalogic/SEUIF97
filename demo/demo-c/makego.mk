ifeq ($(OS),Windows_NT)
	LDFLAGS= -L../target/release/ -lseuif97  
	EXEDIR=../target/release
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS= -L../target/release -Wl,-rpath,../target/release -lseuif97 -lm
		EXEDIR=./
    endif
endif

all: 
	CGO_LDFLAGS="$(LDFLAGS)" go build -o $(EXEDIR)demo demo.go
	$(EXEDIR)demo