#ifndef __RB_RECT_HPP_
#define __RB_RECT_HPP_

#include <ruby.h>

class Rect;

struct rb_rect_data
{
	Rect * impl;
};

extern const rb_data_type_t rb_rect_type;

size_t rb_rect_size(const void * data);
VALUE rb_rect_alloc(VALUE self);
VALUE rb_rect_init(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height);

/*
 * Getters for public variables since we are effectively doing pimpl here.
 */
VALUE rb_rect_getx(VALUE self);
VALUE rb_rect_gety(VALUE self);
VALUE rb_rect_getwidth(VALUE self);
VALUE rb_rect_getheight(VALUE self);

VALUE rb_rect_setx(VALUE self, VALUE x);
VALUE rb_rect_sety(VALUE self, VALUE y);
VALUE rb_rect_setwidth(VALUE self, VALUE width);
VALUE rb_rect_setheight(VALUE self, VALUE height);

VALUE rb_rect_area(VALUE self);

void define_rb_rect();
#endif