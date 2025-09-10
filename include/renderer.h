//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H
#include "raylib.h"
#include <vector>

class renderer
{
public:
    renderer();

    void draw(int cellSize,const Vector2& offset,const Vector2& foodLocation,
                     int snakeSegmentSize, const std::vector<Vector2>& snakeBody);
    private:
    //Game colors
    Color green = {};
    Color darkGreen = {};
    void drawFood(int foodSize, Vector2 offset, Vector2 location);
    void drawSnake(const Vector2& offset,int segmentSize, const std::vector<Vector2>& body) const;
};



#endif //SNAKE_RENDERER_H