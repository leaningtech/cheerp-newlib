## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

noinst_LIBRARIES = lib.a

AM_CCASFLAGS = $(INCLUDES)

lib_a_SOURCES = divti3.c malloc.c cheerpstdio.c clientbridge.cpp

lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)
lib_a_CXXFLAGS = $(AM_CXXFLAGS) $(NEWLIB_CXXFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host

