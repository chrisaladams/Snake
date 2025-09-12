
//
// Created by Christian Adams on 9/11/25.
//
#ifndef SNAKE_GRID_H
#define SNAKE_GRID_H

#include "raylib.h"
struct grid
{
    int cellSize{};
    int width{};
    int height{};
    Vector2 offset{};
    int usedHeight{};
    int usedWidth{};

    // Construct and compute grid layout given screen size and desired grid dimensions
    grid() = default;
    grid(int screenWidth, int screenHeight, int cols, int rows);

    int gridToScreenX(const int gridX) const { return static_cast<int>(offset.x) + gridX * cellSize; }
    int gridToScreenY(const int gridY) const { return static_cast<int>(offset.y) + gridY * cellSize; }
};

#endif // SNAKE_GRID_H