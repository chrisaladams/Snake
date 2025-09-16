cmake_minimum_required(VERSION 4.0)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(Snake src/main.cpp
        src/entities/Snake.cpp
        src/entities/Food.cpp
        src/systems/renderer.cpp
        src/services/high_scores.cpp
        src/game.cpp
        src/systems/animations.cpp
        src/systems/collisions.cpp
        src/systems/grid.cpp
        src/systems/playerInput.cpp
        include/systems/grid.h
)
target_include_directories(Snake PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link raylib and required macOS frameworks
target_link_libraries(Snake
        raylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)
