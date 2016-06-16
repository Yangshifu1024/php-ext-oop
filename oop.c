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
#include "ext/standard/php_var.h"
#include "ext/standard/php_string.h"

#include "php_oop.h"
#include "register.h"
#include "handlers/object_interface.h"
#include "handlers/object.h"
#include "handlers/string.h"

ZEND_DECLARE_MODULE_GLOBALS(oop)

/* True global resources - no need for thread safety here */
static int le_oop;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_BOOLEAN("oop.allow_override", "0", PHP_INI_ALL, OnUpdateBool, allow_override, zend_oop_globals, oop_globals)
PHP_INI_END()
/* }}} */

typedef struct _indirection_function {
    zend_internal_function fn;
    zend_function *fbc;        /* Handler that needs to be invoked */
    zval obj;
} indirection_function;

static void oop_indirection_func(INTERNAL_FUNCTION_PARAMETERS)
{
    indirection_function *ind = (indirection_function *) execute_data->func;
    zval *obj = &ind->obj;
    zval *params = safe_emalloc(sizeof(zval), ZEND_NUM_ARGS() + 1, 0);
    zval result;

    zend_class_entry *ce = ind->fn.scope;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;

    fci.size = sizeof(fci);
    fci.param_count = ZEND_NUM_ARGS() + 1;
    fci.params = params;
    fci.no_separation = 1;

    fcc.initialized = 1;
    fcc.calling_scope = ce;
    fcc.function_handler = ind->fbc;

    zend_get_parameters_array_ex(ZEND_NUM_ARGS(), &params[1]);

    ZVAL_COPY_VALUE(&params[0], obj);
    ZVAL_STR(&fci.function_name, ind->fn.function_name);
    fci.retval = &result;
    fci.object = NULL;

    fcc.object = NULL;
    fcc.called_scope = ce;

    if (zend_call_function(&fci, &fcc TSRMLS_CC) == SUCCESS && !Z_ISUNDEF(result)) {
        ZVAL_COPY_VALUE(return_value, &result);
    }
    zval_ptr_dtor(obj);
    execute_data->func = NULL;

    zval_ptr_dtor(&fci.function_name);
    efree(params);
    efree(ind);
}

static zend_function *oop_get_indirection_func(
    zend_class_entry *ce, zend_function *fbc, zval *method, zval *obj
) {
    indirection_function *ind = emalloc(sizeof(indirection_function));
    zend_function *fn = (zend_function *) &ind->fn;
    long keep_flags = ZEND_ACC_RETURN_REFERENCE;

    ind->fn.type = ZEND_INTERNAL_FUNCTION;
    ind->fn.module = (ce->type == ZEND_INTERNAL_CLASS) ? ce->info.internal.module : NULL;
    ind->fn.handler = oop_indirection_func;
    ind->fn.scope = ce;
    ind->fn.fn_flags = ZEND_ACC_CALL_VIA_HANDLER | (fbc->common.fn_flags & keep_flags);
    ind->fn.num_args = fbc->common.num_args - 1;

    ind->fbc = fbc;
    if (fbc->common.arg_info) {
        fn->common.arg_info = &fbc->common.arg_info[1];
    } else {
        fn->common.arg_info = NULL;
    }

    ind->fn.function_name = zend_string_copy(Z_STR_P(method));
    zend_set_function_arg_flags(fn);
    ZVAL_COPY_VALUE(&ind->obj, obj);

    return fn;
}

/** see http://lxr.php.net/xref/PHP_7_0/Zend/zend_vm_def.h#2892 */
static int oop_method_call_handler(zend_execute_data *execute_data)
{
    const zend_op *opline = execute_data->opline;
    zend_free_op free_op1, free_op2;
    zval *obj = NULL, *method = NULL;
    zend_class_entry *ce = NULL;
    zend_function *fbc = NULL;
    zend_execute_data *call = NULL;

    obj = zend_get_zval_ptr(opline->op1_type, &opline->op1, execute_data, &free_op1, BP_VAR_R);
    method = zend_get_zval_ptr(opline->op2_type, &opline->op2, execute_data, &free_op2, BP_VAR_R);

    if (Z_TYPE_P(obj) == IS_STRING) {
        ce = OOP_G(oop_handlers)[Z_TYPE_P(obj)];

        if (!ce) {
            return ZEND_USER_OPCODE_DISPATCH;
        }

        fbc = zend_std_get_static_method(ce, Z_STR_P(method), NULL);
        if (UNEXPECTED(fbc == NULL)) {
           php_error(E_ERROR, "Call to undefined method %s::%s()", ZSTR_VAL(ce->name), Z_STRVAL_P(method));
        }
        fbc = oop_get_indirection_func(ce, fbc, method, obj);

        call = zend_vm_stack_push_call_frame(ZEND_CALL_NESTED_FUNCTION, fbc, opline->extended_value, ce, NULL);
        call->prev_execute_data = EX(call);
        EX(call) = call;

        FREE_OP(free_op2);
        FREE_OP_IF_VAR(free_op1);

        execute_data->opline++;

        return ZEND_USER_OPCODE_CONTINUE;
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

ZEND_BEGIN_ARG_INFO_EX(register_handler_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, "type")
    ZEND_ARG_INFO(0, "handler")
ZEND_END_ARG_INFO()


/* {{{ proto string|null register_oop_handler(string $arg, class $ce)
   Register a handler for basic type */
PHP_FUNCTION(register_oop_handler)
{
    zend_string *type = NULL;
    zend_class_entry *ce = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(type)
        Z_PARAM_CLASS_EX(ce, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    zend_bool ret;

    register_handler(&ret, type, ce);

    if (ret) {
        RETURN_STR(ce->name);
    } else {
        RETURN_NULL();
    }
}
/* }}} */


/* {{{ PHP_GINIT_FUNCTION */
PHP_GINIT_FUNCTION(oop) {
    oop_globals->allow_override = 0;
    memset(oop_globals->oop_handlers, 0, sizeof(zend_class_entry *) * MAX_HANDLERS);
}
/* }}} */

/* {{{ PHP_GSHUTDOWN_FUNCTION */
PHP_GSHUTDOWN_FUNCTION(oop) {
    oop_globals->allow_override = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(oop)
{
    REGISTER_INI_ENTRIES();
    OOP_MODULE_STARTUP_CALL(interface_object);
    OOP_MODULE_STARTUP_CALL(handler_object);
    OOP_MODULE_STARTUP_CALL(handler_string);

    zend_bool ret;
    zend_string *basic_type = zend_string_init(ZEND_STRL("string"), 0);

    register_handler(&ret, basic_type, handler_string_ce);

    if (!ret) {
        php_error(E_ERROR, "cant register handler!");
        return FAILURE;
    }

    zend_set_user_opcode_handler(ZEND_INIT_METHOD_CALL, oop_method_call_handler);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(oop)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(oop)
{
#if defined(COMPILE_DL_OOP) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(oop)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(oop)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "oop support", "enabled");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ oop_functions[]
 *
 * Every user visible function must have an entry in oop_functions[].
 */
const zend_function_entry oop_functions[] = {
    PHP_FE(register_oop_handler,	register_handler_arginfo)
    PHP_FE_END	/* Must be the last line in oop_functions[] */
};
/* }}} */

/* {{{ oop_module_entry
 */
zend_module_entry oop_module_entry = {
    STANDARD_MODULE_HEADER,
    "oop",
    oop_functions,
    PHP_MINIT(oop),
    PHP_MSHUTDOWN(oop),
    PHP_RINIT(oop),		/* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(oop),	/* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(oop),
    PHP_OOP_VERSION,
    PHP_MODULE_GLOBALS(oop),
    PHP_GINIT(oop),
    PHP_GSHUTDOWN(oop),
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_OOP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(oop)
#endif

