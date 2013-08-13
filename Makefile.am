ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libHecate.la

libHecate_la_SOURCES = src/main.cc src/Stat.hh src/Stat.impl.hh

check_PROGRAMS = Stat
Stat_SOURCES = test/Stat.cc
Stat_CXXFLAGS = -I$(srcdir)/src $(AM_CXXFLAGS)
