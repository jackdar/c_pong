#ifndef STRUCT_ACTOR_H
#define STRUCT_ACTOR_H

#include "defs.h"
#include <SDL2/SDL.h>

typedef struct {
    float x;
    float y;
    float width;
    float height;
    float delta;
} Actor;

#endif
