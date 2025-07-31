#include "ball.h"

void Ball_init(Ball* ball, int x, int y) {
    ball->x = x;
    ball->y = y;
    ball->width = 20;
    ball->height = 20;
    ball->speedX = 5;
    ball->speedY = 5;
}

void Ball_update(Ball* ball) {
    ball->x += ball->speedX;
    ball->y += ball->speedY;
    if (ball->y < 0 || ball->y + ball->height > 600) {
        ball->speedY = -ball->speedY;
    }
}

void Ball_render(Ball* ball, SDL_Renderer* renderer) {
    SDL_Rect rect = { ball->x, ball->y, ball->width, ball->height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball_bounce(Ball* ball) {
    ball->speedX = -ball->speedX;
}

void Ball_reset(Ball* ball) {
    ball->x = 400;
    ball->y = 300;
    ball->speedX = -ball->speedX;
}

int Ball_collidesWith(const Ball* ball, const Paddle* paddle) {
    return ball->x < paddle->x + paddle->width &&
           ball->x + ball->width > paddle->x &&
           ball->y < paddle->y + paddle->height &&
           ball->y + ball->height > paddle->y;
}

int Ball_getX(const Ball* ball) { return ball->x; }
int Ball_getY(const Ball* ball) { return ball->y; }