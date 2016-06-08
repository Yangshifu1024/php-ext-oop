/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"

#ifndef PHP_OOP_H
#define PHP_OOP_H

extern zend_module_entry oop_module_entry;
#define phpext_oop_ptr &oop_module_entry

#define PHP_OOP_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_OOP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_OOP_API __attribute__ ((visibility("default")))
#else
#	define PHP_OOP_API
#endif

#define OOP_MODULE_STARTUP(module) ZEND_MODULE_STARTUP_N(oop_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define OOP_MODULE_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(oop_##module)
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

ZEND_BEGIN_MODULE_GLOBALS(oop)
    zend_class_entry *oop_handlers[MAX_HANDLERS];
    zend_bool allow_override;
ZEND_END_MODULE_GLOBALS(oop)

#define OOP_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(oop, v)

#if defined(ZTS) && defined(COMPILE_DL_OOP)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

extern ZEND_DECLARE_MODULE_GLOBALS(oop);

#endif	/* PHP_OOP_H */

