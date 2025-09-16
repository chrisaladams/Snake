# Snake

A small Snake game in C++20 using raylib.

- Build system: CMake
- Target: Snake (executable)
- Entry: src/main.cpp

Requirements
- C++20 compiler, CMake, and raylib installed (on macOS via Homebrew: `brew install raylib`).

Build and Run (CLion Debug profile)
- Build target: Snake
- Run target: Snake

Controls
- Arrow keys: move
- Enter: start/restart
- Esc: back to menu

Notes
- High scores are saved to highscores.json (top 10).
- Renderer draws both the world and UI. Input is handled in playerInput().
