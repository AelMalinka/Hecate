AC_DEFUN([EX_WITH_GTEST], [
	AC_ARG_WITH([gtest],
		[AS_HELP_STRING([--with-gtest], [support for google testing framework, required for tests])],
		[with_gtest=$withval],
		[with_gtest=check]
	)

	GTEST=
	AS_IF([test "x$with_gtest" != xno],
		[
			LDFLAGS="${LDFLAGS} -L$with_gtest"
			AC_CHECK_LIB([gtest], [main], [
					AC_SUBST([GTEST], ["-lgtest -lgtest_main"])
				],
				[if test "x$with_gtest" != xcheck; then
					AC_MSG_FAILURE(["--with-gtest: gtest not found"])
				fi]
			)
		]
	)
	AM_CONDITIONAL([GTEST], [test "x$GTEST" != ""])
])
