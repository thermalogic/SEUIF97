// cgo LDFLAGS:
//    Linux:  -L/usr/lib/ -lseuif97 -lm
//    Windows: -LC:/Windows/system -llibseuif97
// go build -o demo.exe demo.go
package main
/*
#cgo LDFLAGS: -LC:/Windows/system -llibseuif97
#include "seuif97.h"
*/
import "C"
import "fmt"

func main() {
	p:=16.14
	t:=512.0
	oid:=4
	h := C.pt(C.double(p),C.double(t),C.int(oid))
	fmt.Printf("(p,t)=(%.2f, %.2f), h=%.2f\n",p,t,float64(h))
}
