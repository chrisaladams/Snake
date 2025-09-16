//
// Created by Christian Adams on 9/2/25.
//
#include "../../include/systems/renderer.h"

renderer::renderer()
: green{173,204,96,255}, darkGreen{43,51,24,255}{}
void renderer::draw(const int cellSize, const Vector2& offset, const Vector2& foodLocation,
                    const int snakeSegmentSize, const std::vector<Vector2>& snakeBody) const
{
    drawFood(cellSize,offset,foodLocation);
    drawSnake(offset,snakeSegmentSize,snakeBody);
}

void renderer::drawBorder() {
    DrawRectangleLinesEx({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, 2, WHITE);
}

void renderer::drawMenu(const std::string& nameBuffer, const int bestHighScore) {
    const char* title = "SNAKE";
    DrawText(title, GetScreenWidth()/2 - MeasureText(title, 60)/2, GetScreenHeight()/3, 60, DARKGREEN);

    const char* prompt = "Enter your name and press Enter";
    DrawText(prompt, GetScreenWidth()/2 - MeasureText(prompt, 20)/2, GetScreenHeight()/2, 20, BLACK);

    const std::string showName = "> " + nameBuffer + ((static_cast<int>(GetTime()*2) % 2) ? "_" : "");
    DrawText(showName.c_str(), GetScreenWidth()/2 - MeasureText(showName.c_str(), 30)/2, GetScreenHeight()/2 + 40, 30, BLACK);

    const std::string hs = "Best: " + std::to_string(bestHighScore);
    DrawText(hs.c_str(), 10, 10, 20, WHITE);
}

void renderer::drawHUD(const int score, const int bestHighScore) {
    const std::string curScore = "Score: " + std::to_string(score);
    DrawText(curScore.c_str(), 10, 10, 20, WHITE);

    const std::string topScore = "Best: " + std::to_string(bestHighScore);
    int w = MeasureText(topScore.c_str(), 20);
    DrawText(topScore.c_str(), GetScreenWidth() - w - 10, 10, 20, WHITE);
}

void renderer::drawGameOver(const int finalScore) {
    const char* over = "GAME OVER";
    DrawText(over, GetScreenWidth()/2 - MeasureText(over, 60)/2, GetScreenHeight()/3, 60, RED);

    std::string s = "Final Score: " + std::to_string(finalScore);
    DrawText(s.c_str(), GetScreenWidth()/2 - MeasureText(s.c_str(), 30)/2, GetScreenHeight()/2, 30, BLACK);

    const char* retry = "Press Enter to play again, Esc for Menu";
    DrawText(retry, GetScreenWidth()/2 - MeasureText(retry, 20)/2, GetScreenHeight()/2 + 40, 20, DARKGRAY);
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
    DrawCircle(location.x * cellSize + offset.x + cellSize / 2, cellSize / 2,
               location.y * cellSize + offset.y + cellSize / 2,GRAY);
}