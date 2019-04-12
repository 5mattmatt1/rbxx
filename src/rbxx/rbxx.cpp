#include "rbxx.hpp"


namespace rbxx
{

VALUE mRbxx = Qnil;

template <typename T>
VALUE to_value(T cxx_value)
{
    return Qnil;
}

template <typename T>
T from_value(VALUE rb_value)
{
    return T();
}

template <>
VALUE to_value<>(int cxx_value)
{
    return INT2NUM(cxx_value);
}

template <>
VALUE to_value<>(bool cxx_value)
{
    return cxx_value ? Qtrue : Qfalse;
}

template <>
int from_value<>(VALUE rb_value)
{
    return NUM2INT(rb_value);
}

template <>
bool from_value<>(VALUE rb_value)
{
    // How to force type to be T_BOOL
    return (rb_value == Qtrue);
}

void define()
{
    mRbxx = rb_define_module("Rbxx");
}

}