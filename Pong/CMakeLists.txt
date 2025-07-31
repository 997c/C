cmake_minimum_required(VERSION 3.10)
project(PongGame)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(PongGame
    main.c
    game.c
    game.h
    paddle.c
    paddle.h
    ball.c
    ball.h
)

target_link_libraries(PongGame ${SDL2_LIBRARIES})