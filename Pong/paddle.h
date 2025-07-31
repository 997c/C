#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

typedef struct {
    int x, y;
    int width, height;
    int speed;
} Paddle;

void Paddle_init(Paddle* paddle, int x, int y);
void Paddle_moveUp(Paddle* paddle);
void Paddle_moveDown(Paddle* paddle);
void Paddle_moveTo(Paddle* paddle, int y);
void Paddle_render(Paddle* paddle, SDL_Renderer* renderer);
int Paddle_getX(const Paddle* paddle);
int Paddle_getY(const Paddle* paddle);
int Paddle_getWidth(const Paddle* paddle);
int Paddle_getHeight(const Paddle* paddle);

#endif // PADDLE_H