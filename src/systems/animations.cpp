//
// Created by Christian Adams on 9/9/25.
//
//movement is a head is place in front of the snake towards the direction its moving and a segment of the tail is removed
//if it eats skip removing a tail segment.
#include "game.h"
#include "raylib.h"
void game::snakeAnimation()
{
    // Compute next head first
    Vector2 newHead = player.body[0];
    newHead.x += player.direction.x;
    newHead.y += player.direction.y;

    // Pre-move bounds check to avoid drawing outside window for a frame
    if (newHead.x < 0 || newHead.x >= gameGrid.width || newHead.y < 0 || newHead.y >= gameGrid.height)
    {
        highscores.submit(playerName, score);
        highscores.save();
        state = GameState::GameOver;
        return;
    }

    // Apply movement
    player.body.insert(player.body.begin(), newHead);

    if (!player.ateFood)
    {
        player.body.pop_back();
    } else
    {
        player.ateFood = false;
    }
}