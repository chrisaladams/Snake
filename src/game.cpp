//
// Created by Christian Adams on 9/2/25.
//
#include "../include/game.h"
#include "../include/entities/food.h"
#include "raylib.h"
#include <algorithm>
#include <fstream>
#include <sstream>

//Set Game Window
game::game(const int screenWidth, const int screenHeight)
        : cellSize(0),
          player(0), gameFood(0), gameGrid()
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

    // Load highscores and compute best
    loadHighScores();
    bestHighScore = 0;
    for (auto &p : highScores) bestHighScore = std::max(bestHighScore, p.second);

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
            case GameState::Menu:
                updateMenu();
                break;
            case GameState::Playing:
                updatePlaying();
                break;
            case GameState::GameOver:
                updateGameOver();
                break;
        }

        // Draw by state
        BeginDrawing();
        ClearBackground(green);

        // Draw a white border around the window to show the true bounds
        DrawRectangleLinesEx({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, 2, WHITE);

        if (state == GameState::Menu)
        {
            drawMenu();
        }
        else if (state == GameState::Playing)
        {
            renderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);
            drawHUD();
        }
        else if (state == GameState::GameOver)
        {
            renderer.draw(cellSize,offset,gameFood.getLocation(),player.segmentSize,player.body);
            drawHUD();
            drawGameOver();
        }

        EndDrawing();
    }
}

// ---------- State updates ----------
void game::updateMenu()
{
    // Accept text input
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && nameInputBuffer.size() < 16)
            nameInputBuffer.push_back(static_cast<char>(key));
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && !nameInputBuffer.empty())
        nameInputBuffer.pop_back();

    // Press Enter to start
    if (IsKeyPressed(KEY_ENTER) && !nameInputBuffer.empty())
    {
        playerName = nameInputBuffer;
        resetRun();
        state = GameState::Playing;
    }
}

void game::updatePlaying()
{
    // Allow ESC to return to Menu without quitting the app
    if (IsKeyPressed(KEY_ESCAPE)) {
        state = GameState::Menu;
        return;
    }

    frameCount++;
    playerInput();
    if (frameCount >= frameSpeed)
    {
        snakeAnimation();
        frameCount = 0;
        // If snakeAnimation triggered GameOver (pre-move bounds), skip further processing
        if (state == GameState::GameOver) return;
    }
    // collisions update score/state
    checkCollisions();
}

void game::updateGameOver()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        resetRun();
        state = GameState::Playing;
        return;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        state = GameState::Menu;
        return;
    }
}

void game::resetRun()
{
    player = snake(cellSize);
    score = 0;
    // respawn food safely
    gameFood.spawnCheck(gameGrid.width, gameGrid.height, player);
}

// ---------- Drawing ----------
void game::drawMenu()
{
    const char* title = "SNAKE";
    DrawText(title, GetScreenWidth()/2 - MeasureText(title, 60)/2, GetScreenHeight()/3, 60, DARKGREEN);

    const char* prompt = "Enter your name and press Enter";
    DrawText(prompt, GetScreenWidth()/2 - MeasureText(prompt, 20)/2, GetScreenHeight()/2, 20, BLACK);

    std::string showName = "> " + nameInputBuffer + ((static_cast<int>(GetTime()*2) % 2) ? "_" : "");
    DrawText(showName.c_str(), GetScreenWidth()/2 - MeasureText(showName.c_str(), 30)/2, GetScreenHeight()/2 + 40, 30, BLACK);

    // Best summary
    std::string hs = "Best: " + std::to_string(bestHighScore);
    DrawText(hs.c_str(), 10, 10, 20, WHITE);
}

void game::drawHUD()
{
    std::string s = "Score: " + std::to_string(score);
    DrawText(s.c_str(), 10, 10, 20, WHITE);

    std::string b = "Best: " + std::to_string(bestHighScore);
    int w = MeasureText(b.c_str(), 20);
    DrawText(b.c_str(), GetScreenWidth() - w - 10, 10, 20, WHITE);
}

void game::drawGameOver()
{
    const char* over = "GAME OVER";
    DrawText(over, GetScreenWidth()/2 - MeasureText(over, 60)/2, GetScreenHeight()/3, 60, RED);

    std::string s = "Final Score: " + std::to_string(score);
    DrawText(s.c_str(), GetScreenWidth()/2 - MeasureText(s.c_str(), 30)/2, GetScreenHeight()/2, 30, BLACK);

    const char* retry = "Press Enter to play again, Esc for Menu";
    DrawText(retry, GetScreenWidth()/2 - MeasureText(retry, 20)/2, GetScreenHeight()/2 + 40, 20, DARKGRAY);
}

// ---------- Highscore persistence (naive JSON) ----------

void game::loadHighScores(const char* path)
{
    highScores.clear();
    std::ifstream f(path);
    if (!f.is_open()) return;
    std::stringstream buffer; buffer << f.rdbuf();
    std::string content = buffer.str();
    // Very small tolerant parser: look for occurrences of "name":"..." and "score":number inside
    size_t pos = 0;
    while (true)
    {
        size_t nameKey = content.find("\"name\"", pos);
        if (nameKey == std::string::npos) break;
        size_t colon = content.find(':', nameKey);
        size_t firstQuote = content.find('"', colon+1);
        size_t secondQuote = content.find('"', firstQuote+1);
        if (colon==std::string::npos || firstQuote==std::string::npos || secondQuote==std::string::npos) break;
        std::string name = content.substr(firstQuote+1, secondQuote-firstQuote-1);

        size_t scoreKey = content.find("\"score\"", secondQuote);
        if (scoreKey == std::string::npos) break;
        size_t colon2 = content.find(':', scoreKey);
        size_t endNum = content.find_first_of(",}\n\r\t ", colon2+1);
        std::string numStr = content.substr(colon2+1, (endNum==std::string::npos?content.size():endNum)-(colon2+1));
        int sc = 0;
        try { sc = std::stoi(numStr); } catch(...) { sc = 0; }

        if (!name.empty()) highScores.emplace_back(name, sc);
        pos = scoreKey + 7;
    }
}

void game::saveHighScores(const char* path)
{
    // Keep only top 10
    std::sort(highScores.begin(), highScores.end(), [](auto&a, auto&b){return a.second > b.second;});
    if (highScores.size() > 10) highScores.resize(10);

    std::ofstream f(path);
    if (!f.is_open()) return;
    f << "[\n";
    for (size_t i=0;i<highScores.size();++i)
    {
        f << "  {\"name\":\"" << highScores[i].first << "\", \"score\":" << highScores[i].second << "}";
        if (i+1<highScores.size()) f << ",";
        f << "\n";
    }
    f << "]\n";
}

void game::considerSubmitHighScore()
{
    if (!playerName.empty())
    {
        highScores.emplace_back(playerName, score);
        // Update best
        bestHighScore = 0;
        for (auto &p : highScores) bestHighScore = std::max(bestHighScore, p.second);
        saveHighScores();
    }
}
