#ifndef __RB_VECTOR_INT_HPP_
#define __RB_VECTOR_INT_HPP_

#include <ruby.h>

#include <vector>

struct rb_vector_int_t
{
    std::vector<int> * impl;
};

extern const rb_data_type_t rb_vector_int_type;
extern VALUE cVecInt;

size_t rb_vector_int_size(const void * data);
VALUE rb_vector_int_alloc(VALUE self);
VALUE rb_vector_int_init(VALUE self);

VALUE rb_vector_int_at(VALUE self, VALUE index);
VALUE rb_vector_int_set_at(VALUE self, VALUE index, VALUE val);

VALUE rb_vector_int_first(VALUE self);
VALUE rb_vector_int_last(VALUE self);


VALUE rb_vector_int_push(VALUE self, VALUE val);
VALUE rb_vector_int_insert(VALUE self, VALUE index, VALUE val);

VALUE rb_vector_int_pop(VALUE self);

VALUE rb_vector_int_each(VALUE self);
VALUE rb_vector_int_each_index(VALUE self);
VALUE rb_vector_int_reverse_each(VALUE self);


VALUE rb_vector_int_sort_bang(VALUE self);
VALUE rb_vector_int_sort(VALUE self);

VALUE rb_vector_int_reverse_bang(VALUE self);
VALUE rb_vector_int_reverse(VALUE self);

VALUE rb_vector_int_length(VALUE self);
VALUE rb_vector_int_empty(VALUE self);

VALUE rb_vector_int_max(VALUE self);
VALUE rb_vector_int_min(VALUE self);

VALUE rb_vector_int_shuffle_bang(VALUE self);
VALUE rb_vector_int_shuffle(VALUE self);

VALUE rb_vector_int_uniq_bang(VALUE self);
VALUE rb_vector_int_uniq(VALUE self);

VALUE rb_vector_int_index(VALUE self, VALUE val);
VALUE rb_vector_int_rindex(VALUE self, VALUE val);

void define_rb_vector_int();

#endif