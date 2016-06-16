/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"


#include "php_oop.h"
#include "object.h"

zend_class_entry *handler_object_ce;

/** {{{ proto public static FullObject\Object::toString() */
PHP_METHOD(handler_object, toString) {
    RETURN_EMPTY_STRING();
}
/* }}} */

/** {{{ proto public static FullObject\Object::toArray() */
PHP_METHOD(handler_object, toArray) {
    array_init(return_value);
}
/* }}} */

const zend_function_entry handler_object_ce_functions[] = {
    PHP_ME(handler_object, toString, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(handler_object, toArray, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};

OOP_MODULE_STARTUP_FUNCTION(handler_object)
{
    zend_class_entry local_handler_object_ce;
    INIT_CLASS_ENTRY(local_handler_object_ce, "OOP\\Object", handler_object_ce_functions);
    handler_object_ce = zend_register_internal_class_ex(&local_handler_object_ce, NULL);

    return SUCCESS;
}
