#include "actor.h"
#include "ball.h"
#include "defs.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int game_is_running = FALSE;
int last_frame_time = 0;

App app;

Actor p1 = {ACTOR_START_X, ACTOR_START_Y, ACTOR_WIDTH, ACTOR_HEIGHT};
Actor p2 = {WINDOW_WIDTH - ACTOR_START_X, ACTOR_START_Y, ACTOR_WIDTH,
            ACTOR_HEIGHT};

Ball b = {BALL_START_X, BALL_START_Y, BALL_WIDTH, BALL_HEIGHT};

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
        p1.y -= 10;
        break;
    case SDLK_s:
        p1.y += 10;
        break;
    case SDLK_UP:
        p2.y -= 10;
        break;
    case SDLK_DOWN:
        p2.y += 10;
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

    // Render the actors
    SDL_Rect p1_rect = {p1.x, p1.y, p1.width, p1.height};
    SDL_Rect p2_rect = {p2.x, p2.y, p2.width, p2.height};

    // Render the ball
    SDL_Rect b_rect = {b.x, b.y, b.width, b.height};

    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.renderer, &p1_rect);
    SDL_RenderFillRect(app.renderer, &p2_rect);
    SDL_RenderFillRect(app.renderer, &b_rect);

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
