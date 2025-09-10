//
// Created by Christian Adams on 9/2/25.
//
#include "../include/renderer.h"

renderer::renderer()
: green{173,204,96,255}, darkGreen{43,51,24,255}{}
void renderer::draw(const int cellSize, const Vector2& offset, const Vector2& foodLocation,
                    const int snakeSegmentSize, const std::vector<Vector2>& snakeBody)
{
    drawFood(cellSize,offset,foodLocation);
    drawSnake(offset,snakeSegmentSize,snakeBody);
}

//Draw snake with offset for screen variations.
void renderer::drawSnake(const Vector2& offset, const int segmentSize, const std::vector<Vector2>& body) const
{
    for (const auto& segment: body)
    {
        DrawRectangle(segment.x * segmentSize + offset.x, segment.y * segmentSize + offset.y, segmentSize, segmentSize,darkGreen);
    }
}

void renderer::drawFood(const int cellSize, const Vector2 offset, const Vector2 location)
{
    //Draw food with offsets and reducing the radius to fit the cell.
    DrawCircle(location.x * cellSize + offset.x + cellSize / 2, location.y * cellSize + offset.y + cellSize / 2,
               cellSize / 2,GRAY);
}