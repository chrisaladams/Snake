//
// Created by Christian Adams on 9/9/25.
//
//movement is a head is place in front of the snake towards the direction its moving and a segment of the tail is removed
//if it eats skip removing a tail segment.
#include "game.h"
#include "raylib.h"
void game::snakeAnimation()
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