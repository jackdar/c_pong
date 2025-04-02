#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL.h"
#include "SDL_ttf.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} App;

#endif
