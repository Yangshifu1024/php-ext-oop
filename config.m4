dnl $Id$
dnl config.m4 for extension full_objects


PHP_ARG_ENABLE(full_objects, whether to enable full_objects support,
[  --enable-full_objects           Enable full_objects support])

if test "$PHP_FULL_OBJECTS" != "no"; then
  PHP_NEW_EXTENSION(full_objects, full_objects.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
