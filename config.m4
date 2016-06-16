dnl $Id$
dnl config.m4 for extension full_objects


PHP_ARG_ENABLE(oop, whether to enable full oop support,
[  --enable-oop           Enable full oop support])

if test "$PHP_OOP" != "no"; then
  PHP_NEW_EXTENSION(oop,
    oop.c \
    register.c \
    handlers/object.c \
    handlers/string.c \
    handlers/object_interface.c \
    , $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
