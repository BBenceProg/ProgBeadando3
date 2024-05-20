#ifndef RENDER_H
#define RENDER_H

#include "gamemaster.hpp"
#include "widget.hpp"

const int XX = 700;
const int YY = 600;
const int CELL_SIZE = 100;

class Render : public Widget
{
public:
    Render();
    int mouse_x;
    int mouse_y;
    void draw_menu() override;
    void draw_game_over(const GameMaster &state) override;
    void draw_board(const GameMaster &state) override;
    void handle_event(const genv::event &ev) override;
};

#endif // RENDER_H
