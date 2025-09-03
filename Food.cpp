//
// Created by Christian Adams on 9/2/25.
//
#include "Food.h"
#include <vector>
#include "raylib.h"
#include "Snake.h"

//Describe food
Food::Food(int cellSize)
{
    location = {18,18}; //Default start
    foodSize = cellSize;
}

    //Check if it's safe to spawn food,
    void Food::spawnCheck(int gridWidth, int gridHeight, const Snake& player)
    {
        bool isSafe = false;
        while (!isSafe)
        {
            int randomX = rand() % gridWidth;
            int randomY = rand() % gridHeight;
            auto newLocation = Vector2{(float) randomX, (float) randomY};
            isSafe = true;
            for (const Vector2& segment: player.body)
            {
                if (newLocation.x == segment.x && newLocation.y == segment.y)
                {
                    isSafe = false;
                    break; //Food Conflicts with snake!
                }
            }
            location = newLocation;
        }
    }

