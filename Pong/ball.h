#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "paddle.h"

typedef struct {
    int x, y;
    int width, height;
    int speedX, speedY;
} Ball;

void Ball_init(Ball* ball, int x, int y);
void Ball_update(Ball* ball);
void Ball_render(Ball* ball, SDL_Renderer* renderer);
void Ball_bounce(Ball* ball);
void Ball_reset(Ball* ball);
int Ball_collidesWith(const Ball* ball, const Paddle* paddle);
int Ball_getX(const Ball* ball);
int Ball_getY(const Ball* ball);

#endif // BALL_H