Name: cheerp-newlib
Version: 2.0
Release:        1%{?dist}
Summary: A C++ compiler for the Web, C library implementation

License:  GPLv2
URL: https://leaningtech.com/cheerp
Source0: %{NAME}_%{VERSION}.orig.tar.gz
Source1: %{NAME}_%{VERSION}.orig-libcxx.tar.gz

BuildRequires: autoconf automake libtool make cheerp-llvm-clang = %{VERSION} cheerp-utils = %{VERSION}
Requires: cheerp-llvm-clang = %{VERSION} cheerp-utils = %{VERSION}

%description
Cheerp is a tool to bring C++ programming to the Web. It can generate a seamless
combination of JavaScript, WebAssembly and Asm.js from a single C++ codebase.

%define debug_package %{nil}

%prep
%autosetup
%setup -T -D -a 1

cd newlib

mkdir build_genericjs
cd build_genericjs
../configure --host=cheerp-genericjs --with-cxx-headers=$PWD/../../libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb --enable-newlib-nano-formatted-io

cd ..
mkdir build_asmjs
cd build_asmjs
../configure --host=cheerp-asmjs --with-cxx-headers=$PWD/../../libcxx/include --prefix=/opt/cheerp --enable-newlib-io-long-long --enable-newlib-iconv --enable-newlib-iconv-encodings=utf-16,utf-8,ucs_2 --enable-newlib-mb --enable-newlib-nano-formatted-io

%build
%make_build -C newlib/build_genericjs
%make_build -C newlib/build_asmjs

%install
%make_install -C newlib/build_genericjs
%make_install -C newlib/build_asmjs
cd newlib/build_genericjs
CHEERP_INSTALL_PREFIX=%{buildroot}/opt/cheerp CHEERP_PREFIX=/opt/cheerp ../build-bc-libs.sh genericjs
cd ../build_asmjs
CHEERP_INSTALL_PREFIX=%{buildroot}/opt/cheerp CHEERP_PREFIX=/opt/cheerp ../build-bc-libs.sh asmjs
rm %{buildroot}/opt/cheerp/lib/libc.a
rm %{buildroot}/opt/cheerp/lib/libm.a
rm %{buildroot}/opt/cheerp/lib/libg.a
rm -r %{buildroot}/opt/cheerp/share

%clean
rm -rf $RPM_BUILD_ROOT

%files
/opt/cheerp/include/
/opt/cheerp/lib/genericjs/libm.bc
/opt/cheerp/lib/genericjs/libc.bc
/opt/cheerp/lib/asmjs/libm.bc
/opt/cheerp/lib/asmjs/libc.bc

%changelog
* Tue Dec 10 2019 Yuri Iozzelli <yuri@leaningtech.com>
- First RPM version
