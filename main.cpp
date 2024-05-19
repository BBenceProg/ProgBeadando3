#include "gamemaster.hpp"
#include "render.hpp"

int main()
{
    GameMaster gamemaster;
    Render renderer;
    gamemaster.run(gamemaster,renderer);
}
