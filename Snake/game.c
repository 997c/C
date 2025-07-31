// game.c
#include "game.h"
#include "food.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

void Game_init(Game* game) {
    game->width = 50;
    game->height = 25;
    game->score = 0;
    game->isRunning = 1;
    Snake_init(&game->snake, game->width / 2, game->height / 2);
    Food_init(&game->food);
    Food_generate(&game->food, game->width, game->height, &game->snake);
}

void Game_drawBorder(const Game* game) {
    for (int i = 0; i < game->width + 2; i++)
        printf("#");
    printf("\n");
}

void Game_drawScore(const Game* game) {
    printf("Score: %d\n", game->score);
}

void Game_draw(const Game* game) {
    system("cls");
    Game_drawBorder(game);

    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (j == 0) printf("#");

            // Draw snake head
            if (j == game->snake.x && i == game->snake.y) {
                printf("O");
            }
            // Draw food
            else if (j == game->food.x && i == game->food.y) {
                printf("F");
            }
            // Draw snake tail
            else {
                int isTail = 0;
                for (int k = 0; k < game->snake.tailLength; k++) {
                    if (game->snake.tail[k].x == j && game->snake.tail[k].y == i) {
                        printf("o");
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) printf(" ");
            }

            if (j == game->width - 1) printf("#");
        }
        printf("\n");
    }

    Game_drawBorder(game);
    Game_drawScore(game);
}

void Game_input(Game* game) {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': Snake_setDirection(&game->snake, LEFT); break;
            case 'd': Snake_setDirection(&game->snake, RIGHT); break;
            case 'w': Snake_setDirection(&game->snake, UP); break;
            case 's': Snake_setDirection(&game->snake, DOWN); break;
            case 'x': game->isRunning = 0; break;
        }
    }
}

void Game_logic(Game* game) {
    Snake_move(&game->snake);

    // Food collision
    if (game->snake.x == game->food.x && game->snake.y == game->food.y) {
        game->score += 10;
        Food_generate(&game->food, game->width, game->height, &game->snake);
        Snake_grow(&game->snake);
    }

    // Wall collision
    if (game->snake.x < 0 || game->snake.x >= game->width ||
        game->snake.y < 0 || game->snake.y >= game->height) {
        game->isRunning = 0;
    }

    // Tail collision
    for (int i = 0; i < game->snake.tailLength; i++) {
        if (game->snake.x == game->snake.tail[i].x && 
            game->snake.y == game->snake.tail[i].y) {
            game->isRunning = 0;
            break;
        }
    }
}

void Game_gameOver(Game* game) {
    system("cls");
    printf("Game Over!\n");
    printf("Final Score: %d\n", game->score);
}

void Game_run(Game* game) {
    while (game->isRunning) {
        Game_draw(game);
        Game_input(game);
        Game_logic(game);
        Sleep(100);
    }
    Game_gameOver(game);
}

void Game_cleanup(Game* game) {
    Snake_cleanup(&game->snake);
}