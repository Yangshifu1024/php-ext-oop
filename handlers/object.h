/**
 * Copyright (C) 2016 Frank Yang <codebear4@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/* $Id$ */

#ifndef PHP_OOP_HANDLERS_OBJECT_H
#define PHP_OOP_HANDLERS_OBJECT_H

#include "php.h"

extern zend_class_entry *handler_object_ce;

OOP_MODULE_STARTUP_FUNCTION(handler_object);

#endif
