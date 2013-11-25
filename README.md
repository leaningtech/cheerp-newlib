Duetto: A C++ compiler for the Web
==================================

Please report bugs on launchpad:
https://bugs.launchpad.net/duetto

Duetto libc build instructions
------------------------------

Building the duetto-enabled libc requires having the duetto compiler
already installed in /opt/duetto. It also require duetto-libcxx and duetto-utils headers.

```
#Please note that newlib is a subdirectory of the duetto-newlib repository and not the
#repository itself
cd newlib
#duetto-libcxx and duetto-utils are only required to access headers and it not necessary (or possible) to build
#them before duetto-newlib
git clone <duetto-libcxx-repo> libcxx
git clone <duetto-utils-repo> duetto-utils
mkdir build
cd build
../configure --host=duetto --with-cxx-headers=$PWD/../libcxx/include:$PWD/../duetto-utils/include --prefix=/opt/duetto
make
make install
../build-bc-libs.sh
```

The last step is necessary since I've not been able (yet) to patch libtool to create
LLVM bitcode-base static libraries.
