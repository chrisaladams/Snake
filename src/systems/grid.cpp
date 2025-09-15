#include "systems/grid.h"
#include <algorithm>

// Grid constructor implementation with grid layout calculations.
grid::grid(const int screenWidth, const int screenHeight, const int cols, const int rows)
{
    width = cols;

    // Make the playable grid span the entire screen width
    cellSize = screenWidth / width;
    if (cellSize <= 0) cellSize = 1; // safety

    // Derive rows to fit the window height using this cell size
    height = screenHeight / cellSize;
    if (height <= 0) height = 1;

    usedWidth = width * cellSize;   // equals screenWidth
    usedHeight = height * cellSize; // <= screenHeight; for 800x800 and 25x25 it's exact

    // Anchor grid to the top-left (no padding), so window border == grid border
    offset.x = 0.0f;
    offset.y = 0.0f;
}