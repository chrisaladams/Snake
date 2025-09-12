//
// Created by Christian Adams on 9/9/25.
//
#include "game.h"
void game::checkCollisions()
{

    bool snakeHead = true;
    //Check collision with food
    if (player.body[0].x == gameFood.getLocation().x && player.body[0].y == gameFood.getLocation().y)
    {
        player.ateFood = true;
        gameFood.spawnCheck(gameGrid.width, gameGrid.height, player);
    }
    //Check collision with screen
    else if (player.body[0].x < 0 || player.body[0].x >= gameGrid.width || player.body[0].y < 0 || player.body[0].y >= gameGrid.height)
    {
        //End game you hit the edge of the screen
    }
    //Check collision with body
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