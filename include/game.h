//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "snake.h"
#include "food.h"
#include "renderer.h"

class food;
class game
{
    public:
    game(int screenWidth,int screenHeight);
    private:
    snake player;
    food gameFood;
    renderer renderer;
    //Game colors
    Color green = {173, 204, 96, 255};
    //Set up the grid and its cells
    int cellSize = 30;
    int GRID_WIDTH = 30;
    int GRID_HEIGHT = 30;
    Vector2 offset;
    int usedHeight;
    int usedWidth;
    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed

    void playerInput();
    void checkCollisions();
    void snakeAnimation();
public:
    void run();

};


#endif //SNAKE_GAME_H