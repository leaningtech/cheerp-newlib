Cheerp: A C++ compiler for the Web
==================================

Please report bugs on GitHub:
https://github.com/leaningtech/cheerp-meta/issues

Cheerp libc build instructions
------------------------------

Building the cheerp-enabled libc requires having the cheerp compiler
and cheerp-utils headers already installed in /opt/cheerp. It also requires
libcxx-cheerp headers. Please see https://docs.leaningtech.com/cheerp/Linux-build-instructions for instructions on how to build the whole suite.

```
#Please note that newlib is a subdirectory of the cheerp-newlib repository and not the
#repository itself
cd newlib
#cheerp-compiler/libcxx is only required to access headers, it not necessary (or possible) to build
#it before cheerp-newlib
git clone <cheerp-compiler repo> cheerp-compiler

# build the genericjs version of newlib
mkdir build_genericjs
cd build_genericjs
../configure --host=cheerp-genericjs --with-cxx-headers=$PWD/../../cheerp-compiler/libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb --enable-newlib-nano-formatted-io
make
make install
../build-bc-libs.sh genericjs

cd ..
#build the asmjs/wasm version of newlib
mkdir build_asmjs
cd build_asmjs
../configure --host=cheerp-asmjs --with-cxx-headers=$PWD/../../cheerp-compiler/libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb --enable-newlib-nano-formatted-io
make
make install
../build-bc-libs.sh asmjs
```

The `./build-bc-libs.sh` step is necessary since I've not been able (yet) to patch libtool to create
LLVM bitcode-base static libraries.

