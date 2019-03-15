#include "rb_vector_int.hpp"

#include <ruby.h>

#include <iostream>
#include <algorithm>

#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

VALUE cVecInt = Qnil;

using rb_func = VALUE(*)(ANYARGS);

const rb_data_type_t rb_vector_int_type = {
	.wrap_struct_name = "rect",
	.function = {
		.dmark = NULL,
		.dfree = RUBY_DEFAULT_FREE,
		.dsize = rb_vector_int_size,
	},
	.data = NULL,
	.flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

size_t rb_vector_int_size(const void * data)
{
	return sizeof(rb_vector_int_t);
}

VALUE rb_vector_int_alloc(VALUE self)
{
    rb_vector_int_t * data;
	VALUE retVal = TypedData_Make_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    return retVal;
}

VALUE rb_vector_int_init(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
	data->impl = new std::vector<int>();
    return self;
}

VALUE rb_vector_int_at(VALUE self, VALUE index)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    int i_index = NUM2INT(index);
    int value = ins->at(i_index);
    return INT2NUM(value);
}

VALUE rb_vector_int_set_at(VALUE self, VALUE index, VALUE val)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    int i_index = NUM2INT(index);
    int value = NUM2INT(val);
    if (i_index >= ins->size())
    {
        // Good enough until I can do proper
        // error handling...
        return Qnil;
    }
    (*ins)[i_index] = value;
    return Qnil;
}

VALUE rb_vector_int_first(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    return INT2NUM(ins->front());
}

VALUE rb_vector_int_last(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    return INT2NUM(ins->back());
}

VALUE rb_vector_int_push(VALUE self, VALUE val)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    data->impl->push_back(NUM2INT(val));
    return self;
}

VALUE rb_vector_int_insert(VALUE self, VALUE index, VALUE val)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    int i_index = NUM2INT(index);
    int value = NUM2INT(val);
    if (i_index >= ins->size())
    {
        // Good enough until I can do proper
        // error handling...
        return Qnil;
    }
    ins->insert(ins->begin()+i_index, 1, value);
    return self;
}

VALUE rb_vector_int_pop(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    
    VALUE ret = INT2NUM(data->impl->back());
    data->impl->pop_back();
    
    return ret;
}

VALUE rb_vector_int_each(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    RETURN_SIZED_ENUMERATOR(self, 0, 0, ins->size());
    
    for (int i = 0; i < ins->size(); i++) 
    {
	    rb_yield(INT2NUM(ins->at(i)));
    }

    return self;
}

VALUE rb_vector_int_each_index(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    RETURN_SIZED_ENUMERATOR(self, 0, 0, ins->size());
    
    for (int i = 0; i < ins->size(); i++) 
    {
	    rb_yield(LONG2NUM(i));
    }

    return self;
}

VALUE rb_vector_int_reverse_each(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    RETURN_SIZED_ENUMERATOR(self, 0, 0, ins->size());
    
    size_t len = ins->size();
    while (len--)
    {
	    rb_yield(INT2NUM(ins->at(len)));
    }

    return self;
}

VALUE rb_vector_int_empty(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    return (ins->size() == 0) ? Qtrue : Qfalse;
}

VALUE rb_vector_int_sort_bang(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    std::sort(ins->begin(), ins->end());
    return self;
}

VALUE rb_vector_int_sort(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;
    
    VALUE dup = rb_funcall(cVecInt, rb_intern("new"), 0);
    
    rb_vector_int_t * dup_data;
	TypedData_Get_Struct(dup, rb_vector_int_t, &rb_vector_int_type, dup_data);
    std::vector<int> * dup_ins = dup_data->impl;
    dup_ins->insert(dup_ins->begin(), ins->begin(), ins->end());
    std::sort(dup_ins->begin(), dup_ins->end());

    return dup;
}

VALUE rb_vector_int_reverse_bang(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    std::reverse(ins->begin(), ins->end());
    return self;
}

VALUE rb_vector_int_reverse(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    VALUE dup = rb_funcall(cVecInt, rb_intern("new"), 0);
    
    rb_vector_int_t * dup_data;
	TypedData_Get_Struct(dup, rb_vector_int_t, &rb_vector_int_type, dup_data);
    std::vector<int> * dup_ins = dup_data->impl;
    dup_ins->insert(dup_ins->begin(), ins->begin(), ins->end());
    std::reverse(dup_ins->begin(), dup_ins->end());

    return dup;
}

VALUE rb_vector_int_max(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    int max = INT_MIN;
    for (const auto elem : *ins)
    {
        max = std::max(max, elem);
    }

    return INT2NUM(max);
}

VALUE rb_vector_int_min(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    int min = INT_MAX;
    for (const auto elem : *ins)
    {
        min = std::min(min, elem);
    }

    return INT2NUM(min);
}

VALUE rb_vector_int_shuffle_bang(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    std::random_shuffle(ins->begin(), ins->end());
    return self;
}

VALUE rb_vector_int_shuffle(VALUE self)
{
    std::srand ( unsigned ( std::time(0) ) );
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    VALUE dup = rb_funcall(cVecInt, rb_intern("new"), 0);
    
    rb_vector_int_t * dup_data;
	TypedData_Get_Struct(dup, rb_vector_int_t, &rb_vector_int_type, dup_data);
    std::vector<int> * dup_ins = dup_data->impl;
    dup_ins->insert(dup_ins->begin(), ins->begin(), ins->end());
    std::random_shuffle(dup_ins->begin(), dup_ins->end());

    return dup;
}

VALUE rb_vector_int_uniq_bang(VALUE self)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    ins->erase(std::unique(ins->begin(), ins->end()), ins->end());
    return self;
}

VALUE rb_vector_int_uniq(VALUE self)
{
    std::srand ( unsigned ( std::time(0) ) );
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    VALUE dup = rb_funcall(cVecInt, rb_intern("new"), 0);
    
    rb_vector_int_t * dup_data;
	TypedData_Get_Struct(dup, rb_vector_int_t, &rb_vector_int_type, dup_data);
    std::vector<int> * dup_ins = dup_data->impl;
    dup_ins->insert(dup_ins->begin(), ins->begin(), ins->end());
    dup_ins->erase(std::unique(dup_ins->begin(), dup_ins->end()), dup_ins->end());

    return dup;
}

VALUE rb_vector_int_index(VALUE self, VALUE val)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    auto pos = std::find(ins->begin(), ins->end(), NUM2INT(val));
    if (pos != ins->end())
    {
        return INT2NUM(std::distance(ins->begin(), pos));
    }
    return Qnil;
}

VALUE rb_vector_int_rindex(VALUE self, VALUE val)
{
    rb_vector_int_t * data;
	TypedData_Get_Struct(self, rb_vector_int_t, &rb_vector_int_type, data);
    std::vector<int> * ins = data->impl;

    auto pos = std::find(ins->rbegin(), ins->rend(), NUM2INT(val));
    if (pos != ins->rend())
    {
        auto dist = std::distance(ins->rbegin().base(), pos.base());
        return INT2NUM(((ins->size()+dist))-1);
    }
    return Qnil;
}

void define_rb_vector_int()
{
    cVecInt = rb_define_class("VecInt", rb_cData);
    rb_include_module(cVecInt, rb_mEnumerable);
	rb_define_alloc_func(cVecInt, rb_vector_int_alloc);
	rb_define_method(cVecInt, "initialize", (rb_func) rb_vector_int_init, 0);	
	rb_define_method(cVecInt, "[]", (rb_func) rb_vector_int_at, 1);
    rb_define_method(cVecInt, "[]=", (rb_func) rb_vector_int_set_at, 2);
    rb_define_method(cVecInt, "first", (rb_func) rb_vector_int_first, 0);
    rb_define_method(cVecInt, "last", (rb_func) rb_vector_int_last, 0);
    rb_define_method(cVecInt, "insert", (rb_func) rb_vector_int_insert, 2);
    rb_define_method(cVecInt, "push", (rb_func) rb_vector_int_push, 1);
    rb_define_method(cVecInt, "<<", (rb_func) rb_vector_int_push, 1);
    rb_define_alias(cVecInt,  "append", "push");
    rb_define_method(cVecInt, "pop", (rb_func) rb_vector_int_pop, 0);
    rb_define_method(cVecInt, "each", (rb_func) rb_vector_int_each, 0);
    rb_define_method(cVecInt, "each_index", (rb_func) rb_vector_int_each_index, 0);
    rb_define_method(cVecInt, "reverse_each", (rb_func) rb_vector_int_reverse_each, 0);
    rb_define_method(cVecInt, "empty?", (rb_func) rb_vector_int_empty, 0);
    rb_define_method(cVecInt, "sort", (rb_func) rb_vector_int_sort, 0);
    rb_define_method(cVecInt, "sort!", (rb_func) rb_vector_int_sort_bang, 0);
    rb_define_method(cVecInt, "reverse", (rb_func) rb_vector_int_reverse, 0);
    rb_define_method(cVecInt, "reverse!", (rb_func) rb_vector_int_reverse_bang, 0);

    rb_define_method(cVecInt, "max", (rb_func) rb_vector_int_max, 0);
    rb_define_method(cVecInt, "min", (rb_func) rb_vector_int_min, 0);
    rb_define_method(cVecInt, "shuffle!", (rb_func) rb_vector_int_shuffle_bang, 0);
    rb_define_method(cVecInt, "shuffle", (rb_func) rb_vector_int_shuffle, 0);
    rb_define_method(cVecInt, "uniq!", (rb_func) rb_vector_int_uniq_bang, 0);
    rb_define_method(cVecInt, "uniq", (rb_func) rb_vector_int_uniq, 0);

    rb_define_method(cVecInt, "index", (rb_func) rb_vector_int_index, 1);
    rb_define_method(cVecInt, "rindex", (rb_func) rb_vector_int_rindex, 1);
}