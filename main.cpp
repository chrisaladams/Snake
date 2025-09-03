#include <iostream>
#include "raylib.h"
#include "Snake.h"
#include "food.h"
#include "Renderer.h"

//Game colors
Color green = {173, 204, 96, 255};


int main()
{

    std::cout << "Starting the game" << std::endl;
    std::cout << screenHeight << " " << screenWidth << std::endl;
    //Setup Starting Game Objects
    Snake player(cellSize);
    Food gameFood(cellSize);
    Renderer renderer;

    gameFood.spawnCheck(GRID_WIDTH, GRID_HEIGHT, player);



    while (!WindowShouldClose())
    {
        //Update
        frameCount++;
        playerInput(player);

        BeginDrawing();
        ClearBackground(green);

        //Set speed for snake
        if (frameCount >= frameSpeed)
        {
            snakeMovement(player);
            frameCount = 0;
        }

        //Collisions
        checkCollisions(player,gameFood,GRID_WIDTH,GRID_HEIGHT);

        //Draw
        renderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);

        EndDrawing();
    }
    return 0;
}
//KNOWN BUGS:
//You never know what you don't know...
//TODO:
//1. Add resolution to snake collision logic
//2. Add menus: Start, name (use same color as snake)
//3. Track high scores
//4. Clean up main function its doing too much
//4. Polish graphics and fonts
//OPTIONAL:
//1. I don't know if I'll ever get to it but I'd love to make this game resolution responsive and learn that
//perhaps even a settings menu?