#include <iostream>
#include "../include/game.h"

int main()
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 800;

    std::cout << "Starting the game" << std::endl;
    //Setup Starting Game Objects

    game game(WINDOW_WIDTH, WINDOW_HEIGHT);
    game.run();

    return 0;
}