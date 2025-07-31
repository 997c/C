// food.h
#ifndef FOOD_H
#define FOOD_H

#include "snake.h"
#include <stdlib.h>

typedef struct {
    int x, y;
} Food;

void Food_init(Food* food);
void Food_generate(Food* food, int width, int height, const Snake* snake);
int Food_getX(const Food* food);
int Food_getY(const Food* food);

#endif // FOOD_H