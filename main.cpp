#include <iostream>
#include "raylib.h"
using namespace std;

//Game colors
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

//Describe a snake
class snake
{
public:
    Vector2 direction = {1, 0};
    vector<Vector2> body;
    int segmentSize;

    explicit snake(int cellSize)
    {
        segmentSize = cellSize;
    }
    //Draw snake with offset for screen variations.
    void draw(const int cellSize, int offSetX, int offSetY) const
    {
        for (auto i: body)
        {
            DrawRectangle(i.x * cellSize + offSetX, i.y * cellSize + offSetY, segmentSize, segmentSize, darkGreen);
        }
    }

    bool ateFood = false;
};

//Describe food
class food
{
public:
    Vector2 location;
    int foodSize;

    explicit food(int cellSize) : location()
    {
        foodSize = cellSize;
    }

    void draw(int cellSize, int offSetX, int offSetY) const
    {
        //Draw food with offsets and reducing the radius to fit the cell.
        DrawCircle(location.x * cellSize + offSetX + cellSize / 2, location.y * cellSize + offSetY + cellSize / 2,
                   foodSize / 2,GRAY);
    }

    //Check if it's safe to spawn food,
    void spawnCheck(int gridWidth, int gridHeight, const snake& player)
    {
        bool isSafe = false;
        while (!isSafe)
        {
            int randomX = rand() % gridWidth;
            int randomY = rand() % gridHeight;
            auto newLocation = Vector2(randomX, randomY);
            isSafe = true;
            for (const Vector2 &segment: player.body)
            {
                if (newLocation.x == segment.x && newLocation.y == segment.y)
                {
                    isSafe = false;
                    break; //Food Conflicts with snake!
                }
            }
            location = newLocation;
        }
    }
};


void playerInput(snake& player)
{
    if (IsKeyPressed(KEY_RIGHT) && player.direction.x != -1)
    {
        player.direction.x = 1;
        player.direction.y = 0;
    }else if (IsKeyPressed(KEY_LEFT) && player.direction.x != 1)
    {
        player.direction.x = -1;
        player.direction.y = 0;
    }else if (IsKeyPressed(KEY_DOWN) && player.direction.y != -1)
    {
        player.direction.y = 1;
        player.direction.x = 0;
    }else if (IsKeyPressed(KEY_UP) && player.direction.y != 1)
    {
        player.direction.y = -1;
        player.direction.x = 0;
    }
}

void snakeMovement(snake& player)
{
    Vector2 newHead = player.body[0];
    newHead.x += player.direction.x;
    newHead.y += player.direction.y;
    player.body.insert(player.body.begin(), newHead);

    if (player.ateFood == false)
    {
        player.body.pop_back();
    } else
    {
        player.ateFood = false;
    }
}

void checkCollisions(snake& player, food& food,int GRID_WIDTH, int GRID_HEIGHT)
{
    if (player.body[0].x == food.location.x && player.body[0].y == food.location.y)
    {
        player.ateFood = true;
        food.spawnCheck(GRID_WIDTH, GRID_HEIGHT, player);
    }
}

int main()
{
    // Start with a reasonable default
    int screenWidth = 800;
    int screenHeight = 600;
    cout << "Starting the game" << endl;
    cout << screenHeight << " " << screenWidth << endl;
    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60);

    //Set up the grid and its cells
    constexpr int GRID_WIDTH = 30;
    constexpr int GRID_HEIGHT = 30;
    const int cellSize = min(screenWidth / GRID_WIDTH, screenHeight / GRID_HEIGHT);
    const int usedWidth = GRID_WIDTH * cellSize; // 30 * cellSize
    int usedHeight = GRID_HEIGHT * cellSize;
    int offsetX = (screenWidth - usedWidth) / 2;
    int offsetY = (screenHeight - usedHeight) / 2;

    //Setup Starting Game Objects
    snake player(cellSize);
    player.body.push_back(Vector2(15, 15));
    player.body.push_back(Vector2(14, 15));
    player.body.push_back(Vector2(13, 15));
    food gameFood(cellSize);
    gameFood.spawnCheck(GRID_WIDTH, GRID_HEIGHT, player);

    //Game loop + speed
    int frameCount = 0;
    int frameSpeed = 10; //adjust for snake speed
    while (!WindowShouldClose())
    {
        //Update
        frameCount++;
        playerInput(player);

        BeginDrawing();
        ClearBackground(green);
        if (frameCount >= frameSpeed)
        {
            snakeMovement(player);
            frameCount = 0;
        }

        //Collisions
        checkCollisions(player,gameFood,GRID_WIDTH,GRID_HEIGHT);

        //Draw
        player.draw(cellSize, offsetX, offsetY);
        gameFood.draw(cellSize, offsetX, offsetY);

        EndDrawing();
    }
    return 0;
}
//KNOWN BUGS:

//2.No Wall or snake self collisions.