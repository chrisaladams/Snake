//
// Created by Christian Adams on 9/9/25.
//
#include "game.h"
// Centralized input handling: menu typing, gameplay arrows, and game over controls
void game::playerInput()
{
    switch (state)
    {
        case GameState::Menu: {
            // Name typing
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && nameInputBuffer.size() < 16) {
                    nameInputBuffer.push_back(static_cast<char>(key));
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !nameInputBuffer.empty()) {
                nameInputBuffer.pop_back();
            }
            if (IsKeyPressed(KEY_ENTER) && !nameInputBuffer.empty()) {
                playerName = nameInputBuffer;
                resetRun();
                state = GameState::Playing;
            }
        } break;
        case GameState::Playing: {
            // Directional input; prevent immediate reversal
            if (IsKeyPressed(KEY_RIGHT) && player.direction.x != -1)
            {
                player.direction = {1, 0};
            } else if (IsKeyPressed(KEY_LEFT) && player.direction.x != 1)
            {
                player.direction = {-1, 0};
            } else if (IsKeyPressed(KEY_DOWN) && player.direction.y != -1)
            {
                player.direction = {0, 1};
            } else if (IsKeyPressed(KEY_UP) && player.direction.y != 1)
            {
                player.direction = {0, -1};
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                state = GameState::Menu;
            }
        } break;
        case GameState::GameOver: {
            if (IsKeyPressed(KEY_ENTER)) {
                resetRun();
                state = GameState::Playing;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                state = GameState::Menu;
            }
        } break;
    }
}