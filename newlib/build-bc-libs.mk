%.bc: %.a
	mkdir -p build_bc_tmp
	cd build_bc_tmp; ar x ../$^; /opt/cheerp/bin/llvm-link *.o -o ../$@
	rm -rf build_bc_tmp

all: build/libc/libc.bc build/libm/libm.bc
