#include "map.hpp"

extern "C" void Init_map()
{
    rbxx::define();
	rbxx::map::define<int, int>("Map_ii");
}