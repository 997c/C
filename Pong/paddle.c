#include "paddle.h"

void Paddle_init(Paddle* paddle, int x, int y) {
    paddle->x = x;
    paddle->y = y;
    paddle->width = 20;
    paddle->height = 100;
    paddle->speed = 10;
}

void Paddle_moveUp(Paddle* paddle) {
    paddle->y = (paddle->y - paddle->speed < 0) ? 0 : paddle->y - paddle->speed;
}

void Paddle_moveDown(Paddle* paddle) {
    paddle->y = (paddle->y + paddle->speed + paddle->height > 600) ? 600 - paddle->height : paddle->y + paddle->speed;
}

void Paddle_moveTo(Paddle* paddle, int targetY) {
    if (targetY < paddle->y + paddle->height / 2) {
        Paddle_moveUp(paddle);
    } else if (targetY > paddle->y + paddle->height / 2) {
        Paddle_moveDown(paddle);
    }
}

void Paddle_render(Paddle* paddle, SDL_Renderer* renderer) {
    SDL_Rect rect = { paddle->x, paddle->y, paddle->width, paddle->height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int Paddle_getX(const Paddle* paddle) { return paddle->x; }
int Paddle_getY(const Paddle* paddle) { return paddle->y; }
int Paddle_getWidth(const Paddle* paddle) { return paddle->width; }
int Paddle_getHeight(const Paddle* paddle) { return paddle->height; }