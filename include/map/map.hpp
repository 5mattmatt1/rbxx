#include "rbxx.hpp"

#include <iostream>
#include <string>
#include <map>

namespace rbxx
{

namespace map
{

template <typename Key, typename T>
class map : public std::map<Key, T>
{
public:
    static rb_data_type_t rb_map_t;
    static VALUE cMap;
    map() {};

    T default_value;
};

template<typename Key, typename T>
size_t size(const void*) { return sizeof(map<Key, T>); }

template<typename Key, typename T>
struct impl
{
    map<Key, T> * impl;
};

template <typename Key, typename T>
rb_data_type_t map<Key, T>::rb_map_t;

template <typename Key, typename T>
VALUE map<Key, T>::cMap = Qnil;

template <typename Key, typename T>
VALUE alloc(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	return TypedData_Make_Struct(self, impl_t, &map_t::rb_map_t, data);
}

template<typename Key, typename T>
VALUE initialize(VALUE self) // Add default argument
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    data->impl = new map<Key, T>();

    return self;
}

template<typename Key, typename T>
VALUE at(VALUE self, VALUE key)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    
    try
    {
        return rbxx::to_value<T>(data->impl->at(rbxx::from_value<Key>(key)));
    } catch (const std::out_of_range & err)
    {
        // Need to get default value setup.
        return Qnil;
    }
    return Qnil;
}

template<typename Key, typename T>
VALUE set_at(VALUE self, VALUE key, VALUE val)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    
    // std::cout << rbxx::from_value<Key>(key) << std::endl;
    // std::cout << rbxx::from_value<T>(val) << std::endl;
    Key cxx_key = rbxx::from_value<Key>(key);
    T cxx_val = rbxx::from_value<T>(val);

    (*data->impl)[cxx_key] = cxx_val;

    return Qnil;
}

template<typename Key, typename T>
VALUE empty(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    return rbxx::to_value<bool>(data->impl->empty());
}

template <typename Key, typename T>
VALUE each_pair(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    
    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());
    
    for (const std::pair<Key, T> & pair : *data->impl)
    {
	    rb_yield(rb_assoc_new(rbxx::to_value<Key>(pair.first), rbxx::to_value<T>(pair.second)));
    }

    return self;
}

template <typename Key, typename T>
VALUE each_key(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    
    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());
    
    for (const std::pair<Key, T> & pair : *data->impl)
    {
	    rb_yield(rbxx::to_value<Key>(pair.first));
    }

    return self;
}

template <typename Key, typename T>
VALUE each_value(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);
    
    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());
    
    for (const std::pair<Key, T> & pair : *data->impl)
    {
	    rb_yield(rbxx::to_value<T>(pair.second));
    }

    return self;
}

template <typename Key, typename T>
VALUE delete_key(VALUE self, VALUE key)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    data->impl->erase(rbxx::from_value<Key>(key));    

    return Qnil;
}

template <typename Key, typename T>
VALUE delete_if(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());   

    VALUE key;
    VALUE value;
    
    for (const std::pair<Key, T> & pair : *data->impl)
    {
        key = rbxx::to_value<Key>(pair.first);
        value = rbxx::to_value<T>(pair.second);

        if (RTEST(rb_yield_values(2, key, value)))
        {
            data->impl->erase(pair.first);
        }
    }

    return Qnil;
}

template <typename Key, typename T>
void define(const std::string & cls_name)
{
    map<Key, T>::rb_map_t = (rb_data_type_t) {
        .wrap_struct_name = cls_name.c_str(),
        .function = {
            .dmark = NULL,
            .dfree = RUBY_DEFAULT_FREE,
            .dsize = size<Key, T>,
        },
        .data = NULL,
        .flags = RUBY_TYPED_FREE_IMMEDIATELY,
    };

    map<Key, T>::cMap = rb_define_class_under(mRbxx, cls_name.c_str(), rb_cData);
    rb_define_alloc_func(map<Key, T>::cMap, alloc<Key, T>);
    rb_define_method(map<Key, T>::cMap, "initialize", (rb_func) initialize<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "[]", (rb_func) at<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "[]=", (rb_func) set_at<Key, T>, 2);
    rb_define_method(map<Key, T>::cMap, "delete", (rb_func) delete_key<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "delete_if", (rb_func) delete_if<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "empty?", (rb_func) empty<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "each", (rb_func) each_pair<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "each_pair", (rb_func) each_pair<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "each_key", (rb_func) each_key<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "each_value", (rb_func) each_value<Key, T>, 0);
}

}

}