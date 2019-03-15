#include "rb_string.h"

#include <ruby.h>

#include <algorithm>

/*
 * Maybe start work on taking off some of those
 * static defintions so I don't have to redefine them.
 */

VALUE rb_str_cmp_m(VALUE str1, VALUE str2)
{
    long len1, len2;
    const char *ptr1, *ptr2;
    int retval;

    if (str1 == str2) 
    {
        return 0;
    }
    RSTRING_GETMEM(str1, ptr1, len1);
    RSTRING_GETMEM(str2, ptr2, len2);
    if (ptr1 == ptr2 || (retval = memcmp(ptr1, ptr2, std::min(len1, len2))) == 0) 
    {
        if (len1 == len2)
        {
            if (!rb_str_comparable(str1, str2))
            {
            // if (ENCODING_GET(str1) > ENCODING_GET(str2))
            //     return 1;
                return -1;
            }
            return 0;
        }
	    if (len1 > len2) 
        {
            return 1;
        }
        return -1;
    }
    if (retval > 0)
    {
        return 1;
    }
    return -1;
}
