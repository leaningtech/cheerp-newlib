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

# build the genericjs version of newlib
mkdir build_genericjs
cd build_genericjs
../configure --host=cheerp-genericjs --with-cxx-headers=$PWD/../libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb
make
make install
../build-bc-libs.sh genericjs

cd ..
#build the asmjs/wasm version of newlib
mkdir build_asmjs
cd build_asmjs
../configure --host=cheerp-asmjs --with-cxx-headers=$PWD/../libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb
make
make install
../build-bc-libs.sh asmjs
```

The `./build-bc-libs.sh` step is necessary since I've not been able (yet) to patch libtool to create
LLVM bitcode-base static libraries.

