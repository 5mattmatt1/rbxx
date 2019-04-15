#ifndef __RBXX_HPP_
#define __RBXX_HPP_

#include <ruby.h>
#include <optional>

namespace rbxx
{

using rb_func = VALUE(*)(ANYARGS);
extern VALUE mRbxx;

template <typename T>
VALUE to_value(T cxx_value);

template <typename T>
VALUE to_opt_value(std::optional<T> cxx_value)
{
    if (cxx_value.has_value())
    {
        return to_value<T>(cxx_value.value());
    }
    return Qnil;
}

template <typename T>
T from_value(VALUE rb_value);

template <typename T>
std::optional<T> from_opt_value(VALUE rb_value)
{
    if(rb_value == Qnil)
    {
        return std::nullopt;
    }

    return std::make_optional<T>(from_value<T>(rb_value));
}

void define();

}

#endif