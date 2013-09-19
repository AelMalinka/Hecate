# Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Lesser General Public License v3

AC_PREREQ([2.53])
m4_pattern_forbid([^AX_])
m4_pattern_forbid([^EX_])

AC_INIT([Hecate], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_TESTDIR([test])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects dist-xz no-dist-gzip])
LT_INIT

AC_PROG_CXX
AC_LANG_PUSH([C++])

AC_CHECK_HEADERS(
	[boost/operators.hpp],
	[],
	[AC_MSG_FAILURE([Boost is required])]
)

EX_WITH_GTEST
EX_FLAGS

AC_LANG_POP([C++])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile atlocal:test/atlocal.in])
AC_OUTPUT
