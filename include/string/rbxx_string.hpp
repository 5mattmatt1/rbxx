#ifndef __RBXX_STRING_HPP_
#define __RBXX_STRING_HPP_

#include <ruby.h>

#include <string>

struct rbxx_string_t
{
    std::string * impl;
};

extern const rb_data_type_t rbxx_string_type;
extern VALUE cRbxxStr;

size_t rbxx_string_size(const void * data);
VALUE rbxx_string_alloc(VALUE self);
VALUE rbxx_string_init(VALUE self, VALUE str);
VALUE rbxx_string_plus(VALUE self, VALUE str);
VALUE rbxx_string_to_str(VALUE self);

void define_rbxx_string();

#endif /* __RBXX_STRING_HPP_ */