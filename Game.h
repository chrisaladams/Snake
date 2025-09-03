//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "Snake.h"

class Food;
class Game
{
    public:
    Game(int screenWidth,int screenHeight);
    void setup();
    void update();
    private:
    //Set up the grid and its cells
    static constexpr int GRID_WIDTH = 30;
    static constexpr int GRID_HEIGHT = 30;
    const int cellSize;
    const int usedWidth;
    int usedHeight;
    Vector2 offset;
    explicit Game(Snake& player);
    void playerInput(Snake& player);
    void checkCollisions(Snake& player, Food& food,int GRID_WIDTH, int GRID_HEIGHT);
    void snakeMovement(Snake& player);
};


#endif //SNAKE_GAME_H