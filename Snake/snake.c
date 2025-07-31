// snake.c
#include "snake.h"
#include <stdlib.h>

void Snake_init(Snake* snake, int startX, int startY) {
    snake->x = startX;
    snake->y = startY;
    snake->dir = RIGHT;
    snake->tailLength = 0;
    snake->tailCapacity = 0;
    snake->tail = NULL;
}

void Snake_move(Snake* snake) {
    // Save current position for tail
    Segment prevHead = { snake->x, snake->y };

    // Move head
    switch (snake->dir) {
        case LEFT:  snake->x--; break;
        case RIGHT: snake->x++; break;
        case UP:    snake->y--; break;
        case DOWN:  snake->y++; break;
        default: break;
    }

    // Update tail
    if (snake->tailLength > 0) {
        // Resize tail array if needed
        if (snake->tailLength >= snake->tailCapacity) {
            int newCapacity = snake->tailCapacity == 0 ? 4 : snake->tailCapacity * 2;
            Segment* newTail = realloc(snake->tail, newCapacity * sizeof(Segment));
            if (!newTail) return;
            snake->tail = newTail;
            snake->tailCapacity = newCapacity;
        }

        // Add new segment at end
        snake->tail[snake->tailLength] = prevHead;
        snake->tailLength++;
    }
}

void Snake_grow(Snake* snake) {
    snake->tailLength++;
}

void Snake_setDirection(Snake* snake, Direction newDir) {
    // Prevent 180-degree turns
    if ((snake->dir == LEFT  && newDir != RIGHT) ||
        (snake->dir == RIGHT && newDir != LEFT) ||
        (snake->dir == UP    && newDir != DOWN) ||
        (snake->dir == DOWN  && newDir != UP)) {
        snake->dir = newDir;
    }
}

void Snake_cleanup(Snake* snake) {
    free(snake->tail);
}