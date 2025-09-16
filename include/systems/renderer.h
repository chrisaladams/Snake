//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H
#include <vector>
#include <string>
#include "raylib.h"

class renderer
{
public:
    renderer();

    void draw(int cellSize,const Vector2& offset,const Vector2& foodLocation,
                     int snakeSegmentSize, const std::vector<Vector2>& snakeBody) const;

    // UI drawing moved here (single renderer handles all rendering)
    static void drawBorder();
    static void drawMenu(const std::string& nameBuffer, int bestHighScore);
    static void drawHUD(int score, int bestHighScore);
    static void drawGameOver(int finalScore);

private:
    //Game colors
    Color green = {};
    Color darkGreen = {};
    static void drawFood(int foodSize, Vector2 offset, Vector2 location);
    void drawSnake(const Vector2& offset,int segmentSize, const std::vector<Vector2>& body) const;
};



#endif //SNAKE_RENDERER_H