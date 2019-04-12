#include <ruby.h>

#include <iostream>

#include "map.hpp"

int main(int argc, char ** argv)
{
	ruby_init();
	ruby_init_loadpath();
    rbxx::define();
	rbxx::map::define<int, int>("Map_ii");
	int state;	
	VALUE test = rb_str_new2("./tests/map/map_int_int_test.rb");
    rb_load_protect(test, 0, &state);
    
    VALUE exception = rb_errinfo();
    VALUE errMsg = Qnil;
    if (exception != Qnil)
    {
        errMsg = rb_funcall(exception, rb_intern("message"), 0);
        std::cerr << "Exception!: " << StringValuePtr(errMsg) << std::endl;
    }

	return ruby_cleanup(0);
}