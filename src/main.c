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

Ball b = {BALL_START_X, BALL_START_Y,    BALL_WIDTH, BALL_HEIGHT, 1,
          0.2,          BALL_START_SPEED};

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
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_is_running = FALSE;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = FALSE;
            }
        }
    }
    // Get current keyboard state
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    // Player 1 controls
    if (key_state[SDL_SCANCODE_W]) {
        p1.y -= ACTOR_MOVE_SPEED;
    }
    if (key_state[SDL_SCANCODE_S]) {
        p1.y += ACTOR_MOVE_SPEED;
    }

    // Player 2 controls
    if (key_state[SDL_SCANCODE_UP]) {
        p2.y -= ACTOR_MOVE_SPEED;
    }
    if (key_state[SDL_SCANCODE_DOWN]) {
        p2.y += ACTOR_MOVE_SPEED;
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

    // Handle paddle constraints
    if (p1.y < 0) {
        p1.y = 0;
    }
    if (p1.y + p1.height > WINDOW_HEIGHT) {
        p1.y = WINDOW_HEIGHT - p1.height;
    }

    if (p2.y < 0) {
        p2.y = 0;
    }
    if (p2.y + p2.height > WINDOW_HEIGHT) {
        p2.y = WINDOW_HEIGHT - p2.height;
    }

    // Begin moving towards player 1
    b.x += b.dx * b.speed;
    b.y += b.dy * b.speed;

    // Ball bounces off the top and bottom walls
    if (b.y <= 0 || b.y + b.height >= WINDOW_HEIGHT) {
        b.dy *= -1;
    }

    // Ball collides with player 1
    if (b.x <= p1.x + p1.width && b.y + b.height >= p1.y &&
        b.y <= p1.y + p1.height) {
        b.dx *= -1;
        b.speed += BALL_DELTA_SPEED;
    }

    // Ball collides with player 2
    if (b.x + b.width >= p2.x && b.y + b.height >= p2.y &&
        b.y <= p2.y + p2.height) {
        b.dx *= -1;
        b.speed += BALL_DELTA_SPEED;
    }

    // Handle out of bounds
    if (b.x < 0 || b.x > WINDOW_WIDTH) {
        srand(time(NULL));

        b.x = BALL_START_X;
        b.y = BALL_START_Y;
        b.dx = (b.x < 0) ? 1 : -1;
        b.dy = ((float)rand() / RAND_MAX) * 0.5;
    }
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
