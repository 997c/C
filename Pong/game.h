#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "paddle.h"
#include "ball.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;
    Paddle playerPaddle;
    Paddle aiPaddle;
    Ball ball;
} Game;

void Game_init(Game* game);
void Game_destroy(Game* game);
void Game_run(Game* game);

#endif // GAME_H