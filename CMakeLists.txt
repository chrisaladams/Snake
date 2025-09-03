cmake_minimum_required(VERSION 4.0)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(Snake main.cpp
        snake.cpp
        snake.h
        food.cpp
        food.h
        Renderer.cpp
        Renderer.h)


# Link raylib and required macOS frameworks
target_link_libraries(Snake
        raylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)
