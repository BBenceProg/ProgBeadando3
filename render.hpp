#ifndef RENDER_H
#define RENDER_H

#include "gamemaster.hpp"

const int XX = 700;
const int YY = 600;
const int CELL_SIZE = 100;

class Render
{
public:
    Render();

    void draw_menu();
    void draw_game_over(const GameMaster &state);
    void draw_board(const GameMaster &state);
};

#endif // RENDER_H
