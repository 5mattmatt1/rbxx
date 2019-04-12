#ifndef __RBXX_FILE_HPP_
#define __RBXX_FILE_HPP_

#include <ruby.h>

namespace rbxx
{

namespace File
{

extern VALUE cFile;
extern const rb_data_type_t File_t;

struct File
{
};

VALUE exists(VALUE obj, VALUE fn);
VALUE expand_path(int argc, VALUE * vargs, VALUE self);

VALUE alloc(VALUE self);
size_t size(const void *);

void define();

}

}

#endif