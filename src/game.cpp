//
// Created by Christian Adams on 9/2/25.
//
#include "../include/game.h"
#include "raylib.h"

//Set Game Window
game::game(const int screenWidth, const int screenHeight)
        : cellSize(0),
          player(0), gameFood(0), gameGrid(), highscores("highscores.json")
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
    // Disable default ESC-to-exit so we can use ESC for menu navigation
    SetExitKey(KEY_NULL);

    // Load highscores
    highscores.load();

    // Start in Menu
    state = GameState::Menu;
    nameInputBuffer.clear();
}

void game::run()
{
    while (!WindowShouldClose())
    {
        // Update by state
        switch (state)
        {
            case GameState::Menu: {
                // Handle name typing and Enter to start inside playerInput
                playerInput();
            } break;
            case GameState::Playing: {
                frameCount++;
                // Handle direction and ESC inside playerInput
                playerInput();
                if (state != GameState::Playing) break; // may have changed to Menu
                if (frameCount >= frameSpeed)
                {
                    snakeAnimation();
                    frameCount = 0;
                    // If snakeAnimation triggered GameOver (pre-move bounds), skip further processing
                    if (state == GameState::GameOver) break;
                }
                // collisions update score/state
                checkCollisions();
            } break;
            case GameState::GameOver: {
                // Handle Enter to restart and Esc to go to Menu
                playerInput();
            } break;
        }

        // Draw by state
        BeginDrawing();
        ClearBackground(green);

        // Draw a white border around the window to show the true bounds
        renderer::drawBorder();

        if (state == GameState::Menu)
        {
            gameRenderer.drawMenu(nameInputBuffer, highscores.best());
        }
        else if (state == GameState::Playing)
        {
            gameRenderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);
            renderer::drawHUD(score, highscores.best());
        }
        else if (state == GameState::GameOver)
        {
            gameRenderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);
            gameRenderer.drawHUD(score, highscores.best());
            gameRenderer.drawGameOver(score);
        }

        EndDrawing();
    }
}




void game::resetRun()
{
    player = snake(cellSize);
    score = 0;
    // respawn food safely
    gameFood.spawnCheck(gameGrid.width, gameGrid.height, player);
}




