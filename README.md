# Snake (C++ + raylib)

A simple Snake game implemented in modern C++ (C++20) using the raylib graphics library. The goal of this project is to build a complete, polished game with a menu, sounds, and high‑score tracking.

## Overview
- Language: C++20
- Framework/Library: raylib (linked with native macOS frameworks in this setup)
- Build system: CMake
- Target: `Snake` (executable)
- Entry point: `src/main.cpp`

The game sets up an 800x600 window and runs the game loop via the `game` class (`include/game.h`, `src/game.cpp`). Systems include rendering, input handling, grid calculations, animations, and collision detection. Entities include the snake and food.

## Requirements
- C++20‑capable compiler (e.g., clang++)
- CMake (CMakeLists.txt uses minimum version 4.0 as specified)
- raylib installed and linkable on your system
  - The current CMake script includes and links raylib from Homebrew paths and macOS frameworks:
    - Include dir: `/opt/homebrew/include`
    - Lib dir: `/opt/homebrew/lib`
    - Frameworks: OpenGL, Cocoa, IOKit, CoreVideo


## Setup
1. Install raylib.
   - On macOS (Apple Silicon, Homebrew): `brew install raylib`
   - Ensure headers and libs are available under `/opt/homebrew/include` and `/opt/homebrew/lib` (or update CMake to your paths).
2. Clone this repository.
3. Configure a CMake build (CLion users can open the folder directly; the project already has a Debug profile configured).

## Build and Run

### Using CLion (recommended for this repo)
- Build target: `Snake`
- Run configuration: `Snake` (executable)

### Command line (generic CMake)
If building outside CLion, a typical flow is:

- Generate build files (if not already generated):
  - Example: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build and run:
  - `cmake --build build --target Snake`
  - On success, run the produced executable (path depends on your generator): `./build/Snake` or similar.

## How to Play
- Use the arrow keys to control the snake.
- Eat food to grow.
- Avoid running into yourself or the walls (collision resolution WIP; see TODOs).

## Project Structure
- `CMakeLists.txt` — CMake project definition and raylib linking
- `include/` — public headers
  - `entities/` — entity interfaces (snake, food)
  - `systems/` — systems interfaces (renderer, grid, ...)
  - `game.h` — main game class
- `src/` — implementations
  - `entities/` — snake and food logic
  - `systems/` — renderer, grid, collisions, animations, player input
  - `game.cpp` — game loop and orchestration
  - `main.cpp` — entry point

## Scripts
No repository scripts are defined at this time (no shell, Python, or package manager scripts). Build is handled via CMake.

## Environment Variables
None required at this time.

## Tests
No automated tests are included yet.
- TODO: Add unit tests (e.g., for grid calculations, collision detection, and input handling) and wire them into CTest.

## Known Issues / TODOs
The original README contained these items; preserving and expanding them here:
- TODO: Sounds
- Optional: Make the game resolution‑responsive (settings menu?)
- KNOWN BUGS: "You never know what you don't know..." (from `src/main.cpp` comments)

## Recent changes (2025-09-14)
Summary of fixes and features added during this session:

1) Added a simple game state machine (Menu, Playing, GameOver)
- Menu: enter player name, press Enter to start.
- Playing: normal gameplay; ESC returns to Menu without quitting.
- GameOver: Enter restarts, ESC returns to Menu.

2) Score and highscores
- Score increases by 10 per food.
- Highscores persist to highscores.json (name + score only). Kept top 10.
- Best score is shown in HUD and Menu.

3) Input and UX
- Disabled raylib default ESC-to-exit and handled ESC explicitly for menu navigation.

4) Visuals
- Playable grid now spans the entire window width and is anchored to the top-left.
- A white border is drawn around the actual window bounds to make edges explicit.

5) Edge-collision correctness (immediate death on touch)
- Movement now performs a pre-move bounds check: if the next head position would go outside the grid, the game switches to GameOver without inserting the head. This prevents any frame from rendering past the edge.
- After a pre-move GameOver, the frame skips further collision checks to avoid double-processing.

6) Window size
- Set the default window to 800x800 so a 25x25 grid fits exactly (cell size 32). This makes the grid edges coincide with the window edges on all sides.

Notes for learning
- See include/game.h for the GameState enum and related fields (score, name input, highscores).
- See src/game.cpp for the state-specific update/draw functions (updateMenu, updatePlaying, updateGameOver; drawMenu, drawHUD, drawGameOver) and highscore load/save.
- See src/systems/animations.cpp for the pre-move bounds check logic.
- See src/systems/grid.cpp for the full-width grid and top-left anchoring (and deriving rows from window height). 

## Platform Notes
- macOS/Homebrew paths are currently hardcoded in CMake (`/opt/homebrew`).
  - TODO: Make raylib discovery portable using `find_package(raylib CONFIG REQUIRED)` or a user‑configurable CMake option.
- TODO: Provide Linux and Windows build instructions and CI.

## License
No license file is present in this repository.
- TODO: Add a LICENSE file (e.g., MIT, Apache‑2.0, etc.) and update this section accordingly.

## Acknowledgements
- Built with [raylib](https://www.raylib.com/).
