// snake.h
#ifndef SNAKE_H
#define SNAKE_H

typedef enum { STOP = 0, LEFT, RIGHT, UP, DOWN } Direction;

typedef struct {
    int x, y;
} Segment;

typedef struct {
    int x, y;
    Direction dir;
    Segment* tail;
    int tailLength;
    int tailCapacity;
} Snake;

void Snake_init(Snake* snake, int startX, int startY);
void Snake_move(Snake* snake);
void Snake_grow(Snake* snake);
void Snake_setDirection(Snake* snake, Direction newDir);
void Snake_cleanup(Snake* snake);

#endif // SNAKE_H