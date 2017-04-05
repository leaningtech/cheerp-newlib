%.bc: %.a
	mkdir -p build_bc_tmp
	cd build_bc_tmp; ar x ../$^; /opt/cheerp/bin/llvm-link *.o -o ../$@
	rm -rf build_bc_tmp

all: libc/libc.bc libm/libm.bc
