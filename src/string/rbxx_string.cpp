#include "rbxx_string.hpp"

#include <ruby.h>

#include "rb_string.h"

#include <iostream>
#include <algorithm>
#include <locale>         // std::locale, std::toupper

#include <vector>
#include <boost/algorithm/string.hpp>

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

VALUE rbxx_string_aref(VALUE self, VALUE rb_idx)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    int idx = NUM2INT(rb_idx);

    if (idx >= data->impl->size())
    {
        return Qnil;
    }
    std::string * aref; 
    aref = new std::string(1, (*data->impl)[idx]);

    return rb_str_new_cstr(aref->c_str());
}

VALUE rbxx_string_aset(VALUE self, VALUE indx, VALUE val)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);
    long idx;

    const char * to_insert;

    if (!FIXNUM_P(indx))
    {
        return Qnil;
    }

    idx = FIX2LONG(indx);

    if (idx > data->impl->size())
    {
        rb_raise(rb_eIndexError, "index %ld out of string", idx);
        return Qnil;
    }

    if (rb_type(val) == T_STRING)
    {
        to_insert = StringValuePtr(val); 
    } else if (rb_type(val) == T_DATA)
    {
        rbxx_string_t * val_data;
	    TypedData_Get_Struct(val, rbxx_string_t, &rbxx_string_type, val_data);
        to_insert = val_data->impl->c_str();    
    }

    data->impl->erase(idx, 1);
    data->impl->insert(idx, to_insert);
    return Qnil;
}

VALUE rbxx_string_upcase(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    VALUE dup = rb_funcall(cRbxxString, rb_intern("new"), 1, rb_str_new_cstr(""));
    rbxx_string_t * dup_data;
	TypedData_Get_Struct(dup, rbxx_string_t, &rbxx_string_type, dup_data);
    
    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        c = std::toupper((*data->impl)[i], loc);
        (*dup_data->impl) += c;
    }

    return dup;
}

VALUE rbxx_string_upcase_bang(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        c = std::toupper((*data->impl)[i], loc);
        (*data->impl)[i] = c;
    }

    return self;
}

VALUE rbxx_string_downcase(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    VALUE dup = rb_funcall(cRbxxString, rb_intern("new"), 1, rb_str_new_cstr(""));
    rbxx_string_t * dup_data;
	TypedData_Get_Struct(dup, rbxx_string_t, &rbxx_string_type, dup_data);
    
    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        c = std::tolower((*data->impl)[i], loc);
        (*dup_data->impl) += c;
    }

    return dup;
}

VALUE rbxx_string_downcase_bang(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        c = std::tolower((*data->impl)[i], loc);
        (*data->impl)[i] = c;
    }

    return self;
}

VALUE rbxx_string_swapcase(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    VALUE dup = rb_funcall(cRbxxString, rb_intern("new"), 1, rb_str_new_cstr(""));

    rbxx_string_t * dup_data;
	TypedData_Get_Struct(dup, rbxx_string_t, &rbxx_string_type, dup_data);
    
    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        if (std::isupper((*data->impl)[i], loc))
        {
            c = std::tolower((*data->impl)[i], loc);
        } else
        {
            c = std::toupper((*data->impl)[i], loc);
        }
        (*dup_data->impl) += c;
    }

    return dup;
}

VALUE rbxx_string_swapcase_bang(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    std::locale loc;
    char c;
    for (std::string::size_type i = 0; i < data->impl->length(); ++i)
    {
        if (std::isupper((*data->impl)[i], loc))
        {
            c = std::tolower((*data->impl)[i], loc);
        } else
        {
            c = std::toupper((*data->impl)[i], loc);
        }
        (*data->impl)[i] = c;
    }

    return self;
}

VALUE rbxx_string_reverse(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    VALUE dup = rb_funcall(cRbxxString, rb_intern("new"), 1, rb_str_new_cstr(""));

    rbxx_string_t * dup_data;
	TypedData_Get_Struct(dup, rbxx_string_t, &rbxx_string_type, dup_data);

    std::string * ins = data->impl;
    std::string * dup_ins = dup_data->impl;
    dup_ins->insert(dup_ins->begin(), ins->begin(), ins->end());
    std::reverse(dup_ins->begin(), dup_ins->end());

    return dup;
}

VALUE rbxx_string_reverse_bang(VALUE self)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    std::reverse(data->impl->begin(), data->impl->end());

    return self;
}

VALUE rbxx_string_split(VALUE self, VALUE str)
{
    rbxx_string_t * data;
	TypedData_Get_Struct(self, rbxx_string_t, &rbxx_string_type, data);

    const char * sep;

    if (rb_type(str) == T_STRING)
    {
        sep = StringValuePtr(str); 
    } else if (rb_type(str) == T_DATA)
    {
        rbxx_string_t * sep_data;
	    TypedData_Get_Struct(str, rbxx_string_t, &rbxx_string_type, sep_data);
        sep = sep_data->impl->c_str();    
    }

    std::vector<std::string> split_vec;
    boost::iter_split(split_vec, (*data->impl), boost::algorithm::first_finder(sep));

    VALUE split_str = rb_ary_new();
    for (const std::string & elem : split_vec)
    {
        rb_ary_push(split_str, rb_str_new_cstr(elem.c_str()));
    }

    return split_str;
}

/*
 * Should probably move these to a
 * rbxx::string namespace
 */

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
    rb_define_method(cRbxxString, "[]", (rb_func) rbxx_string_aref, 1);
    rb_define_method(cRbxxString, "[]=", (rb_func) rbxx_string_aset, 2);
    rb_define_method(cRbxxString, "upcase", (rb_func) rbxx_string_upcase, 0);
    rb_define_method(cRbxxString, "upcase!", (rb_func) rbxx_string_upcase_bang, 0);
    rb_define_method(cRbxxString, "downcase", (rb_func) rbxx_string_downcase, 0);
    rb_define_method(cRbxxString, "downcase!", (rb_func) rbxx_string_downcase_bang, 0);
    rb_define_method(cRbxxString, "swapcase", (rb_func) rbxx_string_swapcase, 0);
    rb_define_method(cRbxxString, "swapcase!", (rb_func) rbxx_string_swapcase_bang, 0);
    rb_define_method(cRbxxString, "reverse", (rb_func) rbxx_string_reverse, 0);
    rb_define_method(cRbxxString, "reverse!", (rb_func) rbxx_string_reverse_bang, 0);
    rb_define_method(cRbxxString, "split", (rb_func) rbxx_string_split, 1);
    rb_define_method(cRbxxString, "to_str", (rb_func) rbxx_string_to_str, 0);
}