//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "raylib.h"
#include "entities/snake.h"
#include "entities/food.h"
#include "systems/renderer.h"
#include "systems/grid.h"

class game
{
    //Game color
    Color green = {173, 204, 96, 255};


    int cellSize;
    Vector2 offset{};
    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed
    //Set up Game objects
    snake player;
    food gameFood;
    renderer renderer;
    grid gameGrid;
    //Game systems
    void playerInput();
    void checkCollisions();
    void snakeAnimation();

public:
    void run();
    game(int screenWidth,int screenHeight);

};


#endif //SNAKE_GAME_H