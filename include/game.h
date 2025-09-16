//
// Created by Christian Adams on 9/2/25.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "raylib.h"
#include "entities/snake.h"
#include "entities/food.h"
#include "systems/renderer.h"       // renderer handles all rendering
#include "systems/grid.h"
#include "services/high_scores.h"    // high score service
#include <string>

class game
{
    //Game color
    Color green = {173, 204, 96, 255};

    // STATES
    enum class GameState { Menu, Playing, GameOver };
    GameState state = GameState::Menu;

    int cellSize{};
    Vector2 offset{};
    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed
    //Set up Game objects
    snake player;
    food gameFood;
    renderer gameRenderer;
    grid gameGrid;
    HighScoreService highscores;

    // Game data
    int score = 0;

    // Name input
    std::string playerName;
    std::string nameInputBuffer;

    //Game systems
    void checkCollisions();
    void snakeAnimation();

    // Control helpers
    void resetRun();

    // Input handling (single place)
    void playerInput();

public:
    void run();
    game(int screenWidth,int screenHeight);

};


#endif //SNAKE_GAME_H