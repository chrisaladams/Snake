//
// Created by Christian Adams on 9/2/25.
//
#include "../../include/snake.h"
#include <vector>
#include "raylib.h"

//Describe a snake
snake::snake(const int cellSize)
{
    direction = {1, 0};
    segmentSize=cellSize;
    ateFood = false;

    //Starting Position
    body.push_back({15, 15});
    body.push_back({14, 15});
    body.push_back({13, 15});
};

