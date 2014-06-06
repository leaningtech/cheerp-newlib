Cheerp: A C++ compiler for the Web
==================================

Please report bugs on launchpad:
https://bugs.launchpad.net/cheerp

Cheerp libc build instructions
------------------------------

Building the cheerp-enabled libc requires having the cheerp compiler
and cheerp-utils headers already installed in /opt/cheerp. It also require
libcxx-cheerp headers.

```
#Please note that newlib is a subdirectory of the cheerp-newlib repository and not the
#repository itself
cd newlib
#cheerp-libcxx is only required to access headers and it not necessary (or possible) to build
#it before cheerp-newlib
git clone <libcxx-cheerp-repo> libcxx
mkdir build
cd build
../configure --host=cheerp --with-cxx-headers=$PWD/../libcxx/include --prefix=/opt/cheerp
make
make install
../build-bc-libs.sh
```

The last step is necessary since I've not been able (yet) to patch libtool to create
LLVM bitcode-base static libraries.
