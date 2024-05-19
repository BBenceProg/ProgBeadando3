#include "graphics.hpp"
#include "gamemaster.hpp"
#include "render.hpp"
using namespace genv;

GameMaster::GameMaster() :
    board(6, std::vector<Player>(7, NONE)), current_player(RED),
    game_over(false), highlighted_col(-1), level(0) {}

void GameMaster::reset() {
    board = std::vector<std::vector<Player>>(6, std::vector<Player>(7, NONE));
    current_player = RED;
    game_over = false;
    highlighted_col = -1;
    level = 1;
}

bool GameMaster::place_piece(GameMaster &state, int col) {
    if (state.game_over || col < 0 || col >= 7) return false;

    for (int row = 5; row >= 0; --row) {
        if (state.board[row][col] == NONE) {
            state.board[row][col] = state.current_player;
            return true;
        }
    }
    return false;
}

void GameMaster::switch_player(GameMaster &state) {
    state.current_player = (state.current_player == RED) ? YELLOW : RED;
}

Player GameMaster::check_winner(const GameMaster &state) {
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            Player player = state.board[row][col];
            if (player == NONE) continue;

            if (col + 3 < 7 &&
                player == state.board[row][col + 1] &&
                player == state.board[row][col + 2] &&
                player == state.board[row][col + 3])
                return player;

            if (row + 3 < 6 &&
                player == state.board[row + 1][col] &&
                player == state.board[row + 2][col] &&
                player == state.board[row + 3][col])
                return player;

            if (row + 3 < 6 && col + 3 < 7 &&
                player == state.board[row + 1][col + 1] &&
                player == state.board[row + 2][col + 2] &&
                player == state.board[row + 3][col + 3])
                return player;

            if (row - 3 >= 0 && col + 3 < 7 &&
                player == state.board[row - 1][col + 1] &&
                player == state.board[row - 2][col + 2] &&
                player == state.board[row - 3][col + 3])
                return player;
        }
    }

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (state.board[row][col] == NONE) {
                return NONE;
            }
        }
    }

    return DRAW;
}

void GameMaster::run(GameMaster &state, Render &renderer) {
    gin.timer(30);
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        if (state.level == 0) {
            if (ev.type == ev_mouse && ev.button == btn_left) {
                if (ev.pos_x >= XX/2 - 50 && ev.pos_x <= XX/2 + 50 &&
                    ev.pos_y >= YY/2 && ev.pos_y <= YY/2 + 20) {
                    state.reset();
                }
            }
            renderer.draw_menu();
        } else if (state.level == 1) {
            if (ev.type == ev_mouse) {
                int col = ev.pos_x / CELL_SIZE;
                if (col >= 0 && col < 7) {
                    state.highlighted_col = col;
                } else {
                    state.highlighted_col = -1;
                }

                if (ev.button == btn_left && !state.game_over) {
                    if (place_piece(state, col)) {
                        Player winner = check_winner(state);
                        if (winner != NONE) {
                            state.game_over = true;
                            state.level = 2;
                            state.draw = (winner == DRAW);
                        } else {
                            switch_player(state);
                        }
                    }
                }
            }
            renderer.draw_board(state);
        } else if (state.level == 2) {
            if (ev.type == ev_mouse && ev.button == btn_left) {
                if (ev.pos_x >= XX/2 - 50 && ev.pos_x <= XX/2 + 50 &&
                    ev.pos_y >= YY/2 + 30 && ev.pos_y <= YY/2 + 50) {
                    state.level = 0;
                }
            }
            renderer.draw_game_over(state);
        }
    }
}
