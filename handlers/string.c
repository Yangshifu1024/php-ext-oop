/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"


#include "php_full_objects.h"
#include "object.h"
#include "string.h"

zend_class_entry *handler_string_ce;

/** {{{ proto public static FullObject\String::toString() */
PHP_METHOD(handler_string, toString) {
    ZEND_ASSERT(getThis() != NULL);
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/** {{{ proto public static FullObject\String::toArray() */
PHP_METHOD(handler_string, toArray) {
    array_init(return_value);
}
/* }}} */

const zend_function_entry handler_string_ce_functions[] = {
    PHP_ME(handler_string, toString, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(handler_string, toArray, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

FULLOBJECTS_MODULE_STARTUP_FUNCTION(handler_string)
{
    zend_class_entry local_handler_string_ce;
    INIT_CLASS_ENTRY(local_handler_string_ce, "FullObjects\\String", handler_string_ce_functions);
    handler_string_ce = zend_register_internal_class_ex(&local_handler_string_ce, handler_object_ce);

    return SUCCESS;
}
