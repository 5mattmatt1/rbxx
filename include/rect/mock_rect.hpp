#ifndef __MOCK_RECT_HPP
#define __MOCK_RECT_HPP

#include <gmock/gmock.h>
#include "rect.hpp"

class MockRect : public Rect
{
public:
    MockRect(int, int, int, int) {x=0; y=0; width=0; height=0;}
    MOCK_METHOD0(area, int());
};

#endif