/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"


#include "php_oop.h"
#include "object_interface.h"

zend_class_entry *interface_object_ce;

const zend_function_entry interface_object_functions[] = {
    PHP_ABSTRACT_ME(interface_object_ce, toString, NULL)
    PHP_ABSTRACT_ME(interface_object_ce, toArray, NULL)
    PHP_ABSTRACT_ME(interface_object_ce, isNull, NULL)
    PHP_FE_END
};

OOP_MODULE_STARTUP_FUNCTION(interface_object)
{
    zend_class_entry local_interface_object_ce;
    INIT_CLASS_ENTRY(local_interface_object_ce, "OOP\\ObjectInterface", interface_object_functions);
    interface_object_ce = zend_register_internal_class_ex(&local_interface_object_ce, NULL);
    interface_object_ce->ce_flags |= ZEND_ACC_INTERFACE;
    return SUCCESS;
}

