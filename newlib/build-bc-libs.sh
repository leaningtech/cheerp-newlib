#!/bin/sh

build_lib(){
	mkdir -p build-bc-$1
	cd build-bc-$1
	ar x ../$1/$1.a
	/opt/cheerp/bin/llvm-link *.o -o $1.bc
	cp -v $1.bc /opt/cheerp/lib
	cd ..
	rm -rf build-bc-$1
}

build_lib libc
build_lib libm
