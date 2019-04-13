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

    VALUE key = Qnil;
    VALUE value = Qnil;
    
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
VALUE keep_if(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());   

    VALUE key = Qnil;
    VALUE value = Qnil;
    
    for (const std::pair<Key, T> & pair : *data->impl)
    {
        key = rbxx::to_value<Key>(pair.first);
        value = rbxx::to_value<T>(pair.second);

        if (!RTEST(rb_yield_values(2, key, value)))
        {
            data->impl->erase(pair.first);
        }
    }

    return Qnil;
}

template <typename Key, typename T>
VALUE invert(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    using inv_impl_t = impl<T, Key>;
    using inv_map_t = map<T, Key>;
    inv_impl_t * cxx_inverted;
    
    /* Create new rbxx::map instance */
    VALUE inverted;
    inverted = TypedData_Make_Struct(inv_map_t::cMap, inv_impl_t, &inv_map_t::rb_map_t, cxx_inverted);
    initialize<T, Key>(inverted);
    
    for (const auto & elem : *(data->impl))
    {
        (*cxx_inverted->impl)[elem.second] = elem.first;
    }

    return inverted;
}

template <typename Key, typename T>
VALUE key(VALUE self, VALUE val)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    T cxx_value = rbxx::from_value<T>(val);
    
    for (const auto & elem : *(data->impl))
    {
        if (elem.second == cxx_value)
        {
            return rbxx::to_value<Key>(elem.first);
        }
    }

    return Qnil;
}

template <typename Key, typename T>
VALUE has_key(VALUE self, VALUE key)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    T cxx_key = rbxx::from_value<Key>(key);
    
    for (const auto & elem : *(data->impl))
    {
        if (elem.first == cxx_key)
        {
            return Qtrue;
        }
    }

    return Qfalse;
}

// template <typename Key, typename T>
// VALUE merge_block_bang(VALUE self, VALUE rb_map)
// {
//     if (data->impl->count(elem.first))
//     {
        
//     }
// }

template <typename Key, typename T>
VALUE merge(VALUE self, VALUE rb_map)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_map;
    TypedData_Get_Struct(rb_map, impl_t, &map_t::rb_map_t, cxx_map);

    impl_t * cxx_merged;
    VALUE merged = Qnil;
    merged = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_merged);
    initialize<Key, T>(merged);
    
    if (rb_block_given_p())
    {
        rb_raise(rb_eRuntimeError, "Block support not implemented yet\n");
        return Qnil;
    }

    // Definitely some gains to be had by implementing this as a class function of rbxx::map
    // And then calling it in the ruby bindings.
    *cxx_merged->impl = *data->impl;
    for (const auto & elem : *cxx_map->impl)
    {
        (*data->impl)[elem.first] = elem.second;
    }

    return Qfalse;
}

template <typename Key, typename T>
VALUE merge_bang(VALUE self, VALUE rb_map)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_map;
    TypedData_Get_Struct(rb_map, impl_t, &map_t::rb_map_t, cxx_map);
    
    if (rb_block_given_p())
    {
        rb_raise(rb_eRuntimeError, "Block support not implemented yet\n");
        return Qnil;
    }

    for (const auto & elem : *(cxx_map->impl))
    {
        (*data->impl)[elem.first] = elem.second;
    }

    return Qfalse;
}

template <typename Key, typename T>
VALUE transform_keys(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_transformed;
    VALUE transformed = Qnil;
    transformed = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_transformed);
    initialize<Key, T>(transformed);

    RETURN_SIZED_ENUMERATOR(transformed, 0, 0, cxx_transformed->impl->size());
    
    VALUE key = Qnil;
    VALUE val = Qnil;
    VALUE yielded;
    for(const auto & elem : *data->impl)
    {
        key = rbxx::to_value<Key>(elem.first);
        val = rbxx::to_value<T>(elem.second);
        yielded = rb_yield_values(2, key, val);
        (*cxx_transformed->impl)[rbxx::from_value<Key>(yielded)] = elem.second;
    }

    return transformed;
}

template <typename Key, typename T>
VALUE transform_keys_bang(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_transformed;
    VALUE transformed = Qnil;
    transformed = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_transformed);
    initialize<Key, T>(transformed);

    RETURN_SIZED_ENUMERATOR(transformed, 0, 0, cxx_transformed->impl->size());
    
    VALUE key = Qnil;
    VALUE val = Qnil;
    VALUE yielded;
    for(const auto & elem : *data->impl)
    {
        key = rbxx::to_value<Key>(elem.first);
        val = rbxx::to_value<T>(elem.second);
        yielded = rb_yield_values(2, key, val);
        (*cxx_transformed->impl)[rbxx::from_value<Key>(yielded)] = elem.second;
    }

    delete data->impl;
    data->impl = nullptr;
    (data->impl) = (cxx_transformed->impl);
    return Qnil;
}

template <typename Key, typename T>
VALUE transform_values(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_transformed;
    VALUE transformed = Qnil;
    transformed = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_transformed);
    initialize<Key, T>(transformed);

    RETURN_SIZED_ENUMERATOR(transformed, 0, 0, cxx_transformed->impl->size());
    
    VALUE key = Qnil;
    VALUE val = Qnil;
    VALUE yielded;
    for(const auto & elem : *data->impl)
    {
        key = rbxx::to_value<Key>(elem.first);
        val = rbxx::to_value<T>(elem.second);
        yielded = rb_yield_values(2, key, val);
        (*cxx_transformed->impl)[elem.first] = rbxx::from_value<T>(yielded);
    }

    return transformed;
}

template <typename Key, typename T>
VALUE transform_values_bang(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_transformed;
    VALUE transformed = Qnil;
    transformed = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_transformed);
    initialize<Key, T>(transformed);

    RETURN_SIZED_ENUMERATOR(transformed, 0, 0, cxx_transformed->impl->size());
    
    VALUE key = Qnil;
    VALUE val = Qnil;
    VALUE yielded;
    for(const auto & elem : *data->impl)
    {
        key = rbxx::to_value<Key>(elem.first);
        val = rbxx::to_value<T>(elem.second);
        yielded = rb_yield_values(2, key, val);
        (*cxx_transformed->impl)[elem.first] = rbxx::from_value<T>(yielded);
    }

    delete data->impl;
    data->impl = nullptr;
    (data->impl) = (cxx_transformed->impl);
    return Qnil;
}

template <typename Key, typename T>
VALUE length(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);   

    return rbxx::to_value<int>(data->impl->size());
}

template <typename Key, typename T>
VALUE reject_bang(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());   

    VALUE key = Qnil;
    VALUE value = Qnil;
    bool changed = false;

    for (const std::pair<Key, T> & pair : *data->impl)
    {
        key = rbxx::to_value<Key>(pair.first);
        value = rbxx::to_value<T>(pair.second);

        if (RTEST(rb_yield_values(2, key, value)))
        {
            changed = true;
            data->impl->erase(pair.first);
        }
    }

    if (changed)
    {
        return self;
    } else 
    {
        return Qnil;
    }
}

template <typename Key, typename T>
VALUE reject(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_rejected;
    VALUE rejected = Qnil;
    rejected = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_rejected);
    initialize<Key, T>(rejected);

    (*cxx_rejected->impl) = (*data->impl);

    return reject_bang<Key, T>(rejected);
}

template <typename Key, typename T>
VALUE replace(VALUE self, VALUE src)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_src;
	TypedData_Get_Struct(src, impl_t, &map_t::rb_map_t, cxx_src);

    (*data->impl) = (*cxx_src->impl);

    return self;
}


template <typename Key, typename T>
VALUE select_bang(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    RETURN_SIZED_ENUMERATOR(self, 0, 0, data->impl->size());   

    VALUE key = Qnil;
    VALUE value = Qnil;
    bool changed = false;

    for (const std::pair<Key, T> & pair : *data->impl)
    {
        key = rbxx::to_value<Key>(pair.first);
        value = rbxx::to_value<T>(pair.second);

        if (!RTEST(rb_yield_values(2, key, value)))
        {
            changed = true;
            data->impl->erase(pair.first);
        }
    }

    if (changed)
    {
        return self;
    } else 
    {
        return Qnil;
    }
}

template <typename Key, typename T>
VALUE select(VALUE self)
{
    using impl_t = impl<Key, T>;
    using map_t = map<Key, T>;
    impl_t * data;
	TypedData_Get_Struct(self, impl_t, &map_t::rb_map_t, data);

    impl_t * cxx_selected;
    VALUE selected = Qnil;
    selected = TypedData_Make_Struct(map_t::cMap, impl_t, &map_t::rb_map_t, cxx_selected);
    initialize<Key, T>(selected);

    (*cxx_selected->impl) = (*data->impl);

    return select_bang<Key, T>(selected);
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
    // flatten requires finalizing rbxx::vector and rbxx::variant
    rb_define_method(map<Key, T>::cMap, "keep_if", (rb_func) keep_if<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "has_key?", (rb_func) has_key<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "include?", (rb_func) has_key<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "invert", (rb_func) invert<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "key", (rb_func) key<Key, T>, 1);
    // keys requires finalizing rbxx::vector
    rb_define_method(map<Key, T>::cMap, "key?", (rb_func) has_key<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "member?", (rb_func) has_key<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "length", (rb_func) length<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "merge", (rb_func) merge<Key, T>, 1);
    rb_define_method(map<Key, T>::cMap, "merge!", (rb_func) merge_bang<Key, T>, 1);
    // rassoc requires finalizing rbxx::vector
    // or alternatively making a rbxx::pair object...
    // rehash is going to require some thinking...
    rb_define_method(map<Key, T>::cMap, "reject", (rb_func) reject<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "reject!", (rb_func) reject_bang<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "replace", (rb_func) replace<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "select", (rb_func) select<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "select!", (rb_func) select_bang<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "size", (rb_func) length<Key, T>, 0);
    // shift requires finalizing rbxx::vector
    rb_define_method(map<Key, T>::cMap, "store", (rb_func) set_at<Key, T>, 2);
    rb_define_method(map<Key, T>::cMap, "transform_keys", (rb_func) transform_keys<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "transform_keys!", (rb_func) transform_keys_bang<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "transform_values", (rb_func) transform_values<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "transform_values!", (rb_func) transform_values_bang<Key, T>, 0);
    rb_define_method(map<Key, T>::cMap, "update", (rb_func) merge_bang<Key, T>, 1);
    // value requires finalizing rbxx::vector
}

}

}