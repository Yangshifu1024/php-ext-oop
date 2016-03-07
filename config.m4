dnl $Id$
dnl config.m4 for extension full_objects

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(full_objects, for full_objects support,
dnl Make sure that the comment is aligned:
dnl [  --with-full_objects             Include full_objects support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(full_objects, whether to enable full_objects support,
dnl Make sure that the comment is aligned:
dnl [  --enable-full_objects           Enable full_objects support])

if test "$PHP_FULL_OBJECTS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-full_objects -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/full_objects.h"  # you most likely want to change this
  dnl if test -r $PHP_FULL_OBJECTS/$SEARCH_FOR; then # path given as parameter
  dnl   FULL_OBJECTS_DIR=$PHP_FULL_OBJECTS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for full_objects files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FULL_OBJECTS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FULL_OBJECTS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the full_objects distribution])
  dnl fi

  dnl # --with-full_objects -> add include path
  dnl PHP_ADD_INCLUDE($FULL_OBJECTS_DIR/include)

  dnl # --with-full_objects -> check for lib and symbol presence
  dnl LIBNAME=full_objects # you may want to change this
  dnl LIBSYMBOL=full_objects # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FULL_OBJECTS_DIR/$PHP_LIBDIR, FULL_OBJECTS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FULL_OBJECTSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong full_objects lib version or lib not found])
  dnl ],[
  dnl   -L$FULL_OBJECTS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FULL_OBJECTS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(full_objects, full_objects.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
