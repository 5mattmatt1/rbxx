#include <ruby.h>

#include <iostream>

#include "rb_vector_int.hpp"

int main(int argc, char ** argv)
{
	ruby_init();
	ruby_init_loadpath();
	define_rb_vector_int();
	int state;	
	VALUE test = rb_str_new2("./tests/vector_int/vector_int_test.rb");
	rb_load_protect(test, 0, &state);
	if (state)
	{
		std::cerr << "-----------------" << std::endl;
		std::cerr << "Exception caught!" << std::endl;
		VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
    	std::cerr << StringValuePtr(rbError) << std::endl;
	}
	return ruby_cleanup(0);
}