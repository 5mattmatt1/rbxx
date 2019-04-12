#ifndef __ARGUMENT_PARSER_HPP_
#define __ARGUMENT_PARSER_HPP_

#include <vector>
#include <string>
#include "Action.hpp"

class ArgumentParser
{
public:
    ArgumentParser(int argc, char ** argv);
protected:
    void cxx_argv(int argc, char ** argv);
    template <typename T>
    void add_argument();
    void add_help();
    std::vector<std::string> m_argv;
};

#endif