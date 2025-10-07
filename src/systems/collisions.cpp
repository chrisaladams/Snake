//
// Created by Christian Adams on 9/9/25.
//
#include "game.h"

namespace {
    constexpr int SCORE_PER_FOOD = 10;
    constexpr size_t SNAKE_HEAD_INDEX = 0;
}

void game::checkCollisions()
{

    bool snakeHead = true;
    //Check collision with food
    if (player.body[SNAKE_HEAD_INDEX].x == gameFood.getLocation().x && player.body[SNAKE_HEAD_INDEX].y == gameFood.getLocation().y)
    {
        player.ateFood = true;
        score += SCORE_PER_FOOD;
        gameFood.spawnCheck(gameGrid.width, gameGrid.height, player);
    }
    //Check collision with screen
    else if (player.body[SNAKE_HEAD_INDEX].x < 0 || player.body[SNAKE_HEAD_INDEX].x >= gameGrid.width || player.body[SNAKE_HEAD_INDEX].y < 0 || player.body[SNAKE_HEAD_INDEX].y >= gameGrid.height)
    {
        highscores.submit(playerName, score);
        highscores.save();
        state = GameState::GameOver;
        return;
    }
    //Check collision with body
    for (Vector2& segment: player.body)
    {
        if (segment.x == player.body[SNAKE_HEAD_INDEX].x && segment.y == player.body[SNAKE_HEAD_INDEX].y)
        {
            if (snakeHead) { snakeHead = false; } //skip the snake head and check for collisions on the rest of the segments

            else
            {
                highscores.submit(playerName, score);
                highscores.save();
                state = GameState::GameOver;
                return;
            }
        }
    }
}