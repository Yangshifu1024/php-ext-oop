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

#include "php_oop.h"
#include "register.h"

zend_ulong get_type_by_string(const char *type);

void register_handler(zend_bool *ret, zend_string *type, zend_class_entry *ce)
{
    zend_ulong origin_type = get_type_by_string(ZSTR_VAL(type));

    if (OOP_G(oop_handlers)[origin_type]) {
        if (!OOP_G(allow_override)) {
            *ret = 0;
            php_error(E_ERROR, "Type %s has been registered, and it\'s not allow to override.", ZSTR_VAL(type));
        }
    }

    OOP_G(oop_handlers)[origin_type] = ce ;
    if (origin_type == IS_TRUE) {
        OOP_G(oop_handlers)[IS_FALSE] = ce ;
    }
    *ret = 1;
}

zend_ulong get_type_by_string(const char *type)
{
    if (!strcasecmp(type, "null")) {
        return IS_NULL;
    } else if (!strcasecmp(type, "bool")) {
        return IS_TRUE;
    } else if (!strcasecmp(type, "int")) {
        return IS_LONG;
    } else if (!strcasecmp(type, "float")) {
        return IS_DOUBLE;
    } else if (!strcasecmp(type, "string")) {
        return IS_STRING;
    } else if (!strcasecmp(type, "array")) {
        return IS_ARRAY;
    } else if (!strcasecmp(type, "resource")) {
        return IS_RESOURCE;
    } else {
        zend_error(E_WARNING, "Invalid type \"%s\" specified", type);
        return -1;
    }
}


