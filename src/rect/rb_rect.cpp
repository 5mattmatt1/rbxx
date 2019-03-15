#include "rb_rect.hpp"
#include "rect.hpp"
#include "mock_rect.hpp"
#include <ruby.h>

#include <iostream>

using rb_func = VALUE(*)(ANYARGS);

const rb_data_type_t rect_type = {
	.wrap_struct_name = "rect",
	.function = {
		.dmark = NULL,
		.dfree = RUBY_DEFAULT_FREE,
		.dsize = rb_rect_size,
	},
	.data = NULL,
	.flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

size_t rb_rect_size(const void * data)
{
	return sizeof(rb_rect_data);
}

// Maybe use:
// template <typename T, const rb_data_type_t rb_data_type>
// VALUE rbxx_alloc(VALUE self)
// {
//		T * data;
//		VALUE alloc_type = TypedData_Make_Struct(self, T, &rb_data_type, data);
//		return retVal;
// }
// rbxx_alloc<>

VALUE rb_rect_alloc(VALUE self)
{
	std::cout << "Attempting alloc" << std::endl;
	struct rb_rect_data * data;
	VALUE retVal = TypedData_Make_Struct(self, struct rb_rect_data, &rect_type, data);
	return retVal;
}

// Maybe use:
// template <typename T, const rb_data_type_t rb_data_type>
// auto rbxx_this(VALUE self)
// {
//		T * data;
//		TypedData_Get_Struct(self, T, &rb_data_type, data);
//		return data->impl;
// }

VALUE rb_rect_init(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height)
{
	std::cout << "init called" << std::endl;
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	data->impl = new Rect(NUM2INT(x), NUM2INT(y), NUM2INT(width), NUM2INT(height));
	std::cout << "Rect init" << std::endl;
	return self;
}

VALUE rb_rect_getx(VALUE self)
{
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	Rect * ins = data->impl;
	return INT2NUM(ins->x);
}

VALUE rb_rect_gety(VALUE self)
{
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	Rect * ins = data->impl;
	return INT2NUM(ins->y);
}

VALUE rb_rect_getwidth(VALUE self)
{
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	Rect * ins = data->impl;
	return INT2NUM(ins->width);
}

VALUE rb_rect_getheight(VALUE self)
{
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	Rect * ins = data->impl;
	return INT2NUM(ins->height);
}

VALUE rb_rect_area(VALUE self)
{	
	struct rb_rect_data * data;
	TypedData_Get_Struct(self, struct rb_rect_data, &rect_type, data);
	Rect * ins = data->impl; 
	return INT2NUM(ins->area());
}

void define_rb_rect()
{
	VALUE cRect = rb_define_class("Rect", rb_cData);
	rb_define_alloc_func(cRect, rb_rect_alloc);
	rb_define_method(cRect, "initialize", (rb_func) rb_rect_init, 4);	
	rb_define_method(cRect, "area", (rb_func) rb_rect_area, 0);
	rb_define_method(cRect, "x", (rb_func) rb_rect_getx, 0);
	rb_define_method(cRect, "y", (rb_func) rb_rect_gety, 0);
	rb_define_method(cRect, "width", (rb_func) rb_rect_getwidth, 0);
	rb_define_method(cRect, "height", (rb_func) rb_rect_getheight, 0);
	std::cout << "Rect defined" << std::endl;
}