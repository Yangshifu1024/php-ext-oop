/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#ifndef PHP_OOP_HANDLERS_STRING_H
#define PHP_OOP_HANDLERS_STRING_H

#include "php.h"

extern zend_class_entry *handler_string_ce;

OOP_MODULE_STARTUP_FUNCTION(handler_string);

ZEND_BEGIN_ARG_INFO_EX(handler_string_unary_arginfo, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handler_string_slice_arginfo, 0, 0, 3)
    ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 1)
ZEND_END_ARG_INFO()

#endif

