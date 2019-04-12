#ifndef __ACTION_HPP_
#define __ACTION_HPP_

#include <vector>
#include <string>
#include <stdexcept>

bool operator ==(const std::string & str, char chr);

extern const std::string OPTIONAL;
extern const std::string ZERO_OR_MORE;
extern const std::string ONE_OR_MORE;

/*
# ==============
# Action classes
# ==============

class Action(_AttributeHolder):
Information about how to convert command line strings to Python objects.
Action objects are used by an ArgumentParser to represent the information
needed to parse a single argument from one or more strings from the
command line. The keyword arguments to the Action constructor are also
all attributes of Action instances.
Keyword Arguments:
    - option_strings -- A list of command-line option strings which
        should be associated with this action.
    - dest -- The name of the attribute to hold the created object(s)
    - nargs -- The number of command-line arguments that should be
        consumed. By default, one argument will be consumed and a single
        value will be produced.  Other values include:
            - N (an integer) consumes N arguments (and produces a list)
            - '?' consumes zero or one arguments
            - '*' consumes zero or more arguments (and produces a list)
            - '+' consumes one or more arguments (and produces a list)
        Note that the difference between the default and nargs=1 is that
        with the default, a single value will be produced, while with
        nargs=1, a list containing a single value will be produced.
    - const -- The value to be produced if the option is specified and the
        option uses an action that takes no values.
    - default -- The value to be produced if the option is not specified.
    - type -- A callable that accepts a single string argument, and
        returns the converted value.  The standard Python types str, int,
        float, and complex are useful examples of such callables.  If None,
        str is used.
    - choices -- A container of values that should be allowed. If not None,
        after a command-line argument has been converted to the appropriate
        type, an exception will be raised if it is not a member of this
        collection.
    - required -- True if the action must always be specified at the
        command line. This is only meaningful for optional command-line
        arguments.
    - help -- The help string describing the argument.
    - metavar -- The name to be used for the option's argument with the
        help string. If None, the 'dest' value will be used as the name.
*/

template <typename T = std::string>
class Action
{
    Action();
    // type is not needed in this case.
    std::vector<std::string> m_option_strings;
    std::string m_dest;

    std::string m_nargs;
    std::string m_const;
    T m_default;
    std::vector<T> m_choices;
    bool m_required;
    std::string m_help;
    std::string m_metavar;
protected:
    bool valid_nargs(const std::string & nargs);
};

#include "Action.tpp"
#endif