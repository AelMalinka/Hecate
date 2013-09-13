AC_DEFUN([EX_FLAGS], [
	AX_CXX_COMPILE_STDCXX_11([noext])
	AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -Werror -pedantic-errors], [CXXFLAGS])

	AC_ARG_ENABLE([debug],
		[AS_HELP_STRING([--enable-debug],
			[adjust flags to enable debug settings]
		)],
		[enable_debug=$enableval],
		[enable_debug=no]
	)
	AS_IF([test "x$enable_debug" != "x$no"],
		[AX_APPEND_COMPILE_FLAGS([-g3 -O0])],
		[]
	)
])
