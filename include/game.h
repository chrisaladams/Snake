//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "raylib.h"
#include "entities/snake.h"
#include "entities/food.h"
#include "systems/renderer.h"
#include "systems/grid.h"
#include <string>
#include <vector>
#include <utility>

class game
{
    //Game color
    Color green = {173, 204, 96, 255};

    // STATES
    enum class GameState { Menu, Playing, GameOver };
    GameState state = GameState::Menu;

    int cellSize;
    Vector2 offset{};
    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed
    //Set up Game objects
    snake player;
    food gameFood;
    renderer renderer;
    grid gameGrid;

    // Game data
    int score = 0;
    int bestHighScore = 0;

    // Name input
    std::string playerName;
    std::string nameInputBuffer;

    // Highscores: vector of (name, score)
    std::vector<std::pair<std::string,int>> highScores;

    //Game systems
    void playerInput();
    void checkCollisions();
    void snakeAnimation();

    // State update helpers
    void updateMenu();
    void updatePlaying();
    void updateGameOver();

    // Drawing helpers
    void drawMenu();
    void drawHUD();
    void drawGameOver();

    // Control helpers
    void resetRun();

    // Highscore persistence
    void loadHighScores(const char* path = "highscores.json");
    void saveHighScores(const char* path = "highscores.json");
    void considerSubmitHighScore();

public:
    void run();
    game(int screenWidth,int screenHeight);

};


#endif //SNAKE_GAME_H