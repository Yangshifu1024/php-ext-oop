/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#include "php.h"
#include "php_ini.h"
#include "ext/standard/php_string.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"

#include "php_full_objects.h"
#include "register.h"

void register_handler(zend_bool *ret, zend_string *type, zend_class_entry *ce)
{
    zend_bool is_exsit = 0;

    is_exsit = zend_hash_exists(FULL_OBJECTS_G(oop_handlers), type);

    if (is_exsit) {
        if (!FULL_OBJECTS_G(allow_override)) {
            php_error(E_ERROR, "Type %s has been registered, and it\'s not allow to override.", ZSTR_VAL(type));
            *ret = 0;
        }
    }

    zval class;
    ZVAL_CE(&class, ce);
    zend_hash_update(FULL_OBJECTS_G(oop_handlers), type, &class);
    *ret = 1;
}


