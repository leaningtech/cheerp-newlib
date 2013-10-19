%.bc: %.a
	mkdir -p build_bc_tmp
	cd build_bc_tmp; ar x $^; /opt/duetto/bin/llvm-link *.o -o $@
	rm -rf build_bc_tmp

all: $(CURDIR)/$(DESTDIR)/opt/duetto/lib/libc.bc $(CURDIR)/$(DESTDIR)/opt/duetto/lib/libm.bc
