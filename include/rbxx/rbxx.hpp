#ifndef __RBXX_HPP_
#define __RBXX_HPP_

#include <ruby.h>

namespace rbxx
{

using rb_func = VALUE(*)(ANYARGS);
extern VALUE mRbxx;

template <typename T>
VALUE to_value(T cxx_value);

template <typename T>
T from_value(VALUE rb_value);

void define();

}

#endif