//
// Created by Christian Adams on 9/2/25.
//
#include "../../include/systems/renderer.h"

namespace {
    // Color values
    constexpr unsigned char GREEN_R = 173;
    constexpr unsigned char GREEN_G = 204;
    constexpr unsigned char GREEN_B = 96;
    constexpr unsigned char GREEN_A = 255;
    constexpr unsigned char DARK_GREEN_R = 43;
    constexpr unsigned char DARK_GREEN_G = 51;
    constexpr unsigned char DARK_GREEN_B = 24;
    constexpr unsigned char DARK_GREEN_A = 255;
    
    // UI Layout constants
    constexpr float BORDER_THICKNESS = 2.0f;
    constexpr int TITLE_FONT_SIZE = 60;
    constexpr int SUBTITLE_FONT_SIZE = 30;
    constexpr int TEXT_FONT_SIZE = 20;
    constexpr int SCREEN_THIRD_DIVISOR = 3;
    constexpr int SCREEN_HALF_DIVISOR = 2;
    constexpr int UI_PADDING = 10;
    constexpr int TEXT_VERTICAL_OFFSET = 40;
    constexpr int CURSOR_BLINK_MULTIPLIER = 2;
}

renderer::renderer()
: green{GREEN_R, GREEN_G, GREEN_B, GREEN_A}, darkGreen{DARK_GREEN_R, DARK_GREEN_G, DARK_GREEN_B, DARK_GREEN_A}{}
void renderer::draw(const int cellSize, const Vector2& offset, const Vector2& foodLocation,
                    const int snakeSegmentSize, const std::vector<Vector2>& snakeBody) const
{
    drawFood(cellSize,offset,foodLocation);
    drawSnake(offset,snakeSegmentSize,snakeBody);
}

void renderer::drawBorder() {
    DrawRectangleLinesEx({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, BORDER_THICKNESS, WHITE);
}

void renderer::drawMenu(const std::string& nameBuffer, const int bestHighScore) {
    const char* title = "SNAKE";
    DrawText(title, GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(title, TITLE_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_THIRD_DIVISOR, TITLE_FONT_SIZE, DARKGREEN);

    const char* prompt = "Enter your name and press Enter";
    DrawText(prompt, GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(prompt, TEXT_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_HALF_DIVISOR, TEXT_FONT_SIZE, BLACK);

    const std::string showName = "> " + nameBuffer + ((static_cast<int>(GetTime()*CURSOR_BLINK_MULTIPLIER) % SCREEN_HALF_DIVISOR) ? "_" : "");
    DrawText(showName.c_str(), GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(showName.c_str(), SUBTITLE_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_HALF_DIVISOR + TEXT_VERTICAL_OFFSET, SUBTITLE_FONT_SIZE, BLACK);

    const std::string hs = "Best: " + std::to_string(bestHighScore);
    DrawText(hs.c_str(), UI_PADDING, UI_PADDING, TEXT_FONT_SIZE, WHITE);
}

void renderer::drawHUD(const int score, const int bestHighScore) {
    const std::string curScore = "Score: " + std::to_string(score);
    DrawText(curScore.c_str(), UI_PADDING, UI_PADDING, TEXT_FONT_SIZE, WHITE);

    const std::string topScore = "Best: " + std::to_string(bestHighScore);
    int w = MeasureText(topScore.c_str(), TEXT_FONT_SIZE);
    DrawText(topScore.c_str(), GetScreenWidth() - w - UI_PADDING, UI_PADDING, TEXT_FONT_SIZE, WHITE);
}

void renderer::drawGameOver(const int finalScore) {
    const char* over = "GAME OVER";
    DrawText(over, GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(over, TITLE_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_THIRD_DIVISOR, TITLE_FONT_SIZE, RED);

    std::string s = "Final Score: " + std::to_string(finalScore);
    DrawText(s.c_str(), GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(s.c_str(), SUBTITLE_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_HALF_DIVISOR, SUBTITLE_FONT_SIZE, BLACK);

    const char* retry = "Press Enter to play again, Esc for Menu";
    DrawText(retry, GetScreenWidth()/SCREEN_HALF_DIVISOR - MeasureText(retry, TEXT_FONT_SIZE)/SCREEN_HALF_DIVISOR, GetScreenHeight()/SCREEN_HALF_DIVISOR + TEXT_VERTICAL_OFFSET, TEXT_FONT_SIZE, DARKGRAY);
}

//Draw snake with offset for screen variations.
void renderer::drawSnake(const Vector2& offset, const int segmentSize, const std::vector<Vector2>& body) const
{
    for (const auto& segment: body)
    {
        DrawRectangle(segment.x * segmentSize + offset.x, segment.y * segmentSize + offset.y, segmentSize, segmentSize,darkGreen);
    }
}

void renderer::drawFood(const int cellSize, const Vector2 offset, const Vector2 location)
{
    //Draw food with offsets and reducing the radius to fit the cell.
    DrawCircle(location.x * cellSize + offset.x + cellSize / 2,
               location.y * cellSize + offset.y + cellSize / 2, cellSize / 2, GRAY);
}