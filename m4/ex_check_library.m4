dnl Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU General Public License v3

AC_DEFUN([EX_CHECK_LIBRARY], [
	AX_CHECK_LIBRARY($1, $2, $3, $4, $5)
	AS_TR_SH($1[_LIBS])=;
	AS_IF([test "x$ax_cv_have_]$1[" = "xyes"], [
			AS_TR_SH($1[_LIBS])=-l$3
	])

	AC_SUBST($1[_LIBS])
])
