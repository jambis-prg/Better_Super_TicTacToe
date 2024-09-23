#include "include/Game.hpp"

int main()
{
    std::srand(time(NULL));

    Game game;

    // Game loop
    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}