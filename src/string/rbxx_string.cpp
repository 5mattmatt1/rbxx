#include "rbxx_string.hpp"

#include <ruby.h>

#include "rb_string.h"

#include <iostream>
#include <algorithm>

VALUE cRbxxString = Qnil;

using rb_func = VALUE(*)(ANYARGS);

const rb_data_type_t rbxx_string_type = {
	.wrap_struct_name = "RbxxString",
	.function = {
		.dmark = NULL,
		.dfree = RUBY_DEFAULT_FREE,
		.dsize = rbxx_string_size,
	},
	.data = NULL,
	.flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

size_t rbxx_string_size(const void * data)
{
    return sizeof(rbxx_string_t);
}

VALUE rbxx_string_alloc(VALUE self)
{
    rbxx_string_t * data;
	VALUE retVal = TypedData_Make_Struct(self, rbxx_string_t, &rbxx_string_type, data);
    return retVal;
}

VALUE rbxx_string_init(VALUE self, VALUE str)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);
	
    char * c_str = StringValuePtr(str);
    data->impl = new std::string(c_str);
    
    return self;
}

VALUE rbxx_string_to_s(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);
	
    return rb_str_new(data->impl->c_str(), data->impl->size());
}

VALUE rbxx_string_plus(VALUE self, VALUE str2)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    VALUE str3;
    rbxx_string_t * str3_data;
    if (rb_type(str2) == T_STRING)
    {
        str3 = rb_funcall(cRbxxString, rb_intern("new"), 1, str2);
        TypedData_Get_Struct(str3, rbxx_string_t, &rbxx_string_type, str3_data);
        str3_data->impl = new std::string(*(data->impl) + *(str3_data->impl));
    }
    else
    {
        rbxx_string_t * str2_data;
	    TypedData_Get_Struct(str2, rbxx_string_t, &rbxx_string_type, str2_data);
        str3 = rb_funcall(cRbxxString, rb_intern("new"), 1, rb_str_new_cstr(""));
        TypedData_Get_Struct(str3, rbxx_string_t, &rbxx_string_type, str3_data);
        str3_data->impl = new std::string(*(data->impl) + *(str2_data->impl));
    }

    return str3;
}

VALUE rbxx_string_to_str(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    return rb_str_new_cstr(data->impl->c_str());
}

VALUE rbxx_string_concat(VALUE self, VALUE str2)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    if (rb_type(str2) == T_STRING)
    {
        *(data->impl) += StringValuePtr(str2);
    }
    else
    {
        rbxx_string_t * str2_data;
	    TypedData_Get_Struct(str2, rbxx_string_t, &rbxx_string_type, str2_data);

        *(data->impl) += *(str2_data->impl);
    }

    return self;
}

VALUE rbxx_str_cmp_m(VALUE self, VALUE cmp)
{
    if (rb_type(cmp) == T_STRING)
    {
        return INT2FIX(rb_str_cmp_m(rbxx_string_to_str(self), cmp));
    } else if (rb_type(cmp) == T_DATA)
    {
        return INT2FIX(rb_str_cmp_m(rbxx_string_to_str(self), rbxx_string_to_str(cmp)));
    }

    return Qnil;
	// return rb_invcmp(self, cmp);
}

void define_rbxx_string()
{
    cRbxxString = rb_define_class("RbxxString", rb_cData);
    rb_define_alloc_func(cRbxxString, rbxx_string_alloc);
	rb_define_method(cRbxxString, "initialize", (rb_func) rbxx_string_init, 1);
    rb_define_method(cRbxxString, "to_s", (rb_func) rbxx_string_to_s, 0);
    rb_define_method(cRbxxString, "+", (rb_func) rbxx_string_plus, 1);
    rb_define_method(cRbxxString, "concat", (rb_func) rbxx_string_concat, 1);
    rb_define_method(cRbxxString, "<<", (rb_func) rbxx_string_concat, 1);
    rb_define_method(cRbxxString, "<=>", (rb_func) rbxx_str_cmp_m, 1);

    rb_define_method(cRbxxString, "to_str", (rb_func) rbxx_string_to_str, 0);
}