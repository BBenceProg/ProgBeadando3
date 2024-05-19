#include "render.hpp"
#include "graphics.hpp"

using namespace genv;

Render::Render() : Widget(0, 0, XX, YY) // Initializing Widget with default position and size
{
    genv::gout.open(XX, YY);
}

void Render::draw_menu()
{
    gout << move_to(0, 0) << color(255, 0, 0) << box(XX, YY);
    gout << move_to(XX / 2 - 50, YY / 2) << color(255, 255, 255) << text("Start Game");
    gout << refresh;
}

void Render::draw_game_over(const GameMaster &state) {
    gout << move_to(0, 0) << color(255, 0, 255) << box(XX, YY);
    gout << move_to(XX / 2 - 50, YY / 2 - 100) << color(255, 255, 255);
    if (state.draw) {
        gout << text("Draw!");
    } else if (state.current_player == RED) {
        gout << text("Red Wins!");
    } else {
        gout << text("Yellow Wins!");
    }
    gout << color(50, 50, 50) << move_to(XX / 2 - 65, YY / 2 + 15) << box(123, 20)
         << color(255, 255, 255) << move_to(XX / 2 - 50, YY / 2 + 30) << text("Back to Menu");
    gout << refresh;
}

void Render::draw_board(const GameMaster &state)
{
    gout << move_to(0, 0) << color(0, 0, 255) << box(XX, YY);

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;
            if (col == state.highlighted_col) {
                gout << move_to(x + 10, y + 10) << color(100, 100, 255) << box(CELL_SIZE - 20, CELL_SIZE - 20);
            } else {
                gout << move_to(x + 10, y + 10) << color(255, 255, 255) << box(CELL_SIZE - 20, CELL_SIZE - 20);
            }

            if (state.board[row][col] == RED) {
                gout << move_to(x + 10, y + 10) << color(255, 0, 0) << box(CELL_SIZE - 20, CELL_SIZE - 20);
            } else if (state.board[row][col] == YELLOW) {
                gout << move_to(x + 10, y + 10) << color(255, 255, 0) << box(CELL_SIZE - 20, CELL_SIZE - 20);
            }
        }
    }

    gout << refresh;
}
