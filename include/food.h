//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H
#include <raylib.h>
#include "snake.h"

//Describe food
class food
{
public:
    [[nodiscard]] Vector2 getLocation() const {return location;}
    explicit food(int cellSize);

    //Check if it's safe to spawn food,
    void spawnCheck(int gridWidth, int gridHeight, const snake& player);

private:
    Vector2 location;
    int foodSize;
};


#endif //SNAKE_FOOD_H