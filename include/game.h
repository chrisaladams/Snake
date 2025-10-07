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
    static constexpr unsigned char GREEN_R = 173;
    static constexpr unsigned char GREEN_G = 204;
    static constexpr unsigned char GREEN_B = 96;
    static constexpr unsigned char GREEN_A = 255;
    Color green = {GREEN_R, GREEN_G, GREEN_B, GREEN_A};

    // STATES
    enum class GameState { Menu, Playing, GameOver };
    GameState state = GameState::Menu;

    int cellSize{};
    Vector2 offset{};
    //Game loop + speed
    static constexpr int DEFAULT_FRAME_COUNT = 0;
    static constexpr int DEFAULT_FRAME_SPEED = 10; //adjust for snake speed
    int frameCount = DEFAULT_FRAME_COUNT;
    int frameSpeed = DEFAULT_FRAME_SPEED;
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