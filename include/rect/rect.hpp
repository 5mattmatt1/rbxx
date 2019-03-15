#ifndef __RECT_HPP_
#define __RECT_HPP_

struct Rect
{
	Rect(int x, int y, int width, int height);
	virtual ~Rect() {};
	virtual int area();
	
	int x;
	int y;
	int width;
	int height;
protected:
	Rect() = default;
};

#endif