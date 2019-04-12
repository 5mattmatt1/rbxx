#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser(int argc, char ** argv)
{
    this->cxx_argv(argc, argv);
}

void ArgumentParser::cxx_argv(int argc, char ** argv)
{
    for (int i = 0; i < argc; i++)
    {
        m_argv.push_back(std::string(argv[i]));
    }
}