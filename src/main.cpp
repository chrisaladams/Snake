#include <iostream>
#include "../include/game.h"

int main()
{

    std::cout << "Starting the game" << std::endl;
    //Setup Starting Game Objects

    game game(800,800);
    game.run();

    return 0;
}