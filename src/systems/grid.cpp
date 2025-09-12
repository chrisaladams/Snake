#include "../../include/systems/grid.h"
#include <algorithm>

// Grid constructor implementation encapsulating layout calculations
grid::grid(const int screenWidth, const int screenHeight, const int cols, const int rows)
{
    width = cols;
    height = rows;

    cellSize = std::min(screenWidth / width, screenHeight / height);
    if (cellSize <= 0) cellSize = 1; // safety

    usedWidth = width * cellSize;
    usedHeight = height * cellSize;

    offset.x = (float)(screenWidth - usedWidth) / 2.0f;
    offset.y = (float)(screenHeight - usedHeight) / 2.0f;
}