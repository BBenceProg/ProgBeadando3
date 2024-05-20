#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gamemaster.hpp"
#include "graphics.hpp"

class Widget
{
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget(int x, int y, int sx, int sy);
    virtual void draw_menu() = 0 ;
    virtual void draw_game_over(const GameMaster &state) = 0 ;
    virtual void draw_board(const GameMaster &state) = 0 ;
    virtual void handle_event(const genv::event &ev) = 0;
};


#endif // WIDGET_HPP
