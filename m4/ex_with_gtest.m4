dnl Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU General Public License v3

AC_DEFUN([EX_WITH_GTEST], [
	AC_ARG_WITH([gtest],
		[AS_HELP_STRING([--with-gtest], [support for google testing framework, required for some tests])],
		[with_gtest=$withval],
		[with_gtest=check]
	)

	AS_IF([test "x$with_gtest" != xno],
		[
			test "x$with_gtest" != xyes -a "x$with_gtest" != xcheck && GTEST_LDFLAGS="-L$with_gtest/lib" && GTEST_CPPFLAGS="-I$with_gtest/include"
			LDFLAGS_save=$LDFLAGS
			CPPFLAGS_save=$CPPFLAGS
			LDFLAGS="$LDFLAGS $GTEST_LDFLAGS"
			CPPFLAGS="$CPPFLAGS $GTEST_CPPFLAGS"
			EX_CHECK_LIBRARY([GTEST], ["gtest/gtest.h"], [gtest], [], [
				AS_IF([test "x$with_gtest" != xcheck], [
					AC_MSG_FAILURE(["--with-gtest: gtest not found"])
				])
			])
			AC_CHECK_LIB([gtest_main], [main], [
					GTEST_LIBS="-lgtest_main $GTEST_LIBS"
				], [AS_IF([test "x$with_gtest" != xcheck], [
					AC_MSG_FAILURE(["--with-gtest: gtest_main not found"])
				])
			])
			LDFLAGS=$LDFLAGS_save
			CPPFLAGS=$CPPFLAGS_save
		]
	)
	AM_CONDITIONAL([GTEST], [test "x$GTEST_LIBS" != x])
])
