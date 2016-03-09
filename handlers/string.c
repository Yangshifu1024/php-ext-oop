/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"
#include "ext/standard/php_string.h"

#include "php_full_objects.h"
#include "object.h"
#include "string.h"

zend_class_entry *handler_string_ce;

/** {{{ proto public static FullObject\String::toString() */
PHP_METHOD(handler_string, toString) {
    zend_string *this = NULL;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(this)
    ZEND_PARSE_PARAMETERS_END();
    ZEND_ASSERT(this != NULL);
    RETURN_STR(this);
}
/* }}} */

/** {{{ proto public static FullObject\String::toArray() */
PHP_METHOD(handler_string, toArray) {
    zend_string *this = NULL;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(this)
    ZEND_PARSE_PARAMETERS_END();
    ZEND_ASSERT(this != NULL);

    array_init(return_value);

    if (ZSTR_VAL(this) != "") {
        zend_long len = ZSTR_LEN(this);
        char *p = ZSTR_VAL(this);
        while (len-- > 0) {
            add_next_index_stringl(return_value, p, 1);
            p += 1;
        }
    }
}
/* }}} */

/** {{{ proto public static FullObject\String::length() */
PHP_METHOD(handler_string, length) {
    zend_string *this = NULL;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(this)
    ZEND_PARSE_PARAMETERS_END();
    ZEND_ASSERT(this != NULL);
    RETURN_LONG(ZSTR_LEN(this));
}
/* }}} */

const zend_function_entry handler_string_ce_functions[] = {
    PHP_ME(handler_string, toString, handler_string_unary_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(handler_string, toArray, handler_string_unary_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(handler_string, length, handler_string_unary_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};

FULLOBJECTS_MODULE_STARTUP_FUNCTION(handler_string)
{
    zend_class_entry local_handler_string_ce;
    INIT_CLASS_ENTRY(local_handler_string_ce, "FullObjects\\String", handler_string_ce_functions);
    handler_string_ce = zend_register_internal_class_ex(&local_handler_string_ce, NULL);

    return SUCCESS;
}
