/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_full_objects.h"

ZEND_DECLARE_MODULE_GLOBALS(full_objects)

/* True global resources - no need for thread safety here */
static int le_full_objects;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("full_objects.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_full_objects_globals, full_objects_globals)
    STD_PHP_INI_ENTRY("full_objects.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_full_objects_globals, full_objects_globals)
PHP_INI_END()
*/
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(register_handler_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, "basicType")
    ZEND_ARG_INFO(0, "oopHandler")
ZEND_END_ARG_INFO()


/* {{{ proto void register_full_objects_handler(string $arg, class $ce)
   Register a handler for basic type */
PHP_FUNCTION(register_full_objects_handler)
{
    zend_string *type = NULL;
    zend_class_entry *ce = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(type)
        Z_PARAM_CLASS_EX(ce, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_STR(ce->name);
    // TODO:
}
/* }}} */


/* {{{ php_full_objects_init_globals
 */
static void php_full_objects_init_globals(zend_full_objects_globals *full_objects_globals)
{
    zend_hash_init(full_objects_globals->oop_handlers, 8, NULL, NULL, 0);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(full_objects)
{
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(full_objects)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(full_objects)
{
#if defined(COMPILE_DL_FULL_OBJECTS) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(full_objects)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(full_objects)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "full_objects support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ full_objects_functions[]
 *
 * Every user visible function must have an entry in full_objects_functions[].
 */
const zend_function_entry full_objects_functions[] = {
    PHP_FE(register_full_objects_handler,	register_handler_arginfo)
    PHP_FE_END	/* Must be the last line in full_objects_functions[] */
};
/* }}} */

/* {{{ full_objects_module_entry
 */
zend_module_entry full_objects_module_entry = {
    STANDARD_MODULE_HEADER,
    "full_objects",
    full_objects_functions,
    PHP_MINIT(full_objects),
    PHP_MSHUTDOWN(full_objects),
    PHP_RINIT(full_objects),		/* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(full_objects),	/* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(full_objects),
    PHP_FULL_OBJECTS_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FULL_OBJECTS
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(full_objects)
#endif

