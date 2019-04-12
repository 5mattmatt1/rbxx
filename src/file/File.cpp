#include "File.hpp"
#include <boost/filesystem.hpp>

#include <iostream>

namespace fs = boost::filesystem;
using rb_func = VALUE(*)(ANYARGS);

namespace rbxx
{

namespace File
{

VALUE cFile = Qnil;

const rb_data_type_t File_t = {
	.wrap_struct_name = "RbxxFile",
	.function = {
		.dmark = NULL,
		.dfree = RUBY_DEFAULT_FREE,
		.dsize = size,
	},
	.data = NULL,
	.flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

VALUE exists(VALUE obj, VALUE fn)
{
    fs::path fpath(std::string(StringValuePtr(fn)));
    return fs::exists(fpath) ? Qtrue : Qfalse;
}

VALUE expand_path(int argc, VALUE * vargs, VALUE self)
{
    if (argc > 2 || argc < 1)
    {
        // Need to raise an error.
        return Qnil;
    }
    
    fs::path p(StringValuePtr(vargs[0]));
    fs::path base = fs::current_path();

    if (argc == 2)
    {
        base = fs::path(StringValuePtr(vargs[1]));
    }
    
    // try
    // {
    return rb_str_new_cstr(fs::canonical(p, base).c_str());
    // } catch (const fs::filesystem_error & e)
    // {
    //     return Qnil;
    // }
}

VALUE alloc(VALUE self)
{
    std::cerr << "Attempting alloc" << std::endl;
    File * data;
	return TypedData_Make_Struct(self, File, &File_t, data);
}

VALUE size(const void *)
{
    return sizeof(File);
}

void define()
{
    cFile = rb_define_class("RbxxFile", rb_cData);
    rb_define_alloc_func(cFile, alloc);
    rb_define_singleton_method(cFile, "exist?", (rb_func) exists, 1);
    rb_define_singleton_method(cFile, "exists?", (rb_func) exists, 1);
    rb_define_singleton_method(cFile, "expand_path", (rb_func) expand_path, -1);
}

}

}