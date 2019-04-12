#ifndef __ACTION_TPP_
#define __ACTION_TPP_

#include "Action.hpp"

/* 
 * std::variant would be slightly better.
 */
template <typename T>
bool Action<T>::valid_nargs(const std::string & nargs)
{
    try
    {
        std::stoi(nargs);
        return true;
    } catch (std::invalid_argument e) 
    {

    }

    if (nargs == OPTIONAL)
    {
        return true;
    }

    if (nargs == ZERO_OR_MORE)
    {
        return true;
    }

    if (nargs == ONE_OR_MORE)
    {
        return true;
    }

    return false;
}

#endif