#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"


class Widget
{
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget(int x, int y, int sx, int sy);
    virtual void draw() const  = 0;
    virtual void handle(genv::event ev) = 0;
};


#endif // WIDGET_HPP
