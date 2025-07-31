#include "game.h"

void Game_init(Game* game) {
    game->running = 0;
    Paddle_init(&game->playerPaddle, 10, 150);
    Paddle_init(&game->aiPaddle, 770, 150);
    Ball_init(&game->ball, 400, 300);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        game->window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (!game->window) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
            if (!game->renderer) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                game->running = 1;
            }
        }
    }
}

void Game_destroy(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

static void handleEvents(Game* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = 0;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
        Paddle_moveUp(&game->playerPaddle);
    }
    if (state[SDL_SCANCODE_DOWN]) {
        Paddle_moveDown(&game->playerPaddle);
    }
}

static void update(Game* game) {
    Paddle_moveTo(&game->aiPaddle, game->ball.y);
    Ball_update(&game->ball);
    if (Ball_collidesWith(&game->ball, &game->playerPaddle) || 
        Ball_collidesWith(&game->ball, &game->aiPaddle)) {
        Ball_bounce(&game->ball);
    }
    if (game->ball.x < 0 || game->ball.x > 800) {
        Ball_reset(&game->ball);
    }
}

static void render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    Paddle_render(&game->playerPaddle, game->renderer);
    Paddle_render(&game->aiPaddle, game->renderer);
    Ball_render(&game->ball, game->renderer);

    SDL_RenderPresent(game->renderer);
}

void Game_run(Game* game) {
    while (game->running) {
        handleEvents(game);
        update(game);
        render(game);
        SDL_Delay(16); // ~60 FPS
    }
}