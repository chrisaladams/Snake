//
// Created by Christian Adams on 9/2/25.
//
#include "../include/game.h"
#include "../include/entities/food.h"
#include "raylib.h"


//Set Game Window
game::game(const int screenWidth, const int screenHeight)
        : cellSize(0),
          player(0), gameFood(0), gameGrid()
{
    // Initialize setup grid
    gameGrid = grid(screenWidth, screenHeight, 25, 25);
    cellSize = gameGrid.cellSize;
    offset = gameGrid.offset;

    //Setup game objects
    player = snake(cellSize);
    gameFood = food(cellSize);

    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60);
}

void game::run()
{
    while (!WindowShouldClose())
    {
        //Update
        frameCount++;
        playerInput();
        if (frameCount >= frameSpeed)
        {
            snakeAnimation();
            frameCount = 0;
        }

        BeginDrawing();
        ClearBackground(green);

        //Collisions
        checkCollisions();

        //Draw
        renderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);

        EndDrawing();
    }
}
