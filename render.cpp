#include "render.hpp"
#include "graphics.hpp"

using namespace genv;

Render::Render() : Widget(0, 0, XX, YY), mouse_x(0), mouse_y(0) {
    genv::gout.open(XX, YY);
}

void Render::handle_event(const genv::event& ev) {
    if (ev.type == genv::ev_mouse) {
        mouse_x = ev.pos_x;
        mouse_y = ev.pos_y;
    }
}

void Render::draw_menu() {
    gout << move_to(0,0) << color(0,0,0) << box(XX,YY);
    for (int y = 0; y < YY; ++y) {

        int r = 0 + (255 * y) / YY;
        int g = 0 + (255 * y) / YY;
        int b = 0 + (255 * y) / YY;

        gout << color(r, g, b);
        gout << move_to(0, y) << line(XX, y);
    }

    gout << move_to(XX / 2 - 65, 75) << color(255, 255, 255) << text("Connect Four!");
    gout << move_to(XX / 2 - 80, YY / 2 - 80) << color(255, 50, 255) << text("Choose a gamemode!");

    if (mouse_x >= XX / 2 - 75 && mouse_x <= XX / 2 + 60 && mouse_y >= YY / 2 - 20 && mouse_y <= YY / 2) {
        gout << move_to(XX / 2 - 75, YY / 2) << color(0, 255, 0) << text("Player vs. Player");
    } else {
        gout << move_to(XX / 2 - 75, YY / 2) << color(255, 255, 255) << text("Player vs. Player");
    }

    if (mouse_x >= XX / 2 - 65 && mouse_x <= XX / 2 + 60 && mouse_y >= YY / 2 + 20 && mouse_y <= YY / 2 + 40) {
        gout << move_to(XX / 2 - 62, YY / 2 + 40) << color(0, 255, 0) << text("Player vs. AI");
    } else {
        gout << move_to(XX / 2 - 62, YY / 2 + 40) << color(255, 255, 255) << text("Player vs. AI");
    }

    gout << refresh;
}


void Render::draw_game_over(const GameMaster &state) {
    for (int y = 0; y < YY; ++y) {
        int red = 255;
        int green = 0 + (255 * y) / YY;
        int blue = 0;

        gout << color(red, green, blue);
        gout << move_to(0, y) << line(XX, y);
    }
    gout << color(50, 50, 50) << move_to(XX / 2 - 65, YY / 2 - 55) << box(123, 20);
    if (state.draw) {
        gout << move_to(XX/2-20, YY/ 2 - 40) << color(255,255,255) << text("Draw!");
    } else if (state.winner == RED) {
        gout << move_to(XX/2-45, YY/ 2 - 40) << color(255,255,255) << text("Red Wins!");
    } else if (state.winner == YELLOW) {
        gout << move_to(XX/2-45, YY/ 2 - 40) << color(255,255,255) << text("Yellow Wins!");
    }
    gout << color(50, 50, 50) << move_to(XX / 2 - 65, YY / 2 + 15) << box(123, 20);
    if (mouse_x >= XX / 2 - 65 && mouse_x <= XX / 2 + 60 && mouse_y >= YY / 2 + 20 && mouse_y <= YY / 2 + 40) {
    gout << color(255, 255, 0) << move_to(XX / 2 - 50, YY / 2 + 30) << text("Back to Menu");
    } else
    {
    gout << color(255, 255, 255) << move_to(XX / 2 - 50, YY / 2 + 30) << text("Back to Menu");
    }
    gout << refresh;
}


void Render::draw_board(const GameMaster &state) {
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
