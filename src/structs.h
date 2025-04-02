#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} App;

#endif
