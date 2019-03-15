#include "rect.hpp"

Rect::Rect(int x, int y, int width, int height)
	: x(x),
	  y(y),
	  width(width),
	  height(height)
{

}

int Rect::area()
{
	return x * y;
}
