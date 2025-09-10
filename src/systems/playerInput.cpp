//
// Created by Christian Adams on 9/9/25.
//
#include "game.h"
//Take player arrow key input and prevent snake from turning into its own head in complete reversal.
void game::playerInput()
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