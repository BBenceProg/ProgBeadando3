#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <vector>

enum Player { NONE, RED, YELLOW, DRAW };

class Render;

class GameMaster
{
public:
    std::vector<std::vector<Player>> board; // itt valamit kéne privatelni nem?
    Player current_player;                  // setter getter?
    bool game_over;
    int highlighted_col;
    int level;
    bool draw;

    GameMaster();

    void reset();
    void run(GameMaster &state, Render &renderer);
    bool place_piece(GameMaster &state, int col);
    Player check_winner(const GameMaster &state);
    void switch_player(GameMaster &state);
};

#endif // GAMEMASTER_H
