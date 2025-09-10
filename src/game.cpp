//
// Created by Christian Adams on 9/2/25.
//
#include "../include/game.h"
#include "../include/food.h"
#include "raylib.h"


//Set Game Window
game::game(int screenHeight,int screenWidth) : player(cellSize),
                                            gameFood(cellSize),
                                            cellSize(std::min(screenWidth / GRID_WIDTH,
                                                              screenHeight / GRID_HEIGHT)),
                                            usedHeight(GRID_HEIGHT * cellSize),usedWidth(GRID_WIDTH * cellSize)
{

    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60);
    offset.x = (screenWidth - usedWidth) / 2;
    offset.y = (screenHeight - usedHeight) / 2;
}

void game::run()
{
    while (!WindowShouldClose())
    {
        //Update
        frameCount++;
        playerInput();

        BeginDrawing();
        ClearBackground(green);

        //Collisions
        checkCollisions();

        //Draw
        renderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);

        EndDrawing();
    }
}