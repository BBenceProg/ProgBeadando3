#include "graphics.hpp"
#include "gamemaster.hpp"
#include "render.hpp"
#include <cstdlib>
#include <ctime>

using namespace genv;

GameMaster::GameMaster() :
    board(6, std::vector<Player>(7, NONE)), current_player(RED),
    game_over(false), highlighted_col(-1), level(0) {
    std::srand(std::time(0));
}

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

bool GameMaster::can_win_next_move(const GameMaster &state, Player player, int &col) {
    for (int c = 0; c < 7; ++c) {
        GameMaster copy = state;
        copy.current_player = player;
        if (copy.place_piece(copy, c) && copy.check_winner(copy) == player) {
            col = c;
            return true;
        }
    }
    return false;
}

bool GameMaster::can_block_opponent(const GameMaster &state, Player player, int &col) {
    Player opponent = (player == RED) ? YELLOW : RED;
    for (int c = 0; c < 7; ++c) {
        GameMaster copy = state;
        copy.current_player = opponent;
        if (copy.place_piece(copy, c) && copy.check_winner(copy) == opponent) {
            col = c;
            return true;
        }
    }
    return false;
}

void GameMaster::ai_move() {
    int col = -1;
    if (can_win_next_move(*this, YELLOW, col) || can_block_opponent(*this, YELLOW, col)) {
        place_piece(*this, col);
    } else {
        // Random lépést csinál ha nem tud nyerni/blokkolni
        do {
            col = std::rand() % 7;
        } while (!place_piece(*this, col));
    }
    switch_player(*this);
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
                } else if (ev.pos_x >= XX/2 - 50 && ev.pos_x <= XX/2 + 50 &&
                           ev.pos_y >= YY/2 + 40 && ev.pos_y <= YY/2 + 60) {
                    state.reset();
                    state.level = 3; //Ai szint
                }
            }
            renderer.draw_menu();
        } else if (state.level == 1 || state.level == 3) {
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
                            if (state.level == 3 && state.current_player == YELLOW && !state.game_over) {
                                ai_move();
                                winner = check_winner(state);
                                if (winner != NONE) {
                                    state.game_over = true;
                                    state.level = 2;
                                    state.draw = (winner == DRAW);
                                }
                            }
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
