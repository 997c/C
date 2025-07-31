// food.c
#include "food.h"
#include <time.h>

void Food_init(Food* food) {
    srand((unsigned int)time(NULL));
}

void Food_generate(Food* food, int width, int height, const Snake* snake) {
    int validPosition = 0;
    while (!validPosition) {
        food->x = rand() % width;
        food->y = rand() % height;
        
        // Check snake head collision
        if (food->x != snake->x || food->y != snake->y) {
            int onTail = 0;
            for (int i = 0; i < snake->tailCount; i++) {
                if (food->x == snake->tail[i].x && food->y == snake->tail[i].y) {
                    onTail = 1;
                    break;
                }
            }
            if (!onTail) {
                validPosition = 1;
            }
        }
    }
}

int Food_getX(const Food* food) {
    return food->x;
}

int Food_getY(const Food* food) {
    return food->y;
}