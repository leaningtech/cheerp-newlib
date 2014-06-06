#!/bin/bash

#Custom script to create all the needed configure and Makefile.in

NEWLIB_ROOT=$PWD

doDir()
{
	cd $NEWLIB_ROOT/$1
	aclocal -I $NEWLIB_ROOT
	autoconf
	automake
}

doDir .
doDir libc
doDir libc/machine
doDir libc/machine/cheerp
doDir libc/sys
doDir libm
doDir libm/machine
doDir doc
