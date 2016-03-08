/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"

#ifndef PHP_FULL_OBJECTS_H
#define PHP_FULL_OBJECTS_H

extern zend_module_entry full_objects_module_entry;
#define phpext_full_objects_ptr &full_objects_module_entry

#define PHP_FULL_OBJECTS_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_FULL_OBJECTS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_FULL_OBJECTS_API __attribute__ ((visibility("default")))
#else
#	define PHP_FULL_OBJECTS_API
#endif

#define FULLOBJECTS_MODULE_STARTUP(module) ZEND_MODULE_STARTUP_N(full_objects_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define FULLOBJECTS_MODULE_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(full_objects_##module)
#define MAX_HANDLERS IS_REFERENCE

/* Copy from http://lxr.php.net/xref/PHP_7_0/Zend/zend_execute.c#107 */
# define FREE_OP(should_free) \
    if (should_free) { \
        zval_ptr_dtor_nogc(should_free); \
    }
# define FREE_OP_IF_VAR(should_free) FREE_OP(should_free)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(full_objects)
    zend_class_entry *oop_handlers[MAX_HANDLERS];
    zend_bool allow_override;
ZEND_END_MODULE_GLOBALS(full_objects)

#define FULL_OBJECTS_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(full_objects, v)

#if defined(ZTS) && defined(COMPILE_DL_FULL_OBJECTS)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

extern ZEND_DECLARE_MODULE_GLOBALS(full_objects);

#endif	/* PHP_FULL_OBJECTS_H */

