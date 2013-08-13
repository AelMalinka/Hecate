AC_INIT([Entropy Hecate], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AM_PROG_AR
LT_INIT
AC_LANG_PUSH([C++])
AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -Werror -pedantic-errors], [CXXFLAGS])
AC_CONFIG_HEADERS([config.h])
AX_CXX_COMPILE_STDCXX_11([noext])
AC_LANG_POP([C++])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
