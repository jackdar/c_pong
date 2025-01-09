#include "actor.h"
#include "defs.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int game_is_running = FALSE;
int last_frame_time = 0;

App app;

Actor a1 = {ACTOR_START_X, ACTOR_START_Y, ACTOR_WIDTH, ACTOR_HEIGHT};
Actor a2 = {WINDOW_WIDTH - ACTOR_START_X, ACTOR_START_Y, ACTOR_WIDTH,
            ACTOR_HEIGHT};

int initialise_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initialising SDL.\n");
        return FALSE;
    }

    app.window =
        SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_METAL);
    if (!app.window) {
        fprintf(stderr, "Error creating SDL app.window.\n");
        return FALSE;
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
    if (!app.renderer) {
        fprintf(stderr, "Error creating SDL app.renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        game_is_running = FALSE;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            game_is_running = FALSE;
        break;
    }

    // Player input
    switch (event.key.keysym.sym) {
    case SDLK_w:
        a1.x -= 10;
        break;
    case SDLK_s:
        a1.x += 10;
        break;
    case SDLK_UP:
        a2.x -= 10;
        break;
    case SDLK_DOWN:
        a2.x += 10;
    }
}

void setup() {}

void update() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    /* float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0; */

    last_frame_time = SDL_GetTicks();
}

void render() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

    // TODO: Render the actors
    SDL_Rect a1_rect = {a1.x, a1.y, a1.width, a1.height};
    SDL_Rect a2_rect = {a2.x, a2.y, a2.width, a2.height};

    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.renderer, &a1_rect);
    SDL_RenderFillRect(app.renderer, &a2_rect);

    SDL_RenderPresent(app.renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

int main() {
    game_is_running = initialise_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
