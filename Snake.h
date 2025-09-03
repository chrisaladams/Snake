//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include <vector>
#include "raylib.h"
class Snake
{
public:
    explicit Snake(int cellSize);
    Vector2 direction{};
    std::vector<Vector2> body;
    int segmentSize;
    bool ateFood;
};

#endif //SNAKE_SNAKE_H