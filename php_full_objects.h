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

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(full_objects)
    zend_array *oop_handlers;
    zend_bool allow_override;
ZEND_END_MODULE_GLOBALS(full_objects)

#define FULL_OBJECTS_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(full_objects, v)

#if defined(ZTS) && defined(COMPILE_DL_FULL_OBJECTS)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_FULL_OBJECTS_H */

