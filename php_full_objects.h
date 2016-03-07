/** 
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

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

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(full_objects)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(full_objects)
*/

/* Always refer to the globals in your function as FULL_OBJECTS_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define FULL_OBJECTS_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(full_objects, v)

#if defined(ZTS) && defined(COMPILE_DL_FULL_OBJECTS)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_FULL_OBJECTS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
