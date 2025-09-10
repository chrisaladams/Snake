#include <iostream>
#include "raylib.h"
#include "../include/snake.h"
#include "../include/food.h"
#include "../include/renderer.h"
#include "../include/game.h"

int main()
{

    std::cout << "Starting the game" << std::endl;
    //Setup Starting Game Objects

    game game(800,600);
    game.run();

    return 0;
}
//KNOWN BUGS:
//You never know what you don't know...
//To be Done
//1. Add resolution to snake collision logic
//2. Add menus: Start, name (use same color as snake)
//3. Track high scores
//4. Clean up main function its doing too much
//4. Polish graphics and fonts
//OPTIONAL:
//1. I don't know if I'll ever get to it but I'd love to make this game resolution responsive and learn that
//perhaps even a settings menu?