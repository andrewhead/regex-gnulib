# pty_h.m4 serial 4
dnl Copyright (C) 2009, 2010 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

# gl_PTY
# ------
# Make sure that pty.h provides forkpty, or sets up a replacement header.
AC_DEFUN_ONCE([gl_PTY],
[
  AC_REQUIRE([gl_PTY_H_DEFAULTS])

  # Make sure that pty.h provides forkpty, or setup the replacement.
  AC_CHECK_HEADERS_ONCE([pty.h])
  if test $ac_cv_header_pty_h != yes; then
    HAVE_PTY_H=0
    AC_CHECK_HEADERS([util.h libutil.h])
    if test $ac_cv_header_util_h = yes; then
      HAVE_UTIL_H=1
    fi
    if test $ac_cv_header_libutil_h = yes; then
      HAVE_LIBUTIL_H=1
    fi
  else # Have <pty.h>, assume forkpty is declared there.
    HAVE_PTY_H=1
  fi
  AC_SUBST([HAVE_PTY_H])
  dnl <pty.h> is always overridden, because of GNULIB_POSIXCHECK.
  gl_CHECK_NEXT_HEADERS([pty.h])

  dnl Check for declarations of anything we want to poison if the
  dnl corresponding gnulib module is not in use.
  gl_WARN_ON_USE_PREPARE([[
#if HAVE_PTY_H
# include <pty.h>
#endif
#if HAVE_UTIL_H
# include <util.h>
#endif
#if HAVE_LIBUTIL_H
# include <libutil.h>
#endif
    ]], [forkpty openpty])
])

AC_DEFUN([gl_PTY_MODULE_INDICATOR],
[
  dnl Use AC_REQUIRE here, so that the default settings are expanded once only.
  AC_REQUIRE([gl_PTY_H_DEFAULTS])
  GNULIB_[]m4_translit([$1],[abcdefghijklmnopqrstuvwxyz./-],[ABCDEFGHIJKLMNOPQRSTUVWXYZ___])=1
])

AC_DEFUN([gl_PTY_H_DEFAULTS],
[
  GNULIB_FORKPTY=0;     AC_SUBST([GNULIB_FORKPTY])
  GNULIB_OPENPTY=0;     AC_SUBST([GNULIB_OPENPTY])
  dnl Assume proper GNU behavior unless another module says otherwise.
  HAVE_UTIL_H=0;        AC_SUBST([HAVE_UTIL_H])
  HAVE_LIBUTIL_H=0;     AC_SUBST([HAVE_LIBUTIL_H])
  REPLACE_FORKPTY=0;    AC_SUBST([REPLACE_FORKPTY])
  REPLACE_OPENPTY=0;    AC_SUBST([REPLACE_OPENPTY])
])