//
// Created by Christian Adams on 9/2/25.
//
#include "../../include/entities/snake.h"
#include <vector>
#include "raylib.h"

namespace {
    constexpr int INITIAL_DIRECTION_X = 1;
    constexpr int INITIAL_DIRECTION_Y = 0;
    constexpr int START_HEAD_X = 15;
    constexpr int START_HEAD_Y = 15;
    constexpr int START_BODY1_X = 14;
    constexpr int START_BODY1_Y = 15;
    constexpr int START_BODY2_X = 13;
    constexpr int START_BODY2_Y = 15;
}

//Describe a snake
snake::snake(const int cellSize)
{
    direction = {INITIAL_DIRECTION_X, INITIAL_DIRECTION_Y};
    segmentSize=cellSize;
    ateFood = false;

    //Starting Position
    body.push_back({START_HEAD_X, START_HEAD_Y});
    body.push_back({START_BODY1_X, START_BODY1_Y});
    body.push_back({START_BODY2_X, START_BODY2_Y});
};

