//
// Created by Christian Adams on 9/2/25.
//
#include "Game.h"
#include "Food.h"
#include "raylib.h"

void init()
{
    // Initialize with a reasonable default
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60);
    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed

    //Set up the grid and its cells
    constexpr int GRID_WIDTH = 30;
    constexpr int GRID_HEIGHT = 30;
    constexpr int cellSize = std::min(screenWidth / GRID_WIDTH, screenHeight / GRID_HEIGHT);
    constexpr int usedWidth = GRID_WIDTH * cellSize; // 30 * cellSize
    constexpr int usedHeight = GRID_HEIGHT * cellSize;
    Vector2 offset;
    offset.x = (screenWidth - usedWidth) / 2;
    offset.y = (screenHeight - usedHeight) / 2;
}
//Take player arrow key input and prevent snake from turning into its own head in complete reversal.
void playerInput(Snake& player)
{
    if (IsKeyPressed(KEY_RIGHT) && player.direction.x != -1)
    {
        player.direction.x = 1;
        player.direction.y = 0;
    }else if (IsKeyPressed(KEY_LEFT) && player.direction.x != 1)
    {
        player.direction.x = -1;
        player.direction.y = 0;
    }else if (IsKeyPressed(KEY_DOWN) && player.direction.y != -1)
    {
        player.direction.y = 1;
        player.direction.x = 0;
    }else if (IsKeyPressed(KEY_UP) && player.direction.y != 1)
    {
        player.direction.y = -1;
        player.direction.x = 0;
    }
}

//movement is a head is place in front of the snake towards the direction its moving and a segment of the tail is removed
//if it eats skip removing a tail segment.
void snakeMovement(Snake& player)
{
    Vector2 newHead = player.body[0];
    newHead.x += player.direction.x;
    newHead.y += player.direction.y;
    player.body.insert(player.body.begin(), newHead);

    if (player.ateFood == false)
    {
        player.body.pop_back();
    } else
    {
        player.ateFood = false;
    }
}

void checkCollisions(Snake& player, Food& food, const int GRID_WIDTH, const int GRID_HEIGHT)
{

    bool snakeHead = true;
    if (player.body[0].x == food.getLocation().x && player.body[0].y == food.getLocation().y)
    {
        player.ateFood = true;
        food.spawnCheck(GRID_WIDTH, GRID_HEIGHT, player);
    }
    //Check if you hit the edge of the screen
    else if (player.body[0].x <= 0 || player.body[0].x >= GRID_WIDTH || player.body[0].y <= 0 || player.body[0].y >= GRID_HEIGHT)
    {
        //End game you hit the edge of the screen
    }
    for (Vector2& segment: player.body)
    {
        if (segment.x == player.body[0].x && segment.y == player.body[0].y)
        {
            if (snakeHead) { snakeHead = false; } //skip the snake head and check for collisions on the rest of the segments

            else
            {
                //End game you just hit a snake segment
            }
        }
    }
}