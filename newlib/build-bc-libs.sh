#!/bin/sh

if [ -z $CHEERP_PREFIX ]; then
	CHEERP_PREFIX=/opt/cheerp
fi

if [ "$1" != "genericjs" ] && [ "$1" != "asmjs" ]; then
	echo "first argument must be 'genericjs' or 'asmjs'"
	exit 1
fi

build_lib(){
	mkdir -p build-bc-$1
	cd build-bc-$1
	ar x ../$1/$1.a
	$CHEERP_PREFIX/bin/llvm-link *.o -o $1.bc
	mkdir -p $CHEERP_PREFIX/lib/$2
	cp -v $1.bc $CHEERP_PREFIX/lib/$2/$1.bc
	cd ..
	rm -rf build-bc-$1
}

build_lib libc $1
build_lib libm $1
