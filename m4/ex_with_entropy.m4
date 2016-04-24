# Copyright 2013 (c) Michael Thomas <aelmalinka@gmail.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_ENTROPY], [
	AC_ARG_WITH([entropy],
		[AS_HELP_STRING([--with-entropy], [location to look for libentropy.so])],
		[with_entropy=$withval],
		[with_entropy=check]
	)

	ENTROPY_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_entropy" != xcheck], [AS_IF([test "x$with_entropy" != xyes], [
		LDFLAGS="-L${with_entropy}/lib"
	])])
	AC_CHECK_LIB([entropy], [main], [
			AC_SUBST([ENTROPY_LIBS], ["-lentropy"])
			AC_SUBST([ENTROPY_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-entropy: entropy not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	ENTROPY_CPPFLAGS=
	CPPFLAGS_save="$CPPFLAGS"
	test "x$with_entropy" != xcheck && CPPFLAGS="-I${with_entropy}/include"
	AC_CHECK_HEADER([Entropy/Exception.hh], [
			AC_SUBST([ENTROPY_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-entropy: Entropy/Exception.hh not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
