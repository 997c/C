// main.c
#include "game.h"

int main() {
    Game game;
    Game_init(&game);
    Game_run(&game);
    Game_cleanup(&game);
    return 0;
}