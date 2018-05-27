dnl Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU General Public License v3

AC_DEFUN([EX_BASE_FLAGS], [
	AC_LANG_PUSH([C])
	AX_APPEND_COMPILE_FLAGS([-std=c11], [CFLAGS])
	AC_LANG_POP([C])

	AC_LANG_PUSH([C++])
	AX_APPEND_COMPILE_FLAGS([-std=c++17], [CXXFLAGS])
	AC_LANG_POP([C++])
])

AC_DEFUN([EX_FLAGS], [
	AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -pedantic])
	AC_ARG_ENABLE([debug],
		[AS_HELP_STRING([--enable-debug],
			[adjust flags to enable debug settings]
		)],
		[enable_debug=$enableval],
		[enable_debug=no]
	)
	AC_ARG_ENABLE([profiling],
		[AS_HELP_STRING([--enable-profiling],
			[adjust flags to enable code profiling]
		)],
		[enable_profiling=$enableval],
		[enable_profiling=no]
	)
	AS_IF([test "x$enable_debug" != "xno"],
		[AX_APPEND_COMPILE_FLAGS([-g3 -Og -DDEBUG])],
		[]
	)
	AS_IF([test "x$enable_profiling" != "xno"],
		[AX_APPEND_COMPILE_FLAGS([-pg])],
		[]
	)
])
