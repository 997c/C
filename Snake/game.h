// game.h
#ifndef GAME_H
#define GAME_H

#include <conio.h>
#include <windows.h>

typedef struct {
    int width, height;
    int score;
    int isRunning;
    Snake snake;
    Food food;
} Game;

void Game_init(Game* game);
void Game_run(Game* game);
void Game_cleanup(Game* game);

#endif // GAME_H