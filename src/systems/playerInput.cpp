//
// Created by Christian Adams on 9/9/25.
//
#include "game.h"

namespace {
    constexpr int MIN_PRINTABLE_CHAR = 32;
    constexpr int MAX_PRINTABLE_CHAR = 125;
    constexpr size_t MAX_NAME_LENGTH = 16;
    constexpr int DIR_RIGHT_X = 1;
    constexpr int DIR_RIGHT_Y = 0;
    constexpr int DIR_LEFT_X = -1;
    constexpr int DIR_LEFT_Y = 0;
    constexpr int DIR_DOWN_X = 0;
    constexpr int DIR_DOWN_Y = 1;
    constexpr int DIR_UP_X = 0;
    constexpr int DIR_UP_Y = -1;
}

// Centralized input handling: menu typing, gameplay arrows, and game over controls
void game::playerInput()
{
    switch (state)
    {
        case GameState::Menu: {
            // Name typing
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= MIN_PRINTABLE_CHAR) && (key <= MAX_PRINTABLE_CHAR) && nameInputBuffer.size() < MAX_NAME_LENGTH) {
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
            if (IsKeyPressed(KEY_RIGHT) && player.direction.x != DIR_LEFT_X)
            {
                player.direction = {DIR_RIGHT_X, DIR_RIGHT_Y};
            } else if (IsKeyPressed(KEY_LEFT) && player.direction.x != DIR_RIGHT_X)
            {
                player.direction = {DIR_LEFT_X, DIR_LEFT_Y};
            } else if (IsKeyPressed(KEY_DOWN) && player.direction.y != DIR_UP_Y)
            {
                player.direction = {DIR_DOWN_X, DIR_DOWN_Y};
            } else if (IsKeyPressed(KEY_UP) && player.direction.y != DIR_DOWN_Y)
            {
                player.direction = {DIR_UP_X, DIR_UP_Y};
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