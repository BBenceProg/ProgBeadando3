#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <vector>

enum Player { NONE, RED, YELLOW, DRAW };

class Render;

class GameMaster
{
public:
    std::vector<std::vector<Player>> board;
    Player current_player;
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
    void ai_move();

private:
    bool can_win_next_move(const GameMaster &state, Player player, int &col);
    bool can_block_opponent(const GameMaster &state, Player player, int &col);
};

#endif // GAMEMASTER_HPP
